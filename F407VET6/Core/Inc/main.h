/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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
#define FIVE_Pin GPIO_PIN_2
#define FIVE_GPIO_Port GPIOE
#define FIVEE4_Pin GPIO_PIN_4
#define FIVEE4_GPIO_Port GPIOE
#define FIVEE5_Pin GPIO_PIN_5
#define FIVEE5_GPIO_Port GPIOE
#define FIVEE6_Pin GPIO_PIN_6
#define FIVEE6_GPIO_Port GPIOE
#define TFT_CS_Pin GPIO_PIN_4
#define TFT_CS_GPIO_Port GPIOA
#define TFT_RES_Pin GPIO_PIN_4
#define TFT_RES_GPIO_Port GPIOC
#define TFT_DC_Pin GPIO_PIN_5
#define TFT_DC_GPIO_Port GPIOC
#define TFT_BL_Pin GPIO_PIN_7
#define TFT_BL_GPIO_Port GPIOE
#define SPI2CS_Pin GPIO_PIN_12
#define SPI2CS_GPIO_Port GPIOB
#define SDCARD_Pin GPIO_PIN_3
#define SDCARD_GPIO_Port GPIOD
#define I2C_Pin GPIO_PIN_6
#define I2C_GPIO_Port GPIOB
#define I2CB7_Pin GPIO_PIN_7
#define I2CB7_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
