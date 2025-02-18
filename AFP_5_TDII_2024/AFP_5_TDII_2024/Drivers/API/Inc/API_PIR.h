/*
 * API_PIR.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_PIR_H_
#define API_INC_API_PIR_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

// Definir el puerto y pin del sensor PIR
#define PIR_GPIO_PORT   GPIOB
#define PIR_GPIO_PIN    GPIO_PIN_3

// Prototipos de funciones
void PIR_Init(void);       // Inicializa el sensor PIR y la interrupción
bool PIR_IsDetected(void); // Devuelve true si se detectó movimiento
void resetPIR(void);
extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


#endif /* API_INC_API_PIR_H_ */
