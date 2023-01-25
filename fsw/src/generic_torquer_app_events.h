/************************************************************************
** File:
**  generic_torquer_app_events.h
**
** Purpose:
**  Define Generic_torquer App Event IDs
**
** Notes:
**
*************************************************************************/
#ifndef _GENERIC_TORQUER_APP_EVENTS_H_
#define _GENERIC_TORQUER_APP_EVENTS_H_

#define GENERIC_TORQUER_RESERVED_EID           0
#define GENERIC_TORQUER_STARTUP_INF_EID        1
#define GENERIC_TORQUER_COMMAND_ERR_EID        2
#define GENERIC_TORQUER_COMMANDNOP_INF_EID     3
#define GENERIC_TORQUER_COMMANDRST_INF_EID     4
#define GENERIC_TORQUER_INVALID_MSGID_ERR_EID  5
#define GENERIC_TORQUER_LEN_ERR_EID            6
#define GENERIC_TORQUER_PIPE_ERR_EID           7
#define GENERIC_TORQUER_CMD_DEVRST_INF_EID     8
#define GENERIC_TORQUER_UART_ERR_EID           9
#define GENERIC_TORQUER_UART_WRITE_ERR_EID    10
#define GENERIC_TORQUER_UART_READ_ERR_EID     11
#define GENERIC_TORQUER_COMMANDRAW_INF_EID    12
#define GENERIC_TORQUER_UART_MSG_CNT_DBG_EID  13
#define GENERIC_TORQUER_MUTEX_ERR_EID         14
#define GENERIC_TORQUER_CREATE_DEVICE_ERR_EID 15
#define GENERIC_TORQUER_DEVICE_REG_ERR_EID    16
#define GENERIC_TORQUER_DEVICE_REG_INF_EID    17

#define GENERIC_TORQUER_EVENT_COUNTS 17


/* Added from the previous version of torquers */
#define TRQ_SUB_CMD_ERR_EID           18
#define TRQ_SUB_REQ_HK_ERR_EID        19
#define TRQ_SUB_REQ_DEVICE_ERR_EID    20
#define TRQ_INIT_MUTEX_ERR_EID        21

/* Define any hardware protocol event IDs */
#define TRQ_INIT_TRQ_ERR_EID          22
#define TRQ_INIT_GPIO_ERR_EID         23
#define TRQ_UART_TIMEOUT_ERR_EID      24

/* Define any custom app command event IDs */
#define TRQ_COMMANDENABLE_INF_EID     25
#define TRQ_COMMANDDISABLE_INF_EID    26
#define TRQ_COMMANDNUM_ERR_EID        27
#define TRQ_COMMANDDIRECTION_INF_EID  28
#define TRQ_COMMANDDIRECTION_ERR_EID  29
#define TRQ_COMMANDHIGH_INF_EID       30
#define TRQ_COMMANDHIGH_ERR_EID       31
#define TRQ_COMMANDPERCENT_INF_EID    32
#define TRQ_COMMANDPERCENT_ERR_EID    33
#define TRQ_COMMANDENABLED_ERR_EID    34
#define TRQ_COMMAND_3AXIS_PCT_INF_EID 35


#endif /* _GENERIC_TORQUER_APP_EVENTS_H_ */

/************************/
/*  End of File Comment */
/************************/
