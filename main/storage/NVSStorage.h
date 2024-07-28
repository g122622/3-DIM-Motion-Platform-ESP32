/*
 * File: \NVSStorage.h
 * Project: storage
 * Created Date: 2024-07-28 15:11:47
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 15:43:17
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"

class NVSStorage
{
public:
    NVSStorage(const char *nameSpace);
    ~NVSStorage();
    uint32_t getUint32(const char *key, uint32_t defaultValue);
    void setUint32(const char *key, uint32_t value);
    float getFloat(const char *key, float defaultValue);
    void setFloat(const char *key, float value);

private:
    nvs_handle_t nvs_handle;
    const char *tag = "NVSStorage";
};
