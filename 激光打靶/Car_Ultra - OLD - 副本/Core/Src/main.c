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
#include "L298N.h"
#include <stdio.h>
#include <String.h>
#include "OLED.h"
#include "vofa.h"
#include "matrix_keyboard.h"
#include "convert.h"
#include "pid.h"
#include "HuiDu.h"
#include "interrupt.h"
#include "mpuiic.h"
#include "mpu6050.h"
#include "IMU_FLITER.h"
#include "Delay.h"
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





  uint8_t data[] = 0X60;
  float temperature;
  float Turn_angle;
  extern float GX,GY,GZ;


  int road_flag;
  int move_flag;
  int road;

  extern int right_counter;//右轮前转--，后转++
  extern int left_counter;//左轮前转++ 后转--

  extern float Kp_x_v;  
  extern float Ki_x_v;
  extern float Kd_x_v;   
  extern int line_flag;
  extern int stop;
  extern int target;
  extern int speed_pwm;
	int counter;
  int counter_flag;
  int turn_flag=0;
  int turn_flag1=0;
  extern int cv_x;
  extern int cv_y;

  int liucheng=0;
  int mubiao;
  int mubiao1;
  int dir;
  int dir1;
  extern int target1;

  int stop_flag=0;
  extern int ori;
  extern int theta;

  int mubiao_flag;
  int mubiao1_flag=-1;
  int mubiao_BF;
  int mubiao_x;
  int time;
  int dir_buff;

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
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */



  MPU_Init();
	
  OLED_Init();
  //HAL_UART_Receive_IT(&huart1, (uint8_t *)&k210_Tx, 1); 
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData,1); 
	HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //bluetooth
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1); //openmv
	// HAL_UART_Receive_IT(&huart6, (uint8_t *)&rx_buff, 1);   //k210
	
//	HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1);		

  // HAL_TIM_Base_Start(&htim1);
  // HAL_TIM_Base_Start_IT(&htim1);
  //HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start_IT(&htim2);
 
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
  __HAL_TIM_SET_COUNTER(&htim4, 15000);
  __HAL_TIM_SET_COUNTER(&htim5, 15000);
   HAL_TIM_Base_Start_IT(&htim8);
  // HAL_TIM_Base_Start(&htim8);
   HAL_TIM_Base_Start_IT(&htim9);
  // HAL_TIM_Base_Start(&htim9);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1850);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,1900);

  OLED_Clear();
  HAL_Delay(1000);
// __HAL_TIM_CLEAR_IT(&htim2,TIM_IT_UPDATE ); //清除IT标志位
// __HAL_TIM_CLEAR_IT(&htim8,TIM_IT_UPDATE ); //清除IT标志位
// __HAL_TIM_CLEAR_IT(&htim9,TIM_IT_UPDATE ); //清除IT标志位
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
   Turn_angle=Angle_get();
   temperature=MPU_Get_Temperature();
	//TargetTracking();+
  


	//树莓派显示数字	
    OLED_ShowNum(0,0,target,1,16); OLED_ShowNum(16,0,mubiao,1,16);OLED_ShowNum(32,0,mubiao1,1,16);OLED_ShowNum(48,0,HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0),1,16);
    OLED_ShowNum(0,2,road_flag,1,16);OLED_ShowNum(16,2,liucheng,2,16);OLED_ShowNum(48,2,dir,1,16);OLED_ShowNum(64,2,dir1,1,16);
    OLED_ShowNum(0,4,left_counter,5,16);OLED_ShowNum(64,4,right_counter,5,16);
    OLED_ShowNum(0,6,time,5,16);OLED_ShowNum(84,6,theta,5,16);
    


    //OLED_Showdecimal(0,4,Turn_angle,4,4,16);
    //OLED_Showdecimal(0,6,GX,2,2,16);OLED_Showdecimal(50,6,GY,2,2,16);OLED_Showdecimal(100,6,GZ,2,2,16);


    //HAL_UART_Transmit(&huart2, data, sizeof(data), HAL_MAX_DELAY);
		
	//OLED_Showdecimal(72,2,temperature,4,1,16);
 // OLED_Showdecimal(72,4,USART3_RX_STA,3,1,16);
		
	//灰度	
  // OLED_ShowNum(0,6,L4,1,16);OLED_ShowNum(12,6,L3,1,16);OLED_ShowNum(24,6,L2,1,16);OLED_ShowNum(36,6,L1,1,16);
	// OLED_ShowNum(48,6,R1,1,16);OLED_ShowNum(60,6,R2,1,16);OLED_ShowNum(72,6,R3,1,16);OLED_ShowNum(84,6,R4,1,16);
		
  // int right_counter=__HAL_TIM_GET_COUNTER(&htim4);//右轮前转--，后转++
  // int left_counter=__HAL_TIM_GET_COUNTER(&htim5);//左轮前转++ 后转--

  if(dir_buff==1){dir=1;}

  if(mubiao_flag==0&&mubiao_BF!=0){

    mubiao=mubiao_BF;
    mubiao_flag=1;
    liucheng=-1;

  }

  if(liucheng==99){

    Forward();
  }

  if(liucheng!=0){time++;}

  mubiao1=mubiao_BF;
  //给一个病房
  if(liucheng==-1&&mubiao1==0){


    if(mubiao==1||mubiao==2){liucheng=1;}
    if(mubiao==3||mubiao==4||mubiao==5||mubiao==7||mubiao==6||mubiao==8){liucheng=10;}
    
}
  if(liucheng==1&&HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==0){
    
    move_wasd(1,60000);
   

   }

