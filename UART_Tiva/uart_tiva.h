/*
 * uart_tiva.h
 *
 *  Created on: Aug 3, 2020
 *      Author: mahmoud
 */

#ifndef UART_TIVA_UART_TIVA_H_
#define UART_TIVA_UART_TIVA_H_

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
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <stdio.h>
#include "../Can_Tiva/Can_GeneralTypes.h"
#include "../Can_Tiva/Can_PBcfg.h"


void uart_init();
Can_ReturnType uart_send(const Can_PduType* PduInfo);
Can_ReturnType uart_receive();

#endif /* UART_TIVA_UART_TIVA_H_ */
