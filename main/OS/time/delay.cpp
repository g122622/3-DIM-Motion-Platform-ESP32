/*
 * File: \delay.cpp
 * Project: utils
 * Created Date: 2024-05-27 23:47:14
 * Author: Guoyi
 * -----
 * Last Modified: 2024-05-28 22:12:13
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "delay.h"

void delay(uint32_t ms)
{
    if (ms < 10)
    {
        Logger.warning("Warning: delay time is %d ms, may not be accurate.\n", ms);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        return;
    }
    vTaskDelay(ms / portTICK_PERIOD_MS);
}
