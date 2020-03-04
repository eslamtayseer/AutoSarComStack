
#include "Com.h"
 //#include "Com_Pbcfg.h"
#include <stdio.h>
//  signal signals[];

int main()
{
	signal s = signals[1];
	int x = s.bitPosition;
	printf("signal position : %d", x);
	return 0;
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