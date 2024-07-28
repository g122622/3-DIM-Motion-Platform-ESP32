/*
 * File: \LED.cpp
 * Project: LED
 * Created Date: 2024-07-28 10:08:16
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 11:12:44
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "./LED.h"

void LEDBlinkTask(void *pvParameters)
{
    LED *LEDInstance = (LED *)pvParameters;
    while (1)
    {
        xSemaphoreTake(LEDInstance->semapHandle, portMAX_DELAY);
        for (int i = 0; i < LEDInstance->blink_count; i++)
        {
            LEDInstance->on();
            delay(LEDInstance->blink_duration_ms);
            LEDInstance->off();
            delay(LEDInstance->blink_duration_ms);
        }
    }
}

LED::LED(int pin)
    : led_gpio(pin, gpioModes::_GPIO_MODE_OUTPUT)
{
    this->off();
    semapHandle = xSemaphoreCreateBinary();
    xTaskCreatePinnedToCore(LEDBlinkTask, "LED-Blink-Task",
                            1024, this, 10, &LEDBlinkTaskHandle, 1);
}

void LED::on()
{
    led_gpio.write(1);
    is_on = true;
}

void LED::off()
{
    led_gpio.write(0);
    is_on = false;
}

void LED::toggle()
{
    if (is_on)
        off();
    else
        on();
}

void LED::blink(int count, int duration_ms)
{
    blink_count = count;
    blink_duration_ms = duration_ms;
    xSemaphoreGive(semapHandle);
}

LED::~LED()
{
    vTaskDelete(LEDBlinkTaskHandle);
    vSemaphoreDelete(semapHandle);
    this->off();
}
