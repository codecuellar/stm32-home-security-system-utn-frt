/*
 * API_Delay.c
 *
 *  Created on: Oct 20, 2024
 *      Author: windows10
 */

#include "API_Delay.h"
#include "stm32f4xx_hal.h"

void delayInit(delay_t *delay, tick_t duration) {
    delay->duration = duration;
    delay->running = false;
}

bool_t delayRead(delay_t *delay) {
    if (!delay->running) {
        delay->startTime = HAL_GetTick();
        delay->running = true;
    } else if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
        delay->running = false;
        return true;
    }
    return false;
}

void delayWrite(delay_t *delay, tick_t duration) {
    delay->duration = duration;
}



