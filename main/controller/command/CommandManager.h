/*
 * File: \CommandManager.h
 * Project: command
 * Created Date: 2024-07-08 19:23:53
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-17 14:24:41
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

class CommandManager
{
public:
    CommandManager();
    void sendBatchToQueue(void *commandBatch, uint32_t commandCount);
    void *receiveCommandFromQueue();
    ~CommandManager();
    int executedCommandCount = 0;
    int currentCommandNumber = 0;

private:
    QueueHandle_t taskQueueHandle;
    int bytesPerCommand = 12;
};

