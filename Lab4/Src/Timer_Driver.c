/*
 * Timer_Driver.c
 *
 *  Created on: Oct 25, 2023
 *      Author: stewa
 */

#include "Timer_Driver.h"

void TIMER_init_timer(Timer_Handle_t handle)
{
    // Enable clock prior to peripheral initialization

    handle.pTIMERx->CR1 &= ~(0x11 << 8); // Clear bits 9:8 in CR1 - these hold the clock division value
    handle.pTIMERx->CR1 |= (handle.timer_config.clockDivisionValue << 8); // Set bits to config value

    handle.pTIMERx->CR1 &= ~(0x11 << 5); // Clear bits 6:5 in CR1
    handle.pTIMERx->CR1 |= (handle.timer_config.centerAlignedMode << 5); // Set bits 6:5 to CAM mode value

    handle.pTIMERx->CR1 &= ~(0x1 << 4); // Clear bit 4 in CR1
    handle.pTIMERx->CR1 |= (handle.timer_config.countDownMode << 4);

    handle.pTIMERx->CR1 &= ~(0x1 << 7); // Clear bit 7 in CR1
    handle.pTIMERx->CR1 |= (handle.timer_config.autoReloadBufferEnable << 7); // Set bit 7

    handle.pTIMERx->CR1 &= ~(0x1 << 3); // Clear bit 3 of CR1 register
    handle.pTIMERx->CR1 |= (handle.timer_config.onePulseMode << 3); // Set bit 3 of CR1 register

    handle.pTIMERx->CR1 &= ~(0x1 << 1); // Clear bit 1 of CR1 register
    handle.pTIMERx->CR1 |= (handle.timer_config.disableUpdateEvent << 1); // Set bit 1 of CR1

    handle.pTIMERx->DIER &= ~(0x1 << 0);
    handle.pTIMERx->DIER |= (handle.timer_config.interruptUpdateEnable << 0);

    handle.pTIMERx->PSC &= (0x0); // Clear all bits in prescaler value register
    handle.pTIMERx->PSC |= (handle.timer_config.prescalerValue); // Set prescaler value to 32 bit number

    handle.pTIMERx->AAR &= (0x0); // Clear all bits in auto reload value register
    handle.pTIMERx->AAR |= (handle.timer_config.autoReloadValue); // Set auto reload register value to 16 or 32 bit value

    // Instructions don't say to configure this?
    handle.pTIMERx->CR2 &= ~(0x111 << 4); // Clear bits 6:4 in CR2 - hold master mode selection value
    handle.pTIMERx->CR2 |= (handle.timer_config.masterModeSelection << 4);

    TIMER_init_channel_1(handle);

    // If the updateEvent bit in CR1 is enabled and the interrupt update bit is enabled in DIER
    if(handle.timer_config.interruptUpdateEnable && !handle.timer_config.disableUpdateEvent)
    {
        TIMER_set_interrupt(handle.pTIMERx, ENABLE);
    }
    else // If update event is disabled in CR1 and interrupt update is disabled in DIER
    {
        TIMER_set_interrupt(handle.pTIMERx, DISABLE);
    }
}


// Initialize channel 1 for the specified timer
void TIMER_init_channel_1(Timer_Handle_t handle)
{
    // Output compare mode
    handle.pTIMERx->CCMR1 &= ~(0x111 << 4);
    handle.pTIMERx->CCMR1 |= (handle.timer_config.channel1Config.channelModeSelection << 4);

    // Compare selection mode
    handle.pTIMERx->CCMR1 &= ~(0x11 << 0);
    handle.pTIMERx->CCMR1 |= (handle.timer_config.channel1Config.outputCompareSelection << 0);

    // Output compare clear enable
    handle.pTIMERx->CCMR1 &= ~(0x1 << 7);
    handle.pTIMERx->CCMR1 |= (handle.timer_config.channel1Config.outputCompareClearEnable << 7);

    // Output compare preload enable
    handle.pTIMERx->CCMR1 &= ~(0x1 << 3);
    handle.pTIMERx->CCMR1 |= (handle.timer_config.channel1Config.outputComparePreloadEnable << 3);

    // Output compare fast enable
    handle.pTIMERx->CCMR1 &= ~(0x1 << 2);
    handle.pTIMERx->CCMR1 |= (handle.timer_config.channel1Config.outputCompareFastEnable << 2);

    // Output channel interrupt enable
    handle.pTIMERx->DIER &= ~(0x1 << 1);
    handle.pTIMERx->DIER |= (handle.timer_config.channel1Config.outputChannelInterruptEnable << 1);

    // Set capture compare value
    handle.pTIMERx->CCR1 &= (0x0);
    handle.pTIMERx->CCR1 |= handle.timer_config.channel1Config.captureCompareValue;

}


// Set clock for specified timer
void TIMER_set_clock(GPTIMR_RegDef_t* timer, uint8_t value)
{
    if(value == ENABLE){
        if(timer == TIM2)
        {
            APB1_ENABLE_CLOCK(TIM2_RCC_CLOCK_PIN);
        }
        else if (timer == TIM5)
        {
            APB1_ENABLE_CLOCK(TIM5_RCC_CLOCK_PIN);
        }
    }
    else if (value == DISABLE)
    {
        if(timer == TIM2)
        {
            APB1_DISABLE_CLOCK(TIM2_RCC_CLOCK_PIN);
        }
        else if (timer == TIM5)
        {
            APB1_DISABLE_CLOCK(TIM5_RCC_CLOCK_PIN);
        }
    }
}

// Start a specified timer
void TIMER_start_timer(GPTIMR_RegDef_t* timer)
{
    timer->CR1 |= 0x1; // Enable timer
}


// Stop a specified timer
void TIMER_stop_timer(GPTIMR_RegDef_t* timer)
{
    timer->CR1 &= ~(0x1); // Disable
}

// Reset specified timer
void TIMER_reset_timer(GPTIMR_RegDef_t* timer)
{
    timer->CNT &= 0x0; // Set CNT register to 0
}

// Return value held by specified timer
uint32_t TIMER_get_timer_value(GPTIMR_RegDef_t* timer)
{
    return timer->CNT;
}


// Enable/Disable interrupt for timer
void TIMER_set_interrupt(GPTIMR_RegDef_t* timer, uint8_t value)
{
    if(timer == TIM2)
    {
        if(value == ENABLE)
        {
            IRQ_enable_interrupt(TIM2_IRQ_NUMBER);
        }
        else if(value == DISABLE)
        {
            IRQ_disable_interrupt(TIM2_IRQ_NUMBER);
        }
    }
    else if(timer == TIM5)
    {
        if(value == ENABLE)
        {
            IRQ_enable_interrupt(TIM5_IRQ_NUMBER);
        }
        else if(value == DISABLE)
        {
            IRQ_disable_interrupt(TIM5_IRQ_NUMBER);
        }
    }
}

// Update specified timer's priority
void TIMER_change_interrupt_priority(GPTIMR_RegDef_t* timer, uint8_t priority)
{
    if(timer == TIM2)
    {
        IRQ_set_interrupt_priority(TIM2_IRQ_NUMBER, priority);
    }
    else if(timer == TIM5)
    {
        IRQ_set_interrupt_priority(TIM5_IRQ_NUMBER, priority);
    }
}


