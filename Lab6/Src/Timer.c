#include "Timer.h"

// ----------------------------------------------------------------
// TIM3 function declarations
// ----------------------------------------------------------------

/**
 * @brief Initialize timer 3
*/
void TIMER_init_timer3()
{
    
    TIMER_timer3_enable_clock();

    TIM3->ARR &= 0; // Clear ARR
    TIM3->ARR |= TIM3_ARR; // Set ARR

    TIM3->PSC &= 0; // Clear PSC
    TIM3->PSC |= TIM_PSC; // Set PSC

    TIM3->CR1 &= 0; // Clear CR1
    TIM3->CR1 |= TIM_CR1_CONFIG;

    // Enable interrupts
    TIMER_enable_interrupt_timer3();
    IRQ_enable_interrupt(TIM3_IRQ_NUMBER);

}

/**
 * @brief Enable clock for timer 3
*/
void TIMER_timer3_enable_clock()
{
    RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN);
}

/**
 * @brief Disable clock for timer 3
*/
void TIMER_timer3_disable_clock()
{
    RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN);
}

/**
 * @brief Start timer 3's counting
*/
void TIMER_start_timer3()
{
    TIM3->CR1 |= 0b1; // Set CEN bit 
}

/**
 * @brief Stop timer 3's counting - don't reset
*/ 
void TIMER_stop_timer3()
{
    TIM3->CR1 &= ~(0b1); // Clear CEN bit
}
/**
 * @brief Set UIE bit in DIER register to enable interrupts for timer 3
*/
void TIMER_enable_interrupt_timer3()
{
    TIM3->DIER |= 0b1; // Enable bit 0 of DIER to enable update interrupts 
}

/**
 * @brief Clear UIF in TIM3->SR register
*/
void TIMER_clear_interrupt_timer3()
{
    TIM3->SR &= ~(0b1); // Clear UIF
}

// ----------------------------------------------------------------
// Timer 4 functions
// ----------------------------------------------------------------

/**
 * @brief Initialize timer 4
*/
void TIMER_init_timer4()
{
    
    TIMER_timer4_enable_clock();

    TIM4->ARR &= 0; // Clear ARR
    TIM4->ARR |= TIM4_ARR; // Set ARR

    TIM4->PSC &= 0; // Clear PSC
    TIM4->PSC |= TIM_PSC; // Set PSC

    TIM4->CR1 &= 0; // Clear CR1
    TIM4->CR1 |= TIM_CR1_CONFIG;

    // Enable interrupts
    TIMER_enable_interrupt_timer4();
    IRQ_enable_interrupt(TIM4_IRQ_NUMBER);

}

/**
 * @brief Enable clock for timer 4
*/
void TIMER_timer4_enable_clock()
{
    RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN);
}

/**
 * @brief Disable clock for timer 4
*/
void TIMER_timer4_disable_clock()
{
    RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN);
}

/**
 * @brief Timer 4 starts counting up from 0
*/ 
void TIMER_start_timer4()
{
    TIM4->CR1 |= 0b1; // Set CEN bit 
}

/**
 * @brief Stop timer 4's counting - don't reset
*/
void TIMER_stop_timer4()
{
    TIM4->CR1 &= ~(0b1); // Clear CEN bit
}

/**
 * @brief Set UIE (update interrupt enable) bit in DIER
*/
void TIMER_enable_interrupt_timer4()
{
    TIM4->DIER |= 0b1; // Enable bit 0 of DIER to enable update interrupts 
}

/**
 * @brief Clear UIF in TIM4->SR register
*/
void TIMER_clear_interrupt_timer4()
{
    TIM4->SR &= ~(0b1); // Clear UIF
}
