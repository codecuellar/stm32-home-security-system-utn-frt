/*
 * API_Display.h
 *
 *  Created on: Feb 9, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_DISPLAY_H_
#define API_INC_API_DISPLAY_H_

#include "stm32f4xx_hal.h"

// Inicializa el display OLED
void Display_Init(void);

// Borra la pantalla
void Display_Clear(void);

// Muestra un texto en una posición específica
void Display_Print(char *text, uint8_t x, uint8_t y);

// Refresca la pantalla para aplicar los cambios
void Display_Update(void);


#endif /* API_INC_API_DISPLAY_H_ */
