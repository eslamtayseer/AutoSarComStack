#include "tm4c123gh6pm.h"
#include "Com/Com.h"
#include "PduR/PduR.h"
#include "CanIf/CanIf.h"
#include "Can_Tiva/Can.h"
#include "Timer_Tiva/Timer_Tiva.h"

/**
 * main.c
 */

int main(void)
{
    Com_Init (&configuration);
    CanIf_Init(&CanIfConfiguration);
    Can_Init (&CanConfiguration);
    PduR_Init(&PduRConfig);
    Timer_Init(1000);

    while (1)
    {
        while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);
//        uint64 RxSignal0;
//        if(Com_ReceiveSignal(0, &RxSignal0) == E_OK)
//        {
//
//        }
        uint8 Signal_Data = 5;
        Com_SendSignal(0, &Signal_Data);
        Com_MainFunctionTx();
    }
	return 0;
}
