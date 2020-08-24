#ifndef GPIO_TIVA_H_
#define GPIO_TIVA_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void GPIO_Init(void);
void GPIO_ToggleRedLed(void);
void GPIO_SwitchOnRedLed(void);
void GPIO_SwitchOffRedLed(void);

#endif
