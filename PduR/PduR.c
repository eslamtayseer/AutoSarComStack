#include "PduR.h"
#include "../CanIf/CanIf.h"
#include "PduR_Pbcfg.h"
#include "../Com/Com.h"
 uint8 ComTxPduRMap[NUM_OF_PDUS];
 uint8 CanIfRxPduRMap[NO_OF_HRH];
 uint8 DestinationMap[NUM_OF_PDUR_PDUS];

const PduRRoutingTable* PduRConfiguration;

void PduR_Init(const PduRRoutingTable* ConfigPtr){
    PduRConfiguration = ConfigPtr;
ComTxPduRMap[pdus[0].ComPDUId]= ConfigPtr->pathes[0].source->PduRSourcePduHandleId;
CanIfRxPduRMap[CanIfConfiguration.InitConfig->CanIfRxPdusCfgs[0].CanIfRxPduId]= ConfigPtr->pathes[1].source->PduRSourcePduHandleId;
DestinationMap[0]=  CanIfConfiguration.InitConfig->CanIfTxPdusCfgs[0].CanIfTxPduId;
DestinationMap[1]=  pdus[1].ComPDUId;
}

Std_ReturnType PduR_ComTransmit(PduIdType id,const PduInfoType* info){
    if (id> NUM_OF_PDUR_PDUS) return E_NOT_OK;
    uint8 destination = PduRConfiguration->pathes[id].destination->PduRDestPduHandleId;
    uint8 destinationID= DestinationMap[destination];

    return CanIf_Transmit(destinationID, info);
    // return E_OK;
}

void PduR_CanIfRxIndication( PduIdType RxPduId,const PduInfoType* PduInfoPtr){
    if(RxPduId>NUM_OF_PDUR_PDUS) return;
    uint8 destination = PduRConfiguration->pathes[RxPduId].destination->PduRDestPduHandleId;
    uint8 destinationID= DestinationMap[destination];
    Com_RxIndication(destinationID, PduInfoPtr);
}
