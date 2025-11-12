/*
 * button.h
 *
 *  Created on: Nov 9, 2025
 *      Author: PHITRUONGPC
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"

#define NO_OF_BUTTONS 1 //3 NUT
#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

int isButtonPressed(int index);
int isButtonLongPressed(int index);
void getKeyInput();


#endif /* INC_BUTTON_H_ */
