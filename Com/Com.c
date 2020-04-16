#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Com.h"
#include "../PduR/PduR.h"

const Com_ConfigType *ComConfiguration;

Com_PDU *ComPDUs;

Com_StatusType ComStatus = COM_UININT;

int main()
{
  Com_Init(&configuration);
  uint64 SignalValue = 0;
  uint32 data = 0x0A;
  Com_SendSignal(0,&data);
  Com_MainFunctionTx();

  // if (Com_ReceiveSignal(0, &SignalValue) == E_OK)
  //   printf("Receive Signal 0 %llu\n", SignalValue);
  // else
  //   printf("Not Successful\n");
  Com_DeInit();
  return 0;
}

void Com_Init(const Com_ConfigType *config)
{
  ComConfiguration = config;
  ComPDUs = (Com_PDU *)malloc(NUM_OF_PDUS * sizeof(Com_PDU));

  const Com_ConfigPDUType *ConfigPDUs = ComConfiguration->pdus;
  const Com_ConfigSignalType *ConfigSignals = ComConfiguration->signals;

  /* Initializing each I-PDU */
  for (int i = 0; i < NUM_OF_PDUS; i++)
  {
    ComPDUs[i].ComPDUDataPtr = (void *)malloc(sizeof(uint64));
    memset(ComPDUs[i].ComPDUDataPtr, ConfigPDUs[i].ComTxIPduUnusedAreasDefault, ConfigPDUs[i].ComPDUSize);
    ComPDUs[i].ComPDUDirection = ConfigPDUs[i].ComPDUDirection;
    ComPDUs[i].ComPDUId = ConfigPDUs[i].ComPDUId;
    ComPDUs[i].ComTxModeMode = ConfigPDUs[i].ComTxModeMode;
    ComPDUs[i].ComPDUStatus = STARTED;
  }

  /* Initializing each signal in each I-PDU */
  for (int i = 0; i < NUM_OF_SINGALS; i++)
  {
    /* initialization of signals with ComSignalInitValue */
    Com_SetBits(ComPDUs[ConfigSignals[i].ComPDUId].ComPDUDataPtr, ConfigSignals[i].ComSignalInitValue,
                ConfigSignals[i].ComBitPosition, ConfigSignals[i].ComBitSize);

    /* Clear update-bits of each signal */
    Com_SetBits(ComPDUs[ConfigSignals[i].ComPDUId].ComPDUDataPtr, 0, ConfigSignals[i].ComUpdateBitPosition, 1);
  }

  ComStatus = COM_INIT;
}

uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
  const Com_ConfigSignalType *ConfigSignals = ComConfiguration->signals;

  if (CheckSignalId(SignalId))
  {
    Com_ConfigSignalType updatedSignal = signals[SignalId];
    Com_PDU singalPDU = ComPDUs[ConfigSignals[SignalId].ComPDUId];
    Com_SetBits(singalPDU.ComPDUDataPtr, *(uint32 *)SignalDataPtr, ConfigSignals[SignalId].ComBitPosition, ConfigSignals[SignalId].ComBitSize);
    Com_SetBits(singalPDU.ComPDUDataPtr, 1, ConfigSignals[SignalId].ComUpdateBitPosition, 1);

    switch (updatedSignal.ComSignalType)
    {
    case PENDING:
      // Not yet supported
      break;
    case TRIGGERED:
      if (singalPDU.ComTxModeMode == MIXED || singalPDU.ComTxModeMode == DIRECT)
        singalPDU.ComTxModeNumberOfRepetitions++;
      break;
    case TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:
      // if(singalPDU.ComTxModeMode== MIXED||singalPDU.ComTxModeMode== DIRECT) singalPDU.ComTxModeNumberOfRepetitions=1;
      break;
    case TRIGGERD_ON_CHANGE:
      // if(singalPDU.ComTxModeMode== MIXED||singalPDU.ComTxModeMode== DIRECT) singalPDU.ComTxModeNumberOfRepetitions++;
      break;
    case TRIGGERED_WITHOUT_REPETITION:
      if (singalPDU.ComTxModeMode == MIXED || singalPDU.ComTxModeMode == DIRECT)
        singalPDU.ComTxModeNumberOfRepetitions = 1;
      break;
    }
    return E_OK;
  }
  else
  {
    return E_NOT_OK;
  }
}

uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr)
{
  if (!CheckSignalId(SignalId))
    return E_NOT_OK;

  const Com_ConfigSignalType *ConfigSignals = ComConfiguration->signals;

  uint8 PduId = ConfigSignals[SignalId].ComPDUId;
  if (ComPDUs[PduId].ComPDUDirection != RECIEVE)
    return E_NOT_OK;

  uint64 mask = (uint64)(pow(2, ConfigSignals[SignalId].ComBitSize) - 1);
  uint64 value = *(uint64 *)ComPDUs[PduId].ComPDUDataPtr & mask;
  *(uint64 *)SignalDataPtr = value;

  return E_OK;
}

boolean CheckSignalId(Com_SignalIdType id)
{
  if (id < NUM_OF_SINGALS)
    return TRUE;
  return FALSE;
}

Std_ReturnType Com_TriggeredIPDUSend(PduIdType PduId)
{
  const Com_ConfigSignalType *ConfigSignals = ComConfiguration->signals;

  if (ComPDUs[PduId].ComPDUStatus != STARTED)
  {
    return E_NOT_OK;
  }

  /* TODO: sending IPDU to PDU-Router */
  PduInfoType info = {
      .SduDataPtr = ComPDUs[PduId].ComPDUDataPtr,
      .MetaDataPtr = NULL,
      .SduLength = 8};
  if (PduR_ComTransmit(PduId, &info) == E_OK)
  {
    printf("Pdur received %u \n",*(uint64 *)ComPDUs[PduId].ComPDUDataPtr);
    /* Clearing signals update-bits */
    for (int i = 0; i < NUM_OF_SINGALS; i++)
    {
      if (ConfigSignals[i].ComPDUId == PduId)
      {
        Com_SetBits(ComPDUs[ConfigSignals[i].ComPDUId].ComPDUDataPtr, 0, ConfigSignals[i].ComUpdateBitPosition, 1);
      }
    }

    return E_OK;
  }
  else
    return E_NOT_OK;
}

void Com_MainFunctionTx(void)
{
  if (ComStatus != COM_INIT)
  {
    return;
  }

  for (int i = 0; i < NUM_OF_PDUS; i++)
  {
    switch (ComPDUs[i].ComTxModeMode)
    {
    case DIRECT:
      if (ComPDUs[i].ComTxModeNumberOfRepetitions > 0 && ComPDUs[i].ComPDUDirection == SEND)
      {
        if (Com_TriggeredIPDUSend(ComPDUs[i].ComPDUId) == E_OK)
        {
          ComPDUs[i].ComTxModeNumberOfRepetitions--;
        }
        else
        {
          //Not yet supported
        }
      }
      break;
    case PERIODIC:
      //check timer
      //send in case of timer finished

      break;
    case MIXED:
      // Not yet supoorted
      break;
    }
  }
}

void Com_SetBits(void *DataPtr, uint32 Data, uint8 DataStartPosition, uint8 DataSize)
{
  uint64 mask = (uint64)(pow(2, DataSize) - 1);
  *(uint64 *)DataPtr = (*(uint64 *)DataPtr & ~(mask << DataStartPosition)) | ((Data << DataStartPosition) & (mask << DataStartPosition));
}

void Com_TxConfirmation(PduIdType PduId)
{
}

void Com_DeInit(void)
{
  /* This function should free all of the allocated memory used by the COM Module */
  for (int i = 0; i < NUM_OF_PDUS; i++)
  {
    free(ComPDUs[i].ComPDUDataPtr);
  }

  free((void *)ComPDUs);
  ComStatus = COM_UININT;
}
