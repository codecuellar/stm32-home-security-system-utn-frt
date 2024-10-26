/*
 * API_GPIO.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Grupo 6: Candela Vera, Barrientos Lucas, Cuellar Agustin
 ******************************************************************************/

/* Includes *************************************************************************/
#include "main.h"
#include "API_GPIO.h"

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
void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();  // Habilita el reloj para el puerto del botón (PC13)
    __HAL_RCC_GPIOB_CLK_ENABLE();  // Habilita el reloj para el puerto de los LEDs (PB0, PB7, PB14)

    /* Configure GPIO pin Output Level for LEDs */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14, GPIO_PIN_RESET);

    /* Configure GPIO pin : USER_Btn_Pin (PC13) */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Configure GPIO pins : LD1 (PB0), LD2 (PB7), LD3 (PB14) */
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
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
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET;  // PC13: Botón de usuario
}


