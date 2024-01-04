#include "InterruptControl.h"



void IRQ_enable_interrupt(uint8_t IRQ_number)
{
    uint8_t reg = IRQ_number / 32;
    uint8_t bit = IRQ_number % 32;
    
    *(NVIC_ISER0 + reg) |= (1 << bit);
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

void IRQ_set_interrupt_priority(uint8_t IRQ_number, uint8_t IRQ_priority)
{
    uint32_t reg = IRQ_number / 4;
    uint32_t bitfield = IRQ_number % 4;
    uint32_t shift = bitfield * 8;

    *(NVIC_IPR0 + reg) &= ~(0xFF << shift); // Clear
    *(NVIC_IPR0 + reg) |= (IRQ_priority << shift); // Set
}

void IRQ_clear_EXTI_pending_interrupt(uint8_t pin)
{
    EXTI->EXTI_PR |= (1 << pin);
}
