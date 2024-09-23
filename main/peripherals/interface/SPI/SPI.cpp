/*
 * File: \SPI.cpp
 * Project: SPI
 * Created Date: 2024-09-23 13:31:51
 * Author: Guoyi
 * -----
 * Last Modified: 2024-09-23 13:39:57
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 * 
 * ------------------------------------
 */

#include "./SPI.hpp"

void SPI::lcd_spi_pre_transfer_callback(spi_transaction_t *t)
{
    // TODO dc is not cs
    int dc = (int)t->user;
    gpio_set_level(static_cast<gpio_num_t>(this->pin_cs), dc);
}

// SPI1 can be used as GPSPI only on ESP32
// SPI1_HOST = 0, ///< SPI1
// SPI2_HOST = 1, ///< SPI2
// SPI3_HOST = 2, ///< SPI3 (如果有的话)
SPI::SPI(int SPI_Host_ID, int pin_mosi, int pin_miso, int pin_sclk, int pin_cs)
{
    this->pin_mosi = pin_mosi;
    this->pin_miso = pin_miso;
    this->pin_sclk = pin_sclk;
    this->pin_cs = pin_cs;
    this->SPI_Host_ID = SPI_Host_ID;

    spi_device_handle_t spi;
    spi_bus_config_t buscfg = {
        .mosi_io_num = pin_mosi,
        .miso_io_num = pin_miso,
        .sclk_io_num = pin_sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 16 * 320 * 2 + 8};
    std::function<void(spi_transaction_t *)> cb = std::bind(&SPI::lcd_spi_pre_transfer_callback, this, std::placeholders::_1);
    spi_device_interface_config_t devcfg = {
        .mode = 0,                                          // SPI mode 0
        .clock_speed_hz = 25 * 1000 * 1000,                 // Clock out at 50 MHz
        .spics_io_num = pin_cs,                             // CS pin
        .queue_size = 7,                                    // We want to be able to queue 7 transactions at a time
        .pre_cb = (cb.target<void(spi_transaction_t *)>()), // Specify pre-transfer callback to handle D/C line
    };

    esp_err_t ret;
    // Initialize the SPI bus
    ret = spi_bus_initialize(static_cast<spi_host_device_t>(SPI_Host_ID - 1), &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    // Attach the LCD to the SPI bus
    ret = spi_bus_add_device(static_cast<spi_host_device_t>(SPI_Host_ID - 1), &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
    this->spiHandle = spi;
}

SPI::~SPI()
{
    spi_bus_remove_device(this->spiHandle);
    spi_bus_free(static_cast<spi_host_device_t>(this->SPI_Host_ID - 1));
}

void SPI::transmit(uint8_t *data, int lenInBytes)
{
    spi_transaction_t trans;
    memset(&trans, 0, sizeof(spi_transaction_t));
    trans.length = lenInBytes * 8;
    trans.tx_buffer = data;
    trans.user = (void *)0;
    spi_device_queue_trans(this->spiHandle, &trans, portMAX_DELAY);
}

void SPI::receive(uint8_t *data, int lenInBytes)
{
    spi_transaction_t trans;
    memset(&trans, 0, sizeof(spi_transaction_t));
    trans.length = lenInBytes * 8;
    trans.rx_buffer = data;
    trans.user = (void *)1;
    spi_device_queue_trans(this->spiHandle, &trans, portMAX_DELAY);
}
