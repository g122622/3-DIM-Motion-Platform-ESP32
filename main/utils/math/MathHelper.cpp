/*
 * File: \MathHelper.cpp
 * Project: math
 * Created Date: 2024-06-29 10:45:31
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-18 00:04:41
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./MathHelper.h"
#include <cmath>

// template <typename T>
// T MathHelper_Impl::min(T a, T b)
// {
//     return a < b ? a : b;
// }

// template <typename T>
// T MathHelper_Impl::max(T a, T b)
// {
//     return a > b ? a : b;
// }

// /**
//  * @brief limit the value to the range [-range, range]
//  * @note if value is out of range, it will be limited to the nearest boundary
//  */
// template <typename T>
// T MathHelper_Impl::limit(T value, T range)
// {
//     return max(min(value, range), (-1) * range);
// }

// template <typename T>
// T MathHelper_Impl::abs(T value)
// {
//     return value < 0 ? -value : value;
// }

float MathHelper_Impl::min(float a, float b)
{
    return a < b ? a : b;
}

float MathHelper_Impl::max(float a, float b)
{
    return a > b ? a : b;
}

float MathHelper_Impl::limit(float value, float range)
{
    return max(min(value, range), (-1) * range);
}

float MathHelper_Impl::abs(float value)
{
    return value < 0 ? -value : value;
}

float MathHelper_Impl::distance(float x1, float y1, float x2, float y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
