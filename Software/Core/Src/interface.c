/*
 * interface.c
 *
 *  Created on: Nov 5, 2021
 *      Author: Sahil
 */

#include "interface.h"
#include "bldc.h"
#include "tim.h"

void interface_init(void)
{
    HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1); //Main Channel
    HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_2); //Alternate Channel
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim != &htim3)
    {
        return;
    }
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) //Triggered by rising edge
    {
        
    }
}

