/*
 * File: \GPIO.h
 * Project: GPIO
 * Created Date: 2024-06-29 17:24:46
 * Author: Guoyi
 * -----
 * Last Modified: 2024-09-23 17:48:07
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#ifndef GPIO_H
#define GPIO_H

#include "driver/gpio.h"

typedef enum
{
    _GPIO_MODE_DISABLE = GPIO_MODE_DEF_DISABLE,                                                         /*!< GPIO mode : disable input and output             */
    _GPIO_MODE_INPUT = GPIO_MODE_DEF_INPUT,                                                             /*!< GPIO mode : input only                           */
    _GPIO_MODE_OUTPUT = GPIO_MODE_DEF_OUTPUT,                                                           /*!< GPIO mode : output only mode                     */
    _GPIO_MODE_OUTPUT_OD = ((GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)),                               /*!< GPIO mode : output only with open-drain mode     */
    _GPIO_MODE_INPUT_OUTPUT_OD = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT) | (GPIO_MODE_DEF_OD)), /*!< GPIO mode : output and input with open-drain mode*/
    _GPIO_MODE_INPUT_OUTPUT = ((GPIO_MODE_DEF_INPUT) | (GPIO_MODE_DEF_OUTPUT)),                         /*!< GPIO mode : output and input mode                */
} gpioModes;

typedef enum
{
    GPIO_PULLUP_ONLY,     /*!< Pad pull up            */
    GPIO_PULLDOWN_ONLY,   /*!< Pad pull down          */
    GPIO_PULLUP_PULLDOWN, /*!< Pad pull up + pull down*/
    GPIO_FLOATING,        /*!< Pad floating           */
} gpioPullModes;

class GPIO
{
public:
    GPIO(int pinNumIn, gpioModes modeIn, gpioPullModes pullIn = GPIO_FLOATING);
    void setMode(int mode);
    void setPull(int pull);
    void write(uint32_t value);
    int read();
    ~GPIO();

private:
    int pinNum;
    int mode;
};

#endif
