#ifndef INTERRUPT_CONTROL_H
#define INTERRUPT_CONTROL_H

#include "stdint.h"
#include "STM32F429i.h"

#define EXTI0_IRQ_NUMBER 6 // Check this

void IRQ_enable_interrupt(uint8_t IRQ_number);
void IRQ_disable_interrupt(uint8_t IRQ_number);
void IRQ_clear_pending_interrupt(uint8_t IRQ_number);
void IRQ_set_pending_interrupt(uint8_t IRQ_number);

void IRQ_clear_EXTI_pending_interrupt(uint8_t pin);

#endif
