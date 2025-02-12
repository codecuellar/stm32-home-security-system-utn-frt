/*
 * API_System.h
 *
 *  Created on: Feb 9, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_SYSTEM_H_
#define API_INC_API_SYSTEM_H_


#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_tim.h"

void System_Init(void);  // Función para inicializar todo el sistema

typedef struct {
    bool area_active;
    bool barrier_active;
    bool system_active;
    bool area_alarmed;
    bool barrier_alarmed;
} system_status_t;

typedef struct {
    uint32_t delay_pir;
} system_config_t;

extern system_status_t system_status;
extern system_config_t system_config;
extern UART_HandleTypeDef huart2;

void Error_Handler(void);

#endif /* API_INC_API_SYSTEM_H_ */
