/*
 * ApplicationCode.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Evan Poon
 *
 *  TODO - Check validity of comment for initialization of leds
 */

#ifndef APPLICATIONCODE_H
#define APPLICATIONCODE_H

#include <stdint.h>
#include "Scheduler.h"
#include "LED_Driver.h"
#include "Button_Driver.h"

#define USE_INTERRUPT_FOR_BUTTON 1

#define NAME_LENGTH 4 // Length of my name (Evan)
#define DELAY_MULT 25000

#define APPLICATION_GREEN_LED 0
#define APPLICATION_RED_LED 1

#define USE_LIMITED_RESOURCES 0


static uint8_t APPLICATION_current_led; // 0 is green, 1 is red


void APPLICATION_init(); // Initialize necessary hardware for this application

void APPLICATION_init_green_led(); // Initialize led driver
void APPLICATION_init_red_led();
void APPLICATION_init_green_and_red_led();

// Toggle 'on' status of LEDs
void APPLICATION_toggle_green_led();
void APPLICATION_toggle_red_led();

// Turn LEDs on
void APPLICATION_activate_green_led();
void APPLICATION_activate_red_led();

// Turn LEDs off
void APPLICATION_deactivate_green_led();
void APPLICATION_deactivate_red_led();

void APPLICATION_init_button(); // Initialize button driver
void APPLICATION_execute_button_polling_routine(); // Polling routine for when button is pressed down

void APPLICATION_init_button_interrupt_mode(); // Initialize button driver for interrupt mode

// Delay
void APPLICATION_delay(uint32_t time);

#endif /* APPLICATIONCODE_H_ */
