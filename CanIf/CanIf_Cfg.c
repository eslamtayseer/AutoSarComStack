#include "CanIf_Cfg.h"

// CanIfPrivateCfg PrivateCfg []={

// };

CanIfRxPduCfg  RxPduCfg[] = { {
 .CanIfRxPduCanId = 0,
 .CanIfRxPduCanIdType = STANDARD_CAN,
 .CanIfRxPduDlc = TRUE,
 // CanIfHrhCfg               *CanIfRxPduHrhIdRef;
 .CanIfRxPduId = 0,
 .CanIfRxPduReadNotifyStatus = FALSE,
 .CanIfRxPduReadData = FALSE,
 .CanIfRxPduUserRxIndicationUL = PDUR
 }
};
 CanIfTxPduCfg  TxPduCfg[]={
	 {
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

   // CanIfBufferCfg            *CanIfBuffersCfgs;
   // CanIfInitHohCfg           *CanIfDrvCfgs;
   .CanIfRxPdusCfgs = &RxPduCfg[0],
   .CanIfTxPdusCfgs = &TxPduCfg[0]
   }
};
const CanIf_ConfigType CanIfConfiguration ={
    .InitConfig =&initCfg[0]
};
