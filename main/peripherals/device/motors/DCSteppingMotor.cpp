/*
 * File: \DCSteppingMotor.cpp
 * Project: motors
 * Created Date: 2024-06-29 17:49:56
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-12 14:16:17
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./DCSteppingMotor.h"

void pidTask(void *pvParameters)
{
    const int dt = 10; // 10ms delay between PID updates
    while (1)
    {
        // get this object from parameter, and convert it to DCSteppingMotor type
        DCSteppingMotor *thisObj = (DCSteppingMotor *)pvParameters;
        // set target angle for PID
        thisObj->pid.setTarget(thisObj->angle);
        // update PID
        float output = thisObj->pid.update(thisObj->encoder.readAngle(), dt);
        // set motor speed based on PID output
        thisObj->motor.setSpeedPercentage(output);
        // delay for 10ms
        delay(dt);
    }
}

DCSteppingMotor::DCSteppingMotor(int pin_in1_in, int pin_in2_in, int pin_pwm_in, int scl_in, int sda_in, int port_in)
    : motor(pin_in1_in, pin_in2_in, pin_pwm_in),
      encoder(scl_in, sda_in, port_in),
      pid(3, 0.001, 50)
{
    this->initialAngle = encoder.readAngle();
    this->angle = this->initialAngle;

    this->pid.setOutputLimit(50);
    this->pid.setIntegralLimit(10);
    this->pid.setDeadzoneThreshold(3);

    // create pidTask
    // pass this object as parameter to pidTask
    xTaskCreatePinnedToCore(pidTask, "pidTask-DCSteppingMotor",
                            4096, this, 3, &pidTaskHandle, 1);
}

void DCSteppingMotor::setAngle(float angleIn)
{
    this->angle = angleIn;
}

void DCSteppingMotor::step(float angle_step)
{
    this->angle += angle_step;
}

float DCSteppingMotor::getInitialAngle()
{
    return this->initialAngle;
}

/**
 * @brief Back to the initial angle.
 */
void DCSteppingMotor::reset()
{
    this->angle = this->initialAngle;
}

DCSteppingMotor::~DCSteppingMotor()
{
    vTaskDelete(this->pidTaskHandle);
}
