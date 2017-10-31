/*
 * QEI.cpp
 *
 *  Created on: 20 Eki 2017
 *      Author: Yigit
 */
#include "QEI.h"
extern QEI1* encoder;
void update_QEI1_velocity(void);
QEI1::QEI1(uint32_t ppm) //frequency is 1 Hz
{

    this->vel_samp_period = 1.0f;
    this->vel_samp_freq = 1.0f;

    this->countToDegree = (360.0f)/ppm;
    //QEI initialization
    ///////////
    // QEI1 Peripheral
    // PC4 --> Index
    // PC5 --> Phase A
    // PC6 --> Phase B
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    ROM_GPIOPinConfigure(GPIO_PC4_IDX1);
    ROM_GPIOPinConfigure(GPIO_PC5_PHA1);
    ROM_GPIOPinConfigure(GPIO_PC6_PHB1);
    ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_4 |  GPIO_PIN_5 | GPIO_PIN_6);

    ROM_QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), ppm-1); //the position will not be reset with index pulse
    ROM_QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, ROM_SysCtlClockGet());
    ROM_QEIEnable(QEI1_BASE);
    ROM_QEIVelocityEnable(QEI1_BASE);

    QEIIntRegister(QEI1_BASE, update_QEI1_velocity);

    QEIIntEnable(QEI1_BASE, QEI_INTTIMER);
}

QEI1::QEI1(uint32_t ppm, uint32_t frequency) //takes velocity sampling frequency as input, since integer is required it will take floor of the period
{

    this->vel_samp_period = (uint32_t)(ROM_SysCtlClockGet()/frequency);
    this->vel_samp_freq = (float)frequency;
    this->countToDegree = (360.0f)/ppm;

    //QEI initialization
    ///////////
    // QEI1 Peripheral
    // PC4 --> Index
    // PC5 --> Phase A
    // PC6 --> Phase B
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    ROM_GPIOPinConfigure(GPIO_PC4_IDX1);
    ROM_GPIOPinConfigure(GPIO_PC5_PHA1);
    ROM_GPIOPinConfigure(GPIO_PC6_PHB1);
    ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_4 |  GPIO_PIN_5 | GPIO_PIN_6);

    ROM_QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET | QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), ppm-1); //the position will not be reset with index pulse
    ROM_QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, vel_samp_period);
    ROM_QEIEnable(QEI1_BASE);
    ROM_QEIVelocityEnable(QEI1_BASE);

    QEIIntRegister(QEI1_BASE, update_QEI1_velocity);

    QEIIntEnable(QEI1_BASE, QEI_INTTIMER);
}

uint32_t QEI1::get_pos_count()
{
    this->positionCount = ROM_QEIPositionGet(QEI1_BASE);
    return this->positionCount;
}
uint32_t QEI1::get_vel_count()
{
    this->velocityCount = ROM_QEIVelocityGet(QEI1_BASE);
    return this->velocityCount;
}
int32_t QEI1::get_dir()
{
    this->direction = ROM_QEIDirectionGet(QEI1_BASE);
    return this->direction;
}
float QEI1::get_pos()
{
    this->get_pos_count();
    this->position = this->positionCount * this->countToDegree;
    return this->position;
}
float QEI1::update_vel()
{
    this->get_dir(); //get direction first to be able to find sign
    this->get_vel_count(); //get velocity count
    this->velocity = (float)(this->direction) * this->velocityCount * this->countToDegree * this->vel_samp_freq;
    return this->velocity;
}

float QEI1::get_vel()
{
    return this->velocity;
}
void update_QEI1_velocity(void)
{
    QEIIntClear(QEI1_BASE, QEI_INTTIMER);  // clear velocity timer, timeout interrupt
    encoder->update_vel();
}


