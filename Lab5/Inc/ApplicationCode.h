/*
 * ApplicationCode.h
 *
 *  Created on: Sep 7, 2023
 *      Author: Evan Poon
 *
 *  TODO - Check validity of comment for initialization of leds
 */

#ifndef APPLICATIONCODE_H
#define APPLICATIONCODE_H

#include <stdint.h>
#include "Scheduler.h"

void APPLICATION_init(); // Initialize necessary hardware for this application

// GYRO driver functions
void APPLICATION_init_gyro();
uint32_t APPLICATION_gyro_getID(); // check return - should print device ID
void APPLICATION_power_on_gyro();
void APPLICATION_reboot_gyro();
uint32_t APPLICATION_get_gyro_temp(); // check return - should print temperature measurement
void APPLICATION_configure_gyro(); // May need an argument
uint32_t APPLICATION_get_gyro_status(); // Check name convention/return type
void APPLICATION_enable_gyro_communication();
void APPLICATION_disable_gyro_communication();

#endif /* APPLICATIONCODE_H_ */
