/*
 * File: \PerfMonitor.cpp
 * Project: monitor
 * Created Date: 2024-08-20 22:45:23
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-20 22:45:57
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "./PerfMonitor.hpp"

PerfMonitor::PerfMonitor() : task([](void *parameters)
                                  {
    uint8_t CPU_RunInfo[STR_BUF_LEN]; // 保存任务运行时间信息
    while (1)
    {
        memset(CPU_RunInfo, 0, STR_BUF_LEN); /* 信息缓冲区清零 */
        vTaskList((char *)&CPU_RunInfo); // 获取任务运行时间信息
        printf("----------------------------------------------------\r\n");
        printf("task_name\tstate\tpri\tcore\tfreemem\tid\r\n");
        printf("%s", CPU_RunInfo);
        printf("----------------------------------------------------\r\n");
        memset(CPU_RunInfo, 0, STR_BUF_LEN); /* 信息缓冲区清零 */
        vTaskGetRunTimeStats((char *)&CPU_RunInfo);
        printf("task_name\trun_cnt\tusage_rate\r\n");
        printf("%s", CPU_RunInfo);
        printf("----------------------------------------------------\r\n");
        printf("[esp_get_free_heap_size bytes] %ld\n", esp_get_free_heap_size());
        printf("[xPortGetFreeHeapSize] %d\n", xPortGetFreeHeapSize());
        printf("----------------------------------------------------\r\n");
        delay(1000);
    } }, "PerfMonitor", 4096, NULL, TaskPriority::PRIORITY_LOW, 1)
{
    // ...
}
