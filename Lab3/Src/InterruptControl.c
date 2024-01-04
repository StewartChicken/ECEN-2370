#include "InterruptControl.h"



void IRQ_enable_interrupt(uint8_t IRQ_number)
{
    *NVIC_ISER0 |= (1 << (IRQ_number % 32));
}   

void IRQ_disable_interrupt(uint8_t IRQ_number)
{
    *NVIC_ICER0 |= (1 << (IRQ_number % 32));
}

void IRQ_set_pending_interrupt(uint8_t IRQ_number)
{
    *NVIC_ISPR0 |= (1 << (IRQ_number % 32));
}

void IRQ_clear_pending_interrupt(uint8_t IRQ_number)
{
    *NVIC_ICPR0 |= (1 << (IRQ_number % 32));
}

void IRQ_clear_EXTI_pending_interrupt(uint8_t pin)
{
    EXTI->EXTI_PR |= (1 << pin);
}
