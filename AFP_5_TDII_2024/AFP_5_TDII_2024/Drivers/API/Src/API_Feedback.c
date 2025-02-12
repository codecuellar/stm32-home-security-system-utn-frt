/*
 * API_Feedback.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */


/**
  * @file    API_Feedback.c
  * @author  Grupo 6: Candela Vera, Barrientos Lucas, Cuellar Agustin
  * @brief   Manejo de feedback por UART (mensajes de aceptación/rechazo).
  * @version 0.1
  */

#include "API_Feedback.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "API_System.h"

// UART para comunicación (USART3 en NUCLEO-F429ZI, ajustar según configuración en CubeMX)
extern UART_HandleTypeDef huart3;

/**
  * @brief  Envía mensaje de rechazo por UART (DMA).
  * @param  msg: Mensaje a enviar.
  * @retval None
  */
void feedback_sendRejected(char *msg) {
    HAL_UART_Transmit_DMA(&huart3, (uint8_t*) msg, strlen(msg));
}

/**
  * @brief  Envía mensaje de aceptación por UART (DMA).
  * @param  msg: Mensaje a enviar.
  * @retval None
  */
void feedback_sendAccepted(char *msg) {
    HAL_UART_Transmit_DMA(&huart3, (uint8_t*) msg, strlen(msg));
}

/**
  * @brief  Envía mensaje de PIN inválido por UART (DMA).
  * @param  msg: Mensaje a enviar.
  * @retval None
  */
void feedback_sendInvalidPin(char *msg) {
    HAL_UART_Transmit_DMA(&huart3, (uint8_t*) msg, strlen(msg));
}

/**
  * @brief  Compara dos cadenas de PIN.
  * @param  pin1: Primer PIN a comparar.
  * @param  pin2: Segundo PIN a comparar.
  * @retval true si coinciden, false en caso contrario.
  */
bool feedback_matchPin(char *pin1, char *pin2) {
    return (strcmp(pin1, pin2) == 0);
}
