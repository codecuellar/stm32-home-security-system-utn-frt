/*
 * API_Delay.c
 *
 *  Created on: Oct 19, 2024
 *      Author: windows10
 */

#include "API_Delay.h"
#include "stm32f4xx_hal.h"  // Incluye la HAL de STM32 para usar HAL_GetTick()
#include "main.h"
#include <stdlib.h>
#include "API_System.h"

void delayInit(delay_t *delay, tick_t duration) {
    delay->duration = duration;
    delay->startTime = HAL_GetTick();
    delay->running = true;
}

bool delayRead(delay_t *delay) {
    if (delay->running) {
        if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
            delay->startTime = HAL_GetTick();
            return true;
        }
    }
    return false;
}

void delayWrite(delay_t *delay, tick_t duration) {
    delay->duration = duration;
}
