/*
 * File: \CommandManager.cpp
 * Project: command
 * Created Date: 2024-07-08 19:23:46
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-16 18:27:27
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./CommandManager.h"

CommandManager::CommandManager()
{
    // create a queue with 64 slots and each slot can hold 16 bytes of command data
    taskQueueHandle = xQueueCreate(64, this->bytesPerCommand);
}

void CommandManager::sendBatchToQueue(void *commandBatch, uint32_t commandCount)
{
    uint8_t *uint8Batch = reinterpret_cast<uint8_t *>(commandBatch);
    for (int i = 0; i < commandCount; i++)
    {
        BaseType_t status = xQueueSendToBack(taskQueueHandle, uint8Batch + i * bytesPerCommand, 0);
        if (status != pdTRUE)
        {
            if (status == errQUEUE_FULL)
            {
                printf("Command queue is full\n");
            }
            else
            {
                printf("Failed to send command to queue, status = %d \n", status);
            }
            return;
        }
    }
}

void *CommandManager::receiveCommandFromQueue()
{
    void *command = pvPortMalloc(bytesPerCommand);
    BaseType_t status = xQueueReceive(taskQueueHandle, command, portMAX_DELAY);
    if (status != pdTRUE)
    {
        if (status == errQUEUE_EMPTY)
        {
            printf("Command queue is empty\n");
        }
        else
        {
            printf("Failed to receive command from queue, status = %d \n", status);
        }
        return nullptr;
    }
    return command;
}

CommandManager::~CommandManager()
{
    vQueueDelete(taskQueueHandle);
}
