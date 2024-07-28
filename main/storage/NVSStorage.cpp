/*
 * File: \NVSStorage.cpp
 * Project: storage
 * Created Date: 2024-07-28 15:11:38
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 16:09:53
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "./NVSStorage.h"

NVSStorage::NVSStorage(const char *nameSpace)
{
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    // Open NVS handle
    err = nvs_open(nameSpace, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(this->tag, "Error (%s) opening NVS handle, nameSpace: %s", esp_err_to_name(err), nameSpace);
    }
    else
    {
        ESP_LOGI(this->tag, "NVS initialization successful, nameSpace: %s", nameSpace);
    }
}

NVSStorage::~NVSStorage()
{
    // Close NVS handle
    nvs_close(nvs_handle);
}

uint32_t NVSStorage::getUint32(const char *key, uint32_t defaultValue)
{
    uint32_t result;
    esp_err_t err = nvs_get_u32(nvs_handle, key, &result);
    switch (err)
    {
    case ESP_OK:
        return result;
        break;
    case ESP_ERR_NVS_NOT_FOUND:
        ESP_LOGW(this->tag, "Key %s not found, using default value %u", key, static_cast<unsigned int>(defaultValue));
        return defaultValue;
        break;
    default:
        ESP_LOGE(this->tag, "Error (%s) reading key %s!", esp_err_to_name(err), key);
        return defaultValue;
        break;
    }
}

void NVSStorage::setUint32(const char *key, uint32_t value)
{
    esp_err_t err = nvs_set_u32(nvs_handle, key, value);
    if (err != ESP_OK)
    {
        ESP_LOGE(this->tag, "Error (%s) writing key %s!", esp_err_to_name(err), key);
    }
    else
    {
        // Commit written value.
        // After setting any values, nvs_commit() must be called to ensure changes are written
        // to flash storage. Implementations may write to storage at other times,
        // but this is not guaranteed.
        err = nvs_commit(nvs_handle);
        if (err != ESP_OK)
        {
            ESP_LOGE(this->tag, "Error (%s) committing key %s!", esp_err_to_name(err), key);
        }
    }
}

float NVSStorage::getFloat(const char *key, float defaultValue)
{
    float result;
    // using c++ cast type conversion, directly call this->getUint32 to read float number
    uint32_t temp = this->getUint32(key, defaultValue);
    result = *reinterpret_cast<float *>(&temp);
    return result;
}

void NVSStorage::setFloat(const char *key, float value)
{
    // using c++ cast type conversion, directly call this->setUint32 to write float number
    uint32_t temp = *reinterpret_cast<uint32_t *>(&value);
    this->setUint32(key, temp);
}
