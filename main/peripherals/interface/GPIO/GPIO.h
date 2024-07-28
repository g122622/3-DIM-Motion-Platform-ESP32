/*
 * File: \GPIO.h
 * Project: GPIO
 * Created Date: 2024-06-29 17:24:46
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-28 10:31:40
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

class GPIO
{
public:
    GPIO(int pinNumIn, gpioModes modeIn);
    void setMode(int mode);
    void write(uint32_t value);
    int read();
    ~GPIO();

private:
    int pinNum;
    int mode;
};

#endif
