/*
 * API_Comm.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#include "API_Comm.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_tim.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "API_System.h"

/* Variables y handles */
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
TIM_HandleTypeDef htim_sensor; // Timer para retardos de sensores

/* Estructuras de configuración y estado */
system_status_t system_status;
system_config_t system_config;

/* Flags para control de temporizadores */
bool pir_timer_active = false;
bool magnetic_timer_active = false;

//-------------------------------------------
// Sección de comunicación UART/Bluetooth
//-------------------------------------------
void MX_USART2_UART_Init(void) {
    // Configuración inicial de USART2
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) Error_Handler();
}

void sendMessageBT(char *message) {
    // Envía mensajes por Bluetooth usando DMA (no bloqueante)
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)message, strlen(message));
}

//-------------------------------------------
// Sección de manejo de sensores
//-------------------------------------------
void Sensor_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == SENSOR_PIR_PIN) { // Reemplazar con el pin correcto (ej: GPIO_PIN_3)
        if (system_status.area_active && HAL_GPIO_ReadPin(SENSOR_PIR_PORT, SENSOR_PIR_PIN) == GPIO_PIN_SET && !pir_timer_active) {
            // Iniciar temporizador para retardo del PIR
            MX_TIM_SENSOR_Init(); // Configura TIM2/TIM5 según tu placa
            if (system_config.delay_pir != 0) {
                __HAL_TIM_SET_AUTORELOAD(&htim_sensor, (system_config.delay_pir * 1000) - 1);
            }
            HAL_TIM_Base_Start_IT(&htim_sensor);
            pir_timer_active = true;
        } else {
            // Detener temporizador si la alerta se desactiva
            pir_timer_active = false;
            HAL_TIM_Base_Stop_IT(&htim_sensor);
        }
    }
}

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == htim_sensor.Instance) {
        if (pir_timer_active) {
            sendMessageBT("Alerta: Movimiento detectado\n");
            pir_timer_active = false;
        }
    }
    }
*/
//-------------------------------------------
// Sección de inicialización general
//-------------------------------------------
void initCommSystem(void) {
    MX_USART2_UART_Init(); // Configura UART
    MX_TIM_SENSOR_Init();  // Inicializa timer para retardos
    // Configura interrupciones para el sensor PIR (ej: EXTI3)
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void MX_TIM_SENSOR_Init(void) {
    // Configuración del timer (ej: TIM2)
    htim_sensor.Instance = TIM2;
    htim_sensor.Init.Prescaler = 1600 - 1; // Ajusta según tu reloj
    htim_sensor.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim_sensor.Init.Period = 1000 - 1; // Valor por defecto
    HAL_TIM_Base_Init(&htim_sensor);
}
