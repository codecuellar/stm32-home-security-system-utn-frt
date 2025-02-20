/*
 * API_System.c
 *
 *  Created on: Feb 10, 2025
 *      Author: windows10
 */


#include "API_System.h"
#include "main.h"
#include "Globals.h"
#include "API_Delay.h"
#include "API_keypad_4x4.h"
#include "API_Display.h"
#include "API_GPIO.h"


// Funcion que Inicia el sistema

  void SystemON(void) {
      // reincia las variables clave para volver a funcionar
	  sensorsoff= false;
	  alarmainicio = 0;
      intentos = 0;
      // Muestra en la pantalla que el sistema se esta iniciando
      Display_Clear();
      Display_Print("Iniciando Sistema",0,0);
      Display_Print("GRUPO 6 - TDII =)",0,15);

      // arreglo para poder usar la funcion de retardo no bloqueante

      continicio = 0; //contador inicial del bucle
      contfin = false; // contador final del bucle
      while (!contfin) {
              if (delayRead(&delay1)) {
                  LED_Toggle(LD1); // Toggle LED Azul
                  continicio++;

                  if (continicio >= 8) { // 4 ON + 4 OFF = 8 cambios
                      contfin = true;
                      Turn_Off(LD1); // Apagar LED Azul
                      systemActive = true; // Activar el sistema
                  }
              }
          }

  }

  // Funcion que Apaga el sistema
  void SistemaOFF(void) {

	  Turn_Off(LD2);  //apaga el led verde
	  Turn_Off(LD3); // apaga el led rojo
	  // Muestra en la pantalla que el sistema se esta apagando
	  Display_Clear();
	  Display_Print("APAGANDO SISTEMA",0,0);

      // arreglo apra poder usar la funcion de retardo no bloqueante

      continicio = 0;
      contfin = false;
      while (!contfin) {
            if (delayRead(&delay1)) {
                LED_Toggle(LD1); // Toggle LED Azul
                continicio++;

                if (continicio >= 8) { // 4 ON + 4 OFF = 8 cambios
                    contfin = true;
                    Turn_Off(LD1); // Apagar LED Azul

                }
            }
        }

      Display_Clear();


  }
