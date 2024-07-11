/*
 * File: \MG995.h
 * Project: servo
 * Created Date: 2024-07-02 19:27:32
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-08 01:05:09
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef MG995_H
#define MG995_H

#include "peripherals/interface/PWM/PWM.h"

class MG995
{
public:
    MG995(int controlPin);
    void setAngle(float angle);

private:
    PWM pwm;
};

#endif // MG995_H
