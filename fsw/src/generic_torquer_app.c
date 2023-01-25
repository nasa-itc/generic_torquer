/*******************************************************************************
** File: 
**  generic_torquer_app.c
**
** Purpose:
**   This file contains the source code for the Generic_torquer App.
**
*******************************************************************************/

/*
** Include Files:
*/

//#include "string.h"
//#include "generic_torquer_app_events.h"

#include "generic_torquer_app.h"
#include "generic_torquer_app_version.h"
#include "generic_torquer_app_msgids.h"
#include "generic_torquer_app_perfids.h"
#include "generic_torquer_device.h"

#include "cfe_error.h"

/*
** global data
*/
GENERIC_TORQUER_AppData_t GENERIC_TORQUER_AppData;

// Forward declarations
static int32 GENERIC_TORQUER_AppInit(void);
static void  GENERIC_TORQUER_ProcessCommandPacket(CFE_SB_MsgPtr_t Msg);
static void  GENERIC_TORQUER_ProcessGroundCommand(CFE_SB_MsgPtr_t Msg);
static int32 GENERIC_TORQUER_ReportHousekeeping(const CFE_SB_CmdHdr_t *Msg);
static int32 GENERIC_TORQUER_ResetCounters(const GENERIC_TORQUER_ResetCounters_t *Msg);
static int32 GENERIC_TORQUER_Noop(const GENERIC_TORQUER_Noop_t *Msg);

static bool GENERIC_TORQUER_VerifyCmdLength(CFE_SB_MsgPtr_t Msg, uint16 ExpectedLength);

/*
** Global Data
*/
TRQ_AppData_t TRQ_AppData;

