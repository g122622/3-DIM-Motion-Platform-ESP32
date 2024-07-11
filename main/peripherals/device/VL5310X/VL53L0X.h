/*
 * File: \VL53L0X.h
 * Project: vl5310x
 * Created Date: 2024-05-26 21:55:41
 * Author: Guoyi
 * -----
 * Last Modified: 2024-05-31 23:46:31
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef VL53L0X__h
#define VL53L0X__h

#include "./VL53L0X_IMPL.h"

class VL53L0X
{
public:
    VL53L0X();
    ~VL53L0X();
    VL53L0X_IMPL impl;
    uint16_t readDistance();
};

#endif // VL53L0X__h
