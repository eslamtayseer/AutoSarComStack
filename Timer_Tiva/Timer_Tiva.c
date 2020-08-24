/*
 * Timer_Tiva.c
 *
 *  Created on: Apr 26, 2020
 *      Author: mahmoud
 */


#include "Timer_Tiva.h"
#include "../GPIO_Tiva/gpio.h"

uint32 Timer_Period;
bool toggle_flag;

void Timer_Init (uint32 TimerPeriod)
{
  Timer_Period = TimerPeriod;
  toggle_flag = false;

  SysTickDisable ();
  SysTickPeriodSet (TimerPeriod);
  SysTickIntEnable();
  SysTickIntRegister(timer_int_handler);
  SysTickEnable ();
}

void Timer_SetToggleFlag(bool val)
{
    toggle_flag = val;
}

uint32 Timer_Get_Value (void)
{
  return SysTickValueGet ();
}

uint32 Timer_Get_Period (void)
{
    return Timer_Period;
}

void timer_int_handler(void)
{
    if(toggle_flag)
        GPIO_ToggleRedLed();
}
