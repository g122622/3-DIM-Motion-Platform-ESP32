/*
 * File: \delay.h
 * Project: utils
 * Created Date: 2024-05-27 23:47:05
 * Author: Guoyi
 * -----
 * Last Modified: 2024-05-28 22:05:20
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef __DELAY_H__
#define __DELAY_H__

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "utils/log/Logger.h"

void delay(uint32_t ms);

#endif // __DELAY_H__
