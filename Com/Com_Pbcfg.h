#ifndef __COM_PBCFG_H
#define __COM_PBCFG_H

#include <stddef.h>

#include "../include/Std_Types.h"
#include "../include/ComStack_Types.h"

#define NUM_OF_SINGALS 2
#define NUM_OF_TX_PDUS 1
#define NUM_OF_RX_PDUS 1
#define NUM_OF_PDUS NUM_OF_TX_PDUS + NUM_OF_RX_PDUS

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
  const PduIdType ComPDUId;
  Com_ComTxModeMode ComTxModeMode;
  Com_PduDirectionType ComPDUDirection;
  uint8 ComTxIPduUnusedAreasDefault;
  uint8 ComPDUSize;
  uint8 ComTxModeNumberOfRepetitions;
} Com_ConfigPDUType;

typedef struct
{
  uint64 *ComPDUDataPtr;
  PduIdType ComPDUId;
  Com_ComTxModeMode ComTxModeMode;
  Com_PduDirectionType ComPDUDirection;
  Com_PDUStatusType ComPDUStatus;
  uint8 ComTxModeNumberOfRepetitions;
} Com_PDU;

extern const Com_ConfigSignalType signals[];
extern const Com_ConfigPDUType pdus[];
extern uint64 pdus_buffers[NUM_OF_PDUS];

#endif
