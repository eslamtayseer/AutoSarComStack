#include "../include/Std_Types.h"
#include"../include/ComStack_Types.h"

Std_ReturnType PduR_ComTransmit(
 PduIdType id,
 const PduInfoType* info
);
void PduR_CanIfRxIndication(
 PduIdType RxPduId,
 const PduInfoType* PduInfoPtr
);

