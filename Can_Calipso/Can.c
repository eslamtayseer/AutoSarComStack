#include "Can.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>



const Can_ConfigType* CanTivaConfig;


//tCANMsgObject CAN0TxMessage [NO_OF_HTH];

void Hardware_Init(){

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
       

}
void Can_Init(const Can_ConfigType* Config){
    CanTivaConfig = Config;
    Hardware_Init();

}

Can_ReturnType Can_Write(Can_HwHandleType Hth,const Can_PduType* PduInfo){
   return E_OK;

}

