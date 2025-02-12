/*
 * API_System.c
 *
 *  Created on: Feb 9, 2025
 *      Author: windows10
 */


#include "API_System.h"
#include "API_Delay.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>

//UART_HandleTypeDef huart2;  // UART para comunicación serie

// Configuración de UART
static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        // Manejo de error
        Error_Handler();
    }
}

// Configuración de GPIO
static void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE();  // Habilitar reloj para GPIOB

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configurar un LED en PB0 como salida (puede cambiarse según necesidades)
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Inicializar el pin en bajo
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

// Configuración del Timer SysTick para retardos no bloqueantes
static void SystemClock_Config(void) {
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

// Función de inicialización global del sistema
void System_Init(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
}
