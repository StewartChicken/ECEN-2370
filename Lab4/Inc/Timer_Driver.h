/*
 * Timer_Driver.h
 *
 *  Created on: Oct 25, 2023
 *      Author: stewa
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <stdbool.h>
#include "STM32F429i.h"
#include "InterruptControl.h"

// Timer config macros
//------------------------------------------------

// Master Modes
#define MASTER_MODE_RESET 0x000
#define MASTER_MODE_ENABLE 0x001
#define MASTER_MODE_UPDATE 0x010
#define MASTER_MODE_COMPARE_PULSE 0x011
#define MASTER_MODE_COMPARE_OC1REF 0x100
#define MASTER_MODE_COMPARE_OC2REF 0x101
#define MASTER_MODE_COMPARE_OC3REF 0x110
#define MASTER_MODE_COMPARE_OC4REF 0x111

// Center align mode selection
#define EDGE_ALIGNED_MODE 0x00
#define CENTER_ALIGNED_MODE_1 0x01
#define CENTER_ALIGNED_MODE_2 0x10
#define CENTER_ALIGNED_MODE_3 0x11

#define CKD_1 0x00 // Ratio between timer clock frequency and sampling clock - sample = timer clock
#define CKD_2 0x01 // Ratio between timer clock frequency and sampling clock - sample = 2 * timer clock
#define CKD_3 0x10 // Ratio between timer clock frequency and sampling clock - sample = 4 * timer clock

// Channel config macros
//------------------------------------------------
#define OUTPUT_COMPARE_MODE_FROZEN 0x000
#define OUTPUT_COMPARE_MODE_ACTIVE_LEVEL 0x001
#define OUTPUT_COMPARE_MODE_INACTIVE_LEVEL 0x010
#define OUTPUT_COMPARE_MODE_TOGGLE 0x011
#define OUTPUT_COMPARE_MODE_FORCE_INACTIVE 0x100
#define OUTPUT_COMPARE_MODE_FORCE_ACTIVE 0x101
#define OUTPUT_COMPARE_MODE_PWM_1 0x110
#define OUTPUT_COMPARE_MODE_PWM_2 0x111

#define CHANNEL_MODE_OUTPUT 0x00 // Channel configured as output
#define CHANNEL_MODE_TI1 0x01 // IC1 mapped on TI1
#define CHANNEL_MODE_TI2 0x10 // IC1 mapped on TI2
#define CHANNEL_MODE_TRC 0x11 // IC1 mapped on TRC


// CCMRx registers?
typedef struct {
    uint8_t channelModeSelection; // Bits 6:4 in CCMR1 -
    uint8_t outputCompareSelection; // Bits 1:0 in CCMR1 - should be 00
    bool outputCompareFastEnable; // Bit 2 in CCMR1 - should be 0
    bool outputComparePreloadEnable; // Bit 3 in CCMR1 - 0
    bool outputCompareClearEnable; // Bit 7 in CCMR1 - 0
    bool outputChannelInterruptEnable; // Bit 1 in DIER
    uint32_t captureCompareValue; // To be stored in CCR1 register

} Channel_Config_t;


// Configures the CR register for a specific timer
typedef struct {

    uint32_t autoReloadValue; // Value the timer counts to/from - AAR Register

    uint8_t masterModeSelection; // Bits 6:4 of CR2 register

    uint8_t clockDivisionValue; // Bits 9:8 in CR1
    uint16_t prescalerValue; // Value the clock is divided (prescaled) by - PSC Register
    uint8_t centerAlignedMode; // Bits 6:5 of CR1 register - 4 values - 00, 01, 10, 11
    bool autoReloadBufferEnable; // Is the auto reload buffer enabled? 0 or 1 - bit 7 of CR1 register
    bool countDownMode; // 0 means timer counts up, 1 means timer counts down - bit 4 of CR1 register

    bool interruptUpdateEnable; // Bit 0 of DIER?

    bool disableUpdateEvent; // 0 means update event is enabled - 1 means update event is disabled - bit 1 of CR1 register
    bool onePulseMode; // 0: counter does not stop at update event - 1: counter stops at update event - bit 3 of CR1 register

    Channel_Config_t channel1Config;

} GPTImer_Config_t;

typedef struct {
    GPTIMR_RegDef_t* pTIMERx; // Timer to be configured
    GPTImer_Config_t timer_config;
} Timer_Handle_t;


// Setup
void TIMER_init_timer(Timer_Handle_t handle); // Initialize specified timer
void TIMER_init_channel_1(Timer_Handle_t handle); // Initialize channel 1 of a specified timer
void TIMER_set_clock(GPTIMR_RegDef_t* timer, uint8_t value); // Set clock for specified timer to specified value

// Functionality
void TIMER_start_timer(GPTIMR_RegDef_t* timer); // Start specified timer
void TIMER_stop_timer(GPTIMR_RegDef_t* timer); // Stop specified timer
void TIMER_reset_timer(GPTIMR_RegDef_t* timer); // Reset specified timer

uint32_t TIMER_get_timer_value(GPTIMR_RegDef_t* timer);

void TIMER_set_interrupt(GPTIMR_RegDef_t* timer, uint8_t value); // Enable/Disable interrupt for timer
void TIMER_change_interrupt_priority(GPTIMR_RegDef_t* timer, uint8_t priority); // Change interrupt priority for timer

#endif /* TIMER_DRIVER_H_ */
