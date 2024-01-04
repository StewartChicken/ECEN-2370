#include "LED_Driver.h"

// Initialize a specific LED (either red or green)
// Configure proper ports and pins for that LED
void LED_initialize_led(uint8_t led_number) 
{

    GPIO_set_clock(GPIOG, ENABLE); // Enable clock prior to peripheral initialization

    switch(led_number) 
    {
        case RED_LED: // Populate red led handle struct for configuration

            red_led_handle.pGPIOx = GPIOG; // Set GPIO port to GPIOG
            
            red_led_handle.GPIO_PinConfig.PinNumber = RED_LED_PIN_NUMBER; 
            red_led_handle.GPIO_PinConfig.PinMode = CONFIG_MODE_OUTPUT;
            red_led_handle.GPIO_PinConfig.OPType = GPIO_OUTPUT_PUSH_PULL;
            red_led_handle.GPIO_PinConfig.PinSpeed = GPIO_MEDIUM_SPEED;
            red_led_handle.GPIO_PinConfig.PinPuPdControl = GPIO_PUPD_PULLDOWN;
                
            GPIO_init(&red_led_handle);
            break;
           
        case GREEN_LED:

            green_led_handle.pGPIOx = GPIOG; // Set GPIO port to GPIOG
            
            green_led_handle.GPIO_PinConfig.PinNumber = GREEN_LED_PIN_NUMBER;
            green_led_handle.GPIO_PinConfig.PinMode = CONFIG_MODE_OUTPUT;
            green_led_handle.GPIO_PinConfig.OPType = GPIO_OUTPUT_PUSH_PULL;
            green_led_handle.GPIO_PinConfig.PinSpeed = GPIO_MEDIUM_SPEED;
            green_led_handle.GPIO_PinConfig.PinPuPdControl = GPIO_PUPD_PULLDOWN;
                
            GPIO_init(&green_led_handle);
            break;
    }

    GPIO_set_clock(GPIOG, DISABLE); // Disable clock after initialization
}

void LED_enable_led(uint8_t led_number)
{
    GPIO_set_clock(GPIOG,ENABLE); // Enable clock

    switch(led_number)
    {
        case GREEN_LED:
            GPIO_write(GPIOG, GREEN_LED_PIN_NUMBER, 1);
            break;
        case RED_LED:
            GPIO_write(GPIOG, RED_LED_PIN_NUMBER, 1);
            break;
    }

    GPIO_set_clock(GPIOG, DISABLE); // Disable clock
}

void LED_disable_led(uint8_t led_number) 
{
    GPIO_set_clock(GPIOG, ENABLE); // Enable clock

    switch(led_number)
    {
        case GREEN_LED:
            GPIO_write(GPIOG, GREEN_LED_PIN_NUMBER, 0);
            break;
        case RED_LED:
            GPIO_write(GPIOG, RED_LED_PIN_NUMBER, 0);
            break;
    }

    GPIO_set_clock(GPIOG, DISABLE); // Disable clock
}
// Toggle LED on/off
void LED_toggle_led(uint8_t led_number)
{
    GPIO_set_clock(GPIOG, ENABLE); // Enable clock
    
    switch(led_number) 
    {
        case RED_LED:
            GPIO_toggle_pin(GPIOG, RED_LED_PIN_NUMBER);
            break;
        case GREEN_LED:
            GPIO_toggle_pin(GPIOG, GREEN_LED_PIN_NUMBER);
            break;
    }

    GPIO_set_clock(GPIOG, DISABLE); // Disable clock
}

void LED_init_timer_2()
{
    Timer_Handle_t timer2;
    timer2.pTIMERx = TIM2;

    timer2.timer_config.autoReloadValue = 10000000;
    timer2.timer_config.prescalerValue = 0xFFFE;
    timer2.timer_config.clockDivisionValue = 2;
    timer2.timer_config.centerAlignedMode = EDGE_ALIGNED_MODE;
	timer2.timer_config.autoReloadBufferEnable = false;
	timer2.timer_config.countDownMode = false;
	timer2.timer_config.interruptUpdateEnable = true;
	timer2.timer_config.disableUpdateEvent = false;
	timer2.timer_config.onePulseMode = false;

    timer2.timer_config.masterModeSelection = RESET; // Unsure


    timer2.timer_config.channel1Config.channelModeSelection = CHANNEL_MODE_OUTPUT; // Check this
    timer2.timer_config.channel1Config.outputCompareSelection = OUTPUT_COMPARE_MODE_FROZEN; // Set to output mode
    timer2.timer_config.channel1Config.outputCompareFastEnable = false;
    timer2.timer_config.channel1Config.outputComparePreloadEnable = false;
    timer2.timer_config.channel1Config.outputCompareClearEnable = false;

    timer2.timer_config.channel1Config.outputChannelInterruptEnable = true;

    timer2.timer_config.channel1Config.captureCompareValue = 4000000;

    TIMER_set_clock(TIM2, ENABLE);
    TIMER_init_timer(timer2);
}

void LED_start_timer_2()
{
    TIMER_start_timer(TIM2);
}

void LED_stop_timer_2()
{
    TIMER_stop_timer(TIM2);
}

void LED_reset_timer_2()
{
    TIMER_reset_timer(TIM2);
}

void LED_elevate_timer_2_priority()
{
    IRQ_set_interrupt_priority(TIM2_IRQ_NUMBER, ELEVATED_PRIORITY);
}

void LED_reset_timer_2_priority()
{
    IRQ_set_interrupt_priority(TIM2_IRQ_NUMBER, RED_LED_DEFAULT_PRIORITY);
}

void LED_init_timer_5()
{
    Timer_Handle_t timer5;
    timer5.pTIMERx = TIM5;

    timer5.timer_config.autoReloadValue = 10000000;
    timer5.timer_config.prescalerValue = 0xFFFE;
    timer5.timer_config.clockDivisionValue = 2;
    timer5.timer_config.centerAlignedMode = EDGE_ALIGNED_MODE;
	timer5.timer_config.autoReloadBufferEnable = false;
	timer5.timer_config.countDownMode = false;
	timer5.timer_config.interruptUpdateEnable = true;
	timer5.timer_config.disableUpdateEvent = false;
	timer5.timer_config.onePulseMode = false;

    timer5.timer_config.masterModeSelection = RESET; // Unsure


    timer5.timer_config.channel1Config.channelModeSelection = CHANNEL_MODE_OUTPUT; // Check this
    timer5.timer_config.channel1Config.outputCompareSelection = OUTPUT_COMPARE_MODE_FROZEN; // Set to output mode
    timer5.timer_config.channel1Config.outputCompareFastEnable = false;
    timer5.timer_config.channel1Config.outputComparePreloadEnable = false;
    timer5.timer_config.channel1Config.outputCompareClearEnable = false;

    timer5.timer_config.channel1Config.outputChannelInterruptEnable = true;

    timer5.timer_config.channel1Config.captureCompareValue = 4000000;

    TIMER_set_clock(TIM5, ENABLE);
    TIMER_init_timer(timer5);
}

void LED_start_timer_5()
{
    TIMER_start_timer(TIM5);
}

void LED_stop_timer_5()
{
    TIMER_stop_timer(TIM5);
}

void LED_reset_timer_5()
{
    TIMER_reset_timer(TIM5);
}

void LED_elevate_timer_5_priority()
{
    IRQ_set_interrupt_priority(TIM5_IRQ_NUMBER, ELEVATED_PRIORITY);
}

void LED_reset_timer_5_priority()
{
    IRQ_set_interrupt_priority(TIM5_IRQ_NUMBER, GREEN_LED_DEFAULT_PRIORITY);
}

