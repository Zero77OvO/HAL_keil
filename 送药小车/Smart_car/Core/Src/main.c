/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "L294N.h"
#include <stdio.h>
#include <String.h>
#include "OLED.h"
#include "vofa.h"
#include "matrix_keyboard.h"
#include "convert.h"
#include "pid.h"
#include "Bluetooth.h"

#include "math.h"
//#include "matrix_keyboard.h"
/* USER CODE BEGIN 4 */

/* USER CODE END 4 */


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int time=0;

int key1=3;

float a=0;
float t;
float b=10;

extern tPid pidMotor1Speed;
int flag1=1;


double Wave1=10;

double Wave2=10;

double pi=3.1415;

extern uint8_t rx_buff;


double A =2;  // 幅值
double B =4; 
double sin_x;  // 计算正弦值
double K =0;
double T =6.28;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	
  OLED_Init();
	PID_init();
	//HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_RX_BUF,1);
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData,1);
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_buff, 1); 
//	HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1);		
  __HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);

  HAL_TIM_Base_Start_IT(&htim2);
	//HAL_TIM_Base_Start_IT(&htim2);
	
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);

  






 

  

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	
	
  while (1)
  {
		
		
		
//		for(K=0;K<T;K+=0.01){
//			
//			
//			if(K>=T){K=0;}
//    Wave1 = A*sin(K*pi);
//			
//		Wave2 = B*sin(K*pi);
//		
//			
//		vodka_JustFloat_send(&huart2);	
//		}
//		vodka_JustFloat_send(&huart2);
		
	/*	key1=Key_Scan();
		
		if(key1!=0){
		OLED_Clear();
		//OLED_ShowNum(1,1,key1,3,16);
	
	}
	OLED_Showdecimal(0,0,num,3,1,16);
	OLED_Showdecimal(0,2,num2,3,1,16);
	OLED_Showdecimal(0,4,num3,3,1,16);
	
	
	
	if(num=='u'){
	Forward();
	}
	if(num=='l'){
	Left();
	}
	if(num=='r'){ 
	Right();
	}
	if(num=='d'){
	Back();
	}
	if(num=='0'){
	Reset();
	}*/
	
	
//OLED_Showdecimal(0,6,USART1_RX_STA,3,1,16);
	
	    /* PID_realize(&pidMotor1Speed,t);
	
	
	
        t+= 0.01*PID_x(set_Speed,t,0,0.1,3.5); //（目标值，现值，p,i,d）
	
        if (t >= set_Speed&&flag1==1)   // 达到上限或下限时改变方向
        {
            set_Speed = -set_Speed;    //set_Speed是极值
					flag1=0;
        }
				 if (t <= set_Speed&&flag1==0)   // 达到上限或下限时改变方向
        {
            set_Speed = -set_Speed;
					
					flag1=1;
        }
	
	*/
	
  	
	
	

		
	
 // printf("%d",a);
	   
	 	//TargetTracking();
		// HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		
		 //OLED_ShowNum(1,1,key1,3,16);
		// OLED_Draw12864BMP(1);
		//Forward();
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/*int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

//  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
//  * 输入参数: 无
//  * 返 回 值: 无
//  * 说    明：无
// 
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart2, &ch, 1, 0xffff);
  return ch;
}*/


/*
char order;//指令 0:停止  1:开始
char message[]="hello windows！\n";//输出信息
char tips[]="CommandError\n";//提示1
char tips1[]="Start.....\n";//提示2
char tips2[]="Stop......\n";//提示3
int flag=0;//标志 0:停止发送 1.开始发送





void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)//串口中断回调函数
{   unsigned int com_data; 
		static unsigned int RxCounter1=0;
		static float RxBuffer1[15]={0};
		static unsigned int RxState = 0;	
	
	
	
    if(huart ==&huart2)
    {
        if((USART2_RX_STA&0x8000)==0)//接收未完成
        {
            if(USART2_NewData==0x5A)//接收到了0x5A
            {
                 USART2_RX_STA|=0x8000;   //接收完成了，将USART2_RX_STA中的bit15（15位）置1
            }
            else
            {
                   USART2_RX_BUF[USART2_RX_STA&0X7FFF]=USART2_NewData; //将收到的数据放入数组，
                   USART2_RX_STA++;  //数据长度计数加1
                   if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收

            }
        }
				
				
				
        HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //因为每执行完一次中断回调函数会将接收中断功能关闭，所以最后需要再开启接收中断


    }
}

*/





//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    
//    if (htim == (&htim2))
//    {
//        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//    }
//}












/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
