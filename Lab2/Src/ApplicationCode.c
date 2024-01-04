#include "ApplicationCode.h"

// Initialize application code
void application_init()
{
    init_green_led();
    addSchedulerEvent(LED_TOGGLE_EVENT);
    addSchedulerEvent(DELAY_EVENT);
}

// Initialize green led - configures GPIO port and pins
void init_green_led()
{
    initialize_led(GREEN_LED); // LED driver function
}

// Initialize red led - configures GPIO port and pins
void init_red_led()
{
    initialize_led(RED_LED); // LED driver function
}

// Initialize both green and red leds - configures GPIO port and pins
void init_green_and_red_led()
{
    initialize_led(GREEN_LED);
    initialize_led(RED_LED);
}

// Toggle value of green led
void toggle_green_led()
{
    toggle_led(GREEN_LED);
}

// Toggle value of red led
void toggle_red_led()
{
    toggle_led(RED_LED);
}

// Turn green led on
void activate_green()
{
    enable_led(GREEN_LED);
}

// Turn red led on
void activate_red()
{
    enable_led(RED_LED);
}

// Turn green led off
void deactivate_green()
{
    disable_led(GREEN_LED);
}

// Turn red led off
void deactivate_red()
{
    disable_led(RED_LED);
}

// Delay function using "time" argument to dictate duration
void delay(uint32_t time)
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

