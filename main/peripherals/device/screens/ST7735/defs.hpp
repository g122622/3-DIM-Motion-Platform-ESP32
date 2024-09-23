/*
 * File: \ST7735.defs.hpp
 * Project: ST7735
 * Created Date: 2024-09-23 18:10:45
 * Author: Guoyi
 * -----
 * Last Modified: 2024-09-23 18:15:24
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#pragma once

#include "stdint.h"

#define ST7735_DELAY 0x80

#define ST7735_MADCTL_MY 0x80
#define ST7735_MADCTL_MX 0x40
#define ST7735_MADCTL_MV 0x20
#define ST7735_MADCTL_ML 0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH 0x04

#define LCD_HOST SPI2_HOST

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 27
#define PIN_NUM_CLK 19
#define PIN_NUM_CS 22
#define PIN_NUM_DC 21
#define PIN_NUM_RST 18
#define PIN_NUM_BCKL 5

// 1.44" display, default orientation
#define ST7735_IS_128X128 1
#define ST7735_WIDTH 128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 2
#define ST7735_YSTART 3
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_BGR)

// 1.44" display, rotate right
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 3
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// 1.44" display, rotate left
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 1
#define ST7735_YSTART 2
#define ST7735_ROTATION (ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_BGR)
*/

// 1.44" display, upside down
/*
#define ST7735_IS_128X128 1
#define ST7735_WIDTH  128
#define ST7735_HEIGHT 128
#define ST7735_XSTART 2
#define ST7735_YSTART 1
#define ST7735_ROTATION (ST7735_MADCTL_BGR)
*/

/****************************/

#define ST7735_NOP 0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID 0x04
#define ST7735_RDDST 0x09

#define ST7735_SLPIN 0x10
#define ST7735_SLPOUT 0x11
#define ST7735_PTLON 0x12
#define ST7735_NORON 0x13

#define ST7735_INVOFF 0x20
#define ST7735_INVON 0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E

#define ST7735_PTLAR 0x30
#define ST7735_COLMOD 0x3A
#define ST7735_MADCTL 0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_RDID1 0xDA
#define ST7735_RDID2 0xDB
#define ST7735_RDID3 0xDC
#define ST7735_RDID4 0xDD

#define ST7735_PWCTR6 0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define ST7735_BLACK 0x0000
#define ST7735_BLUE 0x001F
#define ST7735_RED 0xF800
#define ST7735_GREEN 0x07E0
#define ST7735_CYAN 0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW 0xFFE0
#define ST7735_WHITE 0xFFFF
#define ST7735_COLOR565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

// based on Adafruit ST7735 library for Arduino
static const uint8_t init_cmds1[] = { // Init for 7735R, part 1 (red or green tab)
    15,                               // 15 commands in list:
    ST7735_SWRESET, ST7735_DELAY,     //  1: Software reset, 0 args, w/delay
    150,                              //     150 ms delay
    ST7735_SLPOUT, ST7735_DELAY,      //  2: Out of sleep mode, 0 args, w/delay
    255,                              //     500 ms delay
    ST7735_FRMCTR1, 3,                //  3: Frame rate ctrl - normal mode, 3 args:
    0x01, 0x2C, 0x2D,                 //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2, 3,                //  4: Frame rate control - idle mode, 3 args:
    0x01, 0x2C, 0x2D,                 //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6,                //  5: Frame rate ctrl - partial mode, 6 args:
    0x01, 0x2C, 0x2D,                 //     Dot inversion mode
    0x01, 0x2C, 0x2D,                 //     Line inversion mode
    ST7735_INVCTR, 1,                 //  6: Display inversion ctrl, 1 arg, no delay:
    0x07,                             //     No inversion
    ST7735_PWCTR1, 3,                 //  7: Power control, 3 args, no delay:
    0xA2,
    0x02,             //     -4.6V
    0x84,             //     AUTO mode
    ST7735_PWCTR2, 1, //  8: Power control, 1 arg, no delay:
    0xC5,             //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3, 2, //  9: Power control, 2 args, no delay:
    0x0A,             //     Opamp current small
    0x00,             //     Boost frequency
    ST7735_PWCTR4, 2, // 10: Power control, 2 args, no delay:
    0x8A,             //     BCLK/2, Opamp current small & Medium low
    0x2A,
    ST7735_PWCTR5, 2, // 11: Power control, 2 args, no delay:
    0x8A, 0xEE,
    ST7735_VMCTR1, 1, // 12: Power control, 1 arg, no delay:
    0x0E,
    ST7735_INVOFF, 0, // 13: Don't invert display, no args, no delay
    ST7735_MADCTL, 1, // 14: Memory access control (directions), 1 arg:
    ST7735_ROTATION,  //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD, 1, // 15: set color mode, 1 arg, no delay:
    0x05},            //     16-bit color

#if (defined(ST7735_IS_128X128) || defined(ST7735_IS_160X128))
    init_cmds2[] = {     // Init for 7735R, part 2 (1.44" display)
        2,               //  2 commands in list:
        ST7735_CASET, 4, //  1: Column addr set, 4 args, no delay:
        0x00, 0x00,      //     XSTART = 0
        0x00, 0x7F,      //     XEND = 127
        ST7735_RASET, 4, //  2: Row addr set, 4 args, no delay:
        0x00, 0x00,      //     XSTART = 0
        0x00, 0x7F},     //     XEND = 127
#endif                   // ST7735_IS_128X128

    init_cmds3[] = {                                                                                                                // Init for 7735R, part 3 (red or green tab)
        4,                                                                                                                          //  4 commands in list:
        ST7735_GMCTRP1, 16,                                                                                                         //  1: Magical unicorn dust, 16 args, no delay:
        0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2d, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10, ST7735_GMCTRN1, 16,         //  2: Sparkles and rainbows, 16 args, no delay:
        0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10, ST7735_NORON, ST7735_DELAY, //  3: Normal display on, no args, w/delay
        10,                                                                                                                         //     10 ms delay
        ST7735_DISPON, ST7735_DELAY,                                                                                                //  4: Main screen turn on, no args w/delay
        100};                                                                                                                       //     100 ms delay
