/*
 * API_PIR.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#include "API_PIR.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include "API_System.h"

// Variable para almacenar el estado del PIR
static volatile bool pirDetected = false;

// Inicialización del PIR con interrupción EXTI
void PIR_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Habilitar el reloj del puerto GPIO
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Configurar el pin del PIR como entrada con interrupción
    GPIO_InitStruct.Pin = PIR_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; // Interrumpe en flanco de subida
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PIR_GPIO_PORT, &GPIO_InitStruct);

    // Habilitar la interrupción en el NVIC
    HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);  // Ajusta la prioridad según necesites
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

// Función que devuelve si se ha detectado movimiento
bool PIR_IsDetected(void) {
    if (pirDetected) {
        pirDetected = false;  // Reseteamos la bandera
        return true;
    }
    return false;
}

// Callback de interrupción (se ejecuta cuando el PIR detecta movimiento)
/*void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == PIR_GPIO_PIN) {
      pirDetected = true; // Se ha detectado movimiento
    }
}
*/
// Manejador de interrupción para EXTI3 (ajustar según el pin usado)
void EXTI3_IRQHandler(void) {
    if (__HAL_GPIO_EXTI_GET_IT(PIR_GPIO_PIN) != RESET) {  // Verificar si la interrupción es del pin correcto
        __HAL_GPIO_EXTI_CLEAR_IT(PIR_GPIO_PIN);  // Limpiar la bandera de interrupción
        pirDetected = true;  // Actualizar la bandera de detección
    }
}

