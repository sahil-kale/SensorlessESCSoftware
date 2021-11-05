#ifndef BLDC_H
#define BLDC_H

#include "tim.h"
#include <stdbool.h>

/**
 * @brief initalizes the BLDC motor controller
 */
void bldc_init();

/**
 * @brief loops through the BLDC motor control algo. Called by while(1)
 */
void bldc_loop();

/**
 * @brief BackEMF GPIO interrupt callback
 */
void BackEMF_Callback(uint16_t GPIO_Pin);

/**
 * @brief BLDC update control parameters
 */
void update_control(uint8_t new_speed, bool is_reversed);

#endif
