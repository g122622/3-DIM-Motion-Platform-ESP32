/*
 * File: \WriterBot.h
 * Project: core
 * Created Date: 2024-07-07 17:42:44
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-12 14:27:13
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef WRITERBOT_H
#define WRITERBOT_H

#include "peripherals/device/linearSlider/LinearSlider.h"
#include "peripherals/device/motors/servo/MG995.h"
#include "controller/command/CommandManager.h"
#include "peripherals/device/LED/LED.h"
#include "storage/NVSStorage.h"
#include "peripherals/interface/ADC/ADC.h"
#include "esp_log.h"

class WriterBot
{
public:
    WriterBot(int X_in1, int X_in2, int X_pwm, int X_scl, int X_sda, int X_port,
              int Y_in1, int Y_in2, int Y_pwm, int Y_scl, int Y_sda, int Y_port,
              int pen_pwm);
    ~WriterBot();
    void moveToPosition(float x, float y);
    void dropPen();
    void liftPen();

    LinearSlider xSlider;
    LinearSlider ySlider;
    CommandManager commandManager;
    LED statusLED;
    LED bluetoothLED;
    MG995 penServo;
    ADC powerADC;
    float penDownAngle = 92;
    float penDownAngleOffset = 0;
    float penUpAngle = 87;
    bool isPenDown = false;

private:
    TaskHandle_t commandTaskHandle;
    NVSStorage storage;
};

#endif // WRITERBOT_H
