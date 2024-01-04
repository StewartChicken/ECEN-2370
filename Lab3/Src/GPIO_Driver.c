#include "GPIO_Driver.h"

// Initialize GPIO configuration
// 'handle' is a struct which contains a pointer to a GPIO register and
//  a pin configuration struct
void GPIO_init(GPIO_Handle_t* handle) {
	uint32_t temp; // Stores current values that are being configured from "handle" argument

	// Configure pin mode for specific port/pin
	temp = (handle->GPIO_PinConfig.PinMode << (2 * handle->GPIO_PinConfig.PinNumber));
	handle->pGPIOx->MODER &= ~(0x3 << (2 * handle->GPIO_PinConfig.PinNumber)); // Clear to-be-configured bits (set to 0)
	handle->pGPIOx->MODER |= temp; // Assign new bits

	if(temp == CONFIG_MODE_ALTERNATE) { // Is the pin configured to use the alternate function?
		
		// Used to select the proper register within the alternate function
		// register. There are two registers, each 32bit, that sit consecutively
		// within memory. Will hold either 0 or 1
		uint32_t alternate_reg_number = handle->GPIO_PinConfig.PinNumber / 8; 

		// This will select the proper pin with respect to which alt func register we are in
		// For example, if the PinNumber is 14, we are in AF[1], but we need to access
		// pin 6 of the AF[1] register. 14 % 8 = 6. 
		uint32_t pin_to_access = handle->GPIO_PinConfig.PinNumber % 8;

		// This is shifted by 4 times the pin number because each pin has 4 configurable bits (16 combinations)
		// This variable hold the values for the specific pin being modified. 
		uint32_t alternate_function_mode = handle->GPIO_PinConfig.PinAltFunMode << (4 * pin_to_access);
		// 0xF in binary is 1111. Negating this yields 0000 which we can & with the desired pin's bits to
		// reset them. 
		handle->pGPIOx->AF[alternate_reg_number] &= ~(0xF << (4 * handle->GPIO_PinConfig.PinNumber)); // Reset desired pin values (set to 0)
		handle->pGPIOx->AF[alternate_reg_number] |= alternate_function_mode; // Assign new values

	}

	// Configure interrupt mode
	if(handle->GPIO_PinConfig.PinInterruptMode != NO_INTERRUPT)
	{

		SYSCFG_ENABLE_CLOCK;

		if(handle->GPIO_PinConfig.PinInterruptMode == RISING_EDGE)
		{
			EXTI->EXTI_RTSR |= (1 << handle->GPIO_PinConfig.PinNumber);
			EXTI->EXTI_FTSR &= ~(1 << handle->GPIO_PinConfig.PinNumber);
		}
		else if(handle->GPIO_PinConfig.PinInterruptMode == FALLING_EDGE)
		{
			EXTI->EXTI_FTSR |= (1 << handle->GPIO_PinConfig.PinNumber);
			EXTI->EXTI_RTSR &= ~(1 << handle->GPIO_PinConfig.PinNumber);
		}
		else if(handle->GPIO_PinConfig.PinInterruptMode == FALLING_AND_RISING_EDGE)
		{
			EXTI->EXTI_FTSR |= (1 << handle->GPIO_PinConfig.PinNumber);
			EXTI->EXTI_RTSR |= (1 << handle->GPIO_PinConfig.PinNumber);
		}

		uint8_t SYSCFG_CR_register = handle->GPIO_PinConfig.PinNumber / 4;
		uint8_t bitfield = handle->GPIO_PinConfig.PinNumber % 4;
		uint16_t portCode = GPIO_get_port_code(handle->pGPIOx);

		SYSCFG->SYSCFG_EXTICR[SYSCFG_CR_register] &= ~(0xF << (4 * bitfield)); // Clear proper bit field
		SYSCFG->SYSCFG_EXTICR[SYSCFG_CR_register] |= (portCode << (4 * bitfield)); // Set bit field to port code

		EXTI->EXTI_IMR |= (1 << handle->GPIO_PinConfig.PinNumber);

	}

	

	// Configure pin speed for specific port/pin
	temp = (handle->GPIO_PinConfig.PinSpeed << (2 * handle->GPIO_PinConfig.PinNumber));
	handle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * handle->GPIO_PinConfig.PinNumber)); // Clear to-be-configured bits
	handle->pGPIOx->OSPEEDR |= temp; // Assign new values

	// Configure pull-up/pull-down register for specific port/pin
	temp = (handle->GPIO_PinConfig.PinPuPdControl << (2 * handle->GPIO_PinConfig.PinNumber));
	handle->pGPIOx->PUPDR &= ~(0x3 << (2 * handle->GPIO_PinConfig.PinNumber)); // Clear to-be-configured bits
	handle->pGPIOx->PUPDR |= temp; // Assign new values

	// Configure output type for specific port/pin
	temp = (handle->GPIO_PinConfig.OPType << handle->GPIO_PinConfig.PinNumber);
	handle->pGPIOx->OTYPER &= ~(0x1 << handle->GPIO_PinConfig.PinNumber); // Clear to-be-configured bits
	handle->pGPIOx->OTYPER |= temp; // Assign new values

}

