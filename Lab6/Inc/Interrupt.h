#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>
#include "stm32f429xx.h"

// NVIC Addresses
#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100) // Set enable for EXTI0 interrupt
#define NVIC_ICER0 ((volatile uint32_t*) (0xE000E180))
#define NVIC_ISPR0 ((volatile uint32_t*) 0xE000E200)
#define NVIC_ICPR0 ((volatile uint32_t*) 0xE000E280)
#define NVIC_IPR0 ((volatile uint32_t*) 0xE000E400) // Priority

#define TIM3_IRQ_NUMBER 29
#define TIM4_IRQ_NUMBER 30

void IRQ_enable_interrupt(uint8_t IRQ_number);
void IRQ_disable_interrupt(uint8_t IRQ_number);
void IRQ_clear_pending_interrupt(uint8_t IRQ_number);
void IRQ_set_pending_interrupt(uint8_t IRQ_number);

#endif