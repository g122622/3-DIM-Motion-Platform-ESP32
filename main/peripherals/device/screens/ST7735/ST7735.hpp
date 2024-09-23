/*
 * File: \ST7735.hpp
 * Project: ST7735
 * Created Date: 2024-09-22 23:24:32
 * Author: Guoyi
 * -----
 * Last Modified: 2024-09-23 18:29:34
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include "peripherals/interface/SPI/SPI.hpp"
#include "peripherals/interface/GPIO/GPIO.h"
#include "OS/time/delay.h"
#include "./defs.hpp"
#include "./fonts.hpp"

class ST7735
{
public:
    ST7735(int pin_dc_in, int pin_rst_in, int pin_bckl_in);
    ~ST7735();
    void Reset();
    void DrawPixel(uint16_t x, uint16_t y, uint16_t color);
    void WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
    void WriteString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);
    void FillRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
    void FillScreen(uint16_t color);
    void DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *data);
    void InvertColors(bool invert);

private:
    SPI spi;
    GPIO GPIO_DC;
    GPIO GPIO_RST;
    GPIO GPIO_BCKL;

    void Select();
    void Unselect();
    void WriteCommand(uint8_t cmd);
    void WriteData(uint8_t *buff, size_t buff_size);
    void ExecuteCommandList(const uint8_t *addr);
    void SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
};

ST7735::ST7735(int pin_dc_in, int pin_rst_in, int pin_bckl_in)
    : GPIO_DC(pin_dc_in, gpioModes::_GPIO_MODE_OUTPUT, gpioPullModes::GPIO_PULLUP_ONLY),
      GPIO_RST(pin_rst_in, gpioModes::_GPIO_MODE_OUTPUT, gpioPullModes::GPIO_PULLUP_ONLY),
      GPIO_BCKL(pin_bckl_in, gpioModes::_GPIO_MODE_OUTPUT, gpioPullModes::GPIO_PULLUP_ONLY),
      spi(2, 18, 4, 19, 21)
{
    Select();
    Reset();
    ExecuteCommandList(init_cmds1);
    ExecuteCommandList(init_cmds2);
    ExecuteCommandList(init_cmds3);
    Unselect();
}

ST7735::~ST7735()
{
}

void ST7735::Select()
{
    // esp-idf似乎不需要手动拉取CS线，直接写命令即可
    // HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);
}

void ST7735::Unselect()
{
    // esp-idf似乎不需要手动拉取CS线，直接写命令即可
    // HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_SET);
}

// Reset the display
void ST7735::Reset()
{
    this->GPIO_RST.write(0);
    delay(100);
    this->GPIO_RST.write(1);
    delay(100);
}

void ST7735::WriteCommand(uint8_t cmd)
{
    this->GPIO_DC.write(0);
    this->spi.transmit(&cmd, 1);
}

void ST7735::WriteData(uint8_t *buff, size_t buff_size)
{
    this->GPIO_DC.write(1);
    this->spi.transmit(buff, buff_size);
}

void ST7735::ExecuteCommandList(const uint8_t *addr)
{
    uint8_t numCommands, numArgs;
    uint16_t ms;

    numCommands = *addr++;
    while (numCommands--)
    {
        uint8_t cmd = *addr++;
        this->WriteCommand(cmd);

        numArgs = *addr++;
        // If high bit set, delay follows args
        ms = numArgs & ST7735_DELAY;
        numArgs &= ~ST7735_DELAY;
        if (numArgs)
        {
            WriteData((uint8_t *)addr, numArgs);
            addr += numArgs;
        }

        if (ms)
        {
            ms = *addr++;
            if (ms == 255)
                ms = 500;
            delay(ms);
        }
    }
}

void ST7735::SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    // column address set
    WriteCommand(ST7735_CASET);
    uint8_t data[] = {0x00, x0 + ST7735_XSTART, 0x00, x1 + ST7735_XSTART};
    WriteData(data, sizeof(data));

    // row address set
    WriteCommand(ST7735_RASET);
    data[1] = y0 + ST7735_YSTART;
    data[3] = y1 + ST7735_YSTART;
    WriteData(data, sizeof(data));

    // write to RAM
    WriteCommand(ST7735_RAMWR);
}

void ST7735::DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;

    Select();

    SetAddressWindow(x, y, x + 1, y + 1);
    uint8_t data[] = {color >> 8, color & 0xFF};
    WriteData(data, sizeof(data));

    Unselect();
}

void ST7735::WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;

    SetAddressWindow(x, y, x + font.width - 1, y + font.height - 1);

    for (i = 0; i < font.height; i++)
    {
        b = font.data[(ch - 32) * font.height + i];
        for (j = 0; j < font.width; j++)
        {
            if ((b << j) & 0x8000)
            {
                uint8_t data[] = {color >> 8, color & 0xFF};
                WriteData(data, sizeof(data));
            }
            else
            {
                uint8_t data[] = {bgcolor >> 8, bgcolor & 0xFF};
                WriteData(data, sizeof(data));
            }
        }
    }
}

/*
Simpler (and probably slower) implementation:

static void ST7735_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color) {
    uint32_t i, b, j;

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                ST7735_DrawPixel(x + j, y + i, color);
            }
        }
    }
}
*/

void ST7735::WriteString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor)
{
    Select();

    while (*str)
    {
        if (x + font.width >= ST7735_WIDTH)
        {
            x = 0;
            y += font.height;
            if (y + font.height >= ST7735_HEIGHT)
            {
                break;
            }

            if (*str == ' ')
            {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

    Unselect();
}

void ST7735::FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    // clipping
    if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;
    if ((x + w - 1) >= ST7735_WIDTH)
        w = ST7735_WIDTH - x;
    if ((y + h - 1) >= ST7735_HEIGHT)
        h = ST7735_HEIGHT - y;

    Select();
    SetAddressWindow(x, y, x + w - 1, y + h - 1);

    uint8_t data[] = {color >> 8, color & 0xFF};
    for (y = h; y > 0; y--)
    {
        for (x = w; x > 0; x--)
        {
            WriteData(data, sizeof(data));
        }
    }

    Unselect();
}

void ST7735::FillScreen(uint16_t color)
{
    FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

void ST7735::DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *data)
{
    if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
        return;
    if ((x + w - 1) >= ST7735_WIDTH)
        return;
    if ((y + h - 1) >= ST7735_HEIGHT)
        return;

    Select();
    SetAddressWindow(x, y, x + w - 1, y + h - 1);
    WriteData((uint8_t *)data, sizeof(uint16_t) * w * h);
    Unselect();
}

void ST7735::InvertColors(bool invert)
{
    Select();
    WriteCommand(invert ? ST7735_INVON : ST7735_INVOFF);
    Unselect();
}
