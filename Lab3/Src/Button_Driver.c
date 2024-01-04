#include "Button_Driver.h"

void BUTTON_initialize_button(){

    BUTTON_enable_clock(); // Enable clock prior to peripheral initialization

        GPIO_Handle_t button_handle;

        button_handle.pGPIOx = BUTTON_PORT; // Set GPIO port to GPIOG
        
        button_handle.GPIO_PinConfig.PinNumber = BUTTON_PIN_NUMBER; 
        button_handle.GPIO_PinConfig.PinMode = CONFIG_MODE_INPUT;
        button_handle.GPIO_PinConfig.OPType = GPIO_OUTPUT_PUSH_PULL;
        button_handle.GPIO_PinConfig.PinSpeed = GPIO_MEDIUM_SPEED;
        button_handle.GPIO_PinConfig.PinPuPdControl = GPIO_PUPD_NOPULL;
            
        GPIO_init(&button_handle);

}

bool BUTTON_is_pressed(){
    if(GPIO_read_input(BUTTON_PORT, BUTTON_PIN_NUMBER) == BUTTON_IS_PRESSED) // If the button is pressed
    {
        return true;
    }

    return false;
}

void BUTTON_enable_clock(){
    GPIO_set_clock(BUTTON_PORT, ENABLE);
}

void BUTTON_disable_clock(){
    GPIO_set_clock(BUTTON_PORT, DISABLE);   
}

void BUTTON_initialize_interrupt_mode() {
    
    BUTTON_enable_clock(); // Enable clock prior to peripheral initialization

        GPIO_Handle_t button_handle;

        button_handle.pGPIOx = BUTTON_PORT; // Set GPIO port to GPIOG
        
        button_handle.GPIO_PinConfig.PinNumber = BUTTON_PIN_NUMBER; 
        button_handle.GPIO_PinConfig.PinMode = CONFIG_MODE_INPUT;
        button_handle.GPIO_PinConfig.OPType = GPIO_OUTPUT_PUSH_PULL;
        button_handle.GPIO_PinConfig.PinSpeed = GPIO_MEDIUM_SPEED;
        button_handle.GPIO_PinConfig.PinPuPdControl = GPIO_PUPD_NOPULL;
        button_handle.GPIO_PinConfig.PinInterruptMode = FALLING_AND_RISING_EDGE; //  Set interrupt to use rising and falling edge
            
        GPIO_init(&button_handle);
        GPIO_set_NVIC_interrupt(EXTI0_IRQ_NUMBER, ENABLE); // Enable interrupt for the button port
}
