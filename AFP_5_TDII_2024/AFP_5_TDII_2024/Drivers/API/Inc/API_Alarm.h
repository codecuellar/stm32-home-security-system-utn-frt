/*
 * API_Alarm.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_ALARM_H_
#define API_INC_API_ALARM_H_
#include "stm32f4xx_hal.h"

void Alarm_Init(void);
void Alarm_On(void);
void Alarm_Off(void);

// Declaración de la función check_alarms
void check_alarms(void);

extern bool alarma_activa;


#endif /* API_INC_API_ALARM_H_ */
