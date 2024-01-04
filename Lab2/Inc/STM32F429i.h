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
#define PERIPHERAL_BASE_ADDR 0x40000000u // Double check this one
#define AHB1_BASE_ADDR (PERIPHERAL_BASE_ADDR + 0x20000)
#define RCC_BASE_ADDR (AHB1_BASE_ADDR + 0x3800)
#define GPIOG_BASE_ADDR (AHB1_BASE_ADDR + 0x1800)

// Register map of GPIOG register
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



#define GPIOG ((GPIO_RegDef_t*) GPIOG_BASE_ADDR) // GPIOG control - pointer to GPIOG in memory
#define RCC ((RCC_RegDef_t*) RCC_BASE_ADDR) // RCC control - pointer to RCC in memory

#define GPIOG_ENABLE_CLOCK RCC->AHB1ENR |= (1 << 6) // ENABLE clock for GPIOG
#define GPIOG_DISABLE_CLOCK RCC->AHB1ENR &= ~(1 << 6) // DISABLE clock for GPIOG

// Helper macros
#define ACTIVE 1
#define NON_ACTIVE 0
#define SET 1
#define RESET 0
#define ENABLE SET
#define DISABLE RESET

#endif
