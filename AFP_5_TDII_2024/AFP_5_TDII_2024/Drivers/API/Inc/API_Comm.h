/*
 * API_Comm.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_COMM_H_
#define API_INC_API_COMM_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h" // Incluir para GPIO_PIN_3, GPIOB, etc.
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_tim.h"

#define SENSOR_PIR_PIN    GPIO_PIN_3
#define SENSOR_PIR_PORT   GPIOB


/* Declaración de variables globales */
/*extern system_status_t system_status;*/
/*extern system_config_t system_config;*/
extern UART_HandleTypeDef huart2;  // solo está declarado, no definido

/* Prototipos de funciones */
void MX_USART2_UART_Init(void);
void sendMessageBT(char *message);
void initCommSystem(void);
void Sensor_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void Error_Handler(void); // Declaración de la función Error_Handler
void MX_TIM_SENSOR_Init(void); // Prototipo añadido

#endif /* API_INC_API_COMM_H_ */
