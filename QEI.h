/*
 * QEI.h
 *
 *  Created on: 20 Eki 2017
 *      Author: Yigit
 */

#ifndef QEI_H_
#define QEI_H_

#include "main.h"

class QEI1
{
    public:
        float velocity, position;
        int32_t direction;
        uint32_t velocityCount, positionCount;
        float vel_samp_period, vel_samp_freq;
        float countToDegree;

        QEI1(uint32_t ppm); //1 Hz constructor
        QEI1(uint32_t ppm, uint32_t frequency); //parametric velocity sampling frequency constructor
        uint32_t get_pos_count();
        uint32_t get_vel_count();
        int32_t get_dir();
        float get_pos();
        float update_vel();
        float get_vel();
};
#endif /* QEI_H_ */
