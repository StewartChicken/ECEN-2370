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
#define LED_TOGGLE_EVENT 0x1 // 0b00000001 
#define DELAY_EVENT 0x2      // 0b00000010

uint32_t getScheduledEvents(); // Return scheduled events

void addSchedulerEvent(uint32_t event); // Add event to scheduler

void removeSchedulerEvent(uint32_t event); // Remove event from scheduler


#endif
