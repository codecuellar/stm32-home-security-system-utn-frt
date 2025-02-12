/*
 * API_Control.c
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#include "API_Control.h"
#include "API_Feedback.h"
#include "stm32f4xx_hal.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "API_Keypad.h"
#include "API_Alarm.h"
#include "API_Comm.h"
#include "API_GPIO.h"
#include "API_System.h"

#define SYSTEM_PIN "1234" // Cambiar por el PIN real

void initControl(void) {
    deactivateSystem(); // Al inicio, el sistema está desactivado
}

char readKeypad(void) {
    char key = '\0';  // Inicializa la tecla con un valor nulo

    key = scanKeypad();  // Suponiendo que esta función escanea y devuelve la tecla presionada

    if (key != '\0') {  // Si se detecta una tecla presionada
        return key;
    } else {
        return '\0';  // No se presionó ninguna tecla
    }
}

bool checkPIN(void) {
    char enteredPIN[5] = {0};  // Buffer para el PIN ingresado
    for (int i = 0; i < 4; i++) {
        enteredPIN[i] = readKeypad(); // Leer tecla presionada
    }
    return (strcmp(enteredPIN, SYSTEM_PIN) == 0);
}

void activateSystem(void) {
    sendMessageBT("Sistema activado"); // Enviar mensaje por Bluetooth
    commandAccepted();
}

void deactivateSystem(void) {
    stopAlarm(); // Apagar la alarma
    sendMessageBT("Sistema desactivado");
    commandAccepted();
}

void commandAccepted(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // LED indicador
    HAL_Delay(200);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}

void commandRejected(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}


