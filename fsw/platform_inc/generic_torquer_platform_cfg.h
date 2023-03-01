/************************************************************************
** File:
**   $Id: generic_torquer_platform_cfg.h  $
**
** Purpose:
**  Define generic_torquer Platform Configuration Parameters
**
** Notes:
**
*************************************************************************/
#ifndef _GENERIC_TORQUER_PLATFORM_CFG_H_
#define _GENERIC_TORQUER_PLATFORM_CFG_H_

/*
** Default GENERIC_TORQUER Configuration
*/
#ifndef GENERIC_TORQUER_CFG
    /* Notes: 
    **   NOS3 uart requires matching handle and bus number
    */
    #define GENERIC_TORQUER_CFG_STRING           "usart_29"
    #define GENERIC_TORQUER_CFG_HANDLE           29 
    #define GENERIC_TORQUER_CFG_BAUDRATE_HZ      115200
    #define GENERIC_TORQUER_CFG_MS_TIMEOUT       50            /* Max 255 */
    /* Note: Debug flag disabled (commented out) by default */
    //#define GENERIC_TORQUER_CFG_DEBUG
#endif

#endif /* _GENERIC_TORQUER_PLATFORM_CFG_H_ */
