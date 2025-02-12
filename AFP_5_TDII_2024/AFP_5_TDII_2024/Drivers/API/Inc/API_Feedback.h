/*
 * API_Feedback.h
 *
 *  Created on: Feb 8, 2025
 *      Author: windows10
 */

#ifndef API_INC_API_FEEDBACK_H_
#define API_INC_API_FEEDBACK_H_

#include <stdbool.h>

// Prototipos de funciones
void feedback_sendRejected(char *msg);
void feedback_sendAccepted(char *msg);
void feedback_sendInvalidPin(char *msg);
bool feedback_matchPin(char *pin1, char *pin2);

#endif /* API_INC_API_FEEDBACK_H_ */
