#include "uart_tiva.h"

const Can_ConfigType* CanTivaConfig;

void uart_init(const Can_ConfigType* Config)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
    }

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

//    IntEnable(INT_UART0);
//    UARTIntRegister(UART0_BASE, uart_interrupt_handler);
//    UARTIntEnable(UART0_BASE, UART_INT_RX);
//    IntMasterEnable();
//
    UARTEnable(UART0_BASE);

    CanTivaConfig = Config;
}

Can_ReturnType uart_send(const Can_PduType* PduInfo)
{
    uint8_t data = *(PduInfo->sdu);
    if(UARTCharPutNonBlocking(UART0_BASE, data))
        return E_OK;

    return E_NOT_OK;
}

Can_ReturnType uart_receive()
{
//    UARTIntClear(UART0_BASE, UART_INT_RX);
//    Can_HwType hw_type = {
//        .CanId = -1;
//        .Hoh = -1;
//        .ControllerId = -1;
//    };
    Can_CanHardwareObject* HOHs = CanTivaConfig->CanConfigSetConfig->CanHardwareObject;

    PduInfoType pdu_info;

    while(!UARTCharsAvail(UART0_BASE))
    {
    }

    char val;
    val = UARTCharGetNonBlocking(UART0_BASE);

    uint64_t val_64 = (uint64_t) val;
    pdu_info.SduDataPtr = &(val_64);
    pdu_info.MetaDataPtr = NULL;
    pdu_info.SduLength = 8;

    CanIf_RxIndication(&(HOHs[0].CanHwType), &pdu_info);

    return E_OK;
}
