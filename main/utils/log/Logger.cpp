/*
 * File: \logger.c
 * Project: log
 * Created Date: 2024-05-27 23:55:07
 * Author: Guoyi
 * -----
 * Last Modified: 2024-05-28 22:06:59
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "Logger.h"

void Logger_Impl::info(const char *message, ...)
{
    char result[64];

    // 可变参数的处理逻辑，这里使用vaList实现
    va_list vaList;
    va_start(vaList, message);
    vsprintf(result, message, vaList);
    va_end(vaList);
    printf(result);
}

void Logger_Impl::warning(const char *message, ...)
{
    char result[64];

    // 可变参数的处理逻辑，这里使用vaList实现
    va_list vaList;
    va_start(vaList, message);
    vsprintf(result, message, vaList);
    va_end(vaList);
    printf(result);
}

void Logger_Impl::error(const char *message, ...)
{
    char result[64];

    // 可变参数的处理逻辑，这里使用vaList实现
    va_list vaList;
    va_start(vaList, message);
    vsprintf(result, message, vaList);
    va_end(vaList);
    printf(result);
}

void Logger_Impl::debug(const char *message, ...)
{
    char result[64];

    // 可变参数的处理逻辑，这里使用vaList实现
    va_list vaList;
    va_start(vaList, message);
    vsprintf(result, message, vaList);
    va_end(vaList);
    printf(result);
}

// Logger = Logger_Impl();
