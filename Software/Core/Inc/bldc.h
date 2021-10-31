#ifndef BLDC_H
#define BLDC_H

#include "tim.h"

void TIM2_IQR_HANDLER(TIM_HandleTypeDef *htim);

void bldc_init();

void bldc_loop();



#endif
