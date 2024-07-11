/*
 * File: \PIDController.h
 * Project: PID
 * Created Date: 2024-06-29 10:32:20
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-11 23:10:52
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "./utils/math/MathHelper.h"
#include <stdio.h>

class PIDController
{
public:
    PIDController(float Kp, float Ki, float Kd);
    float update(float currentValueIn, float dt);
    void setTarget(float targetValueIn);
    void setOutputLimit(float limitIn);
    void setIntegralLimit(float limitIn);
    void reset();
    void setDeadzoneThreshold(float thresholdIn);
    float Kp, Ki, Kd;        // gains
    float outputLimit;       // output limits
    float integralLimit;     // integral limits
    float deadzoneThreshold; // deadzone threshold for angle input, if input is within this threshold, the output will be zero to avoid jerky situation
    int _id;                 // unique id
    
private:
    float prevError, currentError;   // previous error and current error
    float targetValue, currentValue; // target value and current value
    float errorIntegral; // integral error

    int tickCount; // tick count for update calculation
};

#endif // PID_CONTROLLER_H
