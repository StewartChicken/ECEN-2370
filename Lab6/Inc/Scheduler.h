#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

// Bit masks which represent specific events
#define UPDATE_GAME_EVENT 0x1 			// 0b00000001
           

uint32_t SCHEDULAR_getScheduledEvents(); // Return scheduled events

void SCHEDULAR_addSchedulerEvent(uint32_t event); // Add event to scheduler

void SCHEDULAR_removeSchedulerEvent(uint32_t event); // Remove event from scheduler



#endif