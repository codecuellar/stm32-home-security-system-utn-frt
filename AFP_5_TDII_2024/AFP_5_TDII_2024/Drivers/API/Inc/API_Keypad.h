/*
 * API_Keypad.h
 *
 *  Created on: Feb 7, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_KEYPAD_H_
#define API_INC_API_KEYPAD_H_
#define KEYPAD_VALUE_HASH '#'

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

// Definimos la estructura del teclado matricial
typedef struct {
    uint8_t RowSize;
    uint8_t ColumnSize;
    uint16_t LastKey;
} keypad_t;

// Variables globales
extern keypad_t KeyPad;
extern bool keypad_active;

// Funciones de inicialización y manejo del teclado
void KeyPad_Init(void);
uint16_t KeyPad_Scan(void);
uint16_t KeyPad_WaitForKey(uint32_t Timeout_ms);
char key_pad_get_char(uint32_t Timeout_ms);
char* key_pad_get_pin(void);
void buzz(void);

#endif /* API_INC_API_KEYPAD_H_ */
