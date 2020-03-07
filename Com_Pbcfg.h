#ifndef __COM_PBCFG_H
#define __COM_PBCFG_H

#include <stddef.h>

#include "Std_Types.h"
#include "ComStack_Types.h"

#define NUM_OF_SINGALS 2
#define NUM_OF_PDUS 1

typedef struct
{
  uint8 ComBitPosition;
  uint8 ComUpdateBitPosition;
  uint8 ComBitSize;
  Com_SignalIdType ComSignalId;
  uint32 ComPDUId;
  Com_SignalType ComSignalType;
  uint32 ComSignalInitValue;
} Com_ConfigSignalType;

typedef struct
{
  Com_PduIdType ComPDUId;
  Com_ComTxModeMode ComTxModeMode;
  Com_PduDirectionType ComPDUDirection;
  uint8 ComTxIPduUnusedAreasDefault;
  uint8 ComPDUSize;
} Com_ConfigPDUType;

typedef struct
{
  void *ComPDUDataPtr;
  uint8 ComPDUId;
  Com_ComTxModeMode ComTxModeMode;
  Com_PduDirectionType ComPDUDirection;
  Com_PDUStatusType ComPDUStatus;
} Com_PDU;

extern const Com_ConfigSignalType signals[];
extern const Com_ConfigPDUType pdus[];

#endif
