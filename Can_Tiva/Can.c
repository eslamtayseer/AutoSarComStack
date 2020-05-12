#include "Can.h"
#include "../CanIf/CanIf.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/can.h"

void Receive_Message_Init();

const Can_ConfigType* CanTivaConfig;

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
CANInit(CanTivaConfig->CanConfigSetConfig->CanController->CanControllerBaseAddress);
BitTimeParams.ui32SyncPropPhase1Seg=(CanTivaConfig->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerSeg1) + (CanTivaConfig->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerPropSeg);
BitTimeParams.ui32Phase2Seg=CanTivaConfig->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerSeg2;
BitTimeParams.ui32SJW=CanTivaConfig->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerSyncJumpWidth;
BitTimeParams.ui32QuantumPrescaler= SysCtlClockGet()/((BitTimeParams.ui32SyncPropPhase1Seg
                     +BitTimeParams.ui32Phase2Seg+1U)
                     *(CanTivaConfig->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerBaudRate));
CANBitTimingSet(CanTivaConfig->CanConfigSetConfig->CanController[0].CanControllerBaseAddress,&BitTimeParams);
//CANBitRateSet(CanTivaConfig->CanConfigSetConfig->CanController->CanControllerBaseAddress, SysCtlClockGet(), CanTivaConfig->CanConfigSetConfig->CanController->CanControllerDefaultBaudrate->CanControllerBaudRate);
//Transmit_Message_Init();
Receive_Message_Init();
//IntEnable(CanTivaConfig->CanConfigSetConfig->CanController->CanControllerBaseAddress);
IntEnable (INT_CAN0);
CANIntEnable(CanTivaConfig->CanConfigSetConfig->CanController->CanControllerBaseAddress, CAN_INT_MASTER | CAN_INT_STATUS);

CANEnable(CanTivaConfig->CanConfigSetConfig->CanController->CanControllerBaseAddress);
}
//void Transmit_Message_Init(){
//    Can_CanHardwareObject* HOHs = CanTivaConfig->CanConfigSetConfig->CanHardwareObject;
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
        Can_CanHardwareObject* HOHs = CanTivaConfig->CanConfigSetConfig->CanHardwareObject;
        uint8 i=0 , j=0;
        for (;i<NO_OF_HOH;i++){
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
    CanTivaConfig = Config;
    Hardware_Init();

}

Can_ReturnType Can_Write(Can_HwHandleType Hth,const Can_PduType* PduInfo){
    tCANMsgObject  canTxMessage;
    canTxMessage.ui32MsgID = PduInfo->id;
//    uint64 *           SduDataPtr;
//    uint8 *           MetaDataPtr;
//    PduLengthType   SduLength;

   if(PduInfo->length < 1U)
   {
       canTxMessage.ui32MsgLen = 1U;
   }

   else{
       canTxMessage.ui32MsgLen=PduInfo->length;

       }
   canTxMessage.pui8MsgData =PduInfo->sdu;


   canTxMessage.ui32MsgIDMask = 0U;


   canTxMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;



   CANMessageSet(CanTivaConfig->CanConfigSetConfig->CanHardwareObject[Hth].CanControllerRef->CanControllerBaseAddress,CanTivaConfig->CanConfigSetConfig->CanHardwareObject[Hth].CanObjectId, &canTxMessage, MSG_OBJ_TYPE_TX);
return E_OK;

}

void
CAN0IntHandler(void)
{
  Can_CanHardwareObject* HOHs = CanTivaConfig->CanConfigSetConfig->CanHardwareObject;
  uint32 ui32Status;


  ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

  if(ui32Status < 0x0001 || ui32Status > 0x0020)
  {
    ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
  }
  else
  {
    /*int i = 0;
    for (; i < NO_OF_HOH; i++)
    {
      if (ui32Status == HOHs[i].CanObjectId)
      {
          CANIntClear(CAN0_BASE, HOHs[i].CanObjectId);

          if (HOHs[i].CanObjectType == RECEIVE)
          {
             CANMessageGet (CAN0_BASE, HOHs[i].CanObjectId, &CAN0RxMessage[HOHs[i].CanObjectId], true);
             //Rx Indication
             PduInfoType CanRxPdu = {
             	.SduDataPtr = CAN0RxMessage[HOHs[i].CanObjectId].pui8MsgData,
             	.MetaDataPtr = NULL,
             	.SduLength = ui32MsgLen
             };
             CanIf_RxIndication(&HOHs[i].CanHwType, &CanRxPdu);
          }
          else
          {

          }
      }
    }*/
    uint32_t source = ui32Status & 0xffffffff;
    if(CanConfiguration.CanConfigSetConfig->CanHardwareObject[source - 1].CanObjectType != RECEIVE)
		return;
		
	CANMessageGet (CAN0_BASE, source - 1, &CAN0RxMessage[source - 1], true);
	PduInfoType CanRxPdu = {
     	.SduDataPtr = CAN0RxMessage[source - 1].pui8MsgData,
     	.MetaDataPtr = NULL,
     	.SduLength = CAN0RxMessage[source - 1].ui32MsgLen
     };
     CanIf_RxIndication(&(HOHs[source - 1].CanHwType), &CanRxPdu);
  }
}
