#include "Com_Pbcfg.h"

const Com_ConfigSignalType signals[] = 
{
  {
    .ComBitPosition = 0,
    .ComUpdateBitPosition = 1,
    .ComBitSize = 1,
    .ComSignalId = 0,
    .ComPDUId = 0,
    .ComSignalType = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
    .ComSignalInitValue = 0
  },
  {
    .ComBitPosition = 4,
    .ComUpdateBitPosition = 5,
    .ComBitSize = 1,
    .ComSignalId = 0,
    .ComPDUId = 0,
    .ComSignalType = TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
    .ComSignalInitValue = 0
  }
};

const Com_ConfigPDUType pdus[] =
{
  {
    .ComPDUId = 0,
    .ComPDUType = DIRECT,
    .ComPDUDirection = SEND,
    .ComTxIPduUnusedAreasDefault = 255,
    .ComPDUSize = 8
  }
};
