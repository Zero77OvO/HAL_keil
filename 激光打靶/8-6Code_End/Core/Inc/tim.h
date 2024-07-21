
/* USER CODE BEGIN Header */
/*
 * @Author: WSY
 * @Date: 2023-08-05 09:54:49
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-06 00:10:09
 * @FilePath: \undefinedc:\Users\Alienware\Desktop\8_5Code\Core\Inc\tim.h
 * @Description: ...
 * 日落飞景秀长河,天地壮我行色
 * Copyright (c) 2023 by WSY, All Rights Reserved.
 */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

  /* USER CODE BEGIN Includes */
  extern PID lrControl;
  extern PID upControl;
  void PIDUD(uint8_t aim, uint8_t now);
  void PIDLR(uint8_t aim, uint8_t now);
  void DJIOut(void);
  // void Serve(uint8_t aim,uint8_t now);
  /* USER CODE END Includes */

  extern TIM_HandleTypeDef htim1;

  extern TIM_HandleTypeDef htim3;

  extern TIM_HandleTypeDef htim5;

  /* USER CODE BEGIN Private defines */

  /* USER CODE END Private defines */

  void MX_TIM1_Init(void);
  void MX_TIM3_Init(void);
  void MX_TIM5_Init(void);

  void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

  /* USER CODE BEGIN Prototypes */

  /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */
