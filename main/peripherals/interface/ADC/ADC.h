/*
 * File: \ADC.h
 * Project: ADC
 * Created Date: 2024-07-31 20:47:29
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-01 11:14:09
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include <stdio.h>
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

class ADC
{
private:
    adc_oneshot_unit_handle_t adc_handle;
    adc_cali_handle_t adc_cali_handle = NULL;
    bool do_calibration1_chan0 = false;

    adc_channel_t ADC_CHANNEL = ADC_CHANNEL_7;
    adc_unit_t ADC_UNIT = ADC_UNIT_1;

    bool initCalibration(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle);
    bool didCalibration = false;

    float zoomRatio = 1.0;

public:
    ADC(int pin, float zoomRatioIn);
    ~ADC();
    float readVoltage();
};
