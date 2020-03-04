#include "Com.h"
#include <stdio.h>

const Com_ConfigType *ComConfig;
signal *ComSignals;
pdu *ComIPDUs;

int main()
{
	// signal s = signals[1];
	// int x = s.bitPosition;
	// printf("signal position : %d", x);
	Com_Init(&configuration);
	return 0;
}

void Com_Init(const Com_ConfigType *config)
{
        ComConfig = config;
        const pdu *IPDUs = ComConfig->comPdus;
		ComIPDUs = (pdu*)malloc(NUM_OF_IPDUS * sizeof(pdu)); 
		for(int i =0;i<NUM_OF_IPDUS;i++){
			ComIPDUs[i].ComIPduDirection=IPDUs[i].ComIPduDirection;
			ComIPDUs[i].ComTxIPduUnusedAreasDefault=IPDUs[i].ComTxIPduUnusedAreasDefault;
			ComIPDUs[i].pduId=IPDUs[i].pduId;
			ComIPDUs[i].pduType=IPDUs[i].pduType;
			ComIPDUs[i].repitions=IPDUs[i].repitions;
			// ComIPDUs[i].signals=IPDUs[i].signals;
			for (int j =0; IPDUs[i].signals+j != NULL;j++){
				ComIPDUs[i].signals[j].bitPosition=IPDUs[i].signals[j].bitPosition;
				ComIPDUs[i].signals[j].bitSize=IPDUs[i].signals[j].bitSize;
				ComIPDUs[i].signals[j].ComSignalInitValue=IPDUs[i].signals[j].ComSignalInitValue;
				ComIPDUs[i].signals[j].ComUpdateBitPosition=IPDUs[i].signals[j].ComUpdateBitPosition;
				ComIPDUs[i].signals[j].pduId=IPDUs[i].signals[j].pduId;
				ComIPDUs[i].signals[j].signalDataPtr=IPDUs[i].signals[j].signalDataPtr;
				ComIPDUs[i].signals[j].signalId=IPDUs[i].signals[j].signalId;
				ComIPDUs[i].signals[j].signalType=IPDUs[i].signals[j].signalType;

				printf_s("Com signal bit position %d \n",ComIPDUs[i].signals[j].bitPosition);

			}
			printf_s("comipdu direction %d \n",ComIPDUs[i].ComIPduDirection);
		}


		// printf_s("Direction %d",IPDUs[0].ComIPduDirection);
}

uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
	if (checkSignalID(SignalId))
	{
		signal updatedSignal = signals[SignalId];
		updatedSignal.signalDataPtr = SignalDataPtr;
		pdu updatedSignalPdu=pdus[updatedSignal.pduId];
		

		switch (updatedSignal.signalType)
		{
		case PENDING:

			break;
		case TRIGGERED:

			break;
		case TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:
			updatedSignalPdu.repitions++;

			break;
		case TRIGGERD_ON_CHANGE:

			break;
		}
		return E_OK;
	}
	else
	{
		return E_NOT_OK;
	}
}
boolean checkSignalID(Com_SignalIdType id)
{
	if (id < NUM_OF_SIGNALS)
		return TRUE;
	return FALSE;
}
