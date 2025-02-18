/*
 * API_Timer.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#include "API_Timer.h"
#include "API_Log.h"
#include "API_Comm.h"
#include "API_Control.h"
#include "API_Alarm.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"   // Asegúrate de incluir esta cabecera para el ADC
#include <string.h>
#include <stdlib.h>
#include "API_System.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_adc.h"


// Definir MAX_THRESHOLD
#define MAX_THRESHOLD 1000

// Declarar extern los temporizadores si no están definidos aquí
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

extern ADC_HandleTypeDef hadc1;


extern system_status_t system_status;
uint32_t pir_timer = 0;
uint32_t barrier_timer = 0;

uint32_t threshold = 1000;  // Umbral de ejemplo, REVISAR ESTO
uint16_t dutyCycle = 0;
uint8_t increase = 0;
uint16_t count_pwm = 0;

extern ADC_HandleTypeDef hadc1;


extern void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM10) {
        if (__HAL_TIM_GET_AUTORELOAD(&htim10) == 29999) {
            HAL_TIM_Base_Stop_IT(&htim10);
            HAL_UART_AbortReceive_IT(&huart2);
            /*default_configuration() Nota de agustin: Comento hasta encontrar el propósito de esa funcion (que no está definida)*/
        }
        if (__HAL_TIM_GET_AUTORELOAD(&htim10) == 9999) {
            // Aquí puedes reemplazar la llamada al DS1307 con tu lógica de RTC o temporalización.
        }
    }
    if (htim->Instance == TIM11) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        if(!system_status.barrier_alarmed && system_status.barrier_active) {
            HAL_ADC_Start_DMA(&hadc1, &threshold, 1);  // Inicia la conversión ADC
        }
    }
    if (htim->Instance == TIM5) {
        if ((int) threshold > MAX_THRESHOLD && system_status.barrier_active) {
            system_status.barrier_alarmed = true;
            barrier_timer = false;
            check_alarms();  // Revisa las alarmas
            HAL_ADC_Stop_DMA(&hadc1);  // Detiene la conversión ADC
            HAL_TIM_Base_Stop_IT(&htim5);
        }
    }
    if (htim->Instance == TIM9) {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET && system_status.area_active) {
            system_status.area_alarmed = true;
            pir_timer = false;
            check_alarms();
            HAL_TIM_Base_Stop_IT(&htim9);
        }
    }
    if (htim->Instance == TIM4) {
        HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
        HAL_TIM_Base_Stop_IT(&htim4);

        if(system_status.area_alarmed && system_status.barrier_alarmed) {
            system_status.area_alarmed = false;
            system_status.barrier_alarmed = false;
        }
        else if(system_status.area_alarmed && !system_status.barrier_alarmed) {
            system_status.area_alarmed = false;
        }
        else if(!system_status.area_alarmed && system_status.barrier_alarmed) {
            system_status.barrier_alarmed = false;
        }
    }
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
    dutyCycle = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);

    if (htim->Instance == TIM3) {
        count_pwm++;
        if (count_pwm % 1000) {
            if (dutyCycle >= __HAL_TIM_GET_AUTORELOAD(&htim3)) {
                increase = 0;
            }
            if (dutyCycle <= 0) {
                increase = 1;
            }

            if (increase) {
                dutyCycle += 1;
            } else {
                dutyCycle -= 1;
            }
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, dutyCycle);
        }
    }



	if (htim->Instance == TIM9) {
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET && system_status.area_active) {
			system_status.area_alarmed = true;
			pir_timer = false;
			check_alarms();
			HAL_TIM_Base_Stop_IT(&htim9);
		}
	}

	if (htim->Instance == TIM4) {
		HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
		HAL_TIM_Base_Stop_IT(&htim4);

		if(system_status.area_alarmed && system_status.barrier_alarmed){
			system_status.area_alarmed = false;
			system_status.barrier_alarmed = false;
		}
		else if(system_status.area_alarmed && !system_status.barrier_alarmed){
			system_status.area_alarmed = false;
		}
		else if(!system_status.area_alarmed && system_status.barrier_alarmed){
			system_status.barrier_alarmed = false;
		}
	}
}
