/*
 * API_GPIO.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Grupo 6: Candela Vera, Barrientos Lucas, Cuellar Agustin
 ******************************************************************************/

/* Includes *************************************************************************/
#include "main.h"
#include "API_GPIO.h"
#include "stdbool.h"

/* Defines *************************************************************************/
#define TURN_ON  GPIO_PIN_SET
#define TURN_OFF GPIO_PIN_RESET

/* Declaration of variables ***********************************************************/
// Estructura para manejar los LEDs
comp_T compx;
comp_T LDx;
/*** Function definition ************************************************************/
/**
 *  @brief GPIO Initialization Function
 *  @param None
 *  @retval None
 */


/**
 *  @brief Turn COMPONENTS On
 *  @param comp: Specify which LED (LD1, LD2, LD3) to turn ON
 *          or Specify which  extra component (relay , buzzer)to turn on
 *  @retval None
 */
void Turn_On(comp_T componente) {
    switch(componente) {
        case LD1:
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, TURN_ON);   // PF0: LED 1 (blue)
            break;
        case LD2:
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, TURN_ON);   // PF1: LED 2 (green)
            break;
        case LD3:
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, TURN_ON);  // PF2: LED 3 (red)
            break;
        case comp1:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, TURN_ON);  // PD7: RELE
            break;
        case comp2:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, TURN_ON);  // PA3: BUZZER
            break;

        default:
            break;
    }
}

/*
 *  @brief Turn COMPONENTS Off
 *  @param comp : Specify which LED (LD1, LD2, LD3) to turn OFF
 *         or Specify which extra component (relay , buzzer)to turn on
 *  @retval None
 */
void Turn_Off(comp_T componente) {
    switch(componente) {
        case LD1:
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0, TURN_OFF);   // PF0: LED 1 (blue)
            break;
        case LD2:
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_1, TURN_OFF);   // PF1: LED 2 (green)
            break;
        case LD3:
            HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2, TURN_OFF);  // PF2: LED 3 (red)
            break;
        case comp1:
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, TURN_OFF);  // PD7:RELE
            break;
        case comp2:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, TURN_OFF);  // PA3: BUZZER
            break;
        default:
            break;
    }
}

/**
 *  @brief Toggle LED State
 *  @param led: Specify which LED (LD1, LD2, LD3) to toggle
 *
 *  @retval None
 */
void LED_Toggle(comp_T componente) {
    switch(componente) {
        case LD1:
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_0);   // PF0: LED 1 (blue)
            break;
        case LD2:
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_1);   // PF1: LED 2 (green)
            break;
        case LD3:
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_2);  // PF2: LED 3 (red)
            break;
        default:
            break;
    }
}

/**
 *  @brief Read Button State
 *  @retval buttonStatus_t: true if button is pressed, false otherwise
 */
buttonStatus_t readButton_GPIO( void) {

	      return  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET; // PC13: Boton de usuario


}
PIRStatus_t readPIR_GPIO(void) {

	      return  HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_12) == GPIO_PIN_SET; // PF12: PIR

}
MagStatus_t readMag_GPIO(void) {

	      return  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET; // PA6: SENSOR MAGNETICO

}
