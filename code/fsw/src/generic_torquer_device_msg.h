/*******************************************************************************
** File:
**  generic_torquer_device_msg.h
**
** Purpose:
**  Define Generic_torquer Device Messages and info
**
** Notes:
**
**
*******************************************************************************/
#ifndef _GENERIC_TORQUER_DEVICE_MSG_H_
#define _GENERIC_TORQUER_DEVICE_MSG_H_

#include "osapi.h" // for types used below
#include "cfe_sb.h" // for CFE_SB_TLM_HDR_SIZE

/*************************************************************************/
/*
** Type definition (GENERIC_TORQUER Device housekeeping)
*/

typedef struct
{
    uint8 CommandErrorCounter;
    uint8 GetDataCmdCounter;
    uint8 CfgCmdCounter;
    uint8 OtherCmdCounter;
    uint8 RawCmdCounter;
} OS_PACK GENERIC_TORQUER_DeviceCmdData_t;

typedef struct
{
    uint8 CfgRespCounter;
    uint8 OtherRespCounter;
    uint8 RawRespCounter;
    uint32 UnknownResponseCounter;
    uint32 DeviceGeneric_torquerDataCounter;
    uint32 MillisecondStreamDelay;
} OS_PACK GENERIC_TORQUER_DeviceRespHkData_t;

typedef struct
{
    GENERIC_TORQUER_DeviceCmdData_t    GENERIC_TORQUER_DeviceCmdData;
    GENERIC_TORQUER_DeviceRespHkData_t GENERIC_TORQUER_DeviceRespHkData;
} OS_PACK GENERIC_TORQUER_DeviceHkTlm_Payload_t;

typedef struct
{
    uint8                        TlmHeader[CFE_SB_TLM_HDR_SIZE];
    GENERIC_TORQUER_DeviceHkTlm_Payload_t Payload;

} OS_PACK GENERIC_TORQUER_DeviceHkTlm_t;

/*************************************************************************/
/*
** Type definition (GENERIC_TORQUER Device Data)
*/

typedef struct
{
    uint32 Generic_torquerProcessedTimeSeconds;
    uint32 Generic_torquerProcessedTimeSubseconds;
    uint32 Generic_torquersSent;
    uint16 Generic_torquerDataX;
    uint16 Generic_torquerDataY;
    uint16 Generic_torquerDataZ;
} OS_PACK GENERIC_TORQUER_DeviceRespGeneric_torquerData_t;

typedef struct
{
    GENERIC_TORQUER_DeviceRespGeneric_torquerData_t GENERIC_TORQUER_DeviceRespGeneric_torquerData;
} OS_PACK GENERIC_TORQUER_Generic_torquerTlm_Payload_t;

typedef struct
{
    uint8                      TlmHeader[CFE_SB_TLM_HDR_SIZE];
    GENERIC_TORQUER_Generic_torquerTlm_Payload_t Payload;

} OS_PACK GENERIC_TORQUER_DeviceGeneric_torquerTlm_t;

#endif /* _GENERIC_TORQUER_DEVICE_MSG_H_ */

/************************/
/*  End of File Comment */
/************************/
