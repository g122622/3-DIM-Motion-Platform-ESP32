/*
 * File: \MathHelper.cpp
 * Project: math
 * Created Date: 2024-06-29 10:45:31
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-01 00:12:50
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./MathHelper.h"

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

