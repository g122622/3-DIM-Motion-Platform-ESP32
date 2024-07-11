/*
 * File: \DCSteppingMotor.h
 * Project: motors
 * Created Date: 2024-06-29 17:50:09
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-11 14:31:06
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#ifndef DCSTEPPINGMOTOR_H
#define DCSTEPPINGMOTOR_H

#include "peripherals/device/motors/SimpleDCMotor.h"
#include "peripherals/device/MT6701/MT6701.h"
#include "controller/PID/PIDController.h"
#include "utils/time/delay.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class DCSteppingMotor
{
public:
    DCSteppingMotor(int pin_in1_in, int pin_in2_in, int pin_pwm_in, int scl_in, int sda_in, int port_in);
    ~DCSteppingMotor();

    void setAngle(float angle);
    void step(float angle_step);
    void reset();
    SimpleDCMotor motor;
    MT6701 encoder;
    PIDController pid;

private:

    float angle, initialAngle;
    TaskHandle_t pidTaskHandle;

    // declare pidTask as friend function to access private data members
    friend void pidTask(void *pvParameters);
};

#endif // DCSTEPPINGMOTOR_H
