#include "Can.h"
#include "Can_API.h"
#include "MPC5748G.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

const Can_ConfigType* CanCalipsoConfig;

void Hardware_Init(){
	INTC.PSR[580].R = 0x8001; //set interrupt core and priority
	
	hw_init();
	FlexCAN_1_Init();
	Configure_RX_MessageBuffer();

}

void Receive_Message_Init(){
    Configure_RX_MessageBuffer();
}

void Can_Init(const Can_ConfigType* Config){
    CanCalipsoConfig = Config;
    Hardware_Init();
}

Can_ReturnType Can_Write(Can_HwHandleType Hth,const Can_PduType* PduInfo){
    int MB_Index = CanCalipsoConfig->CanConfigSetConfig->CanHardwareObject[Hth].CanObjectId;
    uint32 *ptr = PduInfo->sdu;
    CAN_1.MB[MB_Index].CS.B.CODE = 0x8;          //MB TX inactive
	CAN_1.MB[MB_Index].CS.B.IDE = CanCalipsoConfig->CanConfigSetConfig->CanHardwareObject[Hth].CanIdType;			  //send STD ID
	CAN_1.MB[MB_Index].ID.R = CanCalipsoConfig->CanConfigSetConfig->CanHardwareObject[Hth].CanHwType.CanId;	      		  //set STD ID to 0
	CAN_1.MB[MB_Index].DATA.W[1] = ptr[1];	  //data1 set
	CAN_1.MB[MB_Index].DATA.W[0] = ptr[0];	  //data0 set
	CAN_1.MB[MB_Index].CS.B.DLC = PduInfo->length;			  //message length 8 bytes
	CAN_1.MB[MB_Index].CS.B.RTR = 0;			  //remote frame disable
	CAN_1.MB[MB_Index].CS.B.SRR = 0;			  //not used with STD_ID
	CAN_1.MB[MB_Index].CS.B.CODE = 0xC;		  //MB once transmit data
    return E_OK;
}

