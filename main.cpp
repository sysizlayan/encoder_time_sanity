/**
 * main.cpp
 */
#include "main.h"

#include "SysTick.h"
#include "VelocityTimer.h"
#include "QEI.h"

uint32_t systemClock;
QEI1 encoder(2000,100);
uint32_t period_raw;
void uart_stdio_init(uint32_t baudrate)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //open clock for port a
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); // set pin 0 and 1 as uart
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX); //PA0 as Rx
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX); //PA1 as Tx
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //Open clock for UART0
    UARTStdioConfig(0, baudrate, ROM_SysCtlClockGet()); //Configure UART0 as stdio
}

int main(void)
{

    //Initialization of utils to communicate with the device
    float velocity;
    ROM_SysCtlClockSet(SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ|SYSCTL_SYSDIV_2_5);//80Mhz Clock
    ROM_FPUEnable();//Enable FPU
    ROM_FPULazyStackingEnable();//Enable FPU stacking while interrupt

    systemClock=ROM_SysCtlClockGet();
    systick_setup(0x00FFFFFF); //All 1s
    //ROM_IntMasterDisable(); //Disable all the interrupts during initialization

    uart_stdio_init(115200); //UART0, main usb connection in launchpad, as stdio source
    ROM_IntMasterEnable();//After initializations, enable all the interrupts

    initialize_pulse_timer();

    while(true)
    {
        velocity = convert_period_to_velocity();
        UARTprintf("%d.%d\n", (int)velocity, (int)(1000.0f * velocity - (int)velocity));
        systick_delay(1);
    }
}
