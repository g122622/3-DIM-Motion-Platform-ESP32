/*
 * File: \WriterBot.h
 * Project: core
 * Created Date: 2024-07-07 17:42:44
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-23 15:57:04
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
    MG995 penServo;
    float penDownAngle = 92;
    float penDownAngleOffset = 0;
    float penUpAngle = 87;
    bool isPenDown = false;
    CommandManager commandManager;

private:
    TaskHandle_t commandTaskHandle;
};

#endif // WRITERBOT_H
