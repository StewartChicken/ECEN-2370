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
#include "Timer_Driver.h"

#define GREEN_LED 0
#define RED_LED 1

#define GREEN_LED_PIN_NUMBER GPIO_PIN_13
#define RED_LED_PIN_NUMBER GPIO_PIN_14

#define RED_LED_DEFAULT_PRIORITY 35
#define GREEN_LED_DEFAULT_PRIORITY 57
#define ELEVATED_PRIORITY 20

#define TIMER_PRESCALER_VALUE 18000 // Divide the clock by 180,000 such that it becomes a 10kHz clock
#define TIM2_AUTO_RELOAD_VALUE 10000 // Counter resets every 10000 updates (sends interrupt) - should be 1 second

[[maybe_unused]] static GPIO_Handle_t red_led_handle;
[[maybe_unused]] static GPIO_Handle_t green_led_handle;

void LED_initialize_led(uint8_t led_number); // Initializes red or green led
void LED_enable_clock(uint8_t led_number); // Enable clock for specific led
void LED_enable_led(uint8_t led_number); // Turns red or green led on
void LED_disable_led(uint8_t led_number); // Turns red or green led off
void LED_toggle_led(uint8_t led_number); // Toggle either red or green led

// Timer2 functions for LED
void LED_init_timer_2();
void LED_start_timer_2();
void LED_stop_timer_2();
void LED_reset_timer_2();
void LED_elevate_timer_2_priority(); // Raise priority by 1
void LED_reset_timer_2_priority(); // Reset timer2 priority to default

// Timer5 functions for LED
void LED_init_timer_5();
void LED_start_timer_5();
void LED_stop_timer_5();
void LED_reset_timer_5();
void LED_elevate_timer_5_priority(); // Raise priority by 1
void LED_reset_timer_5_priority(); // Reset timer5 priority to default

#endif

