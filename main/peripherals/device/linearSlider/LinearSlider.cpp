/*
 * File: \LinearSlider.cpp
 * Project: linearSlider
 * Created Date: 2024-06-30 20:21:14
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-23 14:11:48
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./LinearSlider.h"

LinearSlider::LinearSlider(int pin_in1_in, int pin_in2_in, int pin_pwm_in, int scl_in, int sda_in, int port_in, float maxPositionIn)
    : motor(pin_in1_in, pin_in2_in, pin_pwm_in, scl_in, sda_in, port_in)
{
    setMaxPosition(maxPositionIn);
}

// position is in mm
void LinearSlider::setPosition(float position)
{
    if (position < 0)
    {
        position = 0;
    }
    if (position > maxPosition)
    {
        position = maxPosition;
    }

    float angle = ((position - currentPosition) / distancePerCycle) * 360;
    motor.step(angle);
    currentPosition = position;
}

float LinearSlider::getPosition()
{
    return currentPosition;
}

/**
 * @brief Get the real position of the slider, from encoder.
 */
float LinearSlider::getRealPosition()
{
    float realAngle = motor.encoder.readAngle();
    return realAngle / 360.0f * distancePerCycle;
}

void LinearSlider::reset()
{
    motor.reset();
    currentPosition = 0;
}

void LinearSlider::setMaxPosition(float maxPositionIn)
{
    this->maxPosition = maxPositionIn;
}
