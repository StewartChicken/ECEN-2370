#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include <stdbool.h>
#include <stdint.h>
#include "GPIO_Driver.h"

// Button is in port A (GPIOA) pin 0

#define BUTTON_PORT GPIOA // CHECK THIS - THIS MAY BE THE CAUSE OF THE ERROR
#define BUTTON_PIN_NUMBER 0 // Button b1 lies on pin 0 of port A
#define BUTTON_IS_NOT_PRESSED 0
#define BUTTON_IS_PRESSED 1 

void BUTTON_initialize_button();
void BUTTON_enable_clock();
void BUTTON_disable_clock();
bool BUTTON_is_pressed(); // Return true if button is pressed

void BUTTON_initialize_interrupt_mode(); // Initialize button in interrupt mode

#endif