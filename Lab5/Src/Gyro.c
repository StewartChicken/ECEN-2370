/*
 * Gyro.c
 *
 *  Created on: Nov 4, 2023
 *      Author: stewa
 */

#include "Gyro.h"

// Initialize SPI5 peripheral (connected to gyro)
void Gyro_init()
{
	GYRO->CR1 &= ~(SPI_CR1_BR); // Set Baud rate to clk / 2

	GYRO->CR1 &= ~(SPI_CR1_CPHA); // Clock phase config
	GYRO->CR1 &= ~(SPI_CR1_CPOL); // Clock polarity config

	GYRO->CR1 &= ~(SPI_CR1_DFF); // Set Data frame to 8 bit
	GYRO->CR1 &= ~(SPI_CR1_LSBFIRST); // Send most significant byte first
	GYRO->CR1 &= ~(SPI_CR1_SSM); // Slave selected by software
	GYRO->CR1 &= ~(SPI_CR1_SSI); // Chip select pulled low to enable communication
	GYRO->CR2 &= ~(SPI_CR2_FRF); // Set to Motorola mode
	GYRO->CR1 &= ~(SPI_CR1_MSTR); // Enable master mode for stm chip
}

uint8_t Gyro_getID()
{
	uint8_t packet = 0;
	packet |= (1 << 15); // Read from gyro
	packet |= ~(1 << 14); // Do not increment address
	packet |= (WHO_AM_I_ADDR << 8); // Read from register at address 0x0F within gyro 
	GYRO->DR = packet; // Write to DX register to transmit data to gyro

	packet &= 0;
	packet |= GYRO->DR; // Read from DR register to access data sent by gyro

	return packet; // Return ID
}

void Gyro_power_on()
{
	Gyro_enable_slave_communication();
}

void Gyro_reboot()
{
	Gyro_disable_slave_communication();
	GYRO->DR = 0;
	Gyro_enable_slave_communication();
}

uint8_t Gyro_getTemp()
{
	uint8_t packet = 0;
	packet |= (1 << 15); // Read from gyro
	packet |= ~(1 << 14); // Do not increment address
	packet |= (OUT_TEMP_ADDR << 8); // Read from register at address 0x26 within gyro 
	GYRO->DR = packet; // Write to DX register to transmit data to gyro

	packet &= 0;
	packet |= GYRO->DR; // Read from DR register to access data sent by gyro

	return packet; // Return temp
}

// Configure gyro registers using spi
void Gyro_config()
{
	
	uint16_t packet = 0;

	packet |= ~(1 << 15); // Write to gyro	
	packet |= ~(1 << 14); // Do not increment address
	packet |= (CTRL_REG_1_ADDR << 8); // Write to register at address 0x20 within gyro 
	packet |= CTRL_REG_1_CONFIG; // Data to be written
	GYRO->DR = packet; // Write to DX register to gyro

	packet = 0; // Clear packet

	packet |= ~(1 << 15); // Write to gyro	
	packet |= ~(1 << 14); // Do not increment address
	packet |= (CTRL_REG_4_ADDR << 8); // Write to register at address 0x23 within gyro 
	packet |= CTRL_REG_4_CONFIG; // Data to be written
	GYRO->DR = packet; // Write to DX register to gyro

	packet = 0; // Clear packet

	packet |= ~(1 << 15); // Write to gyro	
	packet |= ~(1 << 14); // Do not increment address
	packet |= (CTRL_REG_5_ADDR << 8); // Write to register at address 0x24 within gyro 
	packet |= CTRL_REG_5_CONFIG; // Data to be written
	GYRO->DR = packet; // Write to DX register to gyro

	packet = 0; // Clear packet

	packet |= ~(1 << 15); // Write to gyro	
	packet |= ~(1 << 14); // Do not increment address
	packet |= (FIFO_CTRL_REG_ADDR << 8); // Write to register at address 0x2E within gyro 
	packet |= FIFO_CTRL_REG_CONFIG; // Data to be written
	GYRO->DR = packet; // Write to DX register to gyro

}

uint8_t Gyro_get_HAL_SPI_status()
{
	return Gyro_HAL_status;
}

void Gyro_enable_slave_communication()
{
	GYRO->CR1 |= (SPI_CR1_SPE); // Enable SPE in CR1 of SPI5
}

void Gyro_disable_slave_communication()
{
	GYRO->CR1 &= ~(SPI_CR1_SPE); // Disable SPE in CR1 of SPI5
}

