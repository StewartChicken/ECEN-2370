/*
 * ApplicationCode.c
 *
 *  Created on: Nov 14, 2023
 *      Author: xcowa
 */

#include "Application.h"

/**
 * @brief Function for initializing the application and all necessary peripherals
*/
void APPLICATION_init()
{
    GPIO_Init();
    SPI5_Init();
    GYRO_Init();

    #if 0
    while(1)
    {
        APPLICATION_sample_gyro();
        int16_t force = APPLICATION_get_gyro_angle();
        printf("Force: %d\n", force);
    }
    #endif

    RNG_enable(); // Turn on random number generator
    TIMER_init_timer4();
    TIMER_init_timer3();

    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0, LCD_COLOR_WHITE);

    APPLICATION_initialize_ball();
}

/**
 * @brief Gets a random initial velocity for the ball - uses RNG driver to do so
 *  
 * @param max - indicates the max value the random velocity may be
 * @return - returns a signed integer which represents the initial velocity
*/
int32_t APPLICATION_get_random_velocity(uint32_t max)
{
    int32_t number = RNG_get_random_number(max);
    int32_t mult = RNG_get_random_number(10);

    if(mult < 5)
    {
        return -1 * number;
    }

    return number;
}

/**
 * @brief Gets a random initial position for the ball - uses RNG driver to do so
 *  
 * @param max - indicates the max value the random velocity may be
 * @return - returns a signed integer which represents the initial position
*/
uint32_t APPLICATION_get_random_position(uint32_t max)
{
    return RNG_get_random_number(max);
}

/**
 * @brief Starts stm32 timer 4
*/
void APPLICATION_start_timer4()
{
    TIMER_start_timer4();
}

/**
 * @brief Starts stm32 timer 3
*/
void APPLICATION_start_timer3()
{
    TIMER_start_timer3();
}

/**
 * @brief returns the number of seconds that have elapsed for the current round
 * 
 * @return - returns an int which represents the number of seconds
*/
int APPLICATION_get_round_duration()
{
    return round_duration;
}


/**
 * @brief initializes the ball to its initial position and velocity
*/
void APPLICATION_initialize_ball() // Can draw from 10 to 210
{
    ball_position = APPLICATION_get_random_position(230) + 10;
    ball_velocity = APPLICATION_get_random_velocity(3) + 1;
}

/**
 * @brief called every frame to to update the game state
 *        updates position and velocity of the ball
 *        samples gyro input
*/
void APPLICATION_update_ball()
{
    LCD_update_frame(ball_position, round_duration);
    APPLICATION_sample_gyro();
        
    ball_velocity += (GYRO_get_angle() / 2) * counter_force; 

    if(ball_velocity > 5)
    {
        ball_velocity = 5;
    }
    if(ball_velocity < -5)
    {
        ball_velocity = -5;
    }

    ball_position += ball_velocity;

    HAL_Delay(1000 / frame_rate);
}

/**
 * @brief Reads current data from the gyro 
*/
void APPLICATION_sample_gyro(void)
{
    int8_t data_L = GYRO_get_reg_value(OUT_Y_L_ADDR);
    int8_t data_H = GYRO_get_reg_value(OUT_Y_H_ADDR);
    int16_t data = data_L | data_H << 8;

    data = data * ((float)17.50f);

    data = data / 800;

    if(data > 40)
    {
        data = 40;
    } else if(data < -40)
    {
        data = -40;
    }

    GYRO_update_angle(data);
}

/**
 * @brief Gets the current angle the gyroscope is held at by the user
 * 
 * @return returns a signed integer which represents the angle
*/
int16_t APPLICATION_get_gyro_angle(void)
{
    return GYRO_get_angle();
}

/**
 * @brief Interrupt handler for timer 4 - used to increment round duration
*/
void TIM4_IRQHandler()
{
    IRQ_disable_interrupt(TIM4_IRQ_NUMBER); // Initially disable interrupt
    IRQ_enable_interrupt(TIM3_IRQ_NUMBER);
    
    round_duration ++;
    
    IRQ_clear_pending_interrupt(TIM4_IRQ_NUMBER);
    TIMER_clear_interrupt_timer4(); // Clear UIF bit in tim4 SR register

    IRQ_enable_interrupt(TIM4_IRQ_NUMBER);
}

/**
 * @brief Interrupt handler for timer 3 - used to increment counter force variable
*/
void TIM3_IRQHandler()
{
    IRQ_disable_interrupt(TIM3_IRQ_NUMBER); // Initially disable interrupt
    IRQ_enable_interrupt(TIM4_IRQ_NUMBER);
    
    counter_force ++;
    
    IRQ_clear_pending_interrupt(TIM3_IRQ_NUMBER);
    TIMER_clear_interrupt_timer3(); // Clear UIF bit in tim3 SR register

    IRQ_enable_interrupt(TIM3_IRQ_NUMBER);
}