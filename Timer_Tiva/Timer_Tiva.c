/*
 * Timer_Tiva.c
 *
 *  Created on: Apr 26, 2020
 *      Author: mahmoud
 */


#include "Timer_Tiva.h"

uint32 Timer_Period;

void Timer_Init (uint32 TimerPeriod)
{
  Timer_Period = TimerPeriod;

  SysTickDisable ();
  SysTickPeriodSet (TimerPeriod);
  SysTickEnable ();
}

uint32 Timer_Get_Value (void)
{
  return SysTickValueGet ();
}

uint32 Timer_Get_Period (void)
{
    return Timer_Period;
}
