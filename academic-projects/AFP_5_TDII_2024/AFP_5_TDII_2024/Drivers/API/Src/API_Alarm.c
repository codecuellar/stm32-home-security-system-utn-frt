/*
 * API_Alarm.c
 *
 *  Created on: Feb 10, 2025
 *      Author: windows10
 */


#include "API_Alarm.h"
#include "main.h"
#include "string.h"
#include "API_Display.h"
#include "API_GPIO.h"
#include "Globals.h"
#include "API_Delay.h"
#include "API_keypad_4x4.h"
#include "API_System.h"



extern UART_HandleTypeDef huart2;
// Activa la alarma (activa el rele)
  void activarAlarma(void) {
      //muestra en el display que la alarma se ha activado
	  Display_Clear();
	  Display_Print("ALARMA ACTIVA",0,0);
	  char mensaje1[20]= "ALARMA ACTIVADA\r\n";
	  HAL_UART_Transmit(&huart2, (uint8_t*) mensaje1, strlen(mensaje1), 100); //envia por bluetooth el mesnaje de alerta

      Turn_On(comp1);  // Activar rele
      sensorsoff=true; // cambia a false para que yaa no se lean los sensores

      while (alertTriggered) {  //  Mantiene el bucle hasta que se ingrese la clave correcta

            	  checkKeypad();  // Permite ingresar la clave incluso con la alarma encendida
          }
  }

  // Funcion que desactiva la alarma

  void desactivarAlarma(void) {
	  //muestra en el display que la alarma se ha deactivado
	  char mensaje2[23]= "ALARMA DESACTIVADA\r\n";
	  	  HAL_UART_Transmit(&huart2, (uint8_t*) mensaje2, strlen(mensaje2), 100); //envia por bluetooth el mesnaje de alerta

	  Display_Clear();
	  Display_Print("ALARMA DESACTIVADA ",0,0);
       Turn_Off(LD3); // Apagar LED rojo
       Turn_Off(comp1);  // Desactivar relÃ©
       alertTriggered = false;
       inputIndex = 0;
       systemActive = false;
       HAL_Delay(3000);
       SistemaOFF();

   }


  // Funcion que muestra una alerta en el DISPLAY y enciende el LED rojo

    void mostrarAlerta() {
  	  Turn_Off(LD2); // Apagar LED verde
  	  Turn_On(LD3); // Encender LED rojo
      char mensaje[18]= "ALERTA INTRUSO\r\n";
  	  HAL_UART_Transmit(&huart2, (uint8_t*) mensaje, strlen(mensaje), 100); //envia por bluetooth el mesnaje de alerta

  	  //muestra por el display el mensaje de alerta

        alarmainicio++;// suma 1 al contador de alarmainicio para que solo se guarde un tiempo en alertStartTime
      if ( alarmainicio ==1){ // solo se tomara el alertstartime una vez para que no se reinicie constantemente la cuenta
        alertStartTime = HAL_GetTick();
        alertTriggered = true;
     }
   }
