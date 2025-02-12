/*
 * API_Display.c
 *
 *  Created on: Feb 9, 2025
 *      Author: windows10
 */

#include "API_Display.h"
#include "ssd1306.h"  // Librería del controlador SSD1306
#include "ssd1306_fonts.h"  // Asegúrate de incluir el archivo que define las fuentes
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "API_System.h"

void Display_Init(void) {
    ssd1306_Init();  // Inicializa la pantalla OLED
    Display_Clear();
}

void Display_Clear(void) {
    ssd1306_Fill(Black);  // Llena la pantalla de negro (borra todo)
    Display_Update();
}

void Display_Print(char *text, uint8_t x, uint8_t y) {
    ssd1306_SetCursor(x, y);  // Establece la posición del cursor
    ssd1306_WriteString(text, Font_7x10, White);  // Escribe el texto en blanco
}

void Display_Update(void) {
    ssd1306_UpdateScreen();  // Refresca la pantalla para aplicar los cambios
}

