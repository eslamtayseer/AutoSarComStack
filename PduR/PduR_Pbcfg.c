#include "PduR_Pbcfg.h"


 const PduRDestPdu CanIfDestinationPdu ={
    .PduRDestPduHandleId=0
};

 const PduRSrcPdu ComSourcePdu={
    .PduRSourcePduHandleId =0
};
 const PduRDestPdu comDestinationPdu ={
    .PduRDestPduHandleId=1
};

 const PduRSrcPdu canIfSourcePdu={
    .PduRSourcePduHandleId =1
};
const PduRRoutingPath routingPathes []={
    {
        .destination= &CanIfDestinationPdu,
        .source = &ComSourcePdu
    },
    {
        .destination= &comDestinationPdu,
        .source = &canIfSourcePdu
    }
};

const PduRRoutingTable PduRConfig ={
    .pathes =&routingPathes[0]
} ;
// const uint8 ComTxPduRMap[NUM_OF_PDUS];
// const uint8 CanIfRxPduRMap[NO_OF_HRH];
// const uint8 DestinationMap[NUM_OF_PDUR_PDUS];

// ComTxPduRMap[pdus[0].ComPDUId]= CanIfDestinationPdu.PduRDestPduHandleId;
// CanIfRxPduRMap[canIfSourcePdu.PduRSourcePduHandleId]= comDestinationPdu.PduRDestPduHandleId;
// DestinationMap[0]=  CanIfConfiguration->InitConfig->CanIfRxPdusCfgs[0].CanIfTxPduId;
// DestinationMap[1]=  pdus[1].ComPDUId;
