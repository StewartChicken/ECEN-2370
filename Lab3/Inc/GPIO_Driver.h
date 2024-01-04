/*
 * GPIO.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Evan Poon
 *
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "STM32F429i.h"
#include "InterruptControl.h"

typedef struct // Configure GPIO
{
	uint8_t PinNumber; // Pin Number - which specific pin is being modified
	uint8_t PinMode; // Pin Mode (Configuration modes)
	uint8_t OPType; // Output Type
	uint8_t PinSpeed; // Pin Speed
	uint8_t PinPuPdControl; // Pin Push up/ Pull Down Control
	uint8_t PinAltFunMode; // Alternate Function mode
	uint8_t PinInterruptMode; // Type of interrupt
} GPIO_PinConfig_t;

// Initialize GPIO
typedef struct // AKA the handle struct
{
	GPIO_RegDef_t* pGPIOx; // GPIO port
	GPIO_PinConfig_t GPIO_PinConfig; // The pin configurations
} GPIO_Handle_t;

// Pin numbers
#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7
#define GPIO_PIN_8 8
#define GPIO_PIN_9 9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15

// Configuration modes
#define CONFIG_MODE_INPUT 0
#define CONFIG_MODE_OUTPUT 1
#define CONFIG_MODE_ALTERNATE 2 // Alternate function mode
#define CONFIG_MODE_ANALOG 3

// Output type configurations
#define GPIO_OUTPUT_PUSH_PULL 0
#define GPIO_OUTPUT_OPEN_DRAIN 1

#define GPIO_LOW_SPEED 0
#define GPIO_MEDIUM_SPEED 1
#define GPIO_HIGH_SPEED 2
#define GPIO_VERY_HIGH_SPEED 3

// Configure push-up/pull-down controls
#define GPIO_PUPD_PULLUP 0
#define GPIO_PUPD_PULLDOWN 1
#define GPIO_PUPD_NOPULL 2

// Interrupt modes
#define NO_INTERRUPT 0 
#define FALLING_EDGE 1
#define RISING_EDGE 2
#define FALLING_AND_RISING_EDGE 3

// Port numbers for button ports
#define GPIOA_BUTTON_PORT 0
#define GPIOB_BUTTON_PORT 1
#define GPIOC_BUTTON_PORT 2
#define GPIOD_BUTTON_PORT 3
#define GPIOE_BUTTON_PORT 4
#define GPIOF_BUTTON_PORT 5
#define GPIOG_BUTTON_PORT 6
#define GPIOH_BUTTON_PORT 7
#define GPIOI_BUTTON_PORT 8
#define GPIOJ_BUTTON_PORT 9
#define GPIOK_BUTTON_PORT 10

void GPIO_init(GPIO_Handle_t* handle); // Initialize GPIO configuration
void GPIO_set_clock(GPIO_RegDef_t* reg, uint8_t set); // Enable/Disable clock
void GPIO_toggle_pin(GPIO_RegDef_t* port, uint8_t pin); // Toggle specific pin
void GPIO_write(GPIO_RegDef_t* port, uint8_t pin, uint8_t value); // Write to specific pin

uint8_t GPIO_read_input(GPIO_RegDef_t* port, uint8_t pin); // Read data from specific pin of specific port - return 0 or 1
uint16_t GPIO_get_port_code(GPIO_RegDef_t* port); // Get port code of specific pin number

uint16_t GPIO_get_port_number(GPIO_RegDef_t* port);
void GPIO_set_NVIC_interrupt(uint8_t IRQ_number, uint8_t set); // Enable/disable interrupt for given port

#endif
