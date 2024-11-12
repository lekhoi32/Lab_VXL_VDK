/*
 * fsm_manual.c
 *
 *  Created on: Nov 4, 2024
 *      Author: ADMIN
 */

#include "fsm_manual.h"

int preTimeRed = 5;
int preTimeYellow = 2;
int preTimeGreen = 3;

void fsm_manual_run(){
	switch(status){
	case MAN_MODE1:
		// return INIT status AUTO_RED_GREEN
		setTimer1(defaultTimeGreen*1000);
		setTimer2(1000);
		timeRed = defaultTimeRed;
		timeGreen = defaultTimeGreen;
		tempYellow = defaultTimeYellow;
		updateClockBuffer(timeRed--, timeGreen--);
		status = AUTO_RED_GREEN;
		break;
	case MAN_MODE2:
		// only red leds in both road1 and road2 are ON, other leds are OFF
//		setTrafficRed1();
//		setTrafficRed();
		// if button0 is pressed, status will move to MAN_MODE3
		if(is_button_pressed(0) == 1){
			status = MAN_MODE3;
			setTimer1(500);
			setTrafficOffall();
		}
		//blinking red led
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
			setTimer1(500);
		}
		//if button is pressed, tempRed value'll increase 1 unit
		//if value overcome 99, it'll return 1
		if(is_button_pressed(1) == 1){
			tempRed++;
			if(tempRed >99) tempRed = 1;
		}
		//if button3 is pressed, tempRed is assign for dedefaultTimeRed
		if(is_button_pressed(2) == 1){
			defaultTimeRed = tempRed ;
		}
		updateClockBuffer(2, defaultTimeRed);
		break;
	case MAN_MODE3:
		// only yellow led in both road1 and road2 are ON, other led are OFF
//		setTrafficYellow();
//		setTrafficYellow1();
		// if button0 is pressed, status will move to MAN_MODE4
		if(is_button_pressed(0) == 1){
			status = MAN_MODE4;
			setTimer1(500);
			setTrafficOffall();
		}
		//blinking yellow led
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin);
			HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
			setTimer1(500);
		}
		//if button is pressed, tempYellow value'll increase 1 unit
		//if value overcome 99, it'll return 1
		if(is_button_pressed(1) == 1){
			tempYellow++;
			if(tempYellow > 99) tempYellow = 1;
		}
		//if button3 is pressed, tempYellow is assign for dedefaultTimeYelow
		if(is_button_pressed(2) == 1){
			defaultTimeYellow = tempYellow ;
		}
		updateClockBuffer(3, defaultTimeYellow);
		break;
	case MAN_MODE4:
		// if button0 is pressed, status will move to MAN_MODE1
		if(is_button_pressed(0) == 1){
			if (defaultTimeRed < (defaultTimeGreen + defaultTimeYellow))
			{
				defaultTimeRed = preTimeRed;
				defaultTimeYellow = preTimeYellow;
				defaultTimeGreen = preTimeGreen;
			}
			else
			{
				preTimeRed = defaultTimeRed;
				preTimeYellow = defaultTimeYellow;
				preTimeGreen = defaultTimeGreen;
			}
			status = MAN_MODE1;
			setTrafficOffall();
		}
		// only green led in both road1 and road2 are ON, other led are OFF
//		setTrafficGreen();
//		setTrafficGreen1();
		//blinking Green Led
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
			HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
			setTimer1(500);
		}
		//if button is pressed, tempGreen value 'll increase 1 unit
		//if value overcome 99, it'll return 1
			if(is_button_pressed(1) == 1){
				tempGreen++;
				if(tempGreen > 99) tempGreen = 1;
			}
		//if button3 is pressed, tempGreen is assign for dedefaultTimeGreen
			if(is_button_pressed(2) == 1){
				defaultTimeGreen = tempGreen ;
			}
		updateClockBuffer(4, defaultTimeGreen);
		break;
	default:
			break;
	}
}
