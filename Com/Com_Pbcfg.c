#include "Com_Pbcfg.h"

const Com_ConfigSignalType signals[] = 
{
  {
    .ComBitPosition = 0,
    .ComUpdateBitPosition = 7,
    .ComBitSize = 7,
    .ComSignalId = 0,
    .ComPDUId = 0,
    .ComSignalType = TRIGGERED_WITHOUT_REPETITION,
    .ComSignalInitValue = 10
  },
  {
   .ComBitPosition = 0,
   .ComUpdateBitPosition = 7,
   .ComBitSize = 7,
   .ComSignalId = 1,
   .ComPDUId = 1,
   .ComSignalType = TRIGGERED_WITHOUT_REPETITION,
   .ComSignalInitValue = 10
  }
};

uint64 pdus_buffers[NUM_OF_PDUS];

const Com_ConfigPDUType pdus[] =
{
  {
    .ComPDUId = 0,
    .ComTxModeMode = DIRECT,
    .ComPDUDirection = SEND,
    .ComTxIPduUnusedAreasDefault = 255,
    .ComPDUSize = 8,
    .ComTxModeNumberOfRepetitions= 0
  },
    {
    .ComPDUId = 1,
    .ComTxModeMode = DIRECT,
    .ComPDUDirection = RECIEVE,
    .ComTxIPduUnusedAreasDefault = 255,
    .ComPDUSize = 8,
    .ComTxModeNumberOfRepetitions= 0
  }

};
