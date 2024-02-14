/*
 * main.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Omar Tarek
 */

#include "Gpt.h"

Gpt_ConfigurationType Gpt_Configuration = 
{
    /* Timer 0 */
    .TIM0_mode  = GPT_MODE_NORMAL,
    .TIM0_clk   = GPT_CLK_PRESCALER_1,
    .TIM0_out   = GPT_OUT_DISCONNECTED,
    /* Timer 1 */
    .TIM1_mode  = GPT_MODE_OFF,
    .TIM1_clk   = GPT_CLK_OFF,
    .TIM1A_out  = GPT_OUT_DISCONNECTED,
    .TIM1B_out  = GPT_OUT_DISCONNECTED,
    /* Timer 2 */
    .TIM2_mode  = GPT_MODE_OFF,
    .TIM2_clk   = GPT_CLK_OFF,
    .TIM2_out   = GPT_OUT_DISCONNECTED,
};

