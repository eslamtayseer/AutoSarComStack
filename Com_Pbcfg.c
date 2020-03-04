#include "Com_Pbcfg.h"

  signal Signals []={
    {
        .bitPosition= 0,
        .bitSize = 1,
        .signalId = 0,
        .pduId = 0,
        .signalType = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
        // .signalDataPtr= 0,
    },
    {
        .bitPosition = 1,
        .bitSize = 1,
        .signalId = 1,
        .pduId = 0,
        .signalType = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
        // .signalDataPtr= 0,
    }
};

  pdu Pdus[]={
    {
    .pduId =1,
    .signals = signals,
    .pduType=MIXED,
    .repitions=10,
    .ComIPduDirection = RECIEVE
    },
    {
    .pduId =1,
    .signals = signals,
    .pduType=MIXED,
    .repitions=2,
    .ComIPduDirection = SEND
    }
};