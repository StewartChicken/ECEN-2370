#include "Interrupt.h"

/**
 * @brief Enable specific interrupt
 * 
 * @param IRQ_number - IRQ number of the interrupt to be enabled
*/
void IRQ_enable_interrupt(uint8_t IRQ_number)
{
    uint8_t reg = IRQ_number / 32;
    uint8_t bit = IRQ_number % 32;
    
    *(NVIC_ISER0 + reg) |= (1 << bit);
} 

/**
 * @brief Disable specific interrupt
 * 
 * @param IRQ_number - IRQ number of the interrupt to be disabled
*/
void IRQ_disable_interrupt(uint8_t IRQ_number)
{
    *NVIC_ICER0 |= (1 << (IRQ_number % 32));
}


/**
 * @brief Clear pending interrupt after it has been triggerd
 * 
 * @param IRQ_number - which interrupt should be cleared from pending register
*/
void IRQ_clear_pending_interrupt(uint8_t IRQ_number)
{
    *NVIC_ICPR0 |= (1 << (IRQ_number % 32));
}