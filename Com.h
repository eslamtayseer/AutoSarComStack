#ifndef __COM_H
#define __COM_H

// #include "Std_Types.h"
#include "Com_Lcfg.h"
// #include "ComStack_Types.h"

#define COM_SERVICE_NOT_AVAILABLE 0x80
#define COM_BUSY 0x81


typedef enum
{
    COM_INIT,
    COM_UNINIT
} Com_StatusType;

void Com_Init(
 const Com_ConfigType* config
);
uint8 Com_SendSignal(
 Com_SignalIdType SignalId,
 const void* SignalDataPtr
);
uint8 Com_ReceiveSignal(
 Com_SignalIdType SignalId,
 void* SignalDataPtr
);

void Com_MainFunctionTx(
 void
);

Std_ReturnType Com_TriggerIPDUSend(
 Com_PduIdType PduId
);

void Com_TxConfirmation(
 Com_PduIdType TxPduId
);
boolean checkSignalID(
Com_SignalIdType id
);



#endif