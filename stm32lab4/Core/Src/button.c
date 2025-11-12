/*
 * button.c
 *
 *  Created on: Nov 9, 2025
 *      Author: PHITRUONGPC
 */
/*
 * input_reading.c
 *
 *  Created on: Oct 28, 2025
 *      Author: PHITRUONGPC
 */

#include "button.h"
//we aim to work with more than one buttons


#define LONG_PRESS_TIME     100   // 100 * 10ms = 1s
#define AUTO_REPEAT_TIME    20    // 200ms repeat

GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
GPIO_PinState debounceBuffer1[NO_OF_BUTTONS];
GPIO_PinState debounceBuffer2[NO_OF_BUTTONS];

int counterLongPress[NO_OF_BUTTONS];
int counterAutoRepeat[NO_OF_BUTTONS];

uint8_t flagShortPress[NO_OF_BUTTONS];
uint8_t flagLongPress[NO_OF_BUTTONS];

GPIO_TypeDef* ButtonPorts[NO_OF_BUTTONS] = {b0_GPIO_Port};
uint16_t ButtonPins[NO_OF_BUTTONS] = {b0_Pin};

int isButtonPressed(int index){
	if(index >= NO_OF_BUTTONS) return 0;
	if(flagShortPress[index]){
		flagShortPress[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int index){
	if(index >= NO_OF_BUTTONS) return 0;
	if(flagLongPress[index]){
		flagLongPress[index] = 0;
		return 1;
	}
	return 0;
}

void getKeyInput(){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		debounceBuffer2[i] = debounceBuffer1[i];
		debounceBuffer1[i] = HAL_GPIO_ReadPin(ButtonPorts[i], ButtonPins[i]);

		if(debounceBuffer1[i] == debounceBuffer2[i]){
			if(buttonBuffer[i] != debounceBuffer1[i]){
				buttonBuffer[i] = debounceBuffer1[i];

				if(buttonBuffer[i] == PRESSED_STATE){
					counterLongPress[i] = 0;
					counterAutoRepeat[i] = 0;
					flagShortPress[i] = 1; // detect 1 short click
				}
			} else {
				if(buttonBuffer[i] == PRESSED_STATE){
					counterLongPress[i]++;
					if(counterLongPress[i] >= LONG_PRESS_TIME){
						counterAutoRepeat[i]++;
						if(counterAutoRepeat[i] >= AUTO_REPEAT_TIME){
							counterAutoRepeat[i] = 0;
							flagLongPress[i] = 1; // repeated long press
						}
					}
				}
			}
		}
	}
}
