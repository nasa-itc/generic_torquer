/************************************************************************
** File:
**   $Id: generic_torquer_msgids.h  $
**
** Purpose:
**  Define GENERIC_TORQUER Message IDs
**
*************************************************************************/
#ifndef _GENERIC_TORQUER_MSGIDS_H_
#define _GENERIC_TORQUER_MSGIDS_H_

/* 
** CCSDS V1 Command Message IDs (MID) must be 0x18xx
*/
#define GENERIC_TORQUER_CMD_MID              0x18FA /* TODO: Change this for your app */ 

/* 
** This MID is for commands telling the app to publish its telemetry message
*/
#define GENERIC_TORQUER_REQ_HK_MID           0x18FB /* TODO: Change this for your app */

/* 
** CCSDS V1 Telemetry Message IDs must be 0x08xx
*/
#define GENERIC_TORQUER_HK_TLM_MID           0x08FA /* TODO: Change this for your app */
#define GENERIC_TORQUER_DEVICE_TLM_MID       0x08FB /* TODO: Change this for your app */

#endif /* _GENERIC_TORQUER_MSGIDS_H_ */
