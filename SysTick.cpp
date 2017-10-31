/*
 * SysTick.cpp
 *
 *  Created on: 20 Eki 2017
 *      Author: Yigit
 */
#include "SysTick.h"

void systick_setup(uint32_t period)
{
    ROM_SysTickPeriodSet(period&0x00FFFFFF);
    ROM_SysTickEnable();
}
void systick_wait(uint32_t delay)
{
    volatile uint32_t elapsedTime;
    uint32_t startTime=ROM_SysTickValueGet();
    do
    {
        elapsedTime=(startTime-ROM_SysTickValueGet())&0x00FFFFFF;
    }while(elapsedTime<=delay);
}

void systick_delay(unsigned long delay)
{
  unsigned long i;
  for(i=0; i<delay; i++)systick_wait(ROM_SysCtlClockGet()/1000);//get the clock, calculate 1 ms of delay
}


void systick_delay_microSecond(unsigned long delay)
{
  unsigned long i;
  for(i=0; i<delay; i++)systick_wait(ROM_SysCtlClockGet()/100000l);//get the clock, calculate 1 us of delay
}
