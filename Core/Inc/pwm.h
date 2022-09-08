/**
 * @file pwm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _PWM_H_
#define _PWM_H_

#include "tim.h"


void PWM_Init(TIM_HandleTypeDef *htim, uint32_t channel);

void PWM_Set_Angle(TIM_HandleTypeDef *htim, uint32_t channel, float angle);

#endif