// 'reg' argument is pointer to the GPIO's register structure in memorys
// 'set_to' dictates whether we are enabling or disabling the clock for 
//  the specified GPIO
void GPIO_set_clock(GPIO_RegDef_t* reg, uint8_t set_to) {
	if(set_to == ENABLE) { // If the function is called to enable the clock
		if(reg == GPIOA) {
			GPIO_ENABLE_CLOCK(0);
		}

		if(reg == GPIOG) { // If the memory address of reg is equal to that of GPIO G
			GPIO_ENABLE_CLOCK(6);
		}	
	}
	else if(set_to == DISABLE){
		if(reg == GPIOA) {
			GPIO_DISABLE_CLOCK(0);
		}

		if(reg == GPIOG) { // If the memory address of reg is equal to that
			GPIO_DISABLE_CLOCK(6); // Disable
		}
	}
}

// Write to specific port and pin
// 'port' specifies which GPIO port to write to
// 'pin' specifies which GPIO pin of the specified port to write to
// 'value' specifies which value to write
void GPIO_write(GPIO_RegDef_t* port, uint8_t pin, uint8_t value) {
	if(value == SET) {
		port->ODR |= (1 << pin); // Set proper pin to 1 in Output Data Register
	} else if(value == RESET) {
		port->ODR &= ~(1 << pin); // Reset proper pin to 0 in Output Data Register
	}
}

// Toggle pin value of specific GPIO port/pin
void GPIO_toggle_pin(GPIO_RegDef_t* port, uint8_t pin) {
	port->ODR ^= (1 << pin); // Toggle proper bitCan 
}

// Read value of specific GPIO port/pin
uint8_t GPIO_read_input(GPIO_RegDef_t* port, uint8_t pin) {
	//uint8_t value = (port->IDR >> pin) & 0x01; // Obtain the value of the desired pin

	return (port->IDR >> pin) & 0x01; // Obtain the value of the desired pin
}

// Return port number of specific GPIO port
uint16_t GPIO_get_port_number(GPIO_RegDef_t* port) {
	if(port == GPIOA)
	{
		return GPIOA_BUTTON_PORT;
	}

	return 0;
}

uint16_t GPIO_get_port_code(GPIO_RegDef_t* port) {
	if(port == GPIOA)
	{
		return 0;
	}

	return 0;
}

// Enable proper interrupt in NVIC depending on the port
void GPIO_set_NVIC_interrupt(uint8_t IRQ_number, uint8_t set) {
	if(set == ENABLE) {
		IRQ_enable_interrupt(IRQ_number);
	} else if(set == DISABLE) {
		IRQ_disable_interrupt(IRQ_number);
	}
}
