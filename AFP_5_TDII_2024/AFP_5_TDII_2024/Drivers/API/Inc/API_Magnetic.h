/*
 * API_Magnetic.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_MAGNETIC_H_
#define API_INC_API_MAGNETIC_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

// Definir el puerto y pin del sensor magnético
#define MAGNETIC_GPIO_PORT   GPIOB
#define MAGNETIC_GPIO_PIN    GPIO_PIN_5

// Prototipos de funciones
void Magnetic_Init(void);        // Inicializa el sensor magnético
bool Magnetic_IsDetected(void);  // Devuelve true si se detectó apertura


#endif /* API_INC_API_MAGNETIC_H_ */
