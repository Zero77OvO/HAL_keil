/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    tim.c
 * @brief   This file provides code for the configuration
 *          of the TIM instances.
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
/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "Task.h"
#include "OpenMVTrans.h"
int nextPoint[2] = {0, 0};
/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim5;

/* TIM1 init function */
void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
}
/* TIM3 init function */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 71;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 19999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);
}
/* TIM5 init function */
void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 71;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 9999;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *tim_icHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (tim_icHandle->Instance == TIM1)
  {
    /* USER CODE BEGIN TIM1_MspInit 0 */

    /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PE14     ------> TIM1_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_TIM1_ENABLE();

    /* USER CODE BEGIN TIM1_MspInit 1 */

    /* USER CODE END TIM1_MspInit 1 */
  }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *tim_pwmHandle)
{

  if (tim_pwmHandle->Instance == TIM3)
  {
    /* USER CODE BEGIN TIM3_MspInit 0 */

    /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
    /* USER CODE BEGIN TIM3_MspInit 1 */

    /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle)
{

  if (tim_baseHandle->Instance == TIM5)
  {
    /* USER CODE BEGIN TIM5_MspInit 0 */

    /* USER CODE END TIM5_MspInit 0 */
    /* TIM5 clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();

    /* TIM5 interrupt Init */
    HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
    /* USER CODE BEGIN TIM5_MspInit 1 */

    /* USER CODE END TIM5_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (timHandle->Instance == TIM3)
  {
    /* USER CODE BEGIN TIM3_MspPostInit 0 */

    /* USER CODE END TIM3_MspPostInit 0 */

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USER CODE BEGIN TIM3_MspPostInit 1 */

    /* USER CODE END TIM3_MspPostInit 1 */
  }
}

void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *tim_icHandle)
{

  if (tim_icHandle->Instance == TIM1)
  {
    /* USER CODE BEGIN TIM1_MspDeInit 0 */

    /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /**TIM1 GPIO Configuration
    PE14     ------> TIM1_CH4
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_14);

    /* USER CODE BEGIN TIM1_MspDeInit 1 */

    /* USER CODE END TIM1_MspDeInit 1 */
  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *tim_pwmHandle)
{

  if (tim_pwmHandle->Instance == TIM3)
  {
    /* USER CODE BEGIN TIM3_MspDeInit 0 */

    /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
    /* USER CODE BEGIN TIM3_MspDeInit 1 */

    /* USER CODE END TIM3_MspDeInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle)
{

  if (tim_baseHandle->Instance == TIM5)
  {
    /* USER CODE BEGIN TIM5_MspDeInit 0 */

    /* USER CODE END TIM5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();

    /* TIM5 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM5_IRQn);
    /* USER CODE BEGIN TIM5_MspDeInit 1 */

    /* USER CODE END TIM5_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
#define ABG(x) (((x) > 0) ? (x) : (-(x)))
#define RADIO 10
#define MAXCNT 20
int step = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // 计算PID
  static int cnt = 0;
  cnt++;
  static int stableCnt = 0;
  if (cnt == 1)
  {
    cnt = 0;
    if (ABG(rectPosition[6] - pointPosition[0]) < RADIO && ABG(rectPosition[7] - pointPosition[1]) < RADIO && step == 0)
    {
      stableCnt++;
      if (stableCnt >= MAXCNT)
      {
        step = 1;
        stableCnt = 0;
      }
    }
    else if (ABG(rectPosition[4] - pointPosition[0]) < RADIO && ABG(rectPosition[5] - pointPosition[1]) < RADIO && step == 1)
    {
      stableCnt++;
      if (stableCnt >= MAXCNT)
      {
        step = 2;
        stableCnt = 0;
      }
    }
    else if (ABG(rectPosition[2] - pointPosition[0]) < RADIO && ABG(rectPosition[3] - pointPosition[1]) < RADIO && step == 2)
    {
      stableCnt++;
      if (stableCnt >= MAXCNT)
      {
        step = 3;
        stableCnt = 0;
      }
    }
    else if (ABG(rectPosition[0] - pointPosition[0]) < RADIO && ABG(rectPosition[1] - pointPosition[1]) < RADIO && step == 3)
    {
      stableCnt++;
      if (stableCnt >= MAXCNT)
      {
        step = 0;
        stableCnt = 0;
      }
    }
    else
      stableCnt = 0;
    if (step == 0)
    {
      PIDLR(rectPosition[6], pointPosition[0]);
      PIDUD(rectPosition[7], pointPosition[1]);
    }
    if (step == 1)
    {
      PIDLR(rectPosition[4], pointPosition[0]);
      PIDUD(rectPosition[5], pointPosition[1]);
    }
    if (step == 2)
    {
      PIDLR(rectPosition[2], pointPosition[0]);
      PIDUD(rectPosition[3], pointPosition[1]);
    }
    if (step == 3)
    {
      PIDLR(rectPosition[0], pointPosition[0]);
      PIDUD(rectPosition[1], pointPosition[1]);
    }
  }
  DJIOut();
}
PID lrControl;
PID upControl;
void PIDLR(uint8_t aim, uint8_t now)
{
  static float Error = 0, LastError_01 = 0, LastError_02 = 0;
  // static float LastOut = LRMIDPWM;
  float kp = 0, ki = 0, kd = 0;

  //------历史误差记录
  LastError_02 = LastError_01;
  LastError_01 = Error;

  Error = now - aim;

  //------增量式PID控制
  kp = lrControl.P * (Error - LastError_01);
  ki = lrControl.I * Error;
  kd = lrControl.D * (Error - 2 * LastError_01 + LastError_02);

  if (ki > 5)
    ki = 5;
  if (ki < -5)
    ki = -5;

  lrControl.Out += kp + ki + kd;

  // if (lrControl.Out > LastOut + 10)
  //   lrControl.Out = LastOut + 10;
  // if (lrControl.Out < LastOut - 10)
  //   lrControl.Out = LastOut - 10;

  // LastOut = lrControl.Out;

  if (lrControl.Out > LEFTPWM)
    lrControl.Out = LEFTPWM;
  if (lrControl.Out < RIGHTPWM)
    lrControl.Out = RIGHTPWM;
}
void PIDUD(uint8_t aim, uint8_t now)
{
  static float Error = 0, LastError_01 = 0, LastError_02 = 0;
  // static float LastOut = UDMIDPWM;
  float kp = 0, ki = 0, kd = 0;

  //------历史误差记录
  LastError_02 = LastError_01;
  LastError_01 = Error;

  Error = -(aim - now);

  //------增量式PID控制
  kp = upControl.P * (Error - LastError_01);
  ki = upControl.I * Error;
  kd = upControl.D * (Error - 2 * LastError_01 + LastError_02);

  if (ki > 5)
    ki = 5;
  if (ki < -5)
    ki = -5;

  upControl.Out += kp + ki + kd;

  // if (upControl.Out > LastOut + 10)
  //   upControl.Out = LastOut + 10;
  // if (upControl.Out < LastOut - 10)
  //   upControl.Out = LastOut - 10;

  // LastOut = upControl.Out;

  if (upControl.Out > UPPWM)
    upControl.Out = UPPWM;
  if (upControl.Out < DOWNPWM)
    upControl.Out = DOWNPWM;
}
void DJIOut(void)
{
  TIM3->CCR1 = (uint32_t)lrControl.Out;
  TIM3->CCR2 = (uint32_t)upControl.Out;
}
/**
 * @description: 线性插值服务函数
 * @param {uint8_t} 所处step
 * @return {*}
 */
// void Serve(uint8_t step, uint8_t *nextX, uint8_t *nextY)
// {
  // int abgX = 0, abgY = 0;
  // if (step == 1)
  // {
  //   abgX = pointPosition[4] - rectPosition[6];
  //   abgY = pointPosition[5] - rectPosition[7];
  // }
// }
/* USER CODE END 1 */
