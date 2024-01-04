/*
 * Scheduler.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Evan Poon
 *
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

// Bit masks which represent specific events
#define LED_TOGGLE_EVENT 0x1 			// 0b00000001
#define DELAY_EVENT 0x2      			// 0b00000010
#define POLL_BUTTON_EVENT 0x4 			// 0b00000100
#define GET_GYRO_TEMP_EVENT 0x8 		// 0b00001000
#define GET_GYRO_AXIS_DATA_EVENT 0x16 	// 0b00010000
#define REBOOT_CMD_GYRO_EVENT 0x32 		// 0b00100000

uint32_t SCHEDULAR_getScheduledEvents(); // Return scheduled events

void SCHEDULAR_addSchedulerEvent(uint32_t event); // Add event to scheduler

void SCHEDULAR_removeSchedulerEvent(uint32_t event); // Remove event from scheduler


#endif
