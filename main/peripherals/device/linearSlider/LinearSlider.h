/*
 * File: \LinearSlider.h
 * Project: linearSlider
 * Created Date: 2024-06-30 20:18:54
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-31 18:33:04
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
    LinearSlider(int pin_in1_in, int pin_in2_in, int pin_pwm_in, int scl_in, int sda_in, int port_in, float maxPositionIn);
    void setPosition(float position);
    void setMaxPosition(float maxPositionIn);
    void reset();
    float getTargetPosition();
    float getCurrentRealPosition();
    DCSteppingMotor motor;

private:
    float distancePerCycle = 31.5; // in mm
    float currentPosition = 0.0;
    float maxPosition = 100.0; // in mm
};

#endif // LINEARSLIDER_H
