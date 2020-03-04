#ifndef __COM_PBCFG_H
#define __COM_PBCFG_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#define NUM_OF_SIGNALS 2

typedef struct 
{
    uint8 bitPosition;
    uint8 bitSize;
    Com_SignalIdType signalId;
    uint32 pduId;
    signalType signalType;
    const void *signalDataPtr;

}signal;

typedef struct 
{
    Com_PduIdType pduId;
    signal * signals;
    pduType pduType;
    uint16 repitions;
    ComIPduDirection_type ComIPduDirection;

}pdu;

extern  signal  signals[];
extern  pdu  pdus[];



#endif
