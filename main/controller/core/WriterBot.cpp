/*
 * File: \WriterBot.cpp
 * Project: core
 * Created Date: 2024-07-07 17:42:55
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-18 13:12:55
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
        case 0x00: // M00 quick move (without dropping the pen)
            WriterBotInstance->liftPen();
            // delay(500);
            WriterBotInstance->moveToPosition(data[0], data[1]);
            break;
        case 0x01: // M01 move with pen down, linear
            WriterBotInstance->dropPen();
            WriterBotInstance->moveToPosition(data[0], data[1]);
            break;
        case 0x03: // M03 drop the pen
            WriterBotInstance->dropPen();
            break;
        case 0x04: // M04 delay for dt seconds
            delay(static_cast<uint32_t>(data[0] * 1000));
            break;
        case 0x05: // G05 lift the pen
            WriterBotInstance->liftPen();
            break;
        default:
            printf("Unknown command opcode: %d, this command will be ignored.\n", opcode);
            break;
        }

        // calculate the delay between different commands,
        // based on the distance between the current and last command
        if ((opcode == 0x00 && lastOpcode == 0x00) || (opcode == 0x01 && lastOpcode == 0x01))
        {
            float distance = MathHelper.max(
                MathHelper.abs(data[0] - lastData[0]), MathHelper.abs(data[1] - lastData[1]));
            dt = static_cast<uint32_t>(100 + distance * 150);
        }
        else
        {
            dt = 100;
        }
        // delay for dt milliseconds, then execute the next command
        delay(dt);

        // update executed command count
        WriterBotInstance->commandManager.executedCommandCount++;
        // update last opcode
        lastOpcode = opcode;
        // update last data
        lastData[0] = data[0];
        lastData[1] = data[1];

        // free memory, very important!
        vPortFree(command);
    }
}

WriterBot::WriterBot(int X_in1, int X_in2, int X_pwm, int X_scl, int X_sda, int X_port,
                     int Y_in1, int Y_in2, int Y_pwm, int Y_scl, int Y_sda, int Y_port,
                     int pen_pwm)
    : xSlider(X_in1, X_in2, X_pwm, X_scl, X_sda, X_port),
      ySlider(Y_in1, Y_in2, Y_pwm, Y_scl, Y_sda, Y_port),
      penServo(pen_pwm)
{
    xTaskCreatePinnedToCore(commandTask, "commandTaskHandle",
                            4096 * 2, this, 3, &commandTaskHandle, 1);
    this->moveToPosition(0, 0);
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
    penServo.setAngle(penDownAngle);
    this->isPenDown = true;
}

void WriterBot::liftPen()
{
    penServo.setAngle(penUpAngle);
    this->isPenDown = false;
}

WriterBot::~WriterBot()
{
    xSlider.setPosition(0);
    ySlider.setPosition(0);
    liftPen();
    vTaskDelete(this->commandTaskHandle);
}
