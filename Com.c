#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Com.h"
#include "Com_Lcfg.h"

const Com_ConfigType *ComConfiguration;

Com_PDU *ComPDUs;

int main ()
{
  Com_Init (&configuration);
  printf ("I-PDU data : %llu\n", * (uint64 *) ComPDUs[0].ComPDUDataPtr);
  return 0;
}

void Com_Init (const Com_ConfigType *config)
{
  ComConfiguration = config;
  ComPDUs = (Com_PDU *) malloc (NUM_OF_PDUS * sizeof (Com_PDU));
  
  const Com_ConfigPDUType *ConfigPDUs = ComConfiguration->pdus;
  const Com_ConfigSignalType *ConfigSignals = ComConfiguration->signals;
  
  /* Initializing each I-PDU */
  for (int i = 0; i < NUM_OF_PDUS; i++)
  {
    ComPDUs[i].ComPDUDataPtr = (void *) malloc (sizeof (void));
    memset (ComPDUs[i].ComPDUDataPtr, ConfigPDUs[i].ComTxIPduUnusedAreasDefault, ConfigPDUs[i].ComPDUSize);
    ComPDUs[i].ComPDUDirection = ConfigPDUs[i].ComPDUDirection;
    ComPDUs[i].ComPDUId = ConfigPDUs[i].ComPDUId;
    ComPDUs[i].ComPDUType = ConfigPDUs[i].ComPDUType;
    ComPDUs[i].ComPDUStatus = STARTED;
  }
  
  /* Initializing each signal in each I-PDU */
  for (int i = 0; i < NUM_OF_SINGALS; i++)
  {
    /* initialization of signals with ComSignalInitValue */
    Com_SetBits (ComPDUs[ConfigSignals[i].ComPDUId].ComPDUDataPtr, ConfigSignals[i].ComSignalInitValue, \
                              ConfigSignals[i].ComBitPosition, ConfigSignals[i].ComBitSize);
    
    /* Clear update-bits of each signal */
    Com_SetBits (ComPDUs[ConfigSignals[i].ComPDUId].ComPDUDataPtr, 0, ConfigSignals[i].ComUpdateBitPosition, 1);
  }
}

Std_ReturnType Com_TriggeredIPDUSend (Com_PduIdType PduId)
{
  const Com_ConfigSignalType *ConfigSignals = ComConfiguration->signals;
  
  if (ComPDUs[PduId].ComPDUStatus != STARTED)
  {
    return E_NOT_OK;
  }
  
  /* TODO: sending IPDU to PDU-Router */
  /* Clearing signals update-bits */
  for (int i = 0; i < NUM_OF_SINGALS; i++)
  {
    Com_SetBits (ComPDUs[ConfigSignals[i].ComPDUId].ComPDUDataPtr, 0, ConfigSignals[i].ComUpdateBitPosition, 1);
  }
  
  return E_OK;
}

void Com_SetBits (void *DataPtr, uint32 Data, uint64 DataStartPosition, uint8 DataSize)
{
  int mask = (int) (pow (2, DataSize) - 1);
  * (uint64 *)DataPtr = (* (uint64 *)DataPtr & ~(mask << DataStartPosition)) | ((Data << DataStartPosition) & (mask << DataStartPosition));
}
