#ifndef BLDC_H
#define BLDC_H

#include "tim.h"

/**
 * @brief increments the PWM timer counter
 */
void pwm_tim_cb();

/**
 * @brief initalizes the BLDC motor controller
 */
void bldc_init();

/**
 * @brief loops through the BLDC motor control algo. Called by while(1)
 */
void bldc_loop();



#endif
