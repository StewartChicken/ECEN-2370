#ifndef INTERRUPT_CONTROL_H
#define INTERRUPT_CONTROL_H

#include <stdint.h>
#include "stm32f429xx.h"

void IRQ_enable_interrupt(uint8_t IRQ_number);
void IRQ_disable_interrupt(uint8_t IRQ_number);
void IRQ_clear_pending_interrupt(uint8_t IRQ_number);
void IRQ_set_pending_interrupt(uint8_t IRQ_number);

void IRQ_clear_EXTI_pending_interrupt(uint8_t pin);

#endif
