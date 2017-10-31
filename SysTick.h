/*
 * SysTick.h
 *
 *  Created on: 20 Eki 2017
 *      Author: Yigit
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdbool.h>          // included to use boolean data type
#include <math.h>             // standard C math library
#include <stdint.h>           // C99 variable types
#include <stdio.h>            // standard C input output library
#include <string.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"

#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/rom.h"

void systick_setup(uint32_t period);
void systick_wait(uint32_t delay);
void systick_delay(unsigned long delay);
void systick_delay_microSecond(unsigned long delay);




#endif /* SYSTICK_H_ */
