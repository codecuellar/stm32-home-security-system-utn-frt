/*
 * API_Delay.h
 *
 *  Created on: Oct 19, 2024
 *      Author: windows10
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t tick_t;

typedef struct {
    tick_t startTime;
    tick_t duration;
    bool running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);
#endif


#endif /* API_INC_API_DELAY_H_ */
