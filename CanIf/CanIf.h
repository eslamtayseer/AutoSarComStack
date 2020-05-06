#ifndef __CAN_IF_H
#define __CAN_IF_H

#include "../include/ComStack_Types.h"
#include "CanIf_Types.h"
#include "CanIf_Cfg.h"
#include "../Can_Tiva/Can_GeneralTypes.h"

void                CanIf_Init               (CanIf_ConfigType   *ConfigPtr);
void                CanIf_DeInit             (void);
Std_ReturnType      CanIf_Transmit           (PduIdType           CanIfTxSduId,
                                              const PduInfoType  *CanIfTxInfoPtr);
Std_ReturnType      CanIf_ReadRxPduData      (PduIdType           CanIfRxSduId,
                                              PduInfoType        *CanIfRxInfoPtr);
void                CanIf_TxConfirmation     (PduIdType           CanTxPduId);
void                CanIf_RxIndication       (const Can_HwType   *Mailbox,
                                              const PduInfoType  *PduInfoPtr);
void CanIf_RxIndication(const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr);


#endif
