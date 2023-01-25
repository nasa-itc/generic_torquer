/*******************************************************************************
** File: 
**  generic_torquer_app.h
**
** Purpose:
**   This file is main header file for the Generic_torquer application.
**
*******************************************************************************/
#ifndef _GENERIC_TORQUER_APP_H_
#define _GENERIC_TORQUER_APP_H_

/*
** Required header files.
*/
#include "generic_torquer_app_msg.h"
#include "generic_torquer_app_events.h"
#include "generic_torquer_app_version.h"
#include "generic_torquer_app_platform_cfg.h"
#include "generic_torquer_app_perfids.h"
#include "generic_torquer_app_msgids.h"

#include "cfe_sb.h"
#include "cfe_evs.h"
#include "hwlib.h"


/***********************************************************************/
#define GENERIC_TORQUER_PIPE_DEPTH 32 /* Depth of the Command Pipe for Application */

/************************************************************************
** Type Definitions
*************************************************************************/
#define TRQ_DISABLED              0
#define TRQ_ENABLED               1

/*
 * Buffer to hold telemetry data prior to sending
 * Defined as a union to ensure proper alignment for a CFE_SB_Msg_t type
 */
typedef union
{
    CFE_SB_Msg_t   MsgHdr;
    GENERIC_TORQUER_HkTlm_t HkTlm;
} GENERIC_TORQUER_HkBuffer_t;

/*
** Global Data
*/
typedef struct
{
    /*
    ** Housekeeping telemetry packet...
    */
    GENERIC_TORQUER_HkBuffer_t HkBuf;

    /*
    ** Operational data (not reported in housekeeping)...
    */
    CFE_SB_PipeId_t CommandPipe;
    CFE_SB_MsgPtr_t MsgPtr;
    uint32 RunStatus;                   /* App run status for controlling the application state */
    uint32 MagTrqMutex;                 /* Mutex between trq and mag */


    /*
    ** Initialization data (not reported in housekeeping)...
    */
    char   PipeName[16];
    uint16 PipeDepth;

    CFE_EVS_BinFilter_t EventFilters[GENERIC_TORQUER_EVENT_COUNTS];

    /* 
    ** Device protocols
    */ 
    trq_info_t trqDevice[3];
    gpio_info_t trqEnable[3];


} GENERIC_TORQUER_AppData_t;

/****************************************************************************/
/*
** Function prototypes.
**
** Note: Except for the entry point (GENERIC_TORQUER_AppMain), these
**       functions are not called from any other source module.
*/
void  GENERIC_TORQUER_AppMain(void);

void  GENERIC_TORQUER_Enable_Disable(CFE_SB_MsgPtr_t msg);
void  GENERIC_TORQUER_Direction(CFE_SB_MsgPtr_t msg);
void  GENERIC_TORQUER_Time_High(CFE_SB_MsgPtr_t msg);
void  GENERIC_TORQUER_Percent_On(CFE_SB_MsgPtr_t msg);
void  GENERIC_TORQUER_3Axis_Pct_On(CFE_SB_MsgPtr_t msg);

#endif /* _generic_torquer_app_h_ */

/************************/
/*  End of File Comment */
/************************/
