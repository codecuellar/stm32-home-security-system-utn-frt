/*
 * API_i2c.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"



extern I2C_HandleTypeDef hi2c1;  // Definimos la estructura de I2C

void MX_I2C1_Init(void); // Inicializa el I2C1


#endif /* API_INC_API_I2C_H_ */
