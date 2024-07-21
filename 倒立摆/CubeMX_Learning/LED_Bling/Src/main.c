/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "pid.h"

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
int a = 0;
uint8_t aTxStartMessages[] = "\r\n******UART commucition using IT******\r\nPlease enter 10 characters:\r\n";
uint8_t aRxBuffer[1];
extern pid pid_speed;
extern pid pid_angle;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int c, FILE *stream) //??fputc??
{

  HAL_UART_Transmit(&huart1, (unsigned char *)&c, 1, 1000);
  return 1;
}

uint32_t adc_raw = 0;
uint16_t timer2_counter = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  timer2_counter++;
  if (timer2_counter == 50)
  {

    timer2_counter = 0;

    pid_angle.true_value = adc_raw;
    printf("%d %d\n", pid_angle.true_value, pid_angle.tar_value);
    pid_angle_cal();

    pid_set_tarspeed(pid_angle.output);
  }
  if (timer2_counter % 10 == 0)
  {
    pid_speed.true_value = 30000 - __HAL_TIM_GET_COUNTER(&htim8);
    __HAL_TIM_SET_COUNTER(&htim8, 30000);
    pid_speed_cal();

    if (pid_angle.true_value < TAR_ANGLE - 250 || pid_angle.true_value > TAR_ANGLE + 250)
      pid_speed.output = 0;
    // printf("Speed:%d\n", pid_speed.true_value);
    if (pid_speed.output < 0)
    {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -pid_speed.output);
    }

    else if (pid_speed.output > 0)
    {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pid_speed.output);
    }
    else if (pid_speed.output == 0)
    {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    }
  }
}
uint8_t msg[1];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  printf("%d\n", msg[0]);
  if (msg[0] == '1')
  {
    pid_angle.k_pro += 1;
    printf("Kp->:%.1f\n", pid_angle.k_pro);
  }
  else if (msg[0] == '2')
  {
    pid_angle.k_pro -= 1;
    printf("Kp->:%.1f\n", pid_angle.k_pro);
  }
  else if (msg[0] == '3')
  {
    pid_angle.k_int += 0.1;
    printf("Kd->:%.1f\n", pid_angle.k_int);
  }
  else if (msg[0] == '4')
  {
    pid_angle.k_int -= 0.1;
    printf("Kd->:%.1f\n", pid_angle.k_int);
  }

  else if (msg[0] == '5')
  {
    pid_angle.k_dif += 0.1;
    printf("Kp->:%.1f\n", pid_angle.k_dif);
  }
  else if (msg[0] == '6')
  {
    pid_angle.k_dif -= 0.1;
    printf("Kp->:%.1f\n", pid_angle.k_dif);
  }

  else if (msg[0] == '7')
  {
    pid_angle.k_pro += 0.05;
    printf("Kd->:%.2f\n", pid_angle.k_pro);
  }
  else if (msg[0] == '8')
  {
    pid_angle.k_pro -= 0.05;
    printf("Kd->:%.2f\n", pid_angle.k_pro);
  }
  else if (msg[0] == '9')
  {
    pid_angle.k_dif += 0.005;
    printf("Kd->:%.3f\n", pid_angle.k_dif);
  }
  else if (msg[0] == '0')
  {
    pid_angle.k_dif -= 0.005;
    printf("Kd->:%.3f\n", pid_angle.k_dif);
  }

  HAL_UART_Receive_IT(&huart1, (uint8_t *)&msg, 1);
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  uint8_t adc = 0;

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
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
  __HAL_TIM_SET_COUNTER(&htim8, 30000);
  HAL_TIM_Encoder_Start(&htim8, TIM_CHANNEL_ALL);
  pid_speed_init();
  pid_angle_init();
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  HAL_UART_Receive_IT(&huart1, (uint8_t *)&msg, 1);
  HAL_TIM_Base_Start_IT(&htim1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  HAL_UART_Receive_IT(&huart1, (uint8_t *)aRxBuffer, 1);
  HAL_UART_Transmit(&huart1, aTxStartMessages, sizeof(aTxStartMessages), 100);
  HAL_TIM_Base_Start_IT(&htim2);

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    //		HAL_UART_Transmit(&huart1, (uint8_t *)&msg, 3, 1000);
    //		HAL_Delay(500);
    //		HAL_GPIO_WritePin(LED_Pin1_GPIO_Port, LED_Pin1_Pin, GPIO_PIN_SET);
    //		HAL_Delay(500);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 500);
    adc_raw = HAL_ADC_GetValue(&hadc1);
    // adc = adc_raw / 0xFFFFFF;
    // HAL_UART_Transmit(&huart1, &adc, 1, 100);
    //		printf("Data: %d\n", adc_raw);
    //		printf("End of while");
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

  /** Initializes the CPU, AHB and APB busses clocks
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
  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
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

  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
