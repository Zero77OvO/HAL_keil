/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */



/*float USART2_RX_BUF[USART2_REC_LEN];		//目标数据
uint16_t USART2_RX_STA=0;
int USART2_NewData;
 
int num;
int num2;
int num3;
//static uint8_t RxState = 0;
 
void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)
{
    if(huart ==&huart2)
    { 
			if(RxState ==0){
      USART2_RX_BUF[USART2_RX_STA&0X7FFF]=USART2_NewData; 					
      USART2_RX_STA++; 
      RxState = 1;			
			}
			else if(RxState ==1){
      USART2_RX_BUF[USART2_RX_STA++]=USART2_NewData; 

				
      if(USART2_RX_STA>(USART2_REC_LEN-1)){
			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
			USART2_RX_STA=0;
			}
			
			if(USART2_RX_STA>=5||USART2_RX_BUF[USART2_RX_STA-1]== 0x0A)
			{
				
			num = USART2_RX_BUF[USART2_RX_STA-3];			
			num2 = USART2_RX_BUF[USART2_RX_STA-4];
			num3 = USART2_RX_BUF[USART2_RX_STA-5];	
				
			USART2_RX_STA=0;
			RxState=0;
			}
			
			}
			
			if(USART2_RX_STA>(USART2_REC_LEN-1)){
			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
			USART2_RX_STA=0;
			
			}
			else if(RxState ==2)   //接收异常
			{
				USART2_RX_STA=0;
			  memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
				}
			
			
			
			
      HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1);		
			
    }		

	}

*/

#ifdef __GNUC__
     #define PUTCHAR_PROTOTYPE int _io_putchar(int ch)
 #else
     #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
 #endif /* __GNUC__*/
 
 /******************************************************************
     *@brief  Retargets the C library printf  function to the USART.
     *@param  None
     *@retval None
 ******************************************************************/
 PUTCHAR_PROTOTYPE
 {
     HAL_UART_Transmit(&huart3, (uint8_t *)&ch,1,0xFFFF);
     return ch;
 }




/* USER CODE END 0 */

UART_HandleTypeDef huart3;

/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
