/*
 * main.h
 *
 *  Created on: 20 Eki 2017
 *      Author: Yigit
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdbool.h>          // included to use boolean data type
#include <math.h>             // standard C math library
#include <stdint.h>           // C99 variable types
#include <stdio.h>            // standard C input output library
#include <string.h>

#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_uart.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_i2c.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "driverlib/i2c.h"
#include "driverlib/qei.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"

#define LOWEST_PRIORITY 0xE0
#define HIGHEST_PRIORITY 0x00

#endif /* MAIN_H_ */
