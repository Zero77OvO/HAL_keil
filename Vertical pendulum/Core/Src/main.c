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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <String.h>
#include "math.h"
#include "L298N.h"
#include "OLED.h"
#include "vofa.h"
#include "matrix_keyboard.h"
#include "convert.h"
#include "pid.h"
#include "Bluetooth.h"
#include "adc_get.h"
#include "stdbool.h" 

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



extern tPid pidMotor1Speed;
extern uint8_t rx_buff;
extern uint16_t ADC_Value; //����һ�����������ADC���ص�ֵ


double pi=3.1415;

float kp_x=0.0;
float ki_x=0.0;
float kd_x=0.0;
float target_value;
float Speed_out;

extern float angle;

extern float time;
int stat=-1;

int key1=0;
int key2=0;

int Dr;
extern Motor motor1;
extern float speed;
extern float location;
float Location_out;

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
  MX_I2C1_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	
	Motor_Init();             
  OLED_Init();              //OLED����ʼ��
	PID_init();               //PID��ʼ��
	
	

	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rx_buff, 1); 

 
	

  //��ʱ����ʼ��

	OLED_Clear();
	
	//pwm��ʼ��
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,8000);//   ��ѹ 3/10 * 12
  
	
  HAL_Delay(1000);

  HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);


 

  

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	//130���ڶ�
  while (1)
  {
		
	  OLED_Showdecimal(0,0,stat,1,1,16);
		OLED_Showdecimal(0,2,Dir(),1,0,16); // ���Ұ���0 �������1
		OLED_Showdecimal(32,2,read_pin(),1,0,16);//0������ 1������
		OLED_Showdecimal(0,4,time,4,4,16);
		OLED_Showdecimal(0,6,angle,3,3,16); OLED_Showdecimal(32,6,location,3,3,16);
//		OLED_Showdecimal(0,2,motor1.speed,3,3,16);
//		OLED_Showdecimal(0,4,target_value,3,3,16);
		
		if(stat==-1){
    
	  stat=0;
		
		time=0;
			
		}
		

		//start
	  if(stat==0||stat==1){__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,9000);}
		if(stat==3||stat==4){__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,9500);}
		if(stat==5||stat==6){__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,9000);}
		
		if(stat==0){if(time>1.05){stat=1;time=0.15;}  else{R();} if(angle<330&&angle>320){stat=3;HAL_Delay(10);  }   } 
		if(stat==1){if(time>0.5){stat=0;time=0;}  else{L();} if(angle>170&&angle<180) {stat=4; HAL_Delay(10); }  }
		
	
		
		if(stat==4){if(key1==0){time=0;key1=1;}if(time>1.2){stat=3;time=0;}  else{R();} if(angle<290&&angle>280){time=0;stat=5;HAL_Delay(10);}  }    
		if(stat==3){if(key1==0){time=0;key1=1;}if(time>0.6){stat=4;time=0;}  else{L();} if(angle>200&&angle<210){time=0;stat=6;HAL_Delay(10);}  }	
		
			
		if(stat==6){if(time<0.6){R();}    }    
		if(stat==5){if(time<0.1){L();}    }



			
		if(stat==7){stop();}
		
		
		
		
		
		
		
		
		
			

		if(stat==7){
		  Location_out=PID_y(500,location,0,0,0);
		  Speed_out=PID_x(120,angle,0,0,0);
			if(angle>120){ __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,8000-0.1*Speed_out); R();}
			else         { __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,8000+0.1*Speed_out); L();}
		
		}
  	
	  
		
		


		//vodka_JustFloat_send(&huart3); // vofa
		
	
		
  
	
	
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
