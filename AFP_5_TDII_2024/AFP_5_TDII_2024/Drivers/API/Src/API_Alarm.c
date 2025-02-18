/*
 * API_Alarm.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#include "API_Control.h"
#include "API_Alarm.h"
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "API_System.h"
#include "API_Log.h"


#define ALARM_GPIO_PORT GPIOD
#define ALARM_GPIO_PIN  GPIO_PIN_11

bool alarma_activa = false;  // Inicialmente la alarma está desactivada

void Alarm_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitStruct.Pin = ALARM_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Salida push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(ALARM_GPIO_PORT, &GPIO_InitStruct);

    Alarm_Off();  // Asegurar que inicie apagada
}

void Alarm_On(void) {
	logEvent("Activando alarma...");  // ← Para ver si se llama antes de los 30s
    HAL_GPIO_WritePin(ALARM_GPIO_PORT, ALARM_GPIO_PIN, GPIO_PIN_SET);  // Activa la sirena
}

void Alarm_Off(void) {
    HAL_GPIO_WritePin(ALARM_GPIO_PORT, ALARM_GPIO_PIN, GPIO_PIN_RESET);  // Apaga la sirena
}

void check_alarms(void) {
    if (alarma_activa) {
        Alarm_On();
    } else {
        Alarm_Off();
    }
}



void set_alarma_estado(bool estado) {
    alarma_activa = estado;
}

