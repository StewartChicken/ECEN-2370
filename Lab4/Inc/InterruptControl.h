#ifndef INTERRUPT_CONTROL_H
#define INTERRUPT_CONTROL_H

#include "stdint.h"
#include "STM32F429i.h"

#define EXTI0_IRQ_NUMBER 6

// Timer 2 and 5 interrupt numbers
#define TIM2_IRQ_NUMBER 28
#define TIM5_IRQ_NUMBER 50

void IRQ_enable_interrupt(uint8_t IRQ_number);
void IRQ_disable_interrupt(uint8_t IRQ_number);
void IRQ_clear_pending_interrupt(uint8_t IRQ_number);
void IRQ_set_pending_interrupt(uint8_t IRQ_number);

void IRQ_clear_EXTI_pending_interrupt(uint8_t pin);

void IRQ_set_interrupt_priority(uint8_t IRQ_number, uint8_t IRQ_priority); // Configure the priority of a specific interrupt

#endif
