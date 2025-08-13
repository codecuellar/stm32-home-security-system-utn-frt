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



// DefiniciÃ³n del tipo de dato para representar los LEDs
typedef enum {
    LD1,  // LED verde en PB0
    LD2,  // LED azul en PB7
    LD3,  // LED rojo en PB14
	comp1, // RELE  PD7
	comp2,// BUZZER PA3
} comp_T;

// Tipo de dato para representar el estado de un boton
typedef bool buttonStatus_t;
typedef bool PIRStatus_t;
typedef bool MagStatus_t;

// Prototipos de las funciones

void Turn_On(comp_T componente);   // Encender LEDs o rele o buzzer
void Turn_Off(comp_T componente);  // Apagar LEDs o reles o buzzer
void LED_Toggle(comp_T componente); // Invertir el estado del LED
buttonStatus_t readButton_GPIO(void);  // Lectura del estado del boton
PIRStatus_t readPIR_GPIO(void);
MagStatus_t readMag_GPIO(void);

#endif // API_GPIO_H
