/*
 * Timer_Tiva.h
 *
 *  Created on: Apr 26, 2020
 *      Author: mahmoud
 */

#ifndef TIMER_TIVA_H_
#define TIMER_TIVA_H_

#include <stdint.h>
#include <stdbool.h>

#include "../include/Std_Types.h"
#include "driverlib/systick.h"

void Timer_Init (uint32 TimerPeriod);
uint32 Timer_Get_Value (void);
uint32 Timer_Get_Period (void);
void timer_int_handler(void);
void Timer_SetToggleFlag(bool val);


#endif /* TIMER_TIVA_H_ */
