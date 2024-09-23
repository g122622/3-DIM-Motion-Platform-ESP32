/*
 * File: \Task.cpp
 * Project: OS
 * Created Date: 2024-08-15 22:34:43
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-15 23:46:36
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "./Task.hpp"

Task::Task(TaskFunction_t taskFunc,
           const char *const taskName,
           const uint32_t stackDepth,
           void *const parameters,
           TaskPriority priority,
           const BaseType_t coreID)
{
    xTaskCreatePinnedToCore(taskFunc,
                            taskName,
                            stackDepth,
                            parameters,
                            priority,
                            taskHandle,
                            coreID);
}

Task::~Task()
{
    vTaskDelete(taskHandle);
}
