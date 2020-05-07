#ifndef __COM_H
#define __COM_H

#include "Com_Lcfg.h"

typedef enum
{
  COM_INIT,
  COM_UININT
} Com_StatusType;

void           Com_Init                 (const Com_ConfigType *config);
uint8          Com_SendSignal           (Com_SignalIdType      SignalId,
                                         const void           *SignalDataPtr);
uint8          Com_ReceiveSignal        (Com_SignalIdType      SignalId,
                                         void                 *SignalDataPtr);
void           Com_MainFunctionTx       (void);
Std_ReturnType Com_TriggeredIPDUSend    (PduIdType         PduId);
boolean        CheckSignalId            (Com_SignalIdType      id);
void           Com_SetBits              (uint64                 *DataPtr,
                                         uint64                Data,
                                         uint8                DataStartPosition,
                                         uint8                 DataSize);
void           Com_TxConfirmation       (PduIdType         PduId);
void           Com_DeInit               (void);
void           Com_RxIndication(PduIdType RxPduId,const PduInfoType* PduInfoPtr);
#endif
