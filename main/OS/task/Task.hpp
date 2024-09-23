/*
 * File: \Task.hpp
 * Project: OS
 * Created Date: 2024-08-15 22:34:35
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-16 12:44:47
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Task
{
public:
    Task(TaskFunction_t taskFunc,
         const char *const taskName,
         const uint32_t stackDepth,
         void *const parameters,
         TaskPriority priority,
         const BaseType_t coreID);

    ~Task();

private:
    TaskHandle_t taskHandle;
};

enum TaskPriority
{
    PRIORITY_LOW = 5,
    PRIORITY_MEDIUM = 10,
    PRIORITY_HIGH = 20,
    PRIORITY_CRITICAL = (configMAX_PRIORITIES - 1)
};