if(liucheng==22){
         
    if(mubiao==1&&mubiao_x<=50){  //找到目标病房
      mubiao1_flag=1;
      dir=1;
    }
    else if(mubiao==2&&mubiao_x>70){  //找到目标病房
      mubiao1_flag=1;
      dir=2;
    }

    if(mubiao1_flag==1){
      if(line_flag==0){Forward();}
      
      Line_Detection();  
    }
    


}

 
  if(liucheng==2)
  { if(dir==1){ //病房在左
    if(target1!=2&&target1!=3){
    move_wasd(7,0);
    }
    }
    if(dir==2){  //病房在右
    if(target1!=2&&target1!=3){
    move_wasd(9,0);
    }
    }
  }


  //返程
  if(liucheng==3){

    move_wasd(1,64000);
    
  }

  if(liucheng==4){

  if(dir==1){ //病房在左 返回右拐

    if(target1!=2){
    move_wasd(9,0);
    }

    }
    if(dir==2){  //病房在右 返回左拐

    if(target1!=2){
    move_wasd(7,0);
    }

    }


  }



    
  




  //远端送药
  if(liucheng==10&&HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==0){

    if(target1!=11){
    move_wasd(1,56000); 
    }
    // if(target1!=11){
    // move_wasd(1,51500); 
    // }

  }
  
  if(liucheng==5){

    if(mubiao==mubiao1&&mubiao_x<=50){  //找到目标病房
      dir=1;
    }
    if(mubiao==mubiao1&&mubiao_x>70){  //找到目标病房
      dir=2;
    }

    if(time>200){move_wasd(1,63000);}

    if(dir!=0){
      Forward();
      Line_Detection(); 
    }
  }

  if(liucheng==6){
    if(dir==1){ //病房在左 返回右拐
    if(target1!=2){
    move_wasd(7,0);
    }

    }
    if(dir==2){  //病房在右 返回左拐

    if(target1!=2){
    move_wasd(9,0);
    }

    }

  }




  if(liucheng==11){
  if(stop_flag==0){Reset();stop_flag=1;}

  if(target1!=11){
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,1850*1.2);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1950*1.2);
    move_wasd(10,0); 
    }

  if(mubiao==mubiao1){
    dir=1;dir_buff=1;
  }
  else{dir=2;}      

  }


  if(liucheng==12){
  if(mubiao==mubiao1){
    dir=1;dir_buff=1;
    }
  else{dir=2;}  

    move_wasd(11,0);
  }

  if(liucheng==13){
    
    move_wasd(2,0);
    
    
    Line_Detection();   
  }

  if(liucheng==14){
    stop_flag=0;
    if(dir==1){ //病房在左
    if(target1!=2&&target1!=3){
    move_wasd(7,0);
    }
    }

    if(dir==2){  //病房在右
    if(target1!=2&&target1!=3){
    move_wasd(9,0);
    }
    }
  
    
  }
  if(liucheng==15){
    if(stop_flag==0){
    move_wasd(1,64200);} 
    if(mubiao==mubiao1&&mubiao_x<=50){  //找到目标病房
      mubiao1_flag=1;
      dir1=1;
    }
    else if(mubiao==mubiao1&&mubiao_x>70){  //找到目标病房
      mubiao1_flag=1;
      dir1=2;
    }
    else if(mubiao!=mubiao1&&mubiao_x<=50){  //找到目标病房
      mubiao1_flag=1;
      dir1=2;
    }
    else if(mubiao!=mubiao1&&mubiao_x>50){  //找到目标病房
      mubiao1_flag=1;
      dir1=1;
    }
    if(mubiao1_flag==1&&time>80){
      if(stop_flag==11){stop_flag=12;Reset();}
      Forward();
      Line_Detection(); 
    }
  }
  if(liucheng==16){
  if(dir1==1){ //病房在左
    if(target1!=2&&target1!=3){
    move_wasd(7,0);
    }
    }
    if(dir1==2){  //病房在右
    if(target1!=2&&target1!=3){
    move_wasd(9,0);
    }
    }

  }



    //返程
  if(liucheng==17){

    if(stop_flag==0){
      move_wasd(1,64535);
    }
    if(stop_flag==1){
      //病房在左
      if(dir1==1){if(target1!=2&&target1!=3){move_wasd(9,0);}}
      //病房在右
      if(dir1==2){if(target1!=2&&target1!=3){move_wasd(7,0);}}
    }

  }
  if(liucheng==18){
     
      //病房在左
      if(dir==1){if(target1!=2&&target1!=7){move_wasd(9,0);}}
      //病房在右
      if(dir==2){if(target1!=2&&target1!=7){move_wasd(7,0);}}
    

  }



  
  
