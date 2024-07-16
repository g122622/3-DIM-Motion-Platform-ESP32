/*
 * File: \SimpleDCMotor.cpp
 * Project: motors
 * Created Date: 2024-06-29 16:16:13
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-16 16:31:22
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./SimpleDCMotor.h"

/**
 * @brief Map the input value. Should be called before using the input value.
 */
float inputMapper(float inputIn)
{
    const float base = 8;
    if (inputIn > 0)
    {
        return base + (100 - base) / 100 * inputIn;
    }
    else
    {
        return -base + (100 - base) / 100 * inputIn;
    }
}

SimpleDCMotor::SimpleDCMotor(int pin_in1_in, int pin_in2_in, int pin_pwm_in)
    : pin_in1(pin_in1_in),
      pin_in2(pin_in2_in),
      pin_pwm(pin_pwm_in),
      pwm(pin_pwm_in, 100),
      gpio_in1(pin_in1_in, gpioModes::_GPIO_MODE_OUTPUT),
      gpio_in2(pin_in2_in, gpioModes::_GPIO_MODE_OUTPUT),
      speedPercentage(0)
{
    pwm.setDuty(0);
}

/**
 * @brief Set the speed of the motor, in percentage (-100 to 100).
 *
 * @param speedPercentageIn percentage of speed (-100 to 100)
 * @return void
 * @note If the speed is positive, the motor will turn clockwise. If the speed is negative, the motor will turn counterclockwise.
 */
void SimpleDCMotor::setSpeedPercentage(float speedPercentageIn)
{
    speedPercentage = inputMapper(speedPercentageIn);
    if (speedPercentage >= 0)
    {
        gpio_in1.write(1);
        gpio_in2.write(0);
    }
    else
    {
        gpio_in1.write(0);
        gpio_in2.write(1);
    }
    pwm.setDuty(MathHelper.abs(speedPercentage));
}

/**
 * @brief Stop the motor.
 *
 * @return void
 */
void SimpleDCMotor::stop()
{
    setSpeedPercentage(0); // set speed to 0
}