/*
 * LED_Driver.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Evan Poon
 *
 */

#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include "GPIO_Driver.h"

#define GREEN_LED 0
#define RED_LED 1

#define GREEN_LED_PIN_NUMBER GPIO_PIN_13
#define RED_LED_PIN_NUMBER GPIO_PIN_14

[[maybe_unused]] static GPIO_Handle_t red_led_handle;
[[maybe_unused]] static GPIO_Handle_t green_led_handle;

void LED_initialize_led(uint8_t led_number); // Initializes red or green led
void LED_enable_clock(uint8_t led_number); // Enable clock for specific led
void LED_enable_led(uint8_t led_number); // Turns red or green led on
void LED_disable_led(uint8_t led_number); // Turns red or green led off
void LED_toggle_led(uint8_t led_number); // Toggle either red or green led

#endif

