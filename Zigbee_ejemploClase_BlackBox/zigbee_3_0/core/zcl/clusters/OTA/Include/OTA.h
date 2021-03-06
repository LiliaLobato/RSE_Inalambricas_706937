/*
* Copyright 2012-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*!
\file       ota.h
\brief      Header for Over the air upgrade cluster
*/

#ifndef OTA_H_
#define OTA_H_

#if defined __cplusplus
extern "C" {
#endif

#include <jendefs.h>
#include "zcl.h"
#include "zcl_options.h"
#include "zcl_customcommand.h"
#if defined (CPU_MKW41Z512VHT4) || defined (CPU_K32W042S1M2VPJ_cm4)
  #include "SecLib.h"
#elif (defined JENNIC_CHIP_FAMILY)
  #include "AHI_AES.h"
#else
  #include "aessw_ccm.h"
#endif

#if (defined JENNIC_CHIP_FAMILY)
#ifndef OTA_NO_CERTIFICATE
    #include "eccapi.h"
#endif


#ifndef OTA_UNIT_TEST_FRAMEWORK
#include <PeripheralRegs.h>
#endif
#endif

/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#ifndef OTA_MAX_IMAGES_PER_ENDPOINT
#define OTA_MAX_IMAGES_PER_ENDPOINT 1
#endif

#ifndef OTA_MAX_CO_PROCESSOR_IMAGES
#define OTA_MAX_CO_PROCESSOR_IMAGES 1
#endif

#ifndef OTA_ACKS_ON
#define OTA_ACKS_ON TRUE
#endif

#ifndef OTA_CLIENT_DISABLE_DEFAULT_RESPONSE
#define OTA_CLIENT_DISABLE_DEFAULT_RESPONSE FALSE
#endif

  
#ifndef OTA_TIME_INTERVAL_BETWEEN_RETRIES
    #define OTA_TIME_INTERVAL_BETWEEN_END_REQUEST_RETRIES            10
#else
    #define OTA_TIME_INTERVAL_BETWEEN_END_REQUEST_RETRIES            OTA_TIME_INTERVAL_BETWEEN_RETRIES
#endif

#ifdef OTA_PAGE_REQUEST_SUPPORT
#ifndef OTA_PAGE_REQ_PAGE_SIZE
#define OTA_PAGE_REQ_PAGE_SIZE                    512 //by default 1k page size
#endif
#ifndef OTA_PAGE_REQ_RESPONSE_SPACING
#define OTA_PAGE_REQ_RESPONSE_SPACING             300 //in miliseconds
#endif
#if (OTA_PAGE_REQ_RESPONSE_SPACING < 300)
#error OTA_PAGE_REQ_RESPONSE_SPACING should  not be less than 300
#endif
#endif

#ifndef CLD_OTA_MAX_BLOCK_PAGE_REQ_RETRIES
#define CLD_OTA_MAX_BLOCK_PAGE_REQ_RETRIES            3
#endif

#ifndef OTA_BLOCK_REQUEST_DELAY_MAX_VALUE
#define OTA_BLOCK_REQUEST_DELAY_MAX_VALUE         5 //in seconds
#endif

#define OTA_MIN_TIMER_MS_RESOLUTION               50

#ifndef OTA_BLOCK_REQUEST_DELAY_DEF_VALUE
#define OTA_BLOCK_REQUEST_DELAY_DEF_VALUE         0  //in seconds
#endif
    
#ifndef OTA_MAX_SIMULTANEOUS_CLIENTS
#define OTA_MAX_SIMULTANEOUS_CLIENTS 0
#endif
    
#if OTA_MAX_SIMULTANEOUS_CLIENTS
#define OTA_CLIENT_SESSION_EXPIRATION           30      //in seconds
#define OTA_CLIENT_DELAY_FOR_NEXT_REQUEST       60      //in seconds
#endif

#ifndef CLD_OTA_MANF_ID_VALUE
#define CLD_OTA_MANF_ID_VALUE                     0x1004
#endif

#define OTA_CLUSTER_ID                            (uint16)0x0019
#define OTA_TAG_HEADER_SIZE                       (uint8)6
#define OTA_HEADER_STRING_SIZE                    (uint8)32
#ifdef ZCLIP_ENABLED
#define OTA_MAX_HEADER_SIZE                       (uint8)93
#else
#define OTA_MAX_HEADER_SIZE                       (uint8)69
#endif
#define OTA_MIN_HEADER_SIZE                       (uint8)56
  
/* OTA header information */  
#define OTA_FILE_IDENTIFIER                       (uint32)0x0BEEF11E
#define OTA_FILE_HEADER_VERSION                   (uint16)0x0001
#define OTA_STACK_VERSION                         (uint16)0x0002
  
/* OTA Image Type */  
#ifndef OTA_IMAGE_TYPE_DEFAULT
#define OTA_IMAGE_TYPE_DEFAULT                    (uint16)0x0000  /* Manufacturer Specific - 0x0000: 0xffbf */
#endif
#define OTA_IMAGE_TYPE_SECURITY_CREDENTIAL        (uint16)0xFFC0  
#define OTA_IMAGE_TYPE_WILD_CARD                  (uint16)0xFFFF  
  
/* OTA file version */
#ifndef OTA_FILE_VERSION_DEFAULT
#define OTA_FILE_VERSION_DEFAULT                  (uint32)0x31013102 
#endif
#define OTA_FILE_VERSION_WILD_CARD                (uint32)0xFFFFFFFF 

/* OTA HW Version*/  
#ifndef OTA_FILE_HW_VERSION_MIN
#define OTA_FILE_HW_VERSION_MIN                   (uint16)0x2240
#endif
#ifndef OTA_FILE_HW_VERSION_MAX
#define OTA_FILE_HW_VERSION_MAX                   (uint16)0x2260
#endif
  
/* OTA tag information */  
#define OTA_TAG_ID_UPGRADE_IMAGE                  (uint16)0x0000
#define OTA_TAG_ID_BITMAP_ELEMENT                 (uint16)0xF000
#define OTA_TAG_ID_CRC_ELEMENT                    (uint16)0xF100
#define OTA_TAG_ID_EDCA_SIGNATURE                 (uint16)0x0001
#define OTA_TAG_ID_EDCA_CERT                      (uint16)0x0002
#define OTA_TAG_ID_OVERLAYS                       (uint16)0xF01A
  
#define OTA_SIGNING_CERT_SIZE                     (uint8)48
#define OTA_SIGNITURE_SIZE                        (uint8)42
#define OTA_MAC_ADDRESS_SIZE                      (uint8)8
#define OTA_HEADER_OFFSET                         (uint8)0

#define OTA_SIGNATURE_NONE                        0 
#define OTA_SIGNATURE_CRC                         1
#define OTA_SIGNATURE_HASH                        2  

#ifndef OTA_CLIENT_SIGNATURE
#define OTA_CLIENT_SIGNATURE                       OTA_SIGNATURE_CRC
#endif    
  
#define OTA_IV_LOCATION                           (uint8)16
#define OTA_6X_MAC_OFFSET                         (uint8)64
#define FL_INDEX_SECTOR_CUSTOMER_SETTINGS         (0x01001510)
#define FL_INDEX_SECTOR_ENC_KEY_ADDRESS           (0x010015c0)
#define FL_INDEX_SECTOR_ENC_EXT_FLASH             (0x40)

#define OTA_AES_BLOCK_SIZE                        (uint8)16


#define OTA_ENC_OFFSET                            (uint8)32

    /* Firmware version bitmask */
#define OTA_STACK_BUILD_MASK                      (uint32)0x000000FF
#define OTA_STACK_RELEASE_MASK                    (uint32)0x0000FF00
#define OTA_APPLICATION_BUILD_MASK                (uint32)0x00FF0000
#define OTA_APPLICATION_RELEASE_MASK              (uint32)0xFF000000

/* OTA Header Field Control Bitmask */
#define OTA_HDR_CONTROL_FIELD_BITMASK             (uint8)   0x07
#define OTA_HDR_SECURITY_CRED_VER_PRESENT         (uint8)   0x01
#define OTA_HDR_DEV_SPECF_FILE                    (uint8)   0x02
#define OTA_HDR_HW_VER_PRESENT                    (uint8)   0x04

/*UpgradeCountDownUTCTime value 0x00000001-0xfffffffe upgrade to run in specified time in UTC time*/
#define OTA_UTC_UPGRADE_TO_RUN_NEW_IMAGE_NOW      (uint32)0x00000000
#define OTA_UTC_UPGRADE_WAIT_FOR_RUN_COMMAND      (uint32)0xffffffff

/* OTA Upgrade Status Codes */
#define OTA_STATUS_SUCCESS                        (uint8)0x00
#define OTA_STATUS_ABORT                          (uint8)0x95
#define OTA_STATUS_NOT_AUTHORISED                 (uint8)0x7E
#define OTA_STATUS_IMAGE_INVALID                  (uint8)0x96
#define OTA_STATUS_WAIT_FOR_DATA                  (uint8)0x97
#define OTA_STATUS_NO_IMAGE_AVAILABLE             (uint8)0x98
#define OTA_MALFORMED_COMMAND                     (uint8)0x80
#define OTA_UNSUP_CLUSTER_COMMAND                 (uint8)0x81
#define OTA_REQUIRE_MORE_IMAGE                    (uint8)0x99
#define OTA_EFUSE_REG_CNTRL                       (uint8)24

#define OTA_TOTAL_ACTIVE_IMAGES_ON_SERVER         (OTA_MAX_IMAGES_PER_ENDPOINT+OTA_MAX_CO_PROCESSOR_IMAGES)
#define OTA_TOTAL_ACTIVE_IMAGES                   (1 + OTA_MAX_CO_PROCESSOR_IMAGES)

// This defines offset where MAC address is stored, will be used to set MAC address once Image is received over
// the Air
#define OTA_MAC_ADDRESS_OFFSET                    0x10

#define CLD_OTA_NUMBER_OF_MANDATORY_ATTRIBUTE     (2)  //u8ImageUpgradeStatus, u64UgradeServerID

#ifdef OTA_CLD_ATTR_FILE_OFFSET
    #define ATTR_FILE_OFFSET                      (1)
#else
    #define ATTR_FILE_OFFSET                      (0)
#endif

#ifdef OTA_CLD_ATTR_CURRENT_FILE_VERSION
    #define ATTR_CURRENT_FILE_VERSION             (1)
#else
    #define ATTR_CURRENT_FILE_VERSION             (0)
#endif
#ifdef OTA_CLD_ATTR_DOWNLOADED_FILE_VERSION
    #define ATTR_DOWNLOADED_FILE_VERSION          (1)
#else
    #define ATTR_DOWNLOADED_FILE_VERSION          (0)
#endif

#ifdef OTA_CLD_ATTR_CURRENT_ZIGBEE_STACK_VERSION
    #define ATTR_CURRENT_ZIGBEE_STACK_VERSION     (1)
#else
    #define ATTR_CURRENT_ZIGBEE_STACK_VERSION     (0)
#endif

#ifdef OTA_CLD_ATTR_DOWNLOADED_ZIGBEE_STACK_VERSION
    #define ATTR_DOWNLOADED_ZIGBEE_STACK_VERSION  (1)
#else
    #define ATTR_DOWNLOADED_ZIGBEE_STACK_VERSION  (0)
#endif

#ifdef OTA_CLD_ATTR_MANF_ID
    #define ATTR_MANF_ID                          (1)
#else
    #define ATTR_MANF_ID                          (0)
#endif

#ifdef OTA_CLD_ATTR_IMAGE_TYPE
    #define ATTR_IMAGE_TYPE                       (1)
#else
    #define ATTR_IMAGE_TYPE                       (0)
#endif

#ifdef OTA_CLD_ATTR_REQUEST_DELAY
    #define ATTR_REQUEST_DELAY                    (1)
#else
    #define ATTR_REQUEST_DELAY                    (0)
#endif

#ifdef OTA_CLD_ATTR_IMAGE_STAMP
    #define ATTR_IMAGE_STAMP                      (1)
#else
    #define ATTR_IMAGE_STAMP                      (0)
#endif

#ifndef CLD_OTA_CLUSTER_REVISION
    #define CLD_OTA_CLUSTER_REVISION        1
#endif 

#define CLD_OTA_NUMBER_OF_OPTIONAL_ATTRIBUTE                        \
    ((ATTR_FILE_OFFSET)                            +              \
    (ATTR_CURRENT_FILE_VERSION)                    +              \
    (ATTR_DOWNLOADED_FILE_VERSION)                 +              \
    (ATTR_CURRENT_ZIGBEE_STACK_VERSION)            +              \
    (ATTR_DOWNLOADED_ZIGBEE_STACK_VERSION)         +              \
    (ATTR_MANF_ID)                                 +              \
    (ATTR_IMAGE_TYPE)                              +              \
    (ATTR_REQUEST_DELAY)                           +              \
    (ATTR_IMAGE_STAMP))

#define CLD_OTA_MAX_NUMBER_OF_ATTRIBUTE                           \
    ((CLD_OTA_NUMBER_OF_OPTIONAL_ATTRIBUTE)         +             \
    (CLD_OTA_NUMBER_OF_MANDATORY_ATTRIBUTE))

#ifdef ZCLIP_ENABLED
#ifndef CLD_OTA_FILE_URI_MAX_LENGTH
#define CLD_OTA_FILE_URI_MAX_LENGTH 64
#endif

#define CLD_OTA_FILE_URI_ROOT "/ota"
#define CLD_OTA_FILE_URI_ROOT_LENGTH 4 /* strlen(CLD_OTA_FILE_URI_ROOT) */
#endif

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

#ifdef OTA_SERVER
typedef enum 
{
    E_CLD_OTA_STATE_ALLOW_ALL,
    E_CLD_OTA_STATE_USE_LIST
}eOTA_AuthorisationState;

typedef struct
{
    eOTA_AuthorisationState eState;
    uint64 *pu64WhiteList;
    uint8 u8Size;
}tsOTA_AuthorisationStruct;
#endif

typedef struct
{
    uint32 u32FileIdentifier;
    uint16 u16HeaderVersion;
    uint16 u16HeaderLength;
    uint16 u16HeaderControlField;
    uint16 u16ManufacturerCode;
    uint16 u16ImageType;
    uint32 u32FileVersion;
    uint16 u16StackVersion;
    uint8 stHeaderString[OTA_HEADER_STRING_SIZE];
    uint32 u32TotalImage;
    uint8 u8SecurityCredVersion;
    uint64 u64UpgradeFileDest;
    uint16 u16MinimumHwVersion;
    uint16 u16MaxHwVersion;
}tsOTA_ImageHeader;

typedef struct
{
    tsOTA_ImageHeader sOTA_ImageHeader[1];
}tsOTA_CoProcessorOTAHeader;

typedef enum 
{
    E_CLD_OTA_STACK_ZIGBEE_2006,
    E_CLD_OTA_STACK_ZIGBEE_2007,
    E_CLD_OTA_STACK_ZIGBEE_PRO,
    E_CLD_OTA_STACK_ZIGBEE_IP
}teOTA_StackVersion;

typedef enum 
{
    E_CLD_OTA_ATTR_UPGRADE_SERVER_ID,                   /* 0x0000 */
    E_CLD_OTA_ATTR_FILE_OFFSET,                         /* 0x0001 */
    E_CLD_OTA_ATTR_CURRENT_FILE_VERSION,                /* 0x0002 */
    E_CLD_OTA_ATTR_CURRENT_ZIGBEE_STACK_VERSION,        /* 0x0003 */
    E_CLD_OTA_ATTR_DOWNLOADED_FILE_VERSION,             /* 0x0004 */
    E_CLD_OTA_ATTR_DOWNLOADED_ZIGBEE_STACK_VERSION,     /* 0x0005 */
    E_CLD_OTA_ATTR_IMAGE_UPGRADE_STATUS,                /* 0x0006 */
    E_CLD_OTA_ATTR_MANF_ID,                             /* 0x0007 */
    E_CLD_OTA_ATTR_IMAGE_TYPE,                          /* 0x0008 */
    E_CLD_OTA_ATTR_REQUEST_DELAY,                       /* 0x0009 */
    E_CLD_OTA_ATTR_IMAGE_STAMP                          /* 0x000A */
}teOTA_Cluster;

typedef enum 
{
    E_CLD_OTA_PARAMS_QUERY_JITTER,
    E_CLD_OTA_PARAMS_IMAGE_SIZE,
    E_CLD_OTA_PARAMS_IMAGE_DATA,
    E_CLD_OTA_PARAMS_UPGRADE_COUNT_DOWN_OFFSET,
    E_CLD_OTA_PARAMS_UPGRADE_COUNT_DOWN_UTC_TIME,
    E_CLD_OTA_PARAMS_UPGRADE_SIGNATURE
}teOTA_ServerParms;

/* only values 0x00 - 0x04 are valid all other values are reserved */
typedef enum 
{
    E_CLD_OTA_STATUS_NORMAL,
    E_CLD_OTA_STATUS_DL_IN_PROGRESS,
    E_CLD_OTA_STATUS_DL_COMPLETE,
    E_CLD_OTA_STATUS_WAIT_TO_UPGRADE,
    E_CLD_OTA_STATUS_COUNT_DOWN,
    E_CLD_OTA_STATUS_WAIT_FOR_MORE,
}teOTA_ImageUpgradeStatus;

typedef struct
{
#ifdef OTA_CLIENT
    uint64 u64UgradeServerID;
    uint32 u32FileOffset;
    uint32 u32CurrentFileVersion;
    uint16 u16CurrentStackVersion;
    uint32 u32DownloadedFileVersion;
    uint16 u16DownloadedStackVersion;
    uint8  u8ImageUpgradeStatus;
    uint16 u16ManfId;
    uint16 u16ImageType;
    uint16 u16MinBlockRequestDelay;
    uint32 u32ImageStamp;
#endif
    uint16 u16ClusterRevision;
} tsCLD_AS_Ota;

#ifdef ZCLIP_ENABLED
#define OTA_MAX_OTA_FILE_URI_LENGTH (CLD_OTA_FILE_URI_ROOT_LENGTH + 19 /* strlen("/MMMM-TTTT-VVVVVVVV") */)
typedef struct
{
    uint8 uri[OTA_MAX_OTA_FILE_URI_LENGTH+1];
} tsOta_FileUri;
#endif

typedef struct
{
    uint8   *pu8Data;
    uint32  u32CurrentTime;
    uint32  u32RequestOrUpgradeTime;
    uint8   u8QueryJitter;
    uint8   u8DataSize;
#ifdef ZCLIP_ENABLED
    tsOta_FileUri sFileUri;
#endif
} tsCLD_PR_Ota;


typedef enum 
{
    E_CLD_OTA_COMMAND_IMAGE_NOTIFY,
    E_CLD_OTA_COMMAND_QUERY_NEXT_IMAGE_REQUEST,
    E_CLD_OTA_COMMAND_QUERY_NEXT_IMAGE_RESPONSE,
    E_CLD_OTA_COMMAND_BLOCK_REQUEST,
    E_CLD_OTA_COMMAND_PAGE_REQUEST,
    E_CLD_OTA_COMMAND_BLOCK_RESPONSE,
    E_CLD_OTA_COMMAND_UPGRADE_END_REQUEST,
    E_CLD_OTA_COMMAND_UPGRADE_END_RESPONSE,
    E_CLD_OTA_COMMAND_QUERY_SPECIFIC_FILE_REQUEST,
    E_CLD_OTA_COMMAND_QUERY_SPECIFIC_FILE_RESPONSE,
    E_CLD_OTA_INTERNAL_COMMAND_TIMER_EXPIRED,
    E_CLD_OTA_INTERNAL_COMMAND_SAVE_CONTEXT,
    E_CLD_OTA_INTERNAL_COMMAND_OTA_DL_ABORTED,
    E_CLD_OTA_INTERNAL_COMMAND_POLL_REQUIRED,
    E_CLD_OTA_INTERNAL_COMMAND_RESET_TO_UPGRADE,
    E_CLD_OTA_INTERNAL_COMMAND_LOCK_FLASH_MUTEX,
    E_CLD_OTA_INTERNAL_COMMAND_FREE_FLASH_MUTEX,
    E_CLD_OTA_INTERNAL_COMMAND_SEND_UPGRADE_END_RESPONSE,
    E_CLD_OTA_INTERNAL_COMMAND_CO_PROCESSOR_BLOCK_RESPONSE,
    E_CLD_OTA_INTERNAL_COMMAND_CO_PROCESSOR_DL_ABORT,
    E_CLD_OTA_INTERNAL_COMMAND_CO_PROCESSOR_IMAGE_DL_COMPLETE,
    E_CLD_OTA_INTERNAL_COMMAND_CO_PROCESSOR_SWITCH_TO_NEW_IMAGE,
    E_CLD_OTA_INTERNAL_COMMAND_CO_PROCESSOR_IMAGE_BLOCK_REQUEST,
    E_CLD_OTA_INTERNAL_COMMAND_SPECIFIC_FILE_BLOCK_RESPONSE,
    E_CLD_OTA_INTERNAL_COMMAND_SPECIFIC_FILE_DL_ABORT,
    E_CLD_OTA_INTERNAL_COMMAND_SPECIFIC_FILE_DL_COMPLETE,
    E_CLD_OTA_INTERNAL_COMMAND_SPECIFIC_FILE_USE_NEW_FILE,
    E_CLD_OTA_INTERNAL_COMMAND_SPECIFIC_FILE_NO_UPGRADE_END_RESPONSE,
    E_CLD_OTA_COMMAND_QUERY_NEXT_IMAGE_RESPONSE_ERROR,
    E_CLD_OTA_INTERNAL_COMMAND_VERIFY_SIGNER_ADDRESS,
    E_CLD_OTA_INTERNAL_COMMAND_RCVD_DEFAULT_RESPONSE,
    E_CLD_OTA_INTERNAL_COMMAND_VERIFY_IMAGE_VERSION,
    E_CLD_OTA_INTERNAL_COMMAND_SWITCH_TO_UPGRADE_DOWNGRADE,
    E_CLD_OTA_INTERNAL_COMMAND_REQUEST_QUERY_NEXT_IMAGES,
    E_CLD_OTA_INTERNAL_COMMAND_OTA_START_IMAGE_VERIFICATION_IN_LOW_PRIORITY,
    E_CLD_OTA_INTERNAL_COMMAND_FAILED_VALIDATING_UPGRADE_IMAGE,
    E_CLD_OTA_INTERNAL_COMMAND_FAILED_COPYING_SERIALIZATION_DATA,
    E_CLD_OTA_INTERNAL_COMMAND_VERIFY_STRING,
    E_CLD_OTA_BLOCK_RESPONSE_TAG_OTHER_THAN_UPGRADE_IMAGE_BITMAP_CRC
}teOTA_UpgradeClusterEvents;

typedef enum 
{
    E_CLD_OTA_QUERY_JITTER,
    E_CLD_OTA_MANUFACTURER_ID_AND_JITTER,
    E_CLD_OTA_ITYPE_MDID_JITTER,
    E_CLD_OTA_ITYPE_MDID_FVERSION_JITTER
}teOTA_ImageNotifyPayloadType;
typedef struct
{
    teOTA_ImageNotifyPayloadType ePayloadType;
    uint32 u32NewFileVersion;
    uint16 u16ImageType;
    uint16 u16ManufacturerCode;
    uint8 u8QueryJitter;
}tsOTA_ImageNotifyCommand;

typedef struct
{
    uint32 u32CurrentFileVersion;
    uint16 u16HardwareVersion;
    uint16 u16ImageType;
    uint16 u16ManufacturerCode;
    uint8 u8FieldControl;
}tsOTA_QueryImageRequest;

typedef struct
{
    uint32 u32ImageSize;
    uint32 u32FileVersion;
    uint16 u16ManufacturerCode;
    uint16 u16ImageType;
    uint8  u8Status;
#ifdef ZCLIP_ENABLED
    tsZCL_CharacterString sFileUri;
#endif
}tsOTA_QueryImageResponse;

typedef struct
{
    uint64 u64RequestNodeAddress;
    uint32 u32FileOffset;
    uint32 u32FileVersion;
    uint16 u16ImageType;
    uint16 u16ManufactureCode;
    uint16 u16BlockRequestDelay;
    uint8 u8MaxDataSize;
    uint8 u8FieldControl;
}tsOTA_BlockRequest;

typedef struct
{
    uint64 u64RequestNodeAddress;
    uint32 u32FileOffset;
    uint32 u32FileVersion;
    uint16 u16PageSize;
    uint16 u16ResponseSpacing;
    uint16 u16ImageType;
    uint16 u16ManufactureCode;
    uint8 u8MaxDataSize;
    uint8 u8FieldControl;
}tsOTA_ImagePageRequest;

typedef struct
{
    uint8* pu8Data;
    uint32 u32FileOffset;
    uint32 u32FileVersion;
    uint16 u16ImageType;
    uint16 u16ManufacturerCode;
    uint8 u8DataSize;
}tsOTA_SuccessBlockResponsePayload;

typedef struct
{
    uint8 u8Status;
    uint8* pu8Data;
    uint8 u8DataSize;
}tsOTA_BlockResponseEvent;

typedef struct
{
    uint32 u32CurrentTime;
    uint32 u32RequestTime;
    uint16 u16BlockRequestDelayMs;
}tsOTA_WaitForData;

typedef struct
{
    bool_t bInitialized;
    uint16 u16ClientAddress;
    tsOTA_WaitForData sWaitForDataPyld;
}tsOTA_WaitForDataParams;

typedef void(*pFunc)(void*,tsZCL_EndPointDefinition*);

typedef struct
{
    uint8 u8Status;
    union
    {
        tsOTA_WaitForData sWaitForData;
        tsOTA_SuccessBlockResponsePayload   sBlockPayloadSuccess;
    }uMessage;
}tsOTA_ImageBlockResponsePayload;

typedef struct
{
    uint32 u32FileVersion;
    uint16 u16ImageType;
    uint16 u16ManufacturerCode;
    uint8 u8Status;
}tsOTA_UpgradeEndRequestPayload;

typedef struct
{
    uint32 u32UpgradeTime;
    uint32 u32CurrentTime;
    uint32 u32FileVersion;
    uint16 u16ImageType;
    uint16 u16ManufacturerCode;
}tsOTA_UpgradeEndResponsePayload;

typedef struct
{
    uint64 u64RequestNodeAddress;
    uint16 u16ManufacturerCode;
    uint16 u16ImageType;
    uint32 u32FileVersion;
    uint16 u16CurrentZibgeeStackVersion;
}tsOTA_QuerySpecificFileRequestPayload;

typedef tsOTA_QueryImageResponse tsOTA_QuerySpecificFileResponsePayload;

typedef struct
{
    uint8 u8ImageBlockReqDevEndPoint;
    uint16 u16ImageBlockReqDevAddr;
    tsOTA_BlockRequest sOTA_BlockRequest;
}tsOTA_CoProcessorMediaBlockRequest;


typedef struct
{
    uint64 u64SignerMac;
    teZCL_Status eMacVerifyStatus;
}tsOTA_SignerMacVerify;

typedef struct
{
    uint32 u32NotifiedImageVersion;
    uint32 u32CurrentImageVersion;
    teZCL_Status eImageVersionVerifyStatus;
}tsOTA_ImageVersionVerify;

typedef struct
{
    teZCL_Status eStatus;
    uint8 * pu8Current;
    uint8 * puNotified;
}tsOTA_ImageIdentification;

typedef struct
{
    uint32 u32DownloadImageVersion;
    uint32 u32CurrentImageVersion;
    teZCL_Status eUpgradeDowngradeStatus;
}tsOTA_UpgradeDowngradeVerify;

#ifdef OTA_CLIENT

#ifdef OTA_PAGE_REQUEST_SUPPORT
typedef struct
{
    bool_t bPageReqOn;
    uint8  u8PageReqRetry;
    uint32 u32PageReqFileOffset;
}tsOTA_PageReqParams;
#endif

typedef struct
{
    tsCLD_AS_Ota sAttributes;
    uint32 u32FunctionPointer;
    uint32 u32RequestBlockRequestTime;
    uint32 u32CurrentFlashOffset;
    uint32 u32TagDataWritten;
    uint32 u32Step;
#ifndef ZCLIP_ENABLED
    uint16 u16ServerShortAddress;
#else
    tsZCL_Address serverAddress;
    char *pFileUri;
    uint16 u16ManufacturerCode;
    uint16 u16ImageType;
#endif
#ifdef OTA_CLD_ATTR_REQUEST_DELAY
    bool_t bWaitForBlockReq;
#endif
    uint8 u8ActiveTag[OTA_TAG_HEADER_SIZE];
    uint8 u8PassiveTag[OTA_TAG_HEADER_SIZE];
    uint8 au8Header[OTA_MAX_HEADER_SIZE];
    uint8 u8Retry;
    uint8 u8RequestTransSeqNo;
    uint8 u8DstEndpoint;
    bool_t bIsCoProcessorImage;
    bool_t bIsSpecificFile;
    bool_t bIsNullImage;
    uint8  u8CoProcessorOTAHeaderIndex;
    uint32 u32CoProcessorImageSize;
    uint32 u32SpecificFileSize;
    uint32_t u32CrcValue;
    uint32_t u32CrcByteProcessed;
    uint8_t au8CrcValueReceived[4];
    uint8_t au8Bitmap[32];
#ifdef OTA_PAGE_REQUEST_SUPPORT
    tsOTA_PageReqParams sPageReqParams;
#endif
#if (OTA_MAX_CO_PROCESSOR_IMAGES != 0)
    uint8 u8NumOfDownloadableImages;
#endif
#ifdef OTA_INTERNAL_STORAGE
    uint8 u8Buf[4];
#endif
}tsOTA_PersistedData;

#endif

#if (defined OTA_SERVER && defined OTA_PAGE_REQUEST_SUPPORT)
typedef struct
{
    uint8                      u8TransactionNumber;
    bool_t                     bPageReqRespSpacing;
    uint16                     u16DataSent;
    tsOTA_ImagePageRequest     sPageReq;
    tsZCL_ReceiveEventAddress  sReceiveEventAddress;
}tsOTA_PageReqServerParams;
#endif

typedef struct
{
    /* this function gets called after a cold or warm start */
    void (*prInitHwCb)(uint8, void*);

    /* this function gets called to erase the given sector */
    void (*prEraseCb) (uint8 u8Sector);

    /* this function gets called to write data to an addresss
     * within a given sector. address zero is the start of the
     * given sector */
    void (*prWriteCb) (uint32 u32FlashByteLocation,
                       uint16 u16Len,
                       uint8 *pu8Data);

    /* this function gets called to read data from an addresss
     * within a given sector. address zero is the start of the
     * given sector */
    void (*prReadCb)  (uint32 u32FlashByteLocation,
                       uint16 u16Len,
                       uint8 *pu8Data);
} tsOTA_HwFncTable;


typedef struct
{
    tsOTA_HwFncTable sOtaFnTable;
    uint32 u32SectorSize;
    uint8  u8FlashDeviceType;      // these are equivalent to teFlashChipType defined in AppHardwareAPI
}tsNvmDefs;

typedef struct
{
    teOTA_UpgradeClusterEvents     eEventId;
#ifdef OTA_CLIENT
    tsOTA_PersistedData sPersistedData;
    uint8 au8ReadOTAData[OTA_MAX_BLOCK_SIZE];
    uint8 u8NextFreeImageLocation;
#endif
#ifdef OTA_SERVER
    tsCLD_PR_Ota aServerPrams[OTA_MAX_IMAGES_PER_ENDPOINT+OTA_MAX_CO_PROCESSOR_IMAGES];
    tsOTA_AuthorisationStruct               sAuthStruct;
    bool_t bIsOTAHeaderCopied;
    uint8 au8ServerOTAHeader[OTA_MAX_HEADER_SIZE+OTA_TAG_HEADER_SIZE];
    tsOTA_WaitForDataParams  sWaitForDataParams;
#ifdef OTA_PAGE_REQUEST_SUPPORT
    tsOTA_PageReqServerParams  sPageReqServerParams;
#endif
#endif
    uint8  u8ImageStartSector[OTA_MAX_IMAGES_PER_ENDPOINT];
    uint8 au8CAPublicKey[22];
    uint8 u8MaxNumberOfSectors;
    
    union
    {
        tsOTA_ImageNotifyCommand                sImageNotifyPayload;
        tsOTA_QueryImageRequest                 sQueryImagePayload;
        tsOTA_QueryImageResponse                sQueryImageResponsePayload;
        tsOTA_BlockRequest                      sBlockRequestPayload;
        tsOTA_ImagePageRequest                  sImagePageRequestPayload;
        tsOTA_ImageBlockResponsePayload         sImageBlockResponsePayload;
        tsOTA_UpgradeEndRequestPayload          sUpgradeEndRequestPayload;
        tsOTA_UpgradeEndResponsePayload         sUpgradeResponsePayload;
        tsOTA_QuerySpecificFileRequestPayload   sQuerySpFileRequestPayload;
        tsOTA_QuerySpecificFileResponsePayload  sQuerySpFileResponsePayload;
        teZCL_Status                            eQueryNextImgRspErrStatus;
        tsOTA_SignerMacVerify                   sSignerMacVerify;
        tsOTA_ImageVersionVerify                sImageVersionVerify;
        tsOTA_UpgradeDowngradeVerify            sUpgradeDowngradeVerify;
        tsOTA_ImageIdentification               sImageIdentification;
        tsOTA_BlockResponseEvent                sBlockResponseEvent;
    }uMessage;
}tsOTA_CallBackMessage;

typedef struct
{
    tsZCL_ReceiveEventAddress  sReceiveEventAddress;
    tsZCL_CallBackEvent        sOTACustomCallBackEvent;
    tsOTA_CallBackMessage      sOTACallBackMessage;
} tsOTA_Common;


/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
PUBLIC teZCL_Status eOTA_Create(
                    tsZCL_ClusterInstance      *psClusterInstance,
                    bool_t                      bIsServer,
                    tsZCL_ClusterDefinition    *psClusterDefinition,
                    void                       *pvEndPointSharedStructPtr,
                    uint8                       u8Endpoint,
                    uint8                      *pu8AttributeControlBits,
                    tsOTA_Common               *psCustomDataStruct);

PUBLIC void vOTA_FlashInit(
                    void                       *pvFlashTable,
                    tsNvmDefs                  *psNvmStruct);

PUBLIC teZCL_Status eOTA_AllocateEndpointOTASpace(
                    uint8                       u8Endpoint,
                    uint8                      *pu8Data,
                    uint8                       u8NumberOfImages,
                    uint8                       u8MaxSectorsPerImage,
                    bool_t                      bIsServer,
                    uint8                      *pu8CAPublicKey);

PUBLIC teZCL_Status  eOTA_VerifyImage(
                    uint8                       u8Endpoint,
                    bool_t                        bIsServer,
                    uint8                       u8ImageLocation,
                    bool_t                        bHeaderPresent);

PUBLIC  void vOTA_GenerateHash(
                    tsZCL_EndPointDefinition   *psEndPointDefinition,
                    tsOTA_Common               *psCustomData,
                    bool_t                        bIsServer,
                    bool_t                        bHeaderPresent,
                    AESSW_Block_u              *puHash,
                    uint8                       u8ImageLocation);

PUBLIC void vOTA_SetImageValidityFlag(
                    uint8                       u8Location,
                    tsOTA_Common               *psCustomData,
                    bool_t                        bSet,
                    tsZCL_EndPointDefinition   *psEndPointDefinition);

PUBLIC teZCL_Status eOTA_GetCurrentOtaHeader(
                    uint8                       u8Endpoint,
                    bool_t                      bIsServer,
                    tsOTA_ImageHeader          *psOTAHeader);

PUBLIC bool_t bOtaIsSerializationDataValid(
                    tsZCL_EndPointDefinition   *psEndPointDefinition,
                    tsOTA_Common               *psCustomData,
                    uint8                       u8UpgradeImageIndex);

PUBLIC void vOTA_EncodeString(tsReg128 *psKey, uint8 *pu8Iv,uint8 * pu8DataOut);
#ifdef OTA_SERVER
PUBLIC teZCL_Status eOTA_ServerUpgradeEndResponse(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_UpgradeEndResponsePayload *psUpgradeResponsePayload,
                    uint8                       u8TransactionSequenceNumber);

PUBLIC teZCL_Status eOTA_ServerImageBlockResponse(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_ImageBlockResponsePayload *psImageBlockResponsePayload,
                    uint8                       u8BlockSize,
                    uint8                       u8TransactionSequenceNumber);

PUBLIC teZCL_Status eOTA_ServerQueryNextImageResponse(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_QueryImageResponse   *psQueryImageResponsePayload,
                    uint8                       u8TransactionSequenceNumber);

PUBLIC teZCL_Status eOTA_ServerImageNotify(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_ImageNotifyCommand   *psImageNotifyCommand);

PUBLIC teZCL_Status eOTA_ServerQuerySpecificFileResponse(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_QuerySpecificFileResponsePayload *psQuerySpecificFileResponsePayload,
                    uint8                       u8TransactionSequenceNumber);

PUBLIC teZCL_Status eOTA_SetServerParams(
                    uint8                       u8Endpoint,
                    uint8                       u8ImageIndex,
                    tsCLD_PR_Ota               *psOTAData);

PUBLIC teZCL_Status eOTA_GetServerData(
                    uint8                       u8Endpoint,
                    uint8                       u8ImageIndex,
                    tsCLD_PR_Ota               *psOTAData);

PUBLIC teZCL_Status eOTA_SetServerAuthorisation(
                    uint8                       u8Endpoint,
                    eOTA_AuthorisationState     eState,
                    uint64                     *pu64WhiteList,
                    uint8                       u8Size);

PUBLIC teZCL_Status eOTA_NewImageLoaded(
                    uint8                       u8Endpoint,
                    bool_t                        bIsImageOnCoProcessorMedia,
                    tsOTA_CoProcessorOTAHeader *psOTA_CoProcessorOTAHeader);

PUBLIC teZCL_Status eOTA_FlashWriteNewImageBlock(
                    uint8                       u8Endpoint,
                    uint8                       u8ImageIndex,
                    bool_t                        bIsServerImage,
                    uint8                      *pu8UpgradeBlockData,
                    uint8                       u8UpgradeBlockDataLength,
                    uint32                      u32FileOffSet);

PUBLIC teZCL_Status eOTA_ServerSwitchToNewImage(
                    uint8                       u8Endpoint,
                    uint8                       u8ImageIndex);

PUBLIC teZCL_Status eOTA_InvalidateStoredImage(
                    uint8                       u8Endpoint,
                    uint8                       u8ImageIndex);

PUBLIC teZCL_Status eOTA_EraseFlashSectorsForNewImage(
                    uint8                       u8Endpoint,
                    uint8                       u8ImageIndex);

PUBLIC teZCL_Status eOTA_SetWaitForDataParams(
                    uint8                       u8Endpoint,
                    uint16                      u16ClientAddress,
                    tsOTA_WaitForData          *sWaitForDataParams);
#endif

#ifdef OTA_CLIENT
PUBLIC teZCL_Status eOTA_ClientQueryNextImageRequest(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_QueryImageRequest    *psQueryImageRequest);

PUBLIC teZCL_Status eOTA_ClientImageBlockRequest(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_BlockRequest         *psOtaBlockRequest);

PUBLIC teZCL_Status eOTA_ClientUpgradeEndRequest(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_UpgradeEndRequestPayload *psUpgradeEndRequestPayload);

PUBLIC teZCL_Status eOTA_ClientImagePageRequest(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_ImagePageRequest     *psOtaPageRequest);

PUBLIC teZCL_Status eOTA_ClientQuerySpecificFileRequest(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DestinationEndpoint,
                    tsZCL_Address              *psDestinationAddress,
                    tsOTA_QuerySpecificFileRequestPayload *psQuerySpecificFileRequestPayload);

PUBLIC teZCL_Status eOTA_CoProcessorUpgradeEndRequest(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8Status);

PUBLIC teZCL_Status eOTA_RestoreClientData(
                    uint8                       u8Endpoint,
                    tsOTA_PersistedData        *psOTAData,
                    bool_t                      bReset);

PUBLIC teZCL_Status eOTA_UpdateClientAttributes(uint8 u8Endpoint,
                                                uint32 u32ImageStamp);

PUBLIC teZCL_Status eOTA_SetServerAddress(
                    uint8                       u8Endpoint,
                    uint64                      u64IeeeAddress,
                    uint16                      u16ShortAddress);

PUBLIC teZCL_Status eOTA_UpdateCoProcessorOTAHeader(
                    tsOTA_CoProcessorOTAHeader *psOTA_CoProcessorOTAHeader,
                    bool_t                      bIsCoProcessorImageUpgradeDependent);

PUBLIC teZCL_Status eOTA_SpecificFileUpgradeEndRequest(
                    uint8                       u8SourceEndPointId,
                    uint8                       u8Status);

PUBLIC teZCL_Status eOTA_ClientSwitchToNewImage(
                    uint8                       u8SourceEndPointId);

PUBLIC teZCL_Status eOTA_HandleImageVerification(
                    uint8                       u8SourceEndpoint,
                    uint8                       u8DstEndpoint,
                    teZCL_Status                eImageVerificationStatus);
#endif
/****************************************************************************/
/***        External Variables                                            ***/
/****************************************************************************/
extern tsZCL_ClusterDefinition sCLD_OTA ;
extern    tsNvmDefs            sNvmDefsStruct;
extern uint8 au8OTAAttributeControlBits[];


#ifdef OTA_UPGRADE_VOLTAGE_CHECK
extern bool_t bOta_LowVoltage;
#define vOTA_SetLowVoltageFlag(bValue)   bOta_LowVoltage=bValue
#endif

#ifndef OTA_PC_BUILD
extern void *_FlsOtaHeader, *_FlsLinkKey,*FlsZcCert,*FlsPrivateKey,*_FlsMACAddress
#ifdef OTA_MAINTAIN_CUSTOM_SERIALISATION_DATA
, *FlsCustomDataEnd, *FlsCustomDatabeg
#endif
,*_flash_start
;
#endif

/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/

#endif /* OTA_H_ */
