/*
 * File: \PIDController.cpp
 * Project: PID
 * Created Date: 2024-06-29 10:31:46
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-17 13:42:47
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "PIDController.h"
/*
3. 自适应PID控制
利用自适应控制原理，让PID参数根据系统的实时工况（如误差大小、电机速度）自动调整。在电机静止时，PID控制器可以自动增大其增益，帮助电机克服静摩擦力矩启动；随着速度的提升，再逐步减小增益，确保系统稳定。

5. 摩擦补偿(放入电机的控制逻辑中)
基于对电机特性的了解，可以事先测量或估算出静摩擦力矩的大小，并在控制算法中直接补偿这部分力矩。这意味着在计算控制输出时，先加上一个足以克服静摩擦的固定值或根据负载变化动态调整的值。

6. 起动辅助策略
在电机起动初期，暂时增加给定的参考信号，比如通过在短时间内提高目标速度或施加一个短暂的过冲，帮助电机突破静摩擦力矩后迅速回到正常控制模式。
*/
PIDController::PIDController(float Kp, float Ki, float Kd)
{
    static int id = 1;
    this->_id = id;
    id++;

    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    this->prevError = 0;
    this->currentError = 0;
    this->errorIntegral = 0;

    this->targetValue = 0;
    this->currentValue = 0;

    this->outputLimit = 100;
    this->integralLimit = 100;

    this->deadzoneThreshold = 0;
}

/**
 * Update the PID controller with the current value and time step.
 * @param currentValueIn The current value of the process variable.
 * @param dt The time step.
 * @return The output of the PID controller.
 * @note The output is limited to the range [-outputLimit, outputLimit].
 * @note The integral term is limited to the range [-integralLimit, integralLimit].
 * @note The derivative term is calculated using the current error and the previous error.
 */
float PIDController::update(float currentValueIn, float dt)
{
    this->tickCount++;

    this->currentValue = currentValueIn;
    this->currentError = this->targetValue - this->currentValue;
    // Check if the error is within the deadzone. Then return zero output.
    if (MathHelper.abs(this->currentError) < this->deadzoneThreshold)
    {
        return 0;
    }

    float P = this->Kp * this->currentError;

    this->errorIntegral += this->currentError * dt;
    float I = MathHelper.limit(this->Ki * this->errorIntegral, this->integralLimit);

    float D = this->Kd * (this->currentError - this->prevError) / dt;
    this->prevError = this->currentError;

    // if ((this->tickCount % 2 == 0) && this->_id == 2)
    // {
    //     printf("[ID: %d] P: %f, I: %f, D: %f, target: %f, current: %f \n", this->_id, P, I, D, this->targetValue, this->currentValue);
    //     if (P > 400)
    //     {
    //         printf("\033[31m[ID: %d] P is too large!!! \n\033[0m", this->_id);
    //     }
    // }

    return MathHelper.limit(P + I + D, this->outputLimit);
}

void PIDController::setTarget(float targetValueIn)
{
    // Check if the target value has changed significantly.
    if (MathHelper.abs(targetValueIn - targetValue) > 0.01)
    {
        this->reset();
    }
    this->targetValue = targetValueIn;
}

/**
 * Set the output limit for the PID controller.
 * Note: the output is P + I + D.
 */
void PIDController::setOutputLimit(float outputLimitIn)
{
    this->outputLimit = outputLimitIn;
}

/**
 * Set the integral limit for the PID controller.
 * Note: the integral term is limited to the range [-integralLimit, integralLimit].
 */
void PIDController::setIntegralLimit(float integralLimitIn)
{
    this->integralLimit = integralLimitIn;
}

/**
 * Reset the PID controller to its initial state, without changing the gains.
 */
void PIDController::reset()
{
    this->prevError = 0;
    this->currentError = 0;
    this->errorIntegral = 0;
}

/**
 * Set the threshold for the deadzone.
 */
void PIDController::setDeadzoneThreshold(float deadzoneThresholdIn)
{
    this->deadzoneThreshold = deadzoneThresholdIn;
}
