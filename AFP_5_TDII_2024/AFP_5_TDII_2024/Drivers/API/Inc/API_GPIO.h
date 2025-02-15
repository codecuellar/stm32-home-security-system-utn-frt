/*
 * API_GPIO.h
 *
 *  Created on: Sep 14, 2024
 *      Author: Grupo 6: Candela Vera, Barrientos Lucas, Cuellar Agustin
 *      Function of driver: Driver que contiene funciones para manejo de puertos GPIO que utiliza funciones
 *      de la HAL de STM32 Nucleo F429ZI
 */

#ifndef API_GPIO_H
#define API_GPIO_H

#include "stdint.h"
#include "stdbool.h"  // Para el uso de bool en C
#include "stm32f4xx_hal.h"

// DefiniciÃ³n del tipo de dato para representar los LEDs
typedef enum {
    LD1,  // LED verde en PB0
    LD2,  // LED azul en PB7
    LD3   // LED rojo en PB14
} led_T;

// Tipo de dato para representar el estado de un botÃ³n
typedef bool buttonStatus_t;

// Prototipos de las funciones
void MX_GPIO_Init(void);  // InicializaciÃ³n del GPIO
void LED_On(led_T led);   // Encender LED
void LED_Off(led_T led);  // Apagar LED
void LED_Toggle(led_T led); // Invertir el estado del LED
buttonStatus_t readButton_GPIO(void);  // Lectura del estado del botÃ³n

#endif // API_GPIO_H
