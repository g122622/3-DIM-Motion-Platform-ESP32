/*
 * File: \GPIO.cpp
 * Project: GPIO
 * Created Date: 2024-06-29 17:24:35
 * Author: Guoyi
 * -----
 * Last Modified: 2024-09-23 17:48:15
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./GPIO.h"

GPIO::GPIO(int pinNumIn, gpioModes modeIn, gpioPullModes pullIn)
{
    pinNum = pinNumIn;
    mode = modeIn;
    gpio_set_direction(static_cast<gpio_num_t>(pinNumIn), static_cast<gpio_mode_t>(modeIn));
    gpio_set_pull_mode(static_cast<gpio_num_t>(pinNumIn), static_cast<gpio_pull_mode_t>(pullIn));
}

void GPIO::setMode(int modeIn)
{
    mode = modeIn;
    gpio_set_direction(static_cast<gpio_num_t>(pinNum), static_cast<gpio_mode_t>(modeIn));
}

void GPIO::setPull(int pullIn)
{
    gpio_set_pull_mode(static_cast<gpio_num_t>(pinNum), static_cast<gpio_pull_mode_t>(pullIn));
}

void GPIO::write(uint32_t value)
{
    gpio_set_level(static_cast<gpio_num_t>(pinNum), value);
}

int GPIO::read()
{
    return gpio_get_level(static_cast<gpio_num_t>(pinNum));
}

GPIO::~GPIO()
{
    // do nothing
}
