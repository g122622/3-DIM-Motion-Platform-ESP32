/*
 * File: \SimpleDCMotor.h
 * Project: motors
 * Created Date: 2024-06-29 16:16:24
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-08 01:05:09
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef SIMPLE_DCMOTOR_H
#define SIMPLE_DCMOTOR_H

#include "peripherals/interface/PWM/PWM.h"
#include "peripherals/interface/GPIO/GPIO.h"
#include "utils/math/MathHelper.h"

/**
 * @brief Construct a new SimpleDCMotor object, based on l298n motor driver.
 *
 */
class SimpleDCMotor
{
public:
    SimpleDCMotor(int pin_in1, int pin_in2, int pin_pwm);
    void setSpeedPercentage(float speedPercentageIn);
    void stop();

private:
    const int pin_in1;
    const int pin_in2;
    const int pin_pwm;
    PWM pwm;
    GPIO gpio_in1;
    GPIO gpio_in2;
    float speedPercentage; // percentage of speed (-100 to 100)
};

#endif // SIMPLE_DCMOTOR_H
