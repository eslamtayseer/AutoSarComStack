#ifndef __PDUR_PBCFG_H
#define __PDUR_PBCFG_H

#include "../include/Std_Types.h"
#include "../Com/Com_Pbcfg.h"
#include "../CanIf/CanIf_Cfg.h"

#define NUM_OF_PDUR_PDUS 2


typedef struct 
{
    uint8 PduRDestPduHandleId;
}PduRDestPdu;

typedef struct {
   uint8 PduRSourcePduHandleId;
}PduRSrcPdu;

typedef struct 
{
    const PduRDestPdu* destination;
    const PduRSrcPdu* source;
}PduRRoutingPath;

typedef struct
{
PduRRoutingPath *pathes;
}PduRRoutingTable;

// extern const uint8 ComTxPduRMap[NUM_OF_PDUS];
// extern const uint8 CanIfRxPduRMap[NO_OF_HRH];
// extern const uint8 DestinationMap[NUM_OF_PDUR_PDUS];
extern  uint8 ComTxPduRMap[NUM_OF_PDUS];
extern  uint8 CanIfRxPduRMap[NO_OF_HRH];
extern  uint8 DestinationMap[NUM_OF_PDUR_PDUS];
extern const PduRRoutingTable PduRConfig;

#endif
