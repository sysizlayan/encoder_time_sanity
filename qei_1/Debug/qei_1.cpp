#include "Energia.h"

#line 1 "C:/Users/Yigit/Desktop/workspace_v7/qei_1/qei_1.ino"
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/qei.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
void setup();
void loop();

#line 6
int pos;



void setup() {
  Serial.begin(9600);

  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

  GPIOPinConfigure(GPIO_PC4_IDX1);
  GPIOPinConfigure(GPIO_PC5_PHA1);
  GPIOPinConfigure(GPIO_PC6_PHB1);
  GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_4 |  GPIO_PIN_5 | GPIO_PIN_6);

  
  QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), 2000);
  QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, SysCtlClockGet()); 
  QEIEnable(QEI1_BASE);
  QEIVelocityEnable(QEI1_BASE);
}

void loop() {
  
  int asd1 =  QEIPositionGet(QEI1_BASE);
  int asd2 = QEIVelocityGet(QEI1_BASE);
  Serial.print(QEIPositionGet(QEI1_BASE));
  Serial.print(',');
  Serial.println(QEIVelocityGet(QEI1_BASE));
}



