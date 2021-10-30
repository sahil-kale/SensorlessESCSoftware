#include "pwm.h"

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "tim.h"
#include "gpio.h"

typedef struct PhasePinConfig {
	uint16_t OutputEnableGPIONum;
	GPIO_TypeDef* OutputEnableGPIOPort;
	TIM_HandleTypeDef *timer;
	uint16_t timer_channel;
} PhasePinConfig_t;

static void timer_init()
{
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

  TIM2->CCR1 = 500000;
  TIM2->CCR2 = 500000;
  TIM2->CCR3 = 500000;
  
}


static PhasePinConfig_t PhasePinConfig[3] = {
    {
        .OutputEnableGPIONum = OD_A_Pin,
        .OutputEnableGPIOPort = OD_A_GPIO_Port,
        .timer = &htim2,
        .timer_channel = TIM_CHANNEL_1
    },
    {
        .OutputEnableGPIONum = OD_B_Pin,
        .OutputEnableGPIOPort = OD_B_GPIO_Port,
        .timer = &htim2,
        .timer_channel = TIM_CHANNEL_2
    },
    {
        .OutputEnableGPIONum = OD_C_Pin,
        .OutputEnableGPIOPort = OD_C_GPIO_Port,
        .timer = &htim2,
        .timer_channel = TIM_CHANNEL_3
    },

};

void pwm_init()
{
    timer_init();
}

void setPhaseADuty(uint16_t dutyValue, bool enableOutput)
{

}

void setPhaseBDuty(uint16_t dutyValue, bool enableOutput)
{

}

void setPhaseCDuty(uint16_t dutyValue, bool enableOutput)
{

}