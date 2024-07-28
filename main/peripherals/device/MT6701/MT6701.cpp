/*
 * File: \MT6701.cpp
 * Project: MT6701
 * Created Date: 2024-05-31 22:55:47
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 16:54:45
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./MT6701.h"

MT6701::MT6701(int scl, int sda, int portIn)
{
    _i2c = I2C();
    _i2c.init(scl, sda, 10000, portIn);
    this->port = portIn;
}

uint8_t MT6701::readReg(uint8_t reg)
{
    _i2c.write(address, reg);
    uint8_t value[1];
    _i2c.read(address, value, 1);

    return value[0];
}

/**
 * @brief Read the raw angle value from the MT6701. Ranging from 0 to 360 degrees.
 * @note The data will perform an aberration around 0 or 360 degree.
 */
float MT6701::readRawAngle()
{
    uint8_t half1 = readReg(0x03);
    uint8_t half2 = readReg(0x04);
    uint16_t angle_raw = ((uint16_t)half1 << 6) | (uint16_t)(half2);
    float angle = (float)angle_raw / 16384.0 * 360.0;
    return angle;
}

/**
 * @note concurrent read angle is not allowed, may cause heavy collision.
 */
float MT6701::readAngle()
{
    const float threshold = 15.0;
    float rawAngle = readRawAngle();

    if (this->isFirstRead)
    {
        this->isFirstRead = false;
        lastRawAngle = rawAngle;
        currentAngle = rawAngle;
        return rawAngle;
    }

    float delta = 0;
    if (rawAngle - lastRawAngle > 180)
    {
        delta = rawAngle - lastRawAngle - 360;
    }
    else if (rawAngle - lastRawAngle < -180)
    {
        delta = rawAngle - lastRawAngle + 360;
    }
    if (MathHelper.abs(delta) > threshold * 2)
    {
        printf("\033[33m[MT6701 port:%d] rawAngle: %f, lastRawAngle: %f, delta: %f, exceed the threshold.\n\033[0m", port, rawAngle, lastRawAngle, delta);
        return currentAngle;
    }

    if (rawAngle > -0.1 && rawAngle < threshold && lastRawAngle < 360.1 && lastRawAngle > (360.0 - threshold))
    {
        cycleCount++;
    }
    else if (rawAngle > (360.0 - threshold) && rawAngle < 360.1 && lastRawAngle > -0.1 && lastRawAngle < threshold)
    {
        cycleCount--;
    }
    currentAngle = 360 * cycleCount + rawAngle;
    lastRawAngle = rawAngle;
    return currentAngle;
}