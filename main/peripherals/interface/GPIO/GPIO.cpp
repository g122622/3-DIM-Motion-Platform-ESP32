/*
 * File: \GPIO.cpp
 * Project: GPIO
 * Created Date: 2024-06-29 17:24:35
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 10:32:08
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./GPIO.h"

GPIO::GPIO(int pinNumIn, gpioModes modeIn)
{
    pinNum = pinNumIn;
    mode = modeIn;
    gpio_set_direction(static_cast<gpio_num_t>(pinNumIn), static_cast<gpio_mode_t>(modeIn));
}

void GPIO::setMode(int modeIn)
{
    mode = modeIn;
    gpio_set_direction(static_cast<gpio_num_t>(pinNum), static_cast<gpio_mode_t>(modeIn));
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
