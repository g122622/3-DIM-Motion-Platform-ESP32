/*
 * File: \Angle.cpp
 * Project: math
 * Created Date: 2024-06-30 22:34:33
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-16 15:12:56
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./Angle.h"

Angle::Angle(float angleIn)
{
    setAngle(angleIn);
}

float Angle::getAngle()
{
    return this->angle;
}

/**
 * @brief Get the angle value in the range of [0, 360)
 */
float Angle::getAngleValueIn360()
{
    float result = this->angle;
    while (result < 0 || result >= 360)
    {
        if (result < 0)
        {
            result += 360;
        }
        else if (result >= 360)
        {
            result -= 360;
        }
    }
    return result;
}

void Angle::setAngle(float angleIn)
{
    this->angle = angleIn;
}

Angle Angle::operator+(Angle other)
{

    return Angle(this->angle + other.getAngle());
}

Angle Angle::operator-(Angle other)
{
    float a = this->getAngleValueIn360();
    float b = other.getAngleValueIn360();
    if (a - b > 180)
    {
        return Angle(a - b - 360);
    }
    else if (a - b < -180)
    {
        return Angle(a - b + 360);
    }
}
