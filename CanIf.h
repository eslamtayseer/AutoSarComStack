#ifndef __CAN_IF_H
#define __CAN_IF_H

#include "ComStack_Types.h"
#include "CanIf_Types.h"
#include "CanIf_Cfg.h"

void                CanIf_Init               (CanIf_ConfigType   *ConfigPtr);
void                CanIf_DeInit             (void);
Std_ReturnType      CanIf_Transmit           (PduIdType           CanIfTxSduId,
                                              const PduInfoType  *CanIfTxInfoPtr);
Std_ReturnType      CanIf_ReadRxPduData      (PduIdType           CanIfRxSduId,
                                              PduInfoType        *CanIfRxInfoPtr);
void                CanIf_TxConfirmation     (PduIdType           CanTxPduId);
void                CanIf_RxIndication       (const Can_HwType   *Mailbox,
                                              const PduInfotype  *PduInfoPtr);

#endif
