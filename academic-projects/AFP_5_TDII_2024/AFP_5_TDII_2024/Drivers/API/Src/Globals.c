/*
 * Globals.c
 *
 *  Created on: Feb 13, 2025
 *      Author: ASUS
 */

#include "Globals.h"
#include "API_Delay.h"


// Definición de las variables globales
bool systemActive = false; //indica que el sistema esta activo
bool sensorsoff= false; // variable que controla la pantalla no muestre alertaas  una vez la alarma se active
bool  alertTriggered = false; // indica que se a detectado una alerta
uint32_t alertStartTime = 0;
uint8_t inputIndex = 0;
int intentos = 0;//intentos realizados
int alarmainicio = 0;// variable que controla que solo se inicie el contador una vez y no varias por señales de otros sensores

// variables para el loop de parpadeo del led azul  al encender y apagar
uint8_t continicio = 0;
bool contfin = false;
delay_t delay1;  // Se inicializará en el código (por ejemplo, mediante delayInit())

