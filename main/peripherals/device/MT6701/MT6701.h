/*
 * File: \MT6701.h
 * Project: MT6701
 * Created Date: 2024-05-31 22:55:32
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 16:55:57
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef __MT6701_H__
#define __MT6701_H__

#include "peripherals/interface/I2C/I2C.h"
#include "utils/math/MathHelper.h"

class MT6701
{
public:
    MT6701(int scl = 16, int sda = 17, int port = 0);
    // ~MT6701();
    float readRawAngle();
    float readAngle();

    float currentAngle = 0.0; // last read angle by readAngle()

private:
    I2C _i2c;
    uint8_t address = 0x06;
    uint8_t readReg(uint8_t reg);

    float lastRawAngle = 0.0;
    int cycleCount = 0;

    int port = 0;
    bool isFirstRead = true;
};

#endif // __MT6701_H__