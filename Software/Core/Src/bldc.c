#include "bldc.h"
#include "pwm.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

static volatile uint8_t speed = 30;
static volatile uint8_t bldc_state = 0;
static volatile bool flag_set_state_switch = false;

//Timer Wraparound checks
static volatile uint64_t pwm_tim_cnt = 0;
static volatile uint64_t pwm_tim_ccr = 100;

static void commutate_motor_trapazoidal(uint8_t state);


void pwm_tim_cb()
{
  pwm_tim_cnt += 1;
  if(pwm_tim_cnt == pwm_tim_ccr)
  {
    bldc_state++;
    bldc_state %= 6;
    commutate_motor_trapazoidal(bldc_state);
    //pwm_tim_ccr = ~0;
    pwm_tim_cnt = 0;
  }
}


void bldc_init()
{
	pwm_init();
	HAL_TIM_Base_Start_IT(&htim2); //Start interrupt time base
}

void bldc_loop()
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(500);
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

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  volatile uint8_t state = bldc_state;
  if((GPIO_Pin == BEMF_A_Pin) && ((bldc_state == 2) || (bldc_state == 5)))
  {
	  for(int8_t counter = 0; counter < 10; counter++)
	  {
      bool bemf_state = HAL_GPIO_ReadPin(BEMF_A_GPIO_Port, BEMF_A_Pin);

      //Debounce logic
      if(bldc_state & 1) //falling edge BEMF
      {
        if(bemf_state)
        {
          counter--;
        }
      }
      else //Falling Edge BEMF
      {
        if(!bemf_state)
        {
          counter--;
        }
      }
	  }

    //Update the timer stuff
    pwm_tim_ccr = pwm_tim_cnt;
  }

  if((GPIO_Pin == BEMF_B_Pin) && ((bldc_state == 1) || (bldc_state == 4)))
  {
    for(int8_t counter = 0; counter < 10; counter++)
	  {
      bool bemf_state = HAL_GPIO_ReadPin(BEMF_B_GPIO_Port, BEMF_B_Pin);

      //Debounce logic
      if(bldc_state & 1) //falling edge BEMF
      {
        if(bemf_state)
        {
          counter--;
        }
      }
      else //Falling Edge BEMF
      {
        if(!bemf_state)
        {
          counter--;
        }
      }
	  }

    //Update the timer stuff
    pwm_tim_ccr = pwm_tim_cnt;
  }

  if((GPIO_Pin == BEMF_C_Pin) && ((bldc_state == 0) || (bldc_state == 3)))
  {
    for(int8_t counter = 0; counter < 10; counter++)
	  {
      bool bemf_state = HAL_GPIO_ReadPin(BEMF_C_GPIO_Port, BEMF_C_Pin);

      //Debounce logic
      if(bldc_state & 1) //falling edge BEMF
      {
        if(bemf_state)
        {
          counter--;
        }
      }
      else //Falling Edge BEMF
      {
        if(!bemf_state)
        {
          counter--;
        }
      }
	  }

    //Update the timer stuff
    pwm_tim_ccr = pwm_tim_cnt;
  }

}

