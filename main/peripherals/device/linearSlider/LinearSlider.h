/*
 * File: \LinearSlider.h
 * Project: linearSlider
 * Created Date: 2024-06-30 20:18:54
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-08 18:03:25
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef LINEARSLIDER_H
#define LINEARSLIDER_H

#include "peripherals/device/motors/DCSteppingMotor.h"

class LinearSlider
{
public:
    LinearSlider(int pin_in1_in, int pin_in2_in, int pin_pwm_in, int scl_in, int sda_in, int port_in);
    void step(float distance);
    void setPosition(float position);
    float getPosition();
    float getRealPosition();
    DCSteppingMotor motor;

private:
    float distancePerCycle = 31.5; // in mm
    float currentPosition = 0.0;
};

#endif // LINEARSLIDER_H
