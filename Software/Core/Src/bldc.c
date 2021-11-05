#include "bldc.h"
#include "gpio.h"
#include "main.h"
#include "pwm.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct backemf_gpio_map {
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} backemf_gpio_map_t;

#ifdef ENABLE_BACKEMF_SENSEING_DEBUG
static backemf_gpio_map_t backemf_gpio_mapping[] = {
    {BEMF_A_GPIO_Port, BEMF_A_Pin},
    {BEMF_B_GPIO_Port, BEMF_B_Pin},
    {BEMF_C_GPIO_Port, BEMF_C_Pin},
};
#endif

static volatile uint8_t speed = 30;
static volatile uint8_t bldc_state = 0;
static volatile bool reversed = false;
static volatile bool flag_set_state_switch = false;

// Timer Wraparound checks
static volatile uint64_t pwm_tim_cnt = 0;
static volatile uint64_t pwm_tim_ccr = 10000;

static void control_loop();

static void commutate_motor_trapazoidal(uint8_t state);

void pwm_tim_cb() {
  pwm_tim_cnt += 1;
  if (pwm_tim_cnt == pwm_tim_ccr) {
    bldc_state++;
    bldc_state %= 6;
    commutate_motor_trapazoidal(bldc_state);
#ifdef ENABLE_BACKEMF_SENSEING_DEBUG
    pwm_tim_ccr = ~0;
#endif
    pwm_tim_cnt = 0;
  }

  // Run the 10kHz control loop
  control_loop();
}

void bldc_init() {
  pwm_init();
  HAL_TIM_Base_Start_IT(&htim2); // Start interrupt time base
}

void bldc_loop() {
  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  HAL_Delay(500);
}

// Control Loop, 10kHz
static void control_loop() { invert_phases(reversed); }

void update_control(uint8_t new_speed, bool is_reversed) {
  speed = new_speed;
  reversed = is_reversed;
}

static void commutate_motor_trapazoidal(uint8_t state) {
  switch (state) {
  case 0:
    // Step 0, A high, B low, C off
    // BEMF C rising
    setPhaseADuty(speed, true);
    setPhaseBDuty(0, true);
    setPhaseCDuty(0, false);
    break;
  case 1:
    // Step 1, A high, B off, C low
    // BEMF B falling
    setPhaseADuty(speed, true);
    setPhaseBDuty(0, false);
    setPhaseCDuty(0, true);
    break;
  case 2:
    // Step 2, A off, B high, C low
    // BEMF A rising
    setPhaseADuty(0, false);
    setPhaseBDuty(speed, true);
    setPhaseCDuty(0, true);
    break;
  case 3:
    // Step 3, A low, B high, C off
    // BEMF C falling
    setPhaseADuty(0, true);
    setPhaseBDuty(speed, true);
    setPhaseCDuty(0, false);
    break;
  case 4:
    // Step 4, A low, B off, C high
    // BEMF B rising
    setPhaseADuty(0, true);
    setPhaseBDuty(0, false);
    setPhaseCDuty(speed, true);
    break;
  case 5:
    // Step 5, A off, B low, C high
    // BEMF A falling
    setPhaseADuty(0, false);
    setPhaseBDuty(0, true);
    setPhaseCDuty(speed, true);
    break;
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
#ifdef ENABLE_BACKEMF_SENSEING_DEBUG
  backemf_gpio_map_t phaseA_backemf_map = backemf_gpio_mapping[PHASE_A_INDEX];
  backemf_gpio_map_t phaseB_backemf_map = backemf_gpio_mapping[PHASE_B_INDEX];
  backemf_gpio_map_t phaseC_backemf_map = backemf_gpio_mapping[PHASE_C_INDEX];

  backemf_gpio_map_t *appropriate_backemf_map;

  // MUXING LOGIC
  if (bldc_state == 2 || bldc_state == 5) {
    appropriate_backemf_map = &backemf_gpio_mapping[PHASE_A_INDEX];
  } else if (bldc_state == 1 || bldc_state == 4) {
    appropriate_backemf_map = &backemf_gpio_mapping[PHASE_B_INDEX];
  } else {
    appropriate_backemf_map = &backemf_gpio_mapping[PHASE_C_INDEX];
  }

  if (GPIO_Pin == appropriate_backemf_map->GPIO_Pin) {
    // Correct BackEMF signal
    for (int8_t counter = 0; counter < 10; counter++) {
      bool bemf_state = HAL_GPIO_ReadPin(appropriate_backemf_map->GPIOx,
                                         appropriate_backemf_map->GPIO_Pin);
      // Debounce logic
      if (bldc_state & 1) // falling edge BEMF
      {
        if (bemf_state) {
          counter--;
        }
      } else // Falling Edge BEMF
      {
        if (!bemf_state) {
          counter--;
        }
      }
    }
    // Update the timer stuff
    pwm_tim_ccr = pwm_tim_cnt * 2;
  }
#endif
}
