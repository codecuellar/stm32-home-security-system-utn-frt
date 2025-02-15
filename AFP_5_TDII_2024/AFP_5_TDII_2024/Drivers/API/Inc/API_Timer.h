/*
 * API_Timer.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_TIMER_H_
#define API_INC_API_TIMER_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_adc.h"

extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;
extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;

extern uint32_t pir_timer;
extern uint32_t barrier_timer;



#endif /* API_INC_API_TIMER_H_ */
