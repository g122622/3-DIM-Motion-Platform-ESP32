/*
 * File: \WriterBot.cpp
 * Project: core
 * Created Date: 2024-07-07 17:42:55
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-12 14:33:02
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./WriterBot.h"
#include "utils/math/MathHelper.h"

void commandTask(void *pvParameters)
{
    WriterBot *WriterBotInstance = (WriterBot *)pvParameters;
    uint32_t dt = 0;            // delay between different commands in milliseconds
    uint8_t lastOpcode = 0xff;  // last executed command opcode, initialize to invalid value
    float lastData[2] = {0, 0}; // last executed command data, initialize to 0

    while (1)
    {
        // receive command from queue
        uint8_t *command = reinterpret_cast<uint8_t *>(WriterBotInstance->commandManager.receiveCommandFromQueue());

        // parse commands
        // the structure of a command is as follows:
        // [opcode * 1 byte][number * 2 bytes][reserved * 1 bytes][data * 8 bytes], 12 bytes in total.
        // the data is 2 float numbers in little-endian format
        uint8_t opcode = static_cast<uint8_t>(command[0]);
        uint16_t number = static_cast<uint16_t>(command[2] << 8 | command[1]); // little-endian
        // uint8_t reserved = static_cast<uint8_t>(command[3]);
        float data[2];
        data[0] = *reinterpret_cast<float *>(&command[4]);
        data[1] = *reinterpret_cast<float *>(&command[8]);

        // update current command number
        WriterBotInstance->commandManager.currentCommandNumber = number;

        printf("received command, opcode: %d , number: %d , data: %f, %f\n", opcode, number, data[0], data[1]);
        // execute command
        switch (opcode)
        {
        case 0x00: // G00 quick move (without dropping the pen)
            WriterBotInstance->liftPen();
            delay(300);
            WriterBotInstance->moveToPosition(data[0], data[1]);
            break;
        case 0x01: // G01 move with pen down, linear
            WriterBotInstance->dropPen();
            delay(300);
            WriterBotInstance->moveToPosition(data[0], data[1]);
            break;
        case 0x03: // M03 drop the pen
            WriterBotInstance->dropPen();
            break;
        case 0x04: // G04 delay for dt seconds
            delay(static_cast<uint32_t>(data[0] * 1000));
            break;
        case 0x05: // M05 lift the pen
            WriterBotInstance->liftPen();
            break;
        default:
            printf("Unknown command opcode: %d, this command will be ignored.\n", opcode);
            break;
        }

        if (false)
        {
            // calculate the delay between different commands,
            // based on the distance between the current and last command
            if (opcode == 0x00 || opcode == 0x01)
            {
                float distance = MathHelper.max(
                    MathHelper.abs(data[0] - lastData[0]),
                    MathHelper.abs(data[1] - lastData[1]));
                dt = static_cast<uint32_t>(200 + distance * 75);
            }
            else
            {
                dt = 100;
            }
            // delay for dt milliseconds, then execute the next command
            delay(dt);
        }

        // wait for motors to reach target position
        int cycleCount = 1;
        for (;;)
        {
            if (WriterBotInstance->xSlider.motor.pid.hasReachedTarget() && WriterBotInstance->ySlider.motor.pid.hasReachedTarget())
            {
                break;
            }
            if (cycleCount > 700)
            {
                ESP_LOGE("WriterBot", "Can't keep up! Motors did not reach target position in 7000 ms, this command will be ignored.");
                ESP_LOGE("WriterBot", "States: x.hasReachedTarget() = %d, y.hasReachedTarget() = %d",
                         WriterBotInstance->xSlider.motor.pid.hasReachedTarget(), WriterBotInstance->ySlider.motor.pid.hasReachedTarget());
                break;
            }
            delay(10);
            cycleCount++;
        }

        // update executed command count
        WriterBotInstance->commandManager.executedCommandCount++;
        // update last opcode
        lastOpcode = opcode;
        // update last data
        if (opcode == 0x00 || opcode == 0x01)
        {
            lastData[0] = data[0];
            lastData[1] = data[1];
        }

        // free memory, very important!
        vPortFree(command);
    }
}

// void penCompensationTask(void *pvParameters)
// {
//     WriterBot *WriterBotInstance = (WriterBot *)pvParameters;
//     while (1)
//     {
//         float realPos = WriterBotInstance->xSlider.getCurrentRealPosition();
//         if (realPos < 100 && realPos > 40) {
//             WriterBotInstance->penDownAngleOffset = 1;
//         } else {
//             WriterBotInstance->penDownAngleOffset = 0;}
//         delay(100);
//     }
// }

WriterBot::WriterBot(int X_in1, int X_in2, int X_pwm, int X_scl, int X_sda, int X_port,
                     int Y_in1, int Y_in2, int Y_pwm, int Y_scl, int Y_sda, int Y_port,
                     int pen_pwm)
    : xSlider(X_in1, X_in2, X_pwm, X_scl, X_sda, X_port, 140),
      ySlider(Y_in1, Y_in2, Y_pwm, Y_scl, Y_sda, Y_port, 210),
      statusLED(12),
      bluetoothLED(23),
      penServo(pen_pwm),
      powerADC(35, 11.0),
      storage("main")
{
    xTaskCreatePinnedToCore(commandTask, "commandTask",
                            4096 * 2, this, 3, &commandTaskHandle, 1);
    // xTaskCreatePinnedToCore(penCompensationTask, "penCompensationTask",
    //                         1024, this, 3, &commandTaskHandle, 1);
    this->moveToPosition(0, 0);
    statusLED.on();
}

/**
 * @brief Move the pen to the specified position.
 * @note The position coordinate is in millimeters.
 */
void WriterBot::moveToPosition(float x, float y)
{
    xSlider.setPosition(x);
    ySlider.setPosition(y);
}

void WriterBot::dropPen()
{
    if (xSlider.getTargetPosition() < 100 && xSlider.getTargetPosition() > 40)
    {
        this->penDownAngleOffset = 0.7;
    }
    else
    {
        this->penDownAngleOffset = 0;
    }
    penServo.setAngle(penDownAngle + penDownAngleOffset);
    this->isPenDown = true;
}

void WriterBot::liftPen()
{
    penServo.setAngle(penUpAngle);
    this->isPenDown = false;
}

WriterBot::~WriterBot()
{
    xSlider.reset();
    ySlider.reset();
    liftPen();
    vTaskDelete(this->commandTaskHandle);
    statusLED.off();
}
