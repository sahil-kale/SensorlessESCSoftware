#include "bldc.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct PhasePinConfig {
	uint16_t OutputEnableGPIONum;
	GPIO_TypeDef* OutputEnableGPIOPort;
	TIM_HandleTypeDef *timer;
	uint16_t timer_channel;
} PhasePinConfig_t;


static volatile uint32_t speed = 0;
static volatile uint8_t bldc_state = 0;
static volatile bool flag_set_state_switch = false;

//Timer Wraparound checks
static volatile uint32_t tim2_cnt = 0;
static volatile uint32_t tim2_ccr = ~0;


static void timer_init();

void TIM2_IQR_HANDLER(TIM_HandleTypeDef *htim)
{

  /* TIM Update event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_UPDATE) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
      //Do stuff here
    }
  }

}

static void timer_init()
{
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

  TIM2->CCR1 = 50000;
  TIM2->CCR2 = 500000;
  TIM2->CCR3 = 500;
  
}


void bldc_init()
{
  timer_init();
}

void bldc_loop()
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
}

/*

static void determine_step(uint8_t state)
{
    switch(state)
    {
      case 0:
        //Step 0
        break;
      case 1:
        //Step 1
        break;
      case 2:
        //Step 2
        break;
      case 3:
        //Step 3
        break;
      case 4:
        //Step 4
        break;
      case 5:
        //Step 5
        break;
    }

}


static void set_a_high()
{

}

*/
