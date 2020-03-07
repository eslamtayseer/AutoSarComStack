#include "Com_Pbcfg.h"

const Com_ConfigSignalType signals[] = 
{
  {
    .ComBitPosition = 0,
    .ComUpdateBitPosition = 8,
    .ComBitSize = 8,
    .ComSignalId = 0,
    .ComPDUId = 0,
    .ComSignalType = TRIGGERED_WITHOUT_REPETITION,
    .ComSignalInitValue = 0
  },
  {
    .ComBitPosition = 9,
    .ComUpdateBitPosition = 10,
    .ComBitSize = 1,
    .ComSignalId = 0,
    .ComPDUId = 0,
    .ComSignalType = TRIGGERED_WITHOUT_REPETITION,
    .ComSignalInitValue = 0
  }
};

const Com_ConfigPDUType pdus[] =
{
  {
    .ComPDUId = 0,
    .ComTxModeMode = DIRECT,
    .ComPDUDirection = SEND,
    .ComTxIPduUnusedAreasDefault = 255,
    .ComPDUSize = 8,
    .ComTxModeNumberOfRepetitions= 0
  }
};
