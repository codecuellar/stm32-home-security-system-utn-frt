/*
 * API_i2c.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#include "API_i2c.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"  // Incluir el archivo de cabecera de I2C
#include "stm32f4xx_hal_dma.h"  // Incluir el archivo de cabecera de DMA
#include <string.h>
#include <stdlib.h>
#include "API_System.h"



DMA_HandleTypeDef hdma_i2c1_rx;

/* Inicialización de I2C1 */
void I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;  // Velocidad estándar de 100 kHz
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler();
    }
}

