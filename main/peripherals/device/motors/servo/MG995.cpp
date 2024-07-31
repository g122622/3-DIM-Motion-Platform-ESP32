/*
 * File: \MG995.cpp
 * Project: servo
 * Created Date: 2024-07-02 19:27:48
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-31 18:20:40
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "./MG995.h"

MG995::MG995(int controlPin)
    : pwm(controlPin, 50, 14)
{
}

void MG995::setAngle(float angle)
{
    if (angle < 0 || angle > 180)
    {
        printf("[MG995] Invalid angle: %f\n", angle);
        return;
    }
    float dutyPercentage = (0.5 + 2.0 / 180.0 * angle) / 20.0 * 100.0;
    pwm.setDuty(dutyPercentage);
}
