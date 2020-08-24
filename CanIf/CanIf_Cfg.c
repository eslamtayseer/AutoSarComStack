#include "CanIf_Cfg.h"

 CanIfPrivateCfg PrivateCfg []={

 };

CanIf_CanIfCtrlCfg CanInterfaceControllersCfgs[] =
{
  {
    .CanIfCtrlCanCtrlRef = &CanControllers[0],
    .CanIfCtrlId = 0
  }
};

CanIf_CanIfHthCfg CanInterfaceHthCfgs[] =
{
 {
  .CanIfHrhCanCtrlIdRef = &CanInterfaceControllersCfgs[0],
  .CanIfHthIdSymRef = &CanHardwareObjects[1]
 }
};

CanIf_CanIfHrhCfg CanInterfaceHrhCfgs[] =
{
 {
  .CanIfHrhCanCtrlIdRef = &CanInterfaceControllersCfgs[0],
  .CanIfHthIdSymRef = &CanHardwareObjects[0]
 }
};

CanIf_CanIfInitHohCfg CanInterfaceHohCfgs[] =
{
 {
  .CanIfHthCfg = CanInterfaceHthCfgs,
  .CanIfHrhCfg = CanInterfaceHrhCfgs
 }
};

CanIfBufferCfg CanIfBuffer[] =
{
 {
  .CanIfBufferHthRef = CanInterfaceHthCfgs,
  .CanIfBufferSize = 0
 }
};

CanIfRxPduCfg  RxPduCfg[] = { {
 .CanIfRxPduCanId = 0,
 .CanIfRxPduCanIdType = STANDARD_CAN,
 .CanIfRxPduDlc = TRUE,
 .CanIfRxPduHrhIdRef = &CanInterfaceHrhCfgs[0],
 .CanIfRxPduId = 0,
 .CanIfRxPduReadNotifyStatus = FALSE,
 .CanIfRxPduReadData = FALSE,
 .CanIfRxPduUserRxIndicationUL = PDUR
 }
};
 CanIfTxPduCfg  TxPduCfg[]={
{
  .CanIfTxPduBufferRef = &CanIfBuffer[0],
  .CanIfTxPduCanId = 0,
  .CanIfTxPduCanIdType = STANDARD_CAN,
  .CanIfTxPduId = 0,
  .CanIfTxPduReadNotifyStatus = FALSE,
  .CanIfTxPduTriggerTransmit = FALSE,
  .CanIfTxPduType = STATIC,
  .CanIfTxPduUserConfirmationUL = PDUR
  }
};
 CanIfInitCfg initCfg[] = { {
   //.CanIfMaxBufferSize = 2,
   .CanIfMaxRxPduCfg = 1,
   .CanIfMaxTxPduCfg = 1,

   .CanIfBuffersCfgs = CanIfBuffer,
   .CanIfInitHohCfgs = CanInterfaceHohCfgs,
   .CanIfRxPdusCfgs = RxPduCfg,
   .CanIfTxPdusCfgs = TxPduCfg
   }
};
const CanIf_ConfigType CanIfConfiguration ={
    .InitConfig =&initCfg[0],
    .ControllerConfig = CanInterfaceControllersCfgs
};
