/*
 * File: \logger.h
 * Project: log
 * Created Date: 2024-05-27 23:55:01
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-08 15:03:25
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "esp_log.h"
#include <stdio.h>
#include <stdarg.h>

// static const char *TAG = "logger";

class Logger_Impl
{
public:
    // why we use static functions here？because we don't need to create an instance of Logger class.
    static void info(const char *message, ...);

    static void error(const char *message, ...);

    static void debug(const char *message, ...);

    static void warning(const char *message, ...);
};

inline Logger_Impl Logger = Logger_Impl();

#endif // __LOGGER_H__