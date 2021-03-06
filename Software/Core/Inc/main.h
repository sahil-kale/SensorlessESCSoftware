/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWM_A_Pin GPIO_PIN_0
#define PWM_A_GPIO_Port GPIOA
#define PWM_B_Pin GPIO_PIN_1
#define PWM_B_GPIO_Port GPIOA
#define PWM_C_Pin GPIO_PIN_2
#define PWM_C_GPIO_Port GPIOA
#define OD_A_Pin GPIO_PIN_3
#define OD_A_GPIO_Port GPIOA
#define OD_B_Pin GPIO_PIN_4
#define OD_B_GPIO_Port GPIOA
#define OD_C_Pin GPIO_PIN_5
#define OD_C_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOB
#define BEMF_A_Pin GPIO_PIN_5
#define BEMF_A_GPIO_Port GPIOB
#define BEMF_A_EXTI_IRQn EXTI4_15_IRQn
#define BEMF_B_Pin GPIO_PIN_6
#define BEMF_B_GPIO_Port GPIOB
#define BEMF_B_EXTI_IRQn EXTI4_15_IRQn
#define BEMF_C_Pin GPIO_PIN_7
#define BEMF_C_GPIO_Port GPIOB
#define BEMF_C_EXTI_IRQn EXTI4_15_IRQn
/* USER CODE BEGIN Private defines */

#define TIM_ARR (100UL)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