//直接走
	if(target1==1){
	Forward();
	}
	//直行一定距离 然后 //掉头
  if(target1==2){
   		move_flag=0;

      if(liucheng==14){road=40500;}
      else if(liucheng==2||liucheng==6){road=41000;}
      else if(liucheng==4){road=65535;}


      else if(liucheng==15){road=43000;}
      else if(liucheng==16){road=41000;}
      else if(liucheng==17){road=44500;}
      else if(liucheng==18){road=65535;
      Kp_x_v=4;  Ki_x_v=0.4;Kd_x_v=0; 
      __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,1850*2.5+speed_pwm);
	    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1950*2.5-speed_pwm);}
      
      else{road=42000;}

  		if(counter_flag==0&&move_flag==0){
			Reset();
  			__HAL_TIM_SET_COUNTER(&htim4, 40000);
  			__HAL_TIM_SET_COUNTER(&htim5, 40000);
    		  counter_flag=1; 
			}
    	if(left_counter>=road&&counter_flag==1&&left_counter<=road+500){Reset();move_flag=1;move_wasd(5,0);

		    if(liucheng==2||liucheng==6){if(stop_flag==0){Restart();HAL_Delay(200);stop_flag=1;}Reset();target1=3;}
		    if(liucheng==4){liucheng=5;}

       

		    if(liucheng==14){liucheng=15;}
        if(liucheng==16){target1=3;HAL_UART_Transmit(&huart2, data, sizeof(data), HAL_MAX_DELAY);}

        if(liucheng==17){target1=7;}
		
		
		}
    	else{if(move_flag==0){Forward();}}
  	}
	//转圈而已 &&药物放下后
	if(target1==3&&HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==1){
		  move_flag=0;
    
  		if(counter_flag==0){
  			__HAL_TIM_SET_COUNTER(&htim4, 30000);
  			__HAL_TIM_SET_COUNTER(&htim5, 30000);
        stop_flag=0;
      		counter_flag=1; 
		}
		//(30000-left_counter)+(30000-right_counter)>=3000
 		if(left_counter<=28540&&counter_flag==1){Reset();move_flag=1;move_wasd(5,0);

		
		if(liucheng==2||liucheng==6){liucheng=3;}



		if(liucheng==16){liucheng=17;stop_flag=0;}
		
		
		}
		else{if(move_flag==0){zhuanquan();}}
	}


  if(target1==7){
		  move_flag=0;
    
  		if(counter_flag==0){
  			__HAL_TIM_SET_COUNTER(&htim4, 30000);
  			__HAL_TIM_SET_COUNTER(&htim5, 30000);
      		counter_flag=1; 
		}
		//(30000-left_counter)+(30000-right_counter)>=3000
 		if(left_counter>=29000&&counter_flag==1&&left_counter<=31000){Reset();move_flag=1;move_wasd(5,0);

		

    if(liucheng==15){liucheng=16;}
		if(liucheng==17){liucheng=18;}
		
		
		}
		else{if(move_flag==0){Restart();}}    


  }

	//左小转
	if(target1==11){
	move_flag=0;
	if(counter_flag==0){
	Reset();
  	__HAL_TIM_SET_COUNTER(&htim4, 30000);
  	__HAL_TIM_SET_COUNTER(&htim5, 30000);
	counter_flag=1;
	}

  if(left_counter<=29730&&counter_flag==1){move_wasd(5,0);counter_flag=0;move_flag=1;}
	else{if(move_flag==0){Left_light();}}
	}




	

	
	
	
	
	
	
	
	
	
	vodka_JustFloat_send(&huart6);   //vofa
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
