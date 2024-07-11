/*
 * File: \PWM.cpp
 * Project: PWM
 * Created Date: 2024-06-29 11:21:01
 * Author: Guoyi
 * -----
 * Last Modified: 2024-07-08 01:05:09
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./PWM.h"

PWM::PWM(int pin, uint32_t freq)
{
    static int timer_num = 0; // static variable to keep track of timer number used for PWM
    Logger.info("Creating PWM object, timer_num: %d \n", timer_num);
    if (timer_num > 3)
    {
        Logger.error("PWM timer number exceeds 3 \n");
        return;
    }

    this->pin = pin;
    this->freq = freq;

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,                // timer mode
        .duty_resolution = LEDC_TIMER_12_BIT,              // resolution of PWM duty
        .timer_num = static_cast<ledc_timer_t>(timer_num), // timer index
        .freq_hz = freq,                                   // frequency of PWM signal
        .clk_cfg = LEDC_AUTO_CLK,                          // auto select the source clock
        .deconfigure = false,                              // keep the timer running after initialization
    };
    ledc_timer_config(&ledc_timer);

    /*
     prepare individual configuration for each channel of LED controller, by selecting:
     - channel number of the controller
     - initial output duty cycle, set to 0
     - GPIO number of LED connected to the channel
     - speed mode, high or low
     - timer used for the channel
     @note: if different channels use the same timer, then their frequency and bit number are the same
    */

    ledc_channel_config_t ledc_channel =
        {.gpio_num = pin,
         .speed_mode = LEDC_HIGH_SPEED_MODE,
         .channel = static_cast<ledc_channel_t>(timer_num), // channel number
         .timer_sel = static_cast<ledc_timer_t>(timer_num),
         .duty = 0,
         .hpoint = 0,
         .flags = {
             .output_invert = LEDC_INTR_DISABLE,
         }};

    ledc_channel_config(&ledc_channel);

    timer_num_this = timer_num;
    timer_num++;
};

/**
 * @brief Set the duty cycle of the PWM signal
 * @param percentage The duty cycle of the PWM signal, in percentage (0-100)
 * @return None
 * @note The duty cycle is set in percentage, and the actual duty cycle is calculated based on the timer resolution.
 */
void PWM::setDuty(float percentage)
{
    if (percentage > 100)
        percentage = 100;
    if (percentage < 0)
        percentage = 0;

    // Note: the number 4096 is determined by the resolution of the timer
    // if the timer resolution is 12 bits, then 4096 = 2^12
    // if you want to change the resolution, you need to also modify the calculation of duty
    uint32_t duty = static_cast<uint32_t>(0.01f * percentage * 4096);

    // The channel parameter is not used as an enumeration, and must be passed as an integer value.
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(timer_num_this), duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, static_cast<ledc_channel_t>(timer_num_this));
    this->duty = duty;
}

void PWM::setFrequency(uint32_t freq)
{
    return; // TODO: implement this
}
