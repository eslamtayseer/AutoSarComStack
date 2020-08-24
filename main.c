#include "tm4c123gh6pm.h"
#include "Com/Com.h"
#include "PduR/PduR.h"
#include "CanIf/CanIf.h"
#include "Can_Tiva/Can.h"
#include "Timer_Tiva/Timer_Tiva.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "UART_Tiva/uart_tiva.h"
#include "GPIO_Tiva/gpio.h"

/**
 * main.c
 */

int main(void){
    Com_Init (&configuration);
    CanIf_Init(&CanIfConfiguration);
    Can_Init (&CanConfiguration);
    PduR_Init(&PduRConfig);
    GPIO_Init();
    Timer_Init(10000000);
    uart_init(&CanConfiguration);

    while (1)
    {
//        while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0);
////        uint64 RxSignal0;
////        if(Com_ReceiveSignal(0, &RxSignal0) == E_OK)
////        {
////
////        }
//        uint8 Signal_Data = 5;
//        Com_SendSignal(0, &Signal_Data);
//        Com_MainFunctionTx();
//        IntTrigger(INT_UART0_TM4C123);
        if(uart_receive() == E_OK)
        {
            uint64 RxSignal;
            int TxSignal;
            if(Com_ReceiveSignal(1, &RxSignal) == E_OK)
            {
                if(RxSignal == 115)
                {
                    GPIO_SwitchOnRedLed();
                    Timer_SetToggleFlag(true);
                    TxSignal = 115;
                    Com_SendSignal(0, &TxSignal);
                }
                else
                {
                    GPIO_SwitchOffRedLed();
                    Timer_SetToggleFlag(false);
                    TxSignal = 119;
                    Com_SendSignal(0, &TxSignal);
                }
            }
        }

        Com_MainFunctionTx();
    }
	return 0;
}
