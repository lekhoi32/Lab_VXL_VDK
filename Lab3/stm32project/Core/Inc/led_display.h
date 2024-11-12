/*
 * led_display.h
 *
 *  Created on: Nov 4, 2024
 *      Author: ADMIN
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"
#include "global.h"
#define MAX_MATRIX 10
#define MAX_BUFF 4

void display7SEG(int number);
void updateClockBuffer(int, int);
void scanLed();

#endif /* INC_LED_DISPLAY_H_ */
