/**
 * @file pwm.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "pwm.h"

#define CLK_SPEED 64E6
#define SERVO_RANGE 180
#define MILLISECOND 1E-3


void PWM_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
    HAL_TIM_PWM_Start(htim, channel);
}


void PWM_Set_Angle(TIM_HandleTypeDef *htim, uint32_t channel, float angle)
{
    // Determin counts per pulse
    float fPwm = CLK_SPEED/((htim->Init.Prescaler + 1)*(htim->Init.Period + 1));
    float cps = (htim->Init.Period + 1)*fPwm;

    // Determin pulse length to get the desisered angle on the servo (servos 1ms 0, 2ms 180)
    // Round down
    int pulse = (int)(cps*MILLISECOND*(0.5 + 2*angle/SERVO_RANGE));

    // There might be a HAL function for this but i cant find it
    switch (channel)
    {
        case TIM_CHANNEL_1:
            htim->Instance->CCR1 = pulse;
            break;

        case TIM_CHANNEL_2:
            htim->Instance->CCR2 = pulse;
            break;

        case TIM_CHANNEL_3:
            htim->Instance->CCR3 = pulse;
            break;

        case TIM_CHANNEL_4:
            htim->Instance->CCR4 = pulse;
            break;
    }
}


void PWM_Circle_Test(TIM_HandleTypeDef *htim, uint32_t channel1, uint32_t channel2)
{
    PWM_Set_Angle(htim, channel2, 82.5);
    PWM_Set_Angle(htim, channel1, 130);
    HAL_Delay(50);
    PWM_Set_Angle(htim, channel2, 99.5);
    PWM_Set_Angle(htim, channel1, 111);
    HAL_Delay(50);
    PWM_Set_Angle(htim, channel2, 115);
    PWM_Set_Angle(htim, channel1, 90);
    HAL_Delay(50);
    PWM_Set_Angle(htim, channel2, 99.5);
    PWM_Set_Angle(htim, channel1, 69);
    HAL_Delay(50);
    PWM_Set_Angle(htim, channel2, 82.5);
    PWM_Set_Angle(htim, channel1, 50);
    HAL_Delay(50);
    PWM_Set_Angle(htim, channel2, 65.5);
    PWM_Set_Angle(htim, channel1, 69);
    HAL_Delay(50);
    PWM_Set_Angle(htim, channel2, 50);
    PWM_Set_Angle(htim, channel1, 82.5);
    HAL_Delay(50);
    PWM_Set_Angle(htim, channel2, 65.5);
    PWM_Set_Angle(htim, channel1, 111);
    HAL_Delay(50); 
}