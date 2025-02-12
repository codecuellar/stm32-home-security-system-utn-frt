/*
 * API_Log.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_LOG_H_
#define API_INC_API_LOG_H_

#include <stdint.h>
#include <stdbool.h>


// Estados del sistema (de API_System.h)
typedef enum {
    INITIALIZATION,
    ACTIVE,
    ALERT_PIR,
    ALERT_MAGNETIC,
    ALARM,
	SYSTEM_RESET
} SystemState;

// Estructura de estado del sistema
typedef struct {
    SystemState currentState;
    bool sensorsArmed;
    bool ledsActive;
    bool sirenActive;
} systemStatus_t;

// Funciones públicas
void logEvent(const char* event);
void logSystemStatus(void);


#endif /* API_INC_API_LOG_H_ */
