#include "gpio.h"

void GPIO_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
}

void GPIO_SwitchOnRedLed(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
}

void GPIO_ToggleRedLed(void)
{
    uint32_t pin = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1 ^ pin);
}

void GPIO_SwitchOffRedLed(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
}
