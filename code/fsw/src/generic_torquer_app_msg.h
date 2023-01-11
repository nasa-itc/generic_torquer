/*******************************************************************************
** File:
**  generic_torquer_app_msg.h
**
** Purpose:
**  Define Generic_torquer App Messages and info
**
** Notes:
**
**
*******************************************************************************/
#ifndef _GENERIC_TORQUER_APP_MSG_H_
#define _GENERIC_TORQUER_APP_MSG_H_

#include "osapi.h" // for types used below
#include "cfe_sb.h" // for CFE_SB_CMD_HDR_SIZE, CFE_SB_TLM_HDR_SIZE


/*
** GENERIC_TORQUER App command codes
*/
#define GENERIC_TORQUER_APP_NOOP_CC            0
#define GENERIC_TORQUER_APP_RESET_COUNTERS_CC  1
#define GENERIC_TORQUER_GET_DEV_DATA_CC        2
#define GENERIC_TORQUER_CONFIG_CC              3
#define GENERIC_TORQUER_OTHER_CMD_CC           4
#define GENERIC_TORQUER_RAW_CMD_CC             5
#define GENERIC_TORQUER_APP_RESET_DEV_CNTRS_CC 6
#define GENERIC_TORQUER_SEND_DEV_HK_CC         7
#define GENERIC_TORQUER_SEND_DEV_DATA_CC       8

/*************************************************************************/

/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];

} GENERIC_TORQUER_NoArgsCmd_t;

/*
** The following commands all share the "NoArgs" format
**
** They are each given their own type name matching the command name, which_open_mode
** allows them to change independently in the future without changing the prototype
** of the handler function
*/
typedef GENERIC_TORQUER_NoArgsCmd_t GENERIC_TORQUER_Noop_t;
typedef GENERIC_TORQUER_NoArgsCmd_t GENERIC_TORQUER_ResetCounters_t;
typedef GENERIC_TORQUER_NoArgsCmd_t GENERIC_TORQUER_Process_t;

typedef GENERIC_TORQUER_NoArgsCmd_t GENERIC_TORQUER_GetDevData_cmd_t;
typedef GENERIC_TORQUER_NoArgsCmd_t GENERIC_TORQUER_Other_cmd_t;
typedef GENERIC_TORQUER_NoArgsCmd_t GENERIC_TORQUER_SendDevHk_cmd_t;
typedef GENERIC_TORQUER_NoArgsCmd_t GENERIC_TORQUER_SendDevData_cmd_t;

/*
** GENERIC_TORQUER write configuration command
*/
typedef struct
{
    uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint32   MillisecondStreamDelay;

} GENERIC_TORQUER_Config_cmd_t;

/*
** GENERIC_TORQUER raw command
*/
typedef struct
{
    uint8    CmdHeader[CFE_SB_CMD_HDR_SIZE];
    uint8    RawCmd[5];
} GENERIC_TORQUER_Raw_cmd_t;

/*************************************************************************/
/*
** Type definition (GENERIC_TORQUER App housekeeping)
*/

typedef struct
{
    uint8 CommandErrorCounter;
    uint8 CommandCounter;
} OS_PACK GENERIC_TORQUER_HkTlm_Payload_t;

typedef struct
{
    uint8                  TlmHeader[CFE_SB_TLM_HDR_SIZE];
    GENERIC_TORQUER_HkTlm_Payload_t Payload;

} OS_PACK GENERIC_TORQUER_HkTlm_t;

#endif /* _GENERIC_TORQUER_APP_MSG_H_ */

/************************/
/*  End of File Comment */
/************************/
