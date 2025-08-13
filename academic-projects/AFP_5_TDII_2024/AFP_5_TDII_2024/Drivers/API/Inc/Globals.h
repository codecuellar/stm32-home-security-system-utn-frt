/*
 * Globals.h
 *
 *  Created on: Feb 13, 2025
 *      Author: ASUS
 */

#ifndef API_INC_GLOBALS_H_
#define API_INC_GLOBALS_H_

#include "Globals.h"
#include <stdint.h>
#include <stdbool.h>
#include "API_Delay.h"


// Declaraciones de variables globales (solo declaraciones, sin inicialización)
extern bool systemActive;
extern bool sensorsoff;
extern bool alertTriggered;
extern uint32_t alertStartTime;
extern uint8_t inputIndex;
extern int intentos;
extern int alarmainicio;
extern uint8_t continicio;
extern bool contfin;
extern delay_t delay1;  // Se declara siempre y cuando delay_t esté definido en API_Delay.h




#endif /* API_INC_GLOBALS_H_ */
