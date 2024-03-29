/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "ApplicationCode.h"
#include "Scheduler.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{

	/*READ ME ---- The board may need to be reset for the LED to begin flashing */

	application_init();
	activate_green();

  int32_t events_to_run;

  /* Loop forever */
	for(;;){
		events_to_run = getScheduledEvents();

		if(events_to_run & LED_TOGGLE_EVENT) // If one of the scheduled events is the LED_TOGGLE_EVENT
		{
		  toggle_green_led();
		}

		if(events_to_run & DELAY_EVENT)
		{
			delay(1);
		}

	}

}
