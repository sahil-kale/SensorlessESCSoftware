#include "pwm.h"

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "tim.h"
#include "gpio.h"

#define NUM_PHASES (3UL)

uint8_t PHASE_A_INDEX = 0;
uint8_t PHASE_B_INDEX = 1;
uint8_t PHASE_C_INDEX = 2;

#define MAX_VAL_32_BIT (0xFFFFFFFF)
#define MAX_VAL_16_BIT (0xFFFF)

typedef struct PhasePinConfig {
	uint16_t OutputEnableGPIONum;
	GPIO_TypeDef* OutputEnableGPIOPort;
	TIM_HandleTypeDef *timer;
	uint16_t timer_channel;
} PhasePinConfig_t;

static PhasePinConfig_t PhasePinConfig[NUM_PHASES] = {
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

static void timer_init();
static void set_duty_cycle(PhasePinConfig_t* config, uint32_t dutyValue, bool enableOutput);

static void timer_init()
{
  for(size_t i = 0; i < NUM_PHASES; i++)
  {
      PhasePinConfig_t *config = &PhasePinConfig[i];
      HAL_TIM_PWM_Start(config->timer, config->timer_channel);
      __HAL_TIM_SET_COMPARE(config->timer, config->timer_channel, 0);
      HAL_GPIO_WritePin(config->OutputEnableGPIOPort, config->OutputEnableGPIONum, false);
  }
  
}


void pwm_init()
{
    timer_init();
}

void invert_phases(bool inverted)
{
    if(inverted)
    {
        PHASE_B_INDEX = 2;
        PHASE_C_INDEX = 1;
    }
    else
    {
        PHASE_B_INDEX = 1;
        PHASE_C_INDEX = 2;
    }
}

void setPhaseADuty(uint32_t dutyValue, bool enableOutput)
{
    PhasePinConfig_t *config = &PhasePinConfig[PHASE_A_INDEX];
    set_duty_cycle(config, dutyValue, enableOutput);
}

void setPhaseBDuty(uint32_t dutyValue, bool enableOutput)
{
    PhasePinConfig_t *config = &PhasePinConfig[PHASE_B_INDEX];
    set_duty_cycle(config, dutyValue, enableOutput);
}

void setPhaseCDuty(uint32_t dutyValue, bool enableOutput)
{
    PhasePinConfig_t *config = &PhasePinConfig[PHASE_C_INDEX];
    set_duty_cycle(config, dutyValue, enableOutput);
}

static void set_duty_cycle(PhasePinConfig_t* config, uint32_t dutyValue, bool enableOutput)
{
    if(dutyValue > TIM_ARR)
    {
        dutyValue = TIM_ARR;
    }
    //HAL_TIM_PWM_Stop(config->timer, config->timer_channel);
    __HAL_TIM_SET_COMPARE(config->timer, config->timer_channel, dutyValue);
    HAL_GPIO_WritePin(config->OutputEnableGPIOPort, config->OutputEnableGPIONum, enableOutput);
    //HAL_TIM_PWM_Start(config->timer, config->timer_channel);
}
