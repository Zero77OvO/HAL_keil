/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define KEY_CLO0_OUT_LOW  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET)
#define KEY_CLO1_OUT_LOW  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET)
#define KEY_CLO2_OUT_LOW  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_RESET)
#define KEY_CLO3_OUT_LOW  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_RESET)
 
#define KEY_CLO0_OUT_HIGH  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET)
#define KEY_CLO1_OUT_HIGH  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET)
#define KEY_CLO2_OUT_HIGH  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_SET)
#define KEY_CLO3_OUT_HIGH  HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_SET)
	
	
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
char KEY_SCAN(void);
char KEY_ROW_SCAN(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

