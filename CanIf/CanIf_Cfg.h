#ifndef __CANIF_CFG_H
#define __CANIF_CFG_H

#include "../include/Std_Types.h"
#include "CanIf_Types.h"
#include "../Can_Tiva/Can_PBcfg.h"
#include "../Can_Tiva/Can_GeneralTypes.h"

typedef struct
{
  Can_CanController *CanIfCtrlCanCtrlRef;
  uint8 CanIfCtrlId;
} CanIf_CanIfCtrlCfg;

typedef struct
{
  CanIf_CanIfCtrlCfg *CanIfHrhCanCtrlIdRef;
  Can_CanHardwareObject *CanIfHthIdSymRef;
} CanIf_CanIfHthCfg;

typedef struct
{
  CanIf_CanIfCtrlCfg *CanIfHrhCanCtrlIdRef;
  Can_CanHardwareObject *CanIfHthIdSymRef;
} CanIf_CanIfHrhCfg;

typedef struct
{
  CanIf_CanIfHthCfg *CanIfHthCfg;
  CanIf_CanIfHrhCfg *CanIfHrhCfg;
} CanIf_CanIfInitHohCfg;
typedef struct
{
  CanIf_CanIfHthCfg *CanIfBufferHthRef;
  uint8 CanIfBufferSize;
} CanIfBufferCfg;

typedef struct
{
  boolean CanIfFixedBuffer;
  boolean CanIfPrivateDlcCheck;
} CanIfPrivateCfg;

typedef struct
{
  uint32 CanIfRxPduCanId;
  CanIfPduCanIdType CanIfRxPduCanIdType;
  uint8 CanIfRxPduDlc;
  CanIf_CanIfHrhCfg *CanIfRxPduHrhIdRef;
  uint32 CanIfRxPduId;
  boolean CanIfRxPduReadNotifyStatus;
  boolean CanIfRxPduReadData;
  CanIfPduUserConfirmationUL CanIfRxPduUserRxIndicationUL;
} CanIfRxPduCfg;

typedef struct
{
  CanIfBufferCfg *CanIfTxPduBufferRef;
  uint32 CanIfTxPduCanId;
  CanIfPduCanIdType CanIfTxPduCanIdType;
  uint32 CanIfTxPduId;
  boolean CanIfTxPduReadNotifyStatus;
  boolean CanIfTxPduTriggerTransmit;
  CanIfPduType CanIfTxPduType;
  CanIfPduUserConfirmationUL CanIfTxPduUserConfirmationUL;
} CanIfTxPduCfg;

typedef struct
{
  uint64 CanIfMaxRxPduCfg;
  uint64 CanIfMaxTxPduCfg;

  CanIfBufferCfg *CanIfBuffersCfgs;
  CanIf_CanIfInitHohCfg *CanIfInitHohCfgs;
  CanIfRxPduCfg *CanIfRxPdusCfgs;
  CanIfTxPduCfg *CanIfTxPdusCfgs;
} CanIfInitCfg;

typedef struct
{
  CanIf_CanIfCtrlCfg *ControllerConfig;
  CanIfInitCfg *InitConfig;

} CanIf_ConfigType;

extern const CanIf_ConfigType CanIfConfiguration;

#endif
