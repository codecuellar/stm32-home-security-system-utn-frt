/**
  * @file    API_Debounce.h
  * @brief   Encabezado del driver de anti-rebote para botones usando una MEF
  */

#ifndef API_DEBOUNCE_H
#define API_DEBOUNCE_H

#include "API_Delay.h"       // Para el uso de la estructura de delay no bloqueante
#include "stm32f4xx_hal.h"   // Para el acceso a los GPIO y las funciones de HAL
#include <stdbool.h>         // Para el uso de tipos booleanos

// Definición del tipo de dato bool_t para representar valores booleanos
typedef bool bool_t;

// Definición de los estados de la MEF de anti-rebote
typedef enum {
    BUTTON_UP,         // Estado cuando el botón está sin presionar
    BUTTON_FALLING,    // Estado en transición al presionar el botón
    BUTTON_DOWN,       // Estado cuando el botón está presionado
    BUTTON_RISING      // Estado en transición al soltar el botón
} debounceState_t;

// Declaración de funciones del API de anti-rebote

/**
  * @brief  Inicializa la MEF de anti-rebote.
  * @note   Esta función debe llamarse una vez al inicio del programa.
  */
void debounceFSM_init(void);

/**
  * @brief  Actualiza el estado de la MEF de anti-rebote.
  * @note   Esta función debe llamarse periódicamente en el loop principal.
  */
void debounceFSM_update(void);

/**
  * @brief  Lee el estado del botón después de detectar el flanco descendente.
  * @retval true si el botón fue presionado, false en caso contrario.
  * @note   Esta función solo retorna true una vez por cada pulsación.
  */
bool_t readKey(void);

#endif // API_DEBOUNCE_H
