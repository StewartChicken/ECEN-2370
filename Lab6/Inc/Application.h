#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdbool.h>
#include <stdio.h>
#include "Scheduler.h"
#include "LCD.h"
#include "RNG.h"
#include "Timer.h"
#include "Gyro.h"

[[maybe_unused]] static uint8_t round_duration; // How long has the user been playing the current round?
[[maybe_unused]] static int counter_force = 0; // Counter force on ball
[[maybe_unused]] static int ball_position;
[[maybe_unused]] static int ball_velocity;

[[maybe_unused]] static int frame_rate = 10;


void APPLICATION_init();

// Used to get initial position and velocity of ball
uint32_t APPLICATION_get_random_position(uint32_t max);
int32_t APPLICATION_get_random_velocity(uint32_t max);

// Start timer which displays duration on LCD screen
void APPLICATION_start_timer4(void);
// Start timer which increments counter force on ball
void APPLICATION_start_timer3(void);

int APPLICATION_get_round_duration(void);

void RunDemoForLCD(void);
void APPLICATION_initialize_ball(void); // Set initial position and velocity of ball 
void APPLICATION_update_ball(void);

void APPLICATION_sample_gyro(void);

int16_t APPLICATION_get_gyro_angle(void);

#endif
