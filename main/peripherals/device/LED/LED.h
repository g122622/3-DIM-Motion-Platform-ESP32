/*
 * File: \LED.h
 * Project: LED
 * Created Date: 2024-07-28 10:08:26
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 11:12:37
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include "peripherals/interface/GPIO/GPIO.h"
#include "utils/time/delay.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class LED
{
public:
    LED(int pin);
    ~LED();
    void on();
    void off();
    void toggle();
    void blink(int count, int duration_ms);

private:
    GPIO led_gpio;
    bool is_on = false;
    TaskHandle_t LEDBlinkTaskHandle;
    SemaphoreHandle_t semapHandle;
    friend void LEDBlinkTask(void *pvParameters);
    int blink_count = 0;
    int blink_duration_ms = 0;
};

void LEDBlinkTask(void *pvParameters);
