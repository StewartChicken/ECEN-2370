/*
 * Gyro.h
 *
 *  Created on: Nov 4, 2023
 *      Author: stewa
 */

#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#include <stdint.h>
#include "stm32f429xx.h"

//#define GYRO ((*SPI_TypeDef) SPI5_BASE) // Gyro is in the SPI5 peripheral - address defined in stm32f429xx.h
#define GYRO SPI5

// These four pins of the spi are used to establish communication between the gyro and the board
#define SPC 2               // SPI serial port clock - Connected to SPI5 SCK pin
#define SDI 3               // SPI Serial data input - Connected to SPI5 MOSI pin
#define SDO 4               // SPI serial data ouptut - Connected to SPI5 MISO pin
#define CS 5                // SPI enable - pull low to activate SPI

// Gyro register addresses
#define WHO_AM_I_ADDR 0x0F
#define CTRL_REG_1_ADDR 0x20
#define CTRL_REG_2_ADDR 0x21
#define CTRL_REG_3_ADDR 0x22
#define CTRL_REG_4_ADDR 0x23
#define CTRL_REG_5_ADDR 0x24
#define REFERENCE_DATACAPTURE_ADDR 0x25
#define OUT_TEMP_ADDR 0x26
#define STATUS_REG_ADDR 0x27

// FIFO data read from these registers
#define OUT_X_L_ADDR 0x28 
#define OUT_X_H_ADDR 0x29
#define OUT_Y_L_ADDR 0x2A
#define OUT_Y_H_ADDR 0x2B
#define OUT_Z_L_ADDR 0x2C
#define OUT_Z_H_ADDR 0x2D

#define FIFO_CTRL_REG_ADDR 0x2E
#define FIFO_SRC_REG_ADDR 0x2F
#define INT1_CFG_ADDR 0x30
#define INT1_SRC_ADDR 0x31
#define INT1_THS_XH_ADDR 0x32
#define INT1_THS_XL_ADDR 0x33
#define INT1_THS_YH_ADDR 0x34
#define INT1_THS_YL_ADDR 0x35
#define INT1_THS_ZH_ADDR 0x36
#define INT1_THS_Z_ADDRL 0x37
#define INT1_DURATION_ADDR 0x38

#define CTRL_REG_1_CONFIG 0b00001111 // Enable X, Y, and Z axes, power down mode = normal mode
#define CTRL_REG_4_CONFIG 0b00010000 // Full-scale selection = 500 dps
#define CTRL_REG_5_CONFIG 0b11000000 // FIFO enabled - Reboot memory content enabled
#define FIFO_CTRL_REG_CONFIG 0b00100000 // Configured to FIFO mode

static uint32_t Gyro_HAL_status;

void Gyro_init();
uint8_t Gyro_getID(); // check return - should print device ID
void Gyro_power_on();
void Gyro_reboot();
uint8_t Gyro_getTemp(); // check return - should print temperature measurement
void Gyro_config(); // May need an argument
uint32_t Gyro_get_SPI_status(); // Check name convention/return type
void Gyro_enable_slave_communication();
void Gyro_disable_slave_communication();


#endif /* INC_GYRO_H_ */
