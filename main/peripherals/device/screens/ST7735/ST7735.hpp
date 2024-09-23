/*
 * File: \ST7735.hpp
 * Project: ST7735
 * Created Date: 2024-09-22 23:24:32
 * Author: Guoyi
 * -----
 * Last Modified: 2024-09-23 13:36:36
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include "peripherals/interface/SPI/SPI.hpp"

class ST7735
{
public:
    ST7735();
    ~ST7735();

private:
    SPI spi;
};

ST7735::ST7735()
    : spi(2, 18, 4, 19, 21)
{
    
}
