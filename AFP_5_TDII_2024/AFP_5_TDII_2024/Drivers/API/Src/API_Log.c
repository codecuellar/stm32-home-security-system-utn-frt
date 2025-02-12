/*
 * API_Log.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 * Registro de eventos para sistema de seguridad
 ***********************************************/

#include "API_Log.h"
#include "API_System.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rtc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "API_System.h"

extern UART_HandleTypeDef huart3;  // UART3 (USB Virtual COM en NUCLEO-F429ZI)
extern systemStatus_t systemStatus; // Definido en API_System.h
extern RTC_HandleTypeDef hrtc;

// Buffer para mensajes
static char logMessage[150];

/**
  * @brief Obtiene marca de tiempo del RTC interno
  * @return Cadena con formato [DD-MM-AAAA HH:MM:SS]
  */
static char* getTimestamp() {
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;

    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

    snprintf(logMessage, sizeof(logMessage), "[%02d-%02d-%02d %02d:%02d:%02d]",
             date.Date, date.Month, 2000 + date.Year,
             time.Hours, time.Minutes, time.Seconds);

    return logMessage;
}

/**
  * @brief Registra un evento en el sistema
  * @param event: Cadena descriptiva del evento
  */
void logEvent(const char* event) {
    char timestamp[60];
    strcpy(timestamp, getTimestamp());

    snprintf(logMessage, sizeof(logMessage), "\r\n%s | %s", timestamp, event);

    // Envía por UART3 (Bluetooth/Consola)
    HAL_UART_Transmit(&huart3, (uint8_t*)logMessage, strlen(logMessage), HAL_MAX_DELAY);
}

/**
  * @brief Registra cambios de estado del sistema
  */
void logSystemStatus() {
    char stateDescription[80];

    switch(systemStatus.currentState) {
        case INITIALIZATION:
            snprintf(stateDescription, sizeof(stateDescription),
                    "INIT | LEDs: %s", systemStatus.ledsActive ? "ON" : "OFF");
            break;

        case ACTIVE:
            snprintf(stateDescription, sizeof(stateDescription),
                    "ACTIVE | Sensors: %s", systemStatus.sensorsArmed ? "ARMED" : "DISARMED");
            break;

        case ALARM:
            snprintf(stateDescription, sizeof(stateDescription),
                    "ALARM | Siren: %s", systemStatus.sirenActive ? "ON" : "OFF");
            break;

        default:
            strcpy(stateDescription, "UNKNOWN STATE");
            break;
    }

    logEvent(stateDescription);
}

