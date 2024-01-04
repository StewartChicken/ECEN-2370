/*
 * ApplicationCode.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Evan Poon
 *
 *      // RED LED - Pin 14 port G
 * 		// GREEN LED - Pin 13 port G
 *      // GPIOG Enable Pin (RCC_AHB1ENR) 6
 *      // Example syntax for base addresses: RNG_BASE_ADDR
 *
 *      //TODO - double check address of PERIPHERAL_BASE_ADDR
 *
 */

#ifndef STM32F429i_H
#define STM32F429i_H

#include <stdint.h>

// Memory addresses of buses and peripherals 
#define PERIPHERAL_BASE_ADDR 0x40000000u 

#define AHB1_BASE_ADDR (PERIPHERAL_BASE_ADDR + 0x20000)
#define APB2_BASE_ADDR 0x40013800u

#define RCC_BASE_ADDR (AHB1_BASE_ADDR + 0x3800)

#define GPIOG_BASE_ADDR (AHB1_BASE_ADDR + 0x1800)
#define GPIOA_BASE_ADDR AHB1_BASE_ADDR // GPIOA is the first GPIO port within the AHB1 bus

// NVIC Addresses
#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100) // Set enable for EXTI0 interrupt
#define NVIC_ICER0 ((volatile uint32_t*) (0xE000E180))
#define NVIC_ISPR0 ((volatile uint32_t*) 0xE000E200)
#define NVIC_ICPR0 ((volatile uint32_t*) 0xE000E280)
#define NVIC_IPR0 ((volatile uint32_t*) 0xE000E400) // Priority

#define SYSCFG_BASE_ADDR APB2_BASE_ADDR // SYSCFG is the first peripheral on the APB2 bus
#define EXTI_BASE_ADDR (APB2_BASE_ADDR + 0x400)

#define TIM2_BASE_ADDR (PERIPHERAL_BASE_ADDR) // TIM2 is the first peripheral
#define TIM5_BASE_ADDR (PERIPHERAL_BASE_ADDR + 0x0C00)

#define GPIOG ((GPIO_RegDef_t*) GPIOG_BASE_ADDR) // GPIOG control - pointer to GPIOG in memory
#define GPIOA ((GPIO_RegDef_t*) GPIOA_BASE_ADDR) // GPIOA control - pointer to GPIOG in memory

#define RCC ((RCC_RegDef_t*) RCC_BASE_ADDR) // RCC control - pointer to RCC in memory

#define SYSCFG ((SYSCFG_RegDef_t*) SYSCFG_BASE_ADDR) // SYSCFG control - pointer to SYSCFG in memory
#define EXTI ((EXTI_RegDef_t*) EXTI_BASE_ADDR) // EXTI control - pointer to EXTI in memory

#define TIM2 ((GPTIMR_RegDef_t*) TIM2_BASE_ADDR)
#define TIM5 ((GPTIMR_RegDef_t*) TIM5_BASE_ADDR)

#define GPIOG_RCC_CLOCK_PIN 6
#define GPIOA_RCC_CLOCK_PIN 0

#define TIM2_RCC_CLOCK_PIN 0 // TIM2 peripheral is bit 0 of the RCC_APB1ENR register
#define TIM5_RCC_CLOCK_PIN 3 // TIM2 peripheral is bit 3 of the RCC_APB1ENR register

#define GPIO_ENABLE_CLOCK(x) RCC->AHB1ENR |= (1 << x) // ENABLE clock for a specified pin number
#define GPIO_DISABLE_CLOCK(x) RCC->AHB1ENR &= ~(1 << x) // DISABLE clock a specified pin number

#define SYSCFG_ENABLE_CLOCK RCC->APB2ENR |= (1 << 14)
#define SYSCFG_DISABLE_CLOCK RCC->APB2ENR &= ~(1 << 14)

#define APB1_ENABLE_CLOCK(x) RCC->APB1ENR |= (1 << x) // ENABLE clock for a specified pin in the APB1 register
#define APB1_DISABLE_CLOCK(x) RCC->APB1ENR &= ~(1 << x) // DISABLE clock for specified pin in the APB1 register

// Helper macros
#define ACTIVE 1
#define NON_ACTIVE 0
#define SET 1
#define RESET 0
#define ENABLE SET
#define DISABLE RESET


/*
uint8_t PinNumber; // Pin Number - which specific pin is being modified
	uint8_t PinMode; // Pin Mode (Configuration modes)
	uint8_t OPType; // Output Type
	uint8_t PinSpeed; // Pin Speed
	uint8_t PinPuPdControl; // Pin Push up/ Pull Down Control
	uint8_t PinAltFunMode; // Alternate Function mode
*/

// Register map of GPIO register
typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AF[2]; // AF[0] is alt func low reg 
							 // AF[1] is alt func high reg

} GPIO_RegDef_t;

// Register map of RCC register
typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	volatile uint32_t Reserved1; // Reserved
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t Reserved2[2]; // Reserved
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t Reserved3; // Reserved
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t Reserved4[2]; // Reserved
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	volatile uint32_t Reserved5; // Reserved
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t Reserved6[2]; // Reserved
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t Reserved7[2]; // Reserved
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
} RCC_RegDef_t;

// SYSCFG register map
typedef struct {
	volatile uint32_t SYSCFG_MEMRMP;
	volatile uint32_t SYSCFG_PMC;
	volatile uint32_t SYSCFG_EXTICR[4];
	volatile uint32_t SYSCFG_CMPCR;
} SYSCFG_RegDef_t;

// EXTI register map
typedef struct {
	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;
} EXTI_RegDef_t;

typedef struct {
	volatile uint32_t CR1; // Configuration register
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR; // Contains timer interrupt flag
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;

	// Count register - bits 31:16 are high counter value (TIM2/TIM5 only), reserved for other timers
	// Holds current count value of the timer
	volatile uint32_t CNT;

	// Prescaler value - clock divider
	volatile uint32_t PSC;

	// Auto-reload register - bits 31:16 are high auto-reload value (TIM2/TIM5 only, those bits are reserved for other timers)
	// This register holds the value that the timer will count up to or down from before resetting
	volatile uint32_t AAR;

	volatile uint32_t Reserved1; // Reserved
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t Reserved2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR;
} GPTIMR_RegDef_t;

#endif
