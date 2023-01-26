/*******************************************************************************
** File:
**  generic_torquer_device.h
**
** Purpose:
**   This file is the header file for the Generic_torquer device
**
**
*******************************************************************************/

#ifndef _GENERIC_TORQUER_DEVICE_H_
#define _GENERIC_TORQUER_DEVICE_H_

#include "generic_torquer_device_msg.h"

/*
 * Buffers to hold telemetry data prior to sending
 * Defined as a union to ensure proper alignment for a CFE_SB_Msg_t type
 */

typedef union
{
    CFE_SB_Msg_t         MsgHdr;
    GENERIC_TORQUER_DeviceHkTlm_t HkTlm;
} GENERIC_TORQUER_DeviceHkBuffer_t;

typedef union
{
    CFE_SB_Msg_t             MsgHdr;
    GENERIC_TORQUER_DeviceGeneric_torquerTlm_t Generic_torquerTlm;
} GENERIC_TORQUER_DeviceGeneric_torquerBuffer_t;

/*
** Run Status variable used in the main processing loop.  If the device is asynchronous, this Status
** variable is also used in the device child processing loop.
*/
extern uint32 RunStatus;

/****************************************************************************/
/*
** Function prototypes.
**
*/
int32 GENERIC_TORQUER_DeviceInit(void);
int32 GENERIC_TORQUER_DeviceShutdown(void);
void  GENERIC_TORQUER_DeviceResetCounters(void);

void  GENERIC_TORQUER_DeviceGetGeneric_torquerDataCommand(void);
void  GENERIC_TORQUER_DeviceConfigurationCommand(uint32_t millisecond_stream_delay);
void  GENERIC_TORQUER_DeviceOtherCommand(void);
void  GENERIC_TORQUER_DeviceRawCommand(const uint8 cmd[], const uint32_t cmd_length);

void GENERIC_TORQUER_ReportDeviceHousekeeping(void);
void GENERIC_TORQUER_ReportDeviceGeneric_torquerData(void);

#endif

/************************/
/*  End of File Comment */
/************************/
