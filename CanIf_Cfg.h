#ifndef __CANIF_CFG_H
#define __CANIF_CFG_H

#include "Std_Types.h"
#include "CanIf_Types.h"

typedef struct
{
  CanIfHthCfg               *CanIfBufferHthRef;
  uint8                      CanIfBufferSize;
} CanIfBufferCfg;

typedef struct
{
  boolean CanIfFixedBuffer;
  boolean CanIfPrivateDlcCheck;
} CanIfPrivateCfg;

typedef struct
{
  uint32                     CanIfRxPduCanId;
  CanIfPduCanIdType          CanIfRxPduCanIdType;
  uint8                      CanIfRxPduDlc;
  // CanIfHrhCfg               *CanIfRxPduHrhIdRef;
  uint32                     CanIfRxPduId;
  boolean                    CanIfRxPduReadNotifyStatus;
  boolean                    CanIfRxPduReadData;
  CanIfPduUserConfirmationUL CanIfRxPduUserRxIndicationUL;
} CanIfRxPduCfg;

typedef struct
{
  CanIfBufferCfg            *CanIfTxPduBufferRef;
  uint32                     CanIfTxPduCanId;
  CanIfPduCanIdType          CanIfTxPduCanIdType;
  uint32                     CanIfTxPduId;
  boolean                    CanIfTxPduReadNotifyStatus;
  boolean                    CanIfTxPduTriggerTransmit;
  CanIfPduType               CanIfTxPduType;
  CanIfPduUserConfirmationUL CanIfTxPduUserConfirmationUL;
} CanIfTxPduCfg;

typedef struct
{
  uint64                     CanIfMaxRxPduCfg;
  uint64                     CanIfMaxTxPduCfg;
  
  // CanIfBufferCfg            *CanIfBuffersCfgs;
  // CanIfInitHohCfg           *CanIfDrvCfgs;
  CanIfRxPduCfg             *CanIfRxPdusCfgs;
  CanIfTxPduCfg             *CanIfTxPdusCfgs;
} CanIfInitCfg;

typedef struct {
  	// CanIfCtrlCfg* ControllerConfig;

	
	CanIfInitCfg* InitConfig;

}CanIf_ConfigType;

extern const  CanIf_ConfigType configuration;

#endif

