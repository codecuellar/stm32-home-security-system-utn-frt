/*
 * API_Control.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_CONTROL_H_
#define API_INC_API_CONTROL_H_

#include <stdbool.h>
#include <string.h> // Para usar strcmp

// Mensajes de feedback
#define USER_PIN_REJECTED "\r\nUser Pin Rejected!"
#define COMMAND_REJECTED "\r\nCommand Rejected!"
#define COMMAND_ACCEPTED "\r\nCommand Accepted!"
#define SYSTEM_DEACTIVED "\r\nCommand Rejected, System is not active!"
#define ALARM_ALREADY_ACTIVED "\r\nCommand Rejected, Alarm already activated!"
#define ALARMS_ALREADY_ACTIVED "\r\nCommand Rejected, Alarms already activated!"
#define ALARM_ALREADY_DEACTIVED "\r\nCommand Rejected, Alarm already deactivated!"
#define ALARMS_ALREADY_DEACTIVED "\r\nCommand Rejected, Alarms already deactivated!"

// Representación del estado del sistema
struct system_status_s
{
    bool area_active;
    bool barrier_active;
    bool system_active;
    bool area_alarmed;
    bool barrier_alarmed;
};


// Configuración del sistema
//typedef struct {
    //char pin[5];  // PIN de 4 dígitos + '\0'
//} system_config_t;


/* Prototipos de funciones */
void initControl(void); // Inicializar el control del sistema
bool checkPIN(void); // Verificar el PIN ingresado
void activateSystem(void); // Activar el sistema
void deactivateSystem(void); // Desactivar el sistema
void commandAccepted(void); // Indicar que un comando fue aceptado
void commandRejected(void); // Indicar que un comando fue rechazado
char readKeypad(void);  //modificado a char
void default_configuration(void);
void stopAlarm(void);
char scanKeypad(void);  // Declaración de la función para que pueda ser usada


// Funciones adicionales
void start_sequence(void);
void activeDeactive(void);
void setOrReset(void);
void getSymbols(void);
bool checkSymbol(void);
void clear_vector(void);
void boot_system(void);
void check_magnetic_sensor(void); // Nueva función para leer el sensor magnético

void command_accepted(const char *message);
void command_rejected(const char *message);
void user_pin_rejected(const char *message);
bool matchPin(const char *pin_user, const char *pin_system);

#endif /* API_INC_API_CONTROL_H_ */
