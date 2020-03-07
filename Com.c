#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "Com.h"
#include "Com_Lcfg.h"

const Com_ConfigType *ComConfiguration;

Com_PDU *ComPDUs;

Com_StatusType ComStatus = COM_UININT;
const Com_ConfigPDUType *ConfigPDUs ;
const Com_ConfigSignalType *ConfigSignals ;

int main ()
{
  Com_Init (&configuration);
  printf ("I-PDU data : %llu\n", * (uint64 *) ComPDUs[0].ComPDUDataPtr);
  uint8 * data = 111;
  printf_s("Signal sent %d \n",Com_SendSignal(0,data));
  printf ("I-PDU data : %llu\n", * (uint64 *) ComPDUs[0].ComPDUDataPtr);


  Com_DeInit();
  return 0;
}

void Com_Init (const Com_ConfigType *config)
{
  ComConfiguration = config;
  ComPDUs = (Com_PDU *) malloc (NUM_OF_PDUS * sizeof (Com_PDU));
  
  /*const Com_ConfigPDUType*/ ConfigPDUs = ComConfiguration->pdus;
  /*const Com_ConfigSignalType */ConfigSignals = ComConfiguration->signals;
  
  /* Initializing each I-PDU */
  for (int i = 0; i < NUM_OF_PDUS; i++)
  {
    ComPDUs[i].ComPDUDataPtr = (void *) malloc (sizeof (uint64));
    memset (ComPDUs[i].ComPDUDataPtr, ConfigPDUs[i].ComTxIPduUnusedAreasDefault, ConfigPDUs[i].ComPDUSize);
    ComPDUs[i].ComPDUDirection = ConfigPDUs[i].ComPDUDirection;
    ComPDUs[i].ComPDUId = ConfigPDUs[i].ComPDUId;
    ComPDUs[i].ComTxModeMode = ConfigPDUs[i].ComTxModeMode;
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
  
  ComStatus = COM_INIT;
}
uint8 Com_SendSignal (Com_SignalIdType SignalId, const void *SignalDataPtr)
{
	if (CheckSignalId(SignalId))
	{
		Com_ConfigSignalType updatedSignal = signals[SignalId];
		Com_PDU singalPDU = ComPDUs[ConfigSignals[SignalId].ComPDUId];
    printf_s("Send signal %d \n",SignalDataPtr);
    Com_SetBits (singalPDU.ComPDUDataPtr,SignalDataPtr , ConfigSignals[SignalId].ComBitPosition, ConfigSignals[SignalId].ComBitSize);
    Com_SetBits (singalPDU.ComPDUDataPtr,1 ,ConfigSignals[SignalId].ComUpdateBitPosition,1);

		switch (updatedSignal.ComSignalType)
		{
		case PENDING:
        // Not yet supported 
			break;
		case TRIGGERED:
              if(singalPDU.ComTxModeMode== MIXED||singalPDU.ComTxModeMode== DIRECT) singalPDU.ComTxModeNumberOfRepetitions++;
			break;
		case TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:
              // if(singalPDU.ComTxModeMode== MIXED||singalPDU.ComTxModeMode== DIRECT) singalPDU.ComTxModeNumberOfRepetitions=1;

			break;
		case TRIGGERD_ON_CHANGE:
              // if(singalPDU.ComTxModeMode== MIXED||singalPDU.ComTxModeMode== DIRECT) singalPDU.ComTxModeNumberOfRepetitions++;

			break;
      case TRIGGERED_WITHOUT_REPETITION:
              if(singalPDU.ComTxModeMode== MIXED||singalPDU.ComTxModeMode== DIRECT) singalPDU.ComTxModeNumberOfRepetitions =1;


			break;
		}
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}
boolean CheckSignalId(Com_SignalIdType id)
{
	if (id < NUM_OF_SINGALS)
		return TRUE;
	return FALSE;
} 

Std_ReturnType Com_TriggeredIPDUSend (Com_PduIdType PduId)
{
  // const Com_ConfigSignalType *ConfigSignals = ComConfiguration->signals;
  
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

void Com_MainFunctionTx (void)
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
          if(ComPDUs[i].ComTxModeNumberOfRepetitions>0){
           if(Com_TriggeredIPDUSend(&ComPDUs[i])==E_NOT_OK) {
             ComPDUs[i].ComTxModeNumberOfRepetitions--;
           }
           else{
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

void Com_SetBits (void *DataPtr, uint32 Data, uint64 DataStartPosition, uint8 DataSize)
{
  printf("send bits data %d \n", Data);
  printf("send bits data start position %d \n", DataStartPosition);
  printf("send bits data size %d \n", DataSize);
  int mask = (int) (pow (2, DataSize) - 1);
  * (uint64 *)DataPtr = (* (uint64 *)DataPtr & ~(mask << DataStartPosition)) | ((Data << DataStartPosition) & (mask << DataStartPosition));
  printf("send bits data pointer %d \n", DataPtr);

}

void Com_DeInit (void)
{
  /* This function should free all of the allocated memory used by the COM Module */ 
  for (int i = 0; i < NUM_OF_PDUS; i++)
  {
    free (ComPDUs[i].ComPDUDataPtr);
  }
  
  free ((void *)ComPDUs);
  ComStatus = COM_UININT;
}
