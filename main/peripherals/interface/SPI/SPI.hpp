/*
 * File: \SPI.hpp
 * Project: SPI
 * Created Date: 2024-09-22 23:27:44
 * Author: Guoyi
 * -----
 * Last Modified: 2024-09-23 17:56:39
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <string.h>

class SPI
{
public:
    SPI(int SPI_Host_ID, int pin_mosi, int pin_miso, int pin_sclk, int pin_cs);
    ~SPI();
    void transmit(uint8_t *data, int lenInBytes);
    void receive(uint8_t *data, int lenInBytes);

private:
    int SPI_Host_ID;
    int pin_mosi;
    int pin_miso;
    int pin_sclk;
    int pin_cs;
    spi_device_handle_t spiHandle;

    // This function is called (in irq context!) just before a transmission starts. It will
    // set the D/C line to the value indicated in the user field.
    // 通过回调函数，实现DC自动控制，不需要手动控制DC线
    void lcd_spi_pre_transfer_callback(spi_transaction_t *t);
};
