/*
 * File: \Angle.h
 * Project: math
 * Created Date: 2024-06-30 22:34:42
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-01 23:18:25
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
public:
    Angle(float angleIn);
    float getAngle();
    float getAngleValueIn360();
    void setAngle(float angleIn);
    Angle operator+(Angle other);
    Angle operator-(Angle other);

private:
    float angle;
};

#endif // ANGLE_H
