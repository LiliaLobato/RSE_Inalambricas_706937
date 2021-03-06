
/*
* Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _UDP_CFG_H
#define _UDP_CFG_H
/*!=================================================================================================
\file       udp_cfg.h
\brief      This is a header file for the UDP module. It contains macros used to configure the
            UDP module.
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/
/* General Includes */
#include "EmbeddedTypes.h"
#include "app_stack_config.h"

/*==================================================================================================
Public macros
==================================================================================================*/
/*! Maximum number of UDP connections */
#ifndef MAX_UDP_CONNECTIONS
    #define MAX_UDP_CONNECTIONS         8
#endif

#ifndef UDP_DEFAULT_HOP_LIMIT
    #define UDP_DEFAULT_HOP_LIMIT    (128)   /*!< Default hop limit for IPv6 or TTL for IPv4 */
#endif
/*==================================================================================================
Public type definitions
==================================================================================================*/

/*==================================================================================================
Public global variables declarations
==================================================================================================*/

/*==================================================================================================
Public function prototypes
==================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /* _UDP_CFG_H */
