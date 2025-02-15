/*
 * API_Keypad.h
 *
 *  Created on: Feb 7, 2025
 *      Author: windows10
 */

#include "API_Keypad.h"
#include "API_GPIO.h"
#include "API_Delay.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include "API_System.h"

// Definición de pines para el teclado matricial
// Definición de pines para el teclado matricial

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} GPIO_Pin_t;

GPIO_Pin_t row_ports[] = {
    {GPIOF, GPIO_PIN_10},  // PF10
    {GPIOC, GPIO_PIN_0},   // PC0
    {GPIOC, GPIO_PIN_2},   // PC2
    {GPIOC, GPIO_PIN_3}    // PC3
};

GPIO_Pin_t col_ports[] = {
    {GPIOF, GPIO_PIN_12},  // PF12
    {GPIOF, GPIO_PIN_13},  // PF13
    {GPIOF, GPIO_PIN_14},  // PF14
    {GPIOF, GPIO_PIN_15}   // PF15
};

#define KEYPAD_ROW_GPIO_PIN   {GPIO_PIN_10, GPIO_PIN_0, GPIO_PIN_2, GPIO_PIN_3}

#define KEYPAD_COLUMN_GPIO_PIN  {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15}

keypad_t KeyPad;
bool keypad_active = false;

// Función para inicializar el teclado matricial
void KeyPad_Init(void) {
    GPIO_InitTypeDef gpio;

    // Configurar las columnas como salidas
    KeyPad.ColumnSize = 4;
    KeyPad.RowSize = 4;

    for (uint8_t i = 0; i < KeyPad.ColumnSize; i++) {
        gpio.Mode = GPIO_MODE_OUTPUT_PP;
        gpio.Pull = GPIO_NOPULL;
        gpio.Speed = GPIO_SPEED_FREQ_LOW;
        gpio.Pin = col_ports[i].pin;  // Usar el pin de la estructura col_ports
        HAL_GPIO_Init(col_ports[i].port, &gpio);  // Usar el puerto de la estructura col_ports
        HAL_GPIO_WritePin(col_ports[i].port, col_ports[i].pin, GPIO_PIN_SET); // Apagar columnas
    }

    // Configurar las filas como entradas con pull-up
    for (uint8_t i = 0; i < KeyPad.RowSize; i++) {
        gpio.Mode = GPIO_MODE_INPUT;
        gpio.Pull = GPIO_PULLUP;
        gpio.Speed = GPIO_SPEED_FREQ_LOW;
        gpio.Pin = row_ports[i].pin;  // Usar el pin de la estructura row_ports
        HAL_GPIO_Init(row_ports[i].port, &gpio);  // Usar el puerto de la estructura row_ports
    }

    keypad_active = true;
}

// Función para escanear el teclado matricial
uint16_t KeyPad_Scan(void) {
    uint16_t key = 0;

    for (uint8_t c = 0; c < KeyPad.ColumnSize; c++) {
        // Activar solo una columna
        for (uint8_t i = 0; i < KeyPad.ColumnSize; i++) {
            HAL_GPIO_WritePin(col_ports[i].port, col_ports[i].pin, GPIO_PIN_SET);
        }

        HAL_GPIO_WritePin(col_ports[c].port, col_ports[c].pin, GPIO_PIN_RESET);

        // Pequeño retardo no bloqueante
        delay_t debounce;
        delayInit(&debounce, 5);
        while (!delayRead(&debounce));

        // Leer filas
        for (uint8_t r = 0; r < KeyPad.RowSize; r++) {
            if (HAL_GPIO_ReadPin(row_ports[r].port, row_ports[r].pin) == GPIO_PIN_RESET) {
                // Esperar debounce
                delayInit(&debounce, 50);
                while (!delayRead(&debounce));

                if (HAL_GPIO_ReadPin(row_ports[r].port, row_ports[r].pin) == GPIO_PIN_RESET) {
                    key |= (1 << c);          // Columna activa
                    key |= (1 << (r + 8));    // Fila activa

                    // Esperar a que se suelte la tecla
                    while (HAL_GPIO_ReadPin(row_ports[r].port, row_ports[r].pin) == GPIO_PIN_RESET) {
                        delayInit(&debounce, 5);
                        while (!delayRead(&debounce));
                    }
                    return key;
                }
            }
        }
    }
    return key;
}

// Función para esperar la pulsación de una tecla con timeout
uint16_t KeyPad_WaitForKey(uint32_t Timeout_ms) {
    uint16_t keyRead;
    delay_t timeout;
    delayInit(&timeout, Timeout_ms);

    while (Timeout_ms == 0 || !delayRead(&timeout)) {
        keyRead = KeyPad_Scan();
        if (keyRead != 0) {
            KeyPad.LastKey = keyRead;
            return keyRead;
        }
    }

    KeyPad.LastKey = 0;
    return 0;
}

// Función para hacer sonar el buzzer
void buzz() {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    delay_t buzz_delay;
    delayInit(&buzz_delay, 20);
    while (!delayRead(&buzz_delay));
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
}

// Función para obtener el carácter correspondiente a la tecla presionada
char key_pad_get_char(uint32_t Timeout_ms) {
    switch (KeyPad_WaitForKey(Timeout_ms)) {
        case 0x0000: return 0;
        case 0x0101: buzz(); return '1';
        case 0x0201: buzz(); return '2';
        case 0x0401: buzz(); return '3';
        case 0x0801: buzz(); return 'A';
        case 0x0102: buzz(); return '4';
        case 0x0202: buzz(); return '5';
        case 0x0402: buzz(); return '6';
        case 0x0802: buzz(); return 'B';
        case 0x0104: buzz(); return '7';
        case 0x0204: buzz(); return '8';
        case 0x0404: buzz(); return '9';
        case 0x0804: buzz(); return 'C';
        case 0x0108: buzz(); return '*';
        case 0x0208: buzz(); return '0';
        case 0x0408: buzz(); return '#';
        case 0x0808: buzz(); return 'D';
        default: return 0;
    }
}

// Función para obtener un código PIN de 4 dígitos desde el teclado
char* key_pad_get_pin() {
    bool is_num = false;
    int i = 0;
    char val, *new_pin = malloc(sizeof(char) * 5); // 4 dígitos + '\0'

    do {
        val = key_pad_get_char(5000); // Timeout de 5 segundos
        if (val != 0) {
            is_num = (val >= '0' && val <= '9');
            if (is_num) {
                new_pin[i] = val;
                i++;
            }
        }
    } while (i < 4);

    new_pin[4] = '\0'; // Terminar el string
    return new_pin;
}
