/*
* Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef _ND_EVENTS_H
#define _ND_EVENTS_H
/*!=================================================================================================
\file       nd_events.h
\brief      This is a header file for the Neighbor Discovery for IP version 6 (IPv6) module.
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include "EmbeddedTypes.h"
#include "stack_config.h"


/*==================================================================================================
Public macros
==================================================================================================*/



/*==================================================================================================
Public type definitions
==================================================================================================*/

typedef uint32_t ndEvmCodes_t;

/*! Event codes used by the ND notification mechanism. */
typedef enum
{
    gNdDADSuccess_c                = 0x00010000,
    gNdDADFailed_c                 = 0x00010001,
    gNdRaReceived_c                = 0x00010002,
    gNdRaDnsInfoReceived_c         = 0x00010003,
    gNdRaRouteInfoReceived_c       = 0x00010004
} ndEvmCodes_e;

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
#endif  /* _ND_EVENTS_H */
