/*
 * File: \LinearSlider.cpp
 * Project: linearSlider
 * Created Date: 2024-06-30 20:21:14
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-22 23:44:47
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./LinearSlider.h"

LinearSlider::LinearSlider(int pin_in1_in, int pin_in2_in, int pin_pwm_in, int scl_in, int sda_in, int port_in)
    : motor(pin_in1_in, pin_in2_in, pin_pwm_in, scl_in, sda_in, port_in)
{
}

void LinearSlider::step(float distance)
{
    currentPosition += distance;
    float angle = distance / distancePerCycle * 360;
    motor.step(angle);
}

// position is in mm
void LinearSlider::setPosition(float position)
{
    if (position < 0)
    {
        position = 0;
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

void LinearSlider::reset(){
    motor.reset();
}
