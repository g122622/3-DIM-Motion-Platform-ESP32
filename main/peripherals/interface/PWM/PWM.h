/*
 * File: \PWM.h
 * Project: PWM
 * Created Date: 2024-06-29 11:20:54
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-31 18:13:03
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef PWM_H
#define PWM_H

#include <cstdint>
#include "driver/ledc.h"
#include "utils/log/Logger.h"

class PWM
{
public:
    PWM(int pin, uint32_t freq = 10000, int resolutionIndex = 12);
    void setDuty(float percentage);
    void setFrequency(uint32_t freq);

private:
    int pin;
    uint32_t freq;
    uint32_t duty;
    int timer_num_this;
    int resolutionIndex;
};

#endif // PWM_H
