#ifndef GYRO_H
#define GYRO_H

#include <stdint.h>
#include "stm32f4xx_hal.h"


// GYRO register addresses
#define ID_ADDR 0x0F
#define CTRL1_ADDR 0x20
#define CTRL4_ADDR 0x23
#define CTRL5_ADDR 0x24
#define FIFO_CTRL_ADDR 0x2E
#define OUT_X_L_ADDR 0x28
#define OUT_X_H_ADDR 0x29
#define OUT_Y_L_ADDR 0x2A
#define OUT_Y_H_ADDR 0x2B


// GYRO register configurations
#define CTRL1_CONFIG 0xDF // 0b11011111 - 100Hz output frequency
#define CTRL4_CONFIG 0x10 // 0b00010000
#define CTRL5_CONFIG 0xC0 // 0b11000000
#define FIFO_CTRL_CONFIG 0x40  // 0b01000000 - 0x40 for stream mode or 0x00 for bypass mode

#define GYRO_READ 0b10000000 // Read from gyro register
#define GYRO_WRITE 0b00000000 // Write to gyro register

void GPIO_Init(void);
void SPI5_Init(void);
void GYRO_Init(void);

void GYRO_Power_On(void);
void GYRO_Power_Off(void);
void GYRO_Enable_Slave_Communication(void);
void GYRO_Disable_Slave_Communication(void);

void GYRO_config_reg(uint8_t address, uint8_t config);
uint8_t GYRO_get_reg_value(uint8_t address);

void GYRO_update_angle(int16_t angle);

int16_t GYRO_get_angle(void);

#endif