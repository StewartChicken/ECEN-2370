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

#define NAME_LENGTH 4 // Length of my name (Evan)
#define DELAY_MULT 25000


void application_init(); // Initialize necessary hardware for this application

void init_green_led(); // Initialize led drivers
void init_red_led();
void init_green_and_red_led();

// Toggle 'on' status of LEDs
void toggle_green_led();
void toggle_red_led();

// Turn LEDs on
void activate_green();
void activate_red();

// Turn LEDs off
void deactivate_green();
void deactivate_red();

// Delay
void delay(uint32_t time);

#endif /* APPLICATIONCODE_H_ */
