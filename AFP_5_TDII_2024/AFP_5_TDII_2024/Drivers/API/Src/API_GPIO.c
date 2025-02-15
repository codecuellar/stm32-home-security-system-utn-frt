/*
 * API_GPIO.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Grupo 6: Candela Vera, Barrientos Lucas, Cuellar Agustin
 ******************************************************************************/

/* Includes *************************************************************************/
#include "main.h"
#include "API_GPIO.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include "API_System.h"

/* Defines *************************************************************************/
#define LED_ON  GPIO_PIN_SET
#define LED_OFF GPIO_PIN_RESET

/* Declaration of variables ***********************************************************/
// Estructura para manejar los LEDs
led_T LDx;

/*** Function definition ************************************************************/
/**
 *  @brief GPIO Initialization Function
 *  @param None
 *  @retval None
 */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|Alarm_Pin|LD3_Pin|GPIO_PIN_4
                          |GPIO_PIN_6|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, KeypadF12_Pin|KeypadF13_Pin|KeypadF14_Pin|KeypadF15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Keypad_Pin */
  GPIO_InitStruct.Pin = Keypad_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Keypad_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : KeypadC0_Pin KeypadC2_Pin KeypadC3_Pin */
  GPIO_InitStruct.Pin = KeypadC0_Pin|KeypadC2_Pin|KeypadC3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin Alarm_Pin LD3_Pin PB4
                           PB6 LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|Alarm_Pin|LD3_Pin|GPIO_PIN_4
                          |GPIO_PIN_6|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : KeypadF12_Pin KeypadF13_Pin KeypadF14_Pin KeypadF15_Pin */
  GPIO_InitStruct.Pin = KeypadF12_Pin|KeypadF13_Pin|KeypadF14_Pin|KeypadF15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : PD11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SENSOR_MAGNETIC_Pin */
  GPIO_InitStruct.Pin = SENSOR_MAGNETIC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SENSOR_MAGNETIC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SENSOR_PIR_Pin */
  GPIO_InitStruct.Pin = SENSOR_PIR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(SENSOR_PIR_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/**
 *  @brief Turn LED On
 *  @param led: Specify which LED (LD1, LD2, LD3) to turn ON
 *  @retval None
 */
void LED_On(led_T led) {
    switch(led) {
        case LD1:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, LED_ON);   // PB0: LED 1 (green)
            break;
        case LD2:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, LED_ON);   // PB7: LED 2 (blue)
            break;
        case LD3:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_ON);  // PB14: LED 3 (red)
            break;
        default:
            break;
    }
}

/**
 *  @brief Turn LED Off
 *  @param led: Specify which LED (LD1, LD2, LD3) to turn OFF
 *  @retval None
 */
void LED_Off(led_T led) {
    switch(led) {
        case LD1:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, LED_OFF);   // PB0: LED 1 (green)
            break;
        case LD2:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, LED_OFF);   // PB7: LED 2 (blue)
            break;
        case LD3:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_OFF);  // PB14: LED 3 (red)
            break;
        default:
            break;
    }
}

/**
 *  @brief Toggle LED State
 *  @param led: Specify which LED (LD1, LD2, LD3) to toggle
 *  @retval None
 */
void LED_Toggle(led_T led) {
    switch(led) {
        case LD1:
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);   // PB0: LED 1 (green)
            break;
        case LD2:
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);   // PB7: LED 2 (blue)
            break;
        case LD3:
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);  // PB14: LED 3 (red)
            break;
        default:
            break;
    }
}

/**
 *  @brief Read Button State
 *  @retval buttonStatus_t: true if button is pressed, false otherwise
 */
buttonStatus_t readButton_GPIO(void) {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET;  // PC13: BotÃ³n de usuario
}
