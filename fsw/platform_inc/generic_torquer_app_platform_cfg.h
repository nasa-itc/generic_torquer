/************************************************************************
** File:
**  generic_torquer_app_platform_cfg.h
**
** Purpose: 
**  Define Generic_torquer App platform configuration parameters
**
** Notes:
**
**
*************************************************************************/
#ifndef _GENERIC_TORQUER_APP_PLATFORM_CFG_H_
#define _GENERIC_TORQUER_APP_PLATFORM_CFG_H_

#define GENERIC_TORQUER_UART_BUFFER_SIZE 1024

#define GENERIC_TORQUER_DEVICE_NAME       "GENERIC_TORQUER_DEVICE"
/* Note: Generic_torquer child task stack and priority get defined here. Main app is specified in cfe_es_startup.scr */
#define GENERIC_TORQUER_DEVICE_CHILD_STACK_SIZE  2048
#define GENERIC_TORQUER_DEVICE_CHILD_PRIORITY    100
#define GENERIC_TORQUER_DEVICE_MUTEX_NAME "GENERIC_TORQUER_DEVICE_MUTEX"

/*
** Default Generic_torquer Configuration
** Note: In practice this configuration should be specified in the mission_defs/cpuX_device_cfg.h
**       These parameters are for the I/O to the device and can change per platform (NOS3 vs. flight vs. flatsat)
**       The definitions here will only be used if GENERIC_TORQUER_CFG is not in the cpuX_device_cfg.h 
*/
#ifndef GENERIC_TORQUER_CFG
    /* Note: NOS3 uart requires matching handle and bus number */
    #define GENERIC_TORQUER_CFG_STRING           "usart_29"
    #define GENERIC_TORQUER_CFG_HANDLE           29 
    #define GENERIC_TORQUER_CFG_BAUDRATE_HZ      115200
    #define GENERIC_TORQUER_CFG_MS_TIMEOUT       250
#endif

#endif /* _GENERIC_TORQUER_PLATFORM_CFG_H_ */

/************************/
/*  End of File Comment */
/************************/
