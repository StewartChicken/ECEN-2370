#include "ApplicationCode.h"

// Initialize application code
void APPLICATION_init()
{
    APPLICATION_init_red_led();
    APPLICATION_current_led = APPLICATION_RED_LED;
    APPLICATION_deactivate_red_led();

    #if USE_INTERRUPT_FOR_BUTTON
        APPLICATION_init_button_interrupt_mode();
    #else
        APPLICATION_init_button();
        SCHEDULAR_addSchedulerEvent(POLL_BUTTON_EVENT);
    #endif

    SCHEDULAR_addSchedulerEvent(DELAY_EVENT);

}

// Initialize green led - configures GPIO port and pins
void APPLICATION_init_green_led()
{
    LED_initialize_led(GREEN_LED); // LED driver function
}

// Initialize red led - configures GPIO port and pins
void APPLICATION_init_red_led()
{
    LED_initialize_led(RED_LED); // LED driver function
}

// Initialize both green and red leds - configures GPIO port and pins
void APPLICATION_init_green_and_red_led()
{
    LED_initialize_led(GREEN_LED);
    LED_initialize_led(RED_LED);
}

// Toggle value of green led
void APPLICATION_toggle_green_led()
{
    LED_toggle_led(GREEN_LED);
}

// Toggle value of red led
void APPLICATION_toggle_red_led()
{
    LED_toggle_led(RED_LED);
}

// Turn green led on
void APPLICATION_activate_green_led()
{
    LED_enable_led(GREEN_LED);
}

// Turn red led on
void APPLICATION_activate_red_led()
{
    LED_enable_led(RED_LED);
}

// Turn green led off
void APPLICATION_deactivate_green_led()
{
    LED_disable_led(GREEN_LED);
}

// Turn red led off
void APPLICATION_deactivate_red_led()
{
    LED_disable_led(RED_LED);
}

#if USE_INTERRUPT_FOR_BUTTON == 0

void APPLICATION_init_button()
{
    BUTTON_initialize_button();
}

void APPLICATION_execute_button_polling_routine()
{
    if(BUTTON_is_pressed())
    {
        APPLICATION_activate_red_led();
    }else{
    	APPLICATION_deactivate_red_led();
    }

}

#endif

#if USE_INTERRUPT_FOR_BUTTON

void APPLICATION_init_button_interrupt_mode() {
    BUTTON_initialize_interrupt_mode();
}

#endif

// Delay function using "time" argument to dictate duration
void APPLICATION_delay(uint32_t time)
{
    char name[NAME_LENGTH]; // Array containing my name

    name[0] = 'E';
    name[1] = 'V';
    name[2] = 'A';
    name[3] = 'N';

    [[maybe_unused]] char destination[NAME_LENGTH]; 

    for(int i = 0; i < time * DELAY_MULT; i ++)
    {
        for(int j = 0; j < NAME_LENGTH; j ++)
        {
        	destination[j] = name[j];
        }
    }
}

void EXTI0_IRQHandler() {
    IRQ_disable_interrupt(EXTI0_IRQ_NUMBER);

    if(APPLICATION_current_led) { // 1 means red
        APPLICATION_toggle_red_led();
    } else { // 0 means green
        APPLICATION_toggle_green_led();
    }

    IRQ_clear_EXTI_pending_interrupt(BUTTON_PIN_NUMBER);
    IRQ_enable_interrupt(EXTI0_IRQ_NUMBER);
}

