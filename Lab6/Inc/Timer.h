/**
 * This file is responsible for configuring a timer for the game.
 * Every two seconds, an interrup twill be sent to increase the counter force on the ball.
 * The time, in seconds, will be displayed on the LCD screen. An interrupt will be generated
 * to indicate that the displayed time needs to be updated. 
 * 
 * Timer 2 will be responsible for signaling that the force should be updated
 * Timer 5 will be responsible for signaling that the displayed second should be updated
*/

#ifndef TIMER_H
#define TIMER_H

#include "stm32f429xx.h"
#include "Interrupt.h"

#define TIM4_ARR 1000 // Reload timer every 1000 milliseconds
#define TIM3_ARR 2000 // Reload timer every 1000 milliseconds
#define TIM_PSC 6250 // Timer counts milliseconds
#define TIM_CR1_CONFIG 0b0010000100 // Set ARPE and URS

// ----------------------------------------------------------------
// TIM3 function declarations
// ----------------------------------------------------------------

void TIMER_init_timer3(); // Initialize timer3 - send interrupt every 2 seconds

void TIMER_timer3_enable_clock();
void TIMER_timer3_disable_clock();

void TIMER_start_timer3();
void TIMER_stop_timer3();

// Set UIE (update interrupt enable) bit in DIER
void TIMER_enable_interrupt_timer3();

// Clears UIF bit in the timer status register
void TIMER_clear_interrupt_timer3();

// ----------------------------------------------------------------
// TIM4 function declarations
// ----------------------------------------------------------------

void TIMER_init_timer4(); // Initialize timer4 - send interrupt every second

void TIMER_timer4_enable_clock();
void TIMER_timer4_disable_clock();

void TIMER_start_timer4();
void TIMER_stop_timer4();

// Set UIE (update interrupt enable) bit in DIER
void TIMER_enable_interrupt_timer4();

// Clears UIF bit in the timer status register
void TIMER_clear_interrupt_timer4();


#endif