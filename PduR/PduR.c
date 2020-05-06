#include "PduR.h"
#include "../CanIf/CanIf.h"

Std_ReturnType PduR_ComTransmit(PduIdType id,const PduInfoType* info){
    return CanIf_Transmit(id, info);
    // return E_OK;
}

void PduR_CanIfRxIndication( PduIdType RxPduId,const PduInfoType* PduInfoPtr){
    
}