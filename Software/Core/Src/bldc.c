#include "bldc.h"
#include "pwm.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

static volatile uint8_t speed = 50;
static volatile uint8_t bldc_state = 0;
static volatile bool flag_set_state_switch = false;

//Timer Wraparound checks
static volatile uint32_t tim2_cnt = 0;
static volatile uint32_t tim2_ccr = ~0;

static void commutate_motor_trapazoidal(uint8_t state);


void TIM2_IQR_HANDLER(TIM_HandleTypeDef *htim)
{
  /* 
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_UPDATE) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
      //Do stuff here
    }
  }
  */

  tim2_cnt += 1;

}


void bldc_init()
{
  pwm_init();
}

void bldc_loop()
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(5);
  commutate_motor_trapazoidal(bldc_state);
}

static void commutate_motor_trapazoidal(uint8_t state)
{
    switch(state)
    {
      case 0:
        //Step 0, A high, B low, C off
        //BEMF C rising
        setPhaseADuty(speed, true);
        setPhaseBDuty(0, true);
        setPhaseCDuty(0, false);
        break;
      case 1:
        //Step 1, A high, B off, C low
        //BEMF B falling
        setPhaseADuty(speed, true);
        setPhaseBDuty(0, false);
        setPhaseCDuty(0, true);
        break;
      case 2:
        //Step 2, A off, B high, C low
        //BEMF A rising
        setPhaseADuty(0, false);
        setPhaseBDuty(speed, true);
        setPhaseCDuty(0, true);
        break;
      case 3:
        //Step 3, A low, B high, C off
        //BEMF C falling
        setPhaseADuty(0, true);
        setPhaseBDuty(speed, true);
        setPhaseCDuty(0, false);
        break;
      case 4:
        //Step 4, A low, B off, C high
        //BEMF B rising
        setPhaseADuty(0, true);
        setPhaseBDuty(0, false);
        setPhaseCDuty(speed, true);
        break;
      case 5:
        //Step 5, A off, B low, C high
        //BEMF A falling
        setPhaseADuty(0, false);
        setPhaseBDuty(0, true);
        setPhaseCDuty(speed, true);
        break;
    }

    bldc_state++;
    bldc_state %= 6;

}
