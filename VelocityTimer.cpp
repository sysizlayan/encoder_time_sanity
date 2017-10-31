/*
 * VelocityTimer.cpp
 *
 *  Created on: 24 Eki 2017
 *      Author: Yigit
 */
#include "VelocityTimer.h"
uint64_t first;
extern uint64_t period_raw;  // raw value of the period count, it is updated with timer interrupt

void initialize_pulse_timer()
{
    first = 0xFFFFFFFF;
    //WTIMER1 - timerB will be used in Edge Time Mode, PC7
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);  // Enable PortC Clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);  // Enable Wtimer1 clock
    SysCtlDelay(SysCtlClockGet()/100); //Wait 10ms

    GPIOPinTypeTimer(GPIO_PORTC_BASE, GPIO_PIN_7); //Use PC7 as CCP pin
    GPIOPinConfigure(GPIO_PC7_WT1CCP1); // Configure PC7 as WT1CCP1

    TimerConfigure(WTIMER1_BASE, (TIMER_CFG_SPLIT_PAIR |TIMER_CFG_B_CAP_TIME));  // TimerB will count down
    TimerControlEvent(WTIMER1_BASE, TIMER_B, TIMER_EVENT_BOTH_EDGES);  //WTimer1, timerB will be triggered on both edges
    TimerLoadSet(WTIMER1_BASE, TIMER_B, 0xFFFFFFFF);  // Timer is loaded with max value


    TimerIntRegister(WTIMER1_BASE, TIMER_B, read_period_raw);  // read_period_raw is a interrupt handler
    IntEnable(INT_WTIMER1B_TM4C123);  // Enable WTimer1B interrupts
    TimerIntEnable(WTIMER1_BASE, TIMER_CAPB_EVENT);  // Enable interrupt for edge time event
    SysCtlDelay(SysCtlClockGet()/100); //Wait 10ms

    TimerEnable(WTIMER1_BASE, TIMER_B);  // Enable WT1CCP2 to edge time
}

void read_period_raw()
{
    TimerIntClear(WTIMER1_BASE, TIMER_CAPB_EVENT);  // Clear interrupt of edge time event of timerB
    period_raw = (first-(uint64_t)TimerValueGet(WTIMER1_BASE, TIMER_B))&0xFFFFFFFF;  // Calculate the period and mask it to prevent overflow errors
    first = TimerValueGet(WTIMER1_BASE, TIMER_B);  // Take last time to use in future
    //convert_period_to_velocity();
}

float convert_period_to_velocity(void)
{
    // Since both high and low side is measured, measured time is 0.5 of the 1 pulse distance
    return 0.36 * 80000000.0f / (float)period_raw ;
}
