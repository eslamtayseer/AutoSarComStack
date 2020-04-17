#include "Can.h"
#include "inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"


const Can_ConfigType* configuration;

tCANMsgObject CAN0RxMessage;
tCANMsgObject CAN0TxMessage;

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
Transmit_Message_Init();
Receive_Message_Init();
IntEnable(configuration->CanConfigSetConfig->CanController->CanControllerBaseAddress);
CANEnable(configuration->CanConfigSetConfig->CanController->CanControllerBaseAddress);
}
void Transmit_Message_Init(){
    Can_CanHardwareObject* HOHs = configuration->CanConfigSetConfig->CanHardwareObject;
    for (uint8 i=0;i<NUM_OF_HOH;i++){
        if (HOHs[i].CanObjectType==TRANSMIT){

        }

    }
}
void Receive_Message_Init(){

}
void Can_Init(const Can_ConfigType* Config){
    configuration = Config;
    Hardware_Init();



}
