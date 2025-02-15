/*
 * API_Magnetic.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#include "API_Magnetic.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include "API_System.h"

// Variable para almacenar el estado del sensor magnético
static volatile bool magneticDetected = false;

// Inicialización del sensor magnético con interrupción EXTI
void Magnetic_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Habilitar el reloj del puerto GPIOD
    __HAL_RCC_GPIOD_CLK_ENABLE();

    // Configurar el pin PD0 como entrada con interrupción
    GPIO_InitStruct.Pin = MAGNETIC_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; // Interrupción en flanco de bajada (cuando se abre)
    GPIO_InitStruct.Pull = GPIO_PULLUP; // Activamos pull-up interno (depende del sensor)
    HAL_GPIO_Init(MAGNETIC_GPIO_PORT, &GPIO_InitStruct);

    // Habilitar la interrupción en el NVIC
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

// Función que devuelve si se ha detectado una apertura
bool Magnetic_IsDetected(void) {
    if (magneticDetected) {
        magneticDetected = false;  // Reseteamos la bandera
        return true;
    }
    return false;
}

// Callback de interrupción (se ejecuta cuando el sensor detecta apertura)
extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == MAGNETIC_GPIO_PIN) {
        magneticDetected = true; // Se ha detectado apertura de la puerta/ventana
    }
}

// Manejador de interrupción para EXTI0
/*void EXTI0_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(MAGNETIC_GPIO_PIN);
}
*/
