/**
  * @file    API_Debounce.c
  * @brief   Implementación del driver de anti-rebote utilizando una MEF
  */

#include "API_Debounce.h"
#include "API_Delay.h"      // Para el uso de retardos no bloqueantes
#include "main.h"           // Para acceder a los pines GPIO y las funciones de HAL
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "API_System.h"

// Variables y constantes privadas
static debounceState_t debounceState;   // Estado actual de la MEF de anti-rebote
static delay_t debounceDelay;           // Delay no bloqueante para anti-rebote

// Variable para detectar el flanco descendente de la pulsación
static bool_t buttonPressedFlag = false;

// Prototipos de funciones privadas
void buttonPressed();           // Función para manejar el evento de pulsación del botón
void buttonReleased();          // Función para manejar el evento de liberación del botón

/**
  * @brief  Inicialización de la MEF de anti-rebote
  */
void debounceFSM_init(void) {
    debounceState = BUTTON_UP;               // Estado inicial de la MEF
    delayInit(&debounceDelay, 40);           // Configuración de un retardo de 40 ms
}

/**
  * @brief  Actualización de la MEF de anti-rebote. Debe ser llamada periódicamente.
  */
void debounceFSM_update(void) {
    switch (debounceState) {
        case BUTTON_UP:
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                debounceState = BUTTON_FALLING;
                delayRead(&debounceDelay);   // Inicia el delay para el siguiente estado
            }
            break;

        case BUTTON_FALLING:
            if (delayRead(&debounceDelay)) {
                if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
                    debounceState = BUTTON_DOWN;
                    buttonPressed();         // Evento de pulsación detectado
                } else {
                    debounceState = BUTTON_UP;
                }
            }
            break;

        case BUTTON_DOWN:
            if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
                debounceState = BUTTON_RISING;
                delayRead(&debounceDelay);   // Inicia el delay para el siguiente estado
            }
            break;

        case BUTTON_RISING:
            if (delayRead(&debounceDelay)) {
                if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
                    debounceState = BUTTON_UP;
                    buttonReleased();        // Evento de liberación detectado
                } else {
                    debounceState = BUTTON_DOWN;
                }
            }
            break;

        default:
            debounceFSM_init();              // Reiniciar MEF en caso de error
            break;
    }
}

/**
  * @brief  Función que devuelve si el botón ha sido presionado (flanco descendente).
  * @retval true si el botón fue presionado, false en caso contrario.
  */
bool_t readKey(void) {
    if (buttonPressedFlag) {
        buttonPressedFlag = false;           // Reinicia el flag después de la lectura
        return true;
    }
    return false;
}

/**
  * @brief  Función de manejo del evento de pulsación del botón.
  */
void buttonPressed(void) {
    buttonPressedFlag = true;                // Marca el flag para indicar la pulsación
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);   // Alterna el estado del LED1 como ejemplo
}

/**
  * @brief  Función de manejo del evento de liberación del botón.
  */
void buttonReleased(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);  // Alterna el estado del LED3 como ejemplo
}
