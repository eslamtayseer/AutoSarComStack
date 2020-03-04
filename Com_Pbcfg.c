#include "Com_Pbcfg.h"

const signal signals []={
    {
        .bitPosition= 0,
        .ComUpdateBitPosition = 2,
        .bitSize = 1,
        .signalId = 0,
        .pduId = 0,
        .signalType = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
        .ComSignalInitValue = 0
        // .signalDataPtr= 0,
    },
    {
        .bitPosition = 3,
        .ComUpdateBitPosition = 4
        .bitSize = 1,
        .signalId = 1,
        .pduId = 0,
        .signalType = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
        .ComSignalInitValue = 0
        // .signalDataPtr= 0,
    }
};

const pdu pdus[]={
    {
        .pduId =1,
        .signals = signals,
        .pduType=MIXED,
        .repitions=10,
        .ComIPduDirection = RECIEVE,
        .ComTxIPduUnusedAreasDefault = 255
    },
    {
        .pduId =1,
        .signals = signals,
        .pduType=MIXED,
        .repitions=2,
        .ComIPduDirection = SEND,
        .ComTxIPduUnusedAreasDefault = 255
    }
};
