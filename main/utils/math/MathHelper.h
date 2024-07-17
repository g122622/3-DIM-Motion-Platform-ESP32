/*
 * File: \MathHelper.h
 * Project: math
 * Created Date: 2024-06-29 10:43:22
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-18 00:04:06
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef MATH_HELPER_H
#define MATH_HELPER_H

class MathHelper_Impl
{
public:
    // template <typename T>
    // static T min(T a, T b);

    // template <typename T>
    // static T max(T a, T b);

    // template <typename T>
    // static T limit(T value, T range);

    // template <typename T>
    // static T abs(T value);

    static float min(float a, float b);
    static float max(float a, float b);
    static float limit(float value, float range);
    static float abs(float value);
    static float distance(float x1, float y1, float x2, float y2);
};

inline MathHelper_Impl MathHelper;

#endif // MATH_HELPER_H