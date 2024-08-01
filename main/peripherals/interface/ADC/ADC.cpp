/*
 * File: \ADC.cpp
 * Project: ADC
 * Created Date: 2024-07-31 20:47:35
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-01 11:22:18
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "./ADC.h"

ADC::ADC(int pin, float zoomRatioIn)
{
    this->zoomRatio = zoomRatioIn;
    switch (pin)
    {
    case 36:
        this->ADC_UNIT = ADC_UNIT_1;
        this->ADC_CHANNEL = ADC_CHANNEL_0;
        break;
    case 39:
        this->ADC_UNIT = ADC_UNIT_1;
        this->ADC_CHANNEL = ADC_CHANNEL_3;
        break;
    case 34:
        this->ADC_UNIT = ADC_UNIT_1;
        this->ADC_CHANNEL = ADC_CHANNEL_6;
        break;
    case 35:
        this->ADC_UNIT = ADC_UNIT_1;
        this->ADC_CHANNEL = ADC_CHANNEL_7;
        break;
    case 32:
        this->ADC_UNIT = ADC_UNIT_1;
        this->ADC_CHANNEL = ADC_CHANNEL_4;
        break;
    case 33:
        this->ADC_UNIT = ADC_UNIT_1;
        this->ADC_CHANNEL = ADC_CHANNEL_5;
        break;
    case 4:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_0;
        break;
    case 0:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_1;
        break;
    case 2:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_2;
        break;
    case 15:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_3;
        break;
    case 13:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_4;
        break;
    case 12:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_5;
        break;
    case 14:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_6;
        break;
    case 27:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_7;
        break;
    case 25:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_8;
        break;
    case 26:
        this->ADC_UNIT = ADC_UNIT_2;
        this->ADC_CHANNEL = ADC_CHANNEL_9;
        break;
    default:
        ESP_LOGE("ADC", "Invalid pin number %d", pin);
        return;
    }

    //-------------ADC Init---------------//
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = this->ADC_UNIT,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    //-------------ADC Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, this->ADC_CHANNEL, &config));

    //-------------ADC Calibration Init---------------//
    this->didCalibration = initCalibration(this->ADC_UNIT, this->ADC_CHANNEL, ADC_ATTEN_DB_12, &adc_cali_handle);

    ESP_LOGI("ADC", "ADC initialized successfully with unit %d, channel %d", this->ADC_UNIT, this->ADC_CHANNEL);
}

bool ADC::initCalibration(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

    if (!calibrated)
    {
        ESP_LOGI("ADC", "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK)
        {
            calibrated = true;
        }
    }

    *out_handle = handle;
    if (ret == ESP_OK)
    {
        ESP_LOGI("ADC", "Calibration Success");
    }
    else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated)
    {
        ESP_LOGW("ADC", "eFuse not burnt, skip software calibration");
    }
    else
    {
        ESP_LOGE("ADC", "Invalid arg or no memory");
    }

    return calibrated;
}

/**
 * @brief Read the voltage from the ADC
 *
 * @return float The voltage read from the ADC, float value in volts
 * @note This function will return -1 if the ADC is not calibrated
 */
float ADC::readVoltage()
{
    int adc_raw;
    int voltageInt;

    if (do_calibration1_chan0)
    {
        ESP_ERROR_CHECK(adc_oneshot_read(this->adc_handle, this->ADC_CHANNEL, &adc_raw));
        ESP_ERROR_CHECK(adc_cali_raw_to_voltage(this->adc_cali_handle, adc_raw, &voltageInt));
        return static_cast<float>(voltageInt) * this->zoomRatio / 1000.0;
    }
    else
    {
        // 如果读取数据时还未校准，那么返回-1
        return -1;
    }
}

ADC::~ADC()
{
    // Tear Down
    adc_oneshot_del_unit(this->adc_handle);
    adc_cali_delete_scheme_line_fitting(this->adc_cali_handle);
}
