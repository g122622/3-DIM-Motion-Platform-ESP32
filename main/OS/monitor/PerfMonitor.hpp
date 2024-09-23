/*
 * File: \perfMonitor.hpp
 * Project: monitor
 * Created Date: 2024-08-18 20:42:16
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-20 22:45:39
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include "OS/task/Task.hpp"
#include "OS/time/delay.h"
#include "esp_log.h"

class PerfMonitor
{
public:
    PerfMonitor();

private:
    Task task;
    static const int STR_BUF_LEN = 1024;
};
