#include "Can.h"
#include "inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"


const Can_ConfigType* configuration;

tCANMsgObject CAN0RxMessage [NO_OF_HRH];
//tCANMsgObject CAN0TxMessage [NO_OF_HTH];

void Hardware_Init(){
tCANBitClkParms BitTimeParams;
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));
GPIOPinConfigure(GPIO_PE4_CAN0RX);
GPIOPinConfigure(GPIO_PE5_CAN0TX);
GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0));
CANInit(configuration->CanConfigSetConfig->CanController->CanControllerBaseAddress);
BitTimeParams.ui32SyncPropPhase1Seg=(configuration->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerSeg1) + (configuration->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerPropSeg);
BitTimeParams.ui32Phase2Seg=configuration->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerSeg2;
BitTimeParams.ui32SJW=configuration->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerSyncJumpWidth;
BitTimeParams.ui32QuantumPrescaler= SysCtlClockGet()/((BitTimeParams.ui32SyncPropPhase1Seg
                     +BitTimeParams.ui32Phase2Seg+1U)
                     *(configuration->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerBaudRate));
CANBitTimingSet(Configuration->ControllerConfig->CanIfCtrlCanCtrlRef->CanControllerBaseAddress,&BitTimeParams);
//CANBitRateSet(configuration->CanConfigSetConfig->CanController->CanControllerBaseAddress, SysCtlClockGet(), configuration->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerBaudRate);
CANIntEnable(configuration->CanConfigSetConfig->CanController->CanControllerBaseAddress, CAN_INT_MASTER | CAN_INT_STATUS);
//Transmit_Message_Init();
Receive_Message_Init();
IntEnable(configuration->CanConfigSetConfig->CanController->CanControllerBaseAddress);
CANEnable(configuration->CanConfigSetConfig->CanController->CanControllerBaseAddress);
}
//void Transmit_Message_Init(){
//    Can_CanHardwareObject* HOHs = configuration->CanConfigSetConfig->CanHardwareObject;
//
//    for (uint8 i=0 , j=0;i<NUM_OF_HOH;i++){
//        if (HOHs[i].CanObjectType==TRANSMIT){
//
//                CAN0TxMessage[j].ui32MsgID = HOHs[i].CanObjectId;
//                CAN0TxMessage[j].ui32MsgIDMask = 0;
//                CAN0TxMessage[j].ui32Flags = MSG_OBJ_TX_INT_ENABLE;
//            j++;
//        }
//
//    }
//}
void Receive_Message_Init(){
        Can_CanHardwareObject* HOHs = configuration->CanConfigSetConfig->CanHardwareObject;

        for (uint8 i=0 , j=0;i<NUM_OF_HOH;i++){
            if (HOHs[i].CanObjectType==RECEIVE){

                CAN0RxMessage[j].ui32MsgID = HOHs[i].CanHwType.CanId;
                CAN0RxMessage[j].ui32MsgIDMask = 0;
                CAN0RxMessage[j].ui32Flags = MSG_OBJ_TX_INT_ENABLE |MSG_OBJ_USE_ID_FILTER;
                CAN0RxMessage[j].ui32MsgLen=8U;
                CANMessageSet(HOHs[i].CanControllerRef->CanControllerBaseAddress,HOHs[i].CanObjectId,&CAN0RxMessage[j], MSG_OBJ_TYPE_RX);
                j++;
            }

        }

}
void Can_Init(const Can_ConfigType* Config){
    configuration = Config;
    Hardware_Init();

}

Can_ReturnType Can_Write(Can_HwHandleType Hth,const Can_PduType* PduInfo){
    tCANMsgObject  canTxMessage;
    canTxMessage.ui32MsgID = PduInfo->id;
//    uint64 *           SduDataPtr;
//    uint8 *           MetaDataPtr;
//    PduLengthType   SduLength;

   if(PduInfo->SduLength<1U)
   {
       canTxMessage.ui32MsgLen = 1U;
   }

   else{
       canTxMessage.ui32MsgLen=PduInfo->length;

       }
   canTxMessage.pui8MsgData =PduInfo->sdu;


   canTxMessage.ui32MsgIDMask = 0U;


   canTxMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;



   CANMessageSet(configuration->CanConfigSetConfig->CanHardwareObject[hth].CanControllerRef->CanControllerBaseAddress,configuration->CanConfigSetConfig->CanHardwareObject[hth].CanObjectId, &canTxMessage, MSG_OBJ_TYPE_TX);
return E_OK;

}

