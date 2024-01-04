#include "LED_Driver.h"

// Initialize a specific LED (either red or green)
// Configure proper ports and pins for that LED
void initialize_led(uint8_t led_number) 
{

    GPIO_set_clock(GPIOG, 1); // Enable clock prior to peripheral initialization

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

    GPIO_set_clock(GPIOG, 0); // Disable clock after initialization
}

void enable_led(uint8_t led_number)
{
    GPIO_set_clock(GPIOG, 1); // Enable clock

    switch(led_number)
    {
        case GREEN_LED:
            GPIO_write(GPIOG, GREEN_LED_PIN_NUMBER, 1);
            break;
        case RED_LED:
            GPIO_write(GPIOG, RED_LED_PIN_NUMBER, 1);
            break;
    }

    GPIO_set_clock(GPIOG, 0); // Disable clock
}

void disable_led(uint8_t led_number) 
{
    GPIO_set_clock(GPIOG, 1); // Enable clock

    switch(led_number)
    {
        case GREEN_LED:
            GPIO_write(GPIOG, GREEN_LED_PIN_NUMBER, 0);
            break;
        case RED_LED:
            GPIO_write(GPIOG, RED_LED_PIN_NUMBER, 0);
            break;
    }

    GPIO_set_clock(GPIOG, 0); // Disable clock
}
// Toggle LED on/off
void toggle_led(uint8_t led_number)
{
    GPIO_set_clock(GPIOG, 1); // Enable clock
    
    switch(led_number) 
    {
        case RED_LED:
            GPIO_toggle_pin(GPIOG, RED_LED_PIN_NUMBER);
            break;
        case GREEN_LED:
            GPIO_toggle_pin(GPIOG, GREEN_LED_PIN_NUMBER);
            break;
    }

    GPIO_set_clock(GPIOG, 0); // Disable clock
}