static CFE_EVS_BinFilter_t  TRQ_EventFilters[] =
{   /* Event ID    mask */
    {TRQ_RESERVED_EID,             0x0000},
    {TRQ_STARTUP_INF_EID,          0x0000},
    {TRQ_INVALID_MSGID_ERR_EID,    0x0000},
    {TRQ_LEN_ERR_EID,              0x0000},
    {TRQ_PIPE_ERR_EID,             0x0000},
    {TRQ_SUB_CMD_ERR_EID,          0x0000},
    {TRQ_SUB_REQ_HK_ERR_EID,       0x0000},
    {TRQ_SUB_REQ_DEVICE_ERR_EID,   0x0000},
    {TRQ_UART_ERR_EID,             0x0000},
    {TRQ_COMMAND_ERR_EID,          0x0000},
    {TRQ_COMMANDNOP_INF_EID,       0x0000},
    {TRQ_COMMANDRST_INF_EID,       0x0000},
    {TRQ_COMMANDENABLE_INF_EID,    0x0000},
    {TRQ_COMMANDDISABLE_INF_EID,   0x0000},
    {TRQ_COMMANDNUM_ERR_EID,       0x0000},
    {TRQ_COMMANDDIRECTION_INF_EID, 0x0000},
    {TRQ_COMMANDDIRECTION_ERR_EID, 0x0000},
    {TRQ_COMMANDHIGH_INF_EID,      0x0000},
    {TRQ_COMMANDHIGH_ERR_EID,      0x0000},
    {TRQ_COMMANDPERCENT_INF_EID,   0x0000},
    {TRQ_COMMANDPERCENT_ERR_EID,   0x0000},
    {TRQ_COMMANDENABLED_ERR_EID,   0x0000},
};


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/*                                                                            */
/* Name:  GENERIC_TORQUER_AppMain()                                           */
/* Purpose:                                                                   */
/*        Application entry point and main process loop                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void GENERIC_TORQUER_AppMain(void)
{
    int32 status = OS_SUCCESS;
    uint32 local_run = CFE_ES_APP_RUN;
    uint8_t i;


    /*
    ** Register the app with Executive services
    */
    CFE_ES_RegisterApp();

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(GENERIC_TORQUER_APP_PERF_ID);

    /*
    ** Perform application specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = GENERIC_TORQUER_AppInit();
    if (status != CFE_SUCCESS)
    {
        RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** GENERIC_TORQUER Runloop
    */
    while (CFE_ES_RunLoop(&RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(GENERIC_TORQUER_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status = CFE_SB_RcvMsg(&GENERIC_TORQUER_AppData.MsgPtr, GENERIC_TORQUER_AppData.CommandPipe, CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(GENERIC_TORQUER_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            GENERIC_TORQUER_ProcessCommandPacket(GENERIC_TORQUER_AppData.MsgPtr);
        }
        else
        {
            CFE_EVS_SendEvent(GENERIC_TORQUER_PIPE_ERR_EID, CFE_EVS_EventType_ERROR,
                              "GENERIC_TORQUER APP: SB Pipe Read Error, App Will Exit");

            RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    RunStatus = CFE_ES_RunStatus_APP_EXIT; // we are wanting to exit... make sure everyone knows it

    status = GENERIC_TORQUER_DeviceShutdown();
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Generic_torquer App: Error Shutting Down Device, RC = 0x%08lX\n", (unsigned long)status);
    }

    /*
    ** Close Devices
    */
    for(i = 0; i < 3; i++)
    {
        trq_close(&TRQ_AppData.trqDevice[i]);
        gpio_close(&TRQ_AppData.trqEnable[i]);
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(GENERIC_TORQUER_APP_PERF_ID);

    CFE_ES_ExitApp(RunStatus);

} /* End of GENERIC_TORQUER_AppMain() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* Name:  GENERIC_TORQUER_AppInit()                                                    */
/*                                                                            */
/* Purpose:                                                                   */
/*        Initialization                                                      */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static int32 GENERIC_TORQUER_AppInit(void)
{
    int32 status = OS_SUCCESS;
    uint8_t i;

    RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app command execution counters
    */
    GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandCounter = 0;
    GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter = 0;

    /*
    ** Initialize app configuration data
    */
    GENERIC_TORQUER_AppData.PipeDepth = GENERIC_TORQUER_PIPE_DEPTH;

    /*
    ** Initialize event filter table...
    */
    GENERIC_TORQUER_AppData.EventFilters[0].EventID = GENERIC_TORQUER_STARTUP_INF_EID;
    GENERIC_TORQUER_AppData.EventFilters[0].Mask    = 0x0000;
    GENERIC_TORQUER_AppData.EventFilters[1].EventID = GENERIC_TORQUER_COMMAND_ERR_EID;
    GENERIC_TORQUER_AppData.EventFilters[1].Mask    = 0x0000;
    GENERIC_TORQUER_AppData.EventFilters[2].EventID = GENERIC_TORQUER_COMMANDNOP_INF_EID;
    GENERIC_TORQUER_AppData.EventFilters[2].Mask    = 0x0000;
    GENERIC_TORQUER_AppData.EventFilters[3].EventID = GENERIC_TORQUER_COMMANDRST_INF_EID;
    GENERIC_TORQUER_AppData.EventFilters[3].Mask    = 0x0000;
    GENERIC_TORQUER_AppData.EventFilters[4].EventID = GENERIC_TORQUER_INVALID_MSGID_ERR_EID;
    GENERIC_TORQUER_AppData.EventFilters[4].Mask    = 0x0000;
    GENERIC_TORQUER_AppData.EventFilters[5].EventID = GENERIC_TORQUER_LEN_ERR_EID;
    GENERIC_TORQUER_AppData.EventFilters[5].Mask    = 0x0000;
    GENERIC_TORQUER_AppData.EventFilters[6].EventID = GENERIC_TORQUER_PIPE_ERR_EID;
    GENERIC_TORQUER_AppData.EventFilters[6].Mask    = 0x0000;

    /*
    ** Register the events
    */
    status = CFE_EVS_Register(GENERIC_TORQUER_AppData.EventFilters, GENERIC_TORQUER_EVENT_COUNTS, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Generic_torquer App: Error Registering Events, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Initialize housekeeping packet (clear user data area).
    */
    CFE_SB_InitMsg(&GENERIC_TORQUER_AppData.HkBuf.MsgHdr, GENERIC_TORQUER_APP_HK_TLM_MID, sizeof(GENERIC_TORQUER_AppData.HkBuf), true);

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&GENERIC_TORQUER_AppData.CommandPipe, GENERIC_TORQUER_AppData.PipeDepth, "GENERIC_TORQUER_CMD_PIPE");
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Generic_torquer App: Error creating pipe, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to Housekeeping request commands
    */
    status = CFE_SB_Subscribe(GENERIC_TORQUER_APP_SEND_HK_MID, GENERIC_TORQUER_AppData.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Generic_torquer App: Error Subscribing to HK request, RC = 0x%08lX\n", (unsigned long)status);
        return (status);
    }

    /*
    ** Subscribe to ground command packets
    */
    status = CFE_SB_Subscribe(GENERIC_TORQUER_APP_CMD_MID, GENERIC_TORQUER_AppData.CommandPipe);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Generic_torquer App: Error Subscribing to Command, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }

    status = GENERIC_TORQUER_DeviceInit();
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Generic_torquer App: Error Initializing Device, RC = 0x%08lX\n", (unsigned long)status);

        return (status);
    }

    
    /* ADDED SECTION */
    /*
    ** Initialize GENERIC_TORQUER interfaces
    */ 
    GENERIC_TORQUER_AppData.HkTelemetryPkt.TrqPeriod = TRQ_PERIOD;
    for(i = 0; i < 3; i++)
    {
        GENERIC_TORQUER_AppData.trqDevice[i].trq_num = i;
        GENERIC_TORQUER_AppData.trqDevice[i].timer_period_ns = TRQ_PERIOD;
        GENERIC_TORQUER_AppData.trqDevice[i].enabled = FALSE;

        status = trq_init(&GENERIC_TORQUER_AppData.trqDevice[i]);
        if (status != TRQ_SUCCESS)
        {
            CFE_EVS_SendEvent(GENERIC_TORQUER_INIT_TRQ_ERR_EID, CFE_EVS_ERROR, "GENERIC_TORQUER: device %d initialization error %d", i, status);
        }
    }

    /*
    ** Initialize GPIO interfaces
    */ 
    GENERIC_TORQUER_AppData.trqEnable[0].pin = TRQ1_ENABLE;
    GENERIC_TORQUER_AppData.trqEnable[0].direction = GPIO_OUTPUT;
    GENERIC_TORQUER_AppData.trqEnable[1].pin = TRQ2_ENABLE;
    GENERIC_TORQUER_AppData.trqEnable[1].direction = GPIO_OUTPUT;
    GENERIC_TORQUER_AppData.trqEnable[2].pin = TRQ3_ENABLE;
    GENERIC_TORQUER_AppData.trqEnable[2].direction = GPIO_OUTPUT;
    for(i = 0; i < 3; i++)
    {
        status = gpio_init(&GENERIC_TORQUER_AppData.trqEnable[i]);
        if(status != GPIO_SUCCESS)
        {
            CFE_EVS_SendEvent(GENERIC_TORQUER_INIT_GPIO_ERR_EID, CFE_EVS_ERROR, "GENERIC_TORQUER: device %d initialization error %d", i, status);
            return -1; 
        }

        status = gpio_write(&GENERIC_TORQUER_AppData.trqEnable[i], TRQ_DISABLED);
        if(status != GPIO_SUCCESS)
        {
            CFE_EVS_SendEvent(GENERIC_TORQUER_INIT_GPIO_ERR_EID, CFE_EVS_ERROR, "GENERIC_TORQUER: device %d set disabled error %d", i, status);
            return -1; 
        }
    }

    /*
    ** Create Mutex for Magnetometer and Torquer
    */
    status = OS_MutSemCreate(&GENERIC_TORQUER_AppData.MagTrqMutex, ADCS_MAG_TRQ_MUTEX, 0);
    if(status != OS_SUCCESS)
    {
        CFE_EVS_SendEvent(GENERIC_TORQUER_INIT_MUTEX_ERR_EID, CFE_EVS_ERROR, "GENERIC_TORQUER: Error creating Mag Trq Mutex %d", i, status);
        return status;
    }

    /* 
    ** Always reset all counters during application initialization 
    */
    GENERIC_TORQUER_ResetCounters();

    /* END ADDED SECTION */

    /* 
     ** Send an information event that the app has initialized. 
     ** This is useful for debugging the loading of individual applications.
     */
    status = CFE_EVS_SendEvent(GENERIC_TORQUER_STARTUP_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "GENERIC_TORQUER App Initialized. Version %d.%d.%d.%d",
                      GENERIC_TORQUER_APP_MAJOR_VERSION,
                      GENERIC_TORQUER_APP_MINOR_VERSION,
                      GENERIC_TORQUER_APP_REVISION,
                      GENERIC_TORQUER_APP_MISSION_REV);

    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("TRQ: error sending initialization event: 0x%08X\n", (unsigned int) status);
    }



    return (CFE_SUCCESS);

} /* End of GENERIC_TORQUER_AppInit() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  GENERIC_TORQUER_ProcessCommandPacket                                        */
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the GENERIC_TORQUER    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
static void GENERIC_TORQUER_ProcessCommandPacket(CFE_SB_MsgPtr_t Msg)
{
    CFE_SB_MsgId_t MsgId;

    MsgId = CFE_SB_GetMsgId(Msg);

    switch (MsgId)
    {
        case GENERIC_TORQUER_APP_CMD_MID:
            GENERIC_TORQUER_ProcessGroundCommand(Msg);
            break;

        case GENERIC_TORQUER_APP_SEND_HK_MID:
            GENERIC_TORQUER_ReportHousekeeping((CFE_SB_CmdHdr_t *)Msg);
            break;

        default:
            CFE_EVS_SendEvent(GENERIC_TORQUER_INVALID_MSGID_ERR_EID, CFE_EVS_EventType_ERROR,
                              "GENERIC_TORQUER: invalid command packet,MID = 0x%x", (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }

    return;

} /* End GENERIC_TORQUER_ProcessCommandPacket */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* Name:  GENERIC_TORQUER_ProcessGroundCommand()                                       */
/*                                                                            */
/* Purpose:                                                                   */
/*        GENERIC_TORQUER ground commands                                              */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static void GENERIC_TORQUER_ProcessGroundCommand(CFE_SB_MsgPtr_t Msg)
{
    uint16 CommandCode = CFE_SB_GetCmdCode(Msg);
    GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandCounter++;

    /*
    ** Process "known" GENERIC_TORQUER app ground commands
    */
    switch (CommandCode)
    {
        case GENERIC_TORQUER_APP_NOOP_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_Noop_t)))
            {
                GENERIC_TORQUER_Noop((GENERIC_TORQUER_Noop_t *)Msg);
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }

            break;

        case GENERIC_TORQUER_APP_RESET_COUNTERS_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_ResetCounters_t)))
            {
                GENERIC_TORQUER_ResetCounters((GENERIC_TORQUER_ResetCounters_t *)Msg);
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }

            break;

        /*
        ** TODO: Edit and add more command codes as appropriate for the application
        */
        case GENERIC_TORQUER_APP_RESET_DEV_CNTRS_CC:
            GENERIC_TORQUER_DeviceResetCounters();
            break;

        case GENERIC_TORQUER_GET_DEV_DATA_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_GetDevData_cmd_t))) {
                GENERIC_TORQUER_DeviceGetGeneric_torquerDataCommand();
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }
            break;

        case GENERIC_TORQUER_CONFIG_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_Config_cmd_t)))
            {
                GENERIC_TORQUER_DeviceConfigurationCommand(((GENERIC_TORQUER_Config_cmd_t *)Msg)->MillisecondStreamDelay);
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }
            break;

        case GENERIC_TORQUER_OTHER_CMD_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_Other_cmd_t)))
            {
                GENERIC_TORQUER_DeviceOtherCommand();
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }
            break;

        case GENERIC_TORQUER_RAW_CMD_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_Raw_cmd_t)))
            {
                GENERIC_TORQUER_DeviceRawCommand(((GENERIC_TORQUER_Raw_cmd_t *)Msg)->RawCmd, sizeof(((GENERIC_TORQUER_Raw_cmd_t *)Msg)->RawCmd));
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }
            break;

        case GENERIC_TORQUER_SEND_DEV_HK_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_SendDevHk_cmd_t))) {
                GENERIC_TORQUER_ReportDeviceHousekeeping();
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }
            break;

        case GENERIC_TORQUER_SEND_DEV_DATA_CC:
            if (GENERIC_TORQUER_VerifyCmdLength(Msg, sizeof(GENERIC_TORQUER_SendDevData_cmd_t))) {
                GENERIC_TORQUER_ReportDeviceGeneric_torquerData();
            } else {
                GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            }
            break;

        /* default case already found during FC vs length test */
        default:
            CFE_EVS_SendEvent(GENERIC_TORQUER_COMMAND_ERR_EID, CFE_EVS_EventType_ERROR, "Invalid ground command code: CC = %d",
                              CommandCode);
            GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
            break;
    }

    return;

} /* End of GENERIC_TORQUER_ProcessGroundCommand() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  GENERIC_TORQUER_ReportHousekeeping                                          */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
static int32 GENERIC_TORQUER_ReportHousekeeping(const CFE_SB_CmdHdr_t *Msg)
{
    GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandCounter++;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(&GENERIC_TORQUER_AppData.HkBuf.MsgHdr);
    CFE_SB_SendMsg(&GENERIC_TORQUER_AppData.HkBuf.MsgHdr);

    return CFE_SUCCESS;

} /* End of GENERIC_TORQUER_ReportHousekeeping() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* Name:  GENERIC_TORQUER_Noop                                                         */
/*                                                                            */
/* Purpose:                                                                   */
/*        GENERIC_TORQUER NOOP command                                                 */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static int32 GENERIC_TORQUER_Noop(const GENERIC_TORQUER_Noop_t *Msg)
{

    CFE_EVS_SendEvent(GENERIC_TORQUER_COMMANDNOP_INF_EID, CFE_EVS_EventType_INFORMATION, "GENERIC_TORQUER: NOOP command");

    return CFE_SUCCESS;

} /* End of GENERIC_TORQUER_Noop */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*  Name:  GENERIC_TORQUER_ResetCounters                                               */
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function resets all the global counter variables that are     */
/*         part of the task telemetry.                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
static int32 GENERIC_TORQUER_ResetCounters(const GENERIC_TORQUER_ResetCounters_t *Msg)
{

    GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandCounter = 0;
    GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter = 0;

    CFE_EVS_SendEvent(GENERIC_TORQUER_COMMANDRST_INF_EID, CFE_EVS_EventType_INFORMATION, "GENERIC_TORQUER: RESET command");

    return CFE_SUCCESS;

} /* End of GENERIC_TORQUER_ResetCounters() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* Name:  GENERIC_TORQUER_VerifyCmdLength()                                            */
/*                                                                            */
/* Purpose:                                                                   */
/*        Verify command packet length                                        */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
static bool GENERIC_TORQUER_VerifyCmdLength(CFE_SB_MsgPtr_t Msg, uint16 ExpectedLength)
{
    bool result = true;

    uint16 ActualLength = CFE_SB_GetTotalMsgLength(Msg);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_SB_MsgId_t MessageID   = CFE_SB_GetMsgId(Msg);
        uint16         CommandCode = CFE_SB_GetCmdCode(Msg);

        CFE_EVS_SendEvent(GENERIC_TORQUER_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Invalid Msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
                          (unsigned int)CFE_SB_MsgIdToValue(MessageID), CommandCode, ActualLength, ExpectedLength);

        result = false;

        GENERIC_TORQUER_AppData.HkBuf.HkTlm.Payload.CommandErrorCounter++;
    }

    return (result);

} /* End of GENERIC_TORQUER_VerifyCmdLength() */
