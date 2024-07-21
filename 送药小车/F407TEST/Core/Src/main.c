/* USER CODE BEGIN Header */
/*
 * @Author: yyl
 * @Date: 2024-03-31 23:38:49
 * @LastEditors: yyl
 * @FilePath: \MDK-ARMc:\Users\vanilla\Desktop\F407TEST\Core\Src\main.c
 * @LastEditTime: 2024-04-28 14:52:20
 * @Descripttion:
 * code bless us
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "interrupt.h"
#include "lcd.h"
#include "lcd_init.h"
#include "pic.h"
#include "vofa.h"
#include "stdio.h"
#include "pid.h"
#include "motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// 函数声明
void uart_rx(void);
void lcd_disp(void);
// 内部变量定义
char text[20];
// 外部变量引用
extern int speed_reality;
extern int speed_out;

extern char rxdatas[30];
extern uint8_t rxdata;
extern char rx_pointer;

extern MOTOR motor;
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
int fputc(int ch, FILE *f)

{

  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);

  return ch;
}
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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  // �?启定时器
  HAL_TIM_Base_Start_IT(&htim2); // 10ms 纯定时器 TIM2
  HAL_TIM_Base_Start_IT(&htim1); // 右轮编码�?        TIM1
  HAL_TIM_Base_Start_IT(&htim3); // 左轮编码�?        TIM3
  HAL_TIM_Base_Start_IT(&htim4); // pwm           TIM4
  // �?启pwm通道
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
  // LCD初始�?
  LCD_Init();
  LCD_Fill(0, 0, LCD_W, LCD_H, BLACK);
  // 蓝牙初始�?
  HAL_UART_Receive_IT(&huart2, &rxdata, 1);
  // pid初始�?
  PID_Init();
  Set_Pid(30, 80, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    vodka_JustFloat_send(&huart3);

    lcd_disp();
    uart_rx();
    motor_stop();
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
  RCC_OscInitStruct.PLL.PLLM = 25;
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
void lcd_disp()
{
  sprintf(text, "speed:%d   ", speed_reality);
  LCD_ShowString(0, 0, (uint8_t *)text, WHITE, BLACK, 16, 0);
  sprintf(text, "speed_out:%d   ", speed_out);
  LCD_ShowString(0, 16, (uint8_t *)text, WHITE, BLACK, 16, 0);
  sprintf(text, "stop:%d   ", motor.flag_stop);
  LCD_ShowString(0, 32, (uint8_t *)text, WHITE, BLACK, 16, 0);
  // sprintf(text, "flag_stop:%d   ", flag_stop);
  // LCD_ShowString(0, 0, (uint8_t *)text, WHITE, BLACK, 16, 0);
  // sprintf(text, "rxpointer:%d   ", rx_pointer);
  // LCD_ShowString(0, 16, (uint8_t *)text, WHITE, BLACK, 16, 0);
  // sprintf(text, "rxdata:%d   ", rxdatas[0]);
  // LCD_ShowString(0, 32, (uint8_t *)text, WHITE, BLACK, 16, 0);
  // LCD_ShowChinese(0, 0, "中景园电�?", RED, WHITE, 24, 0);
  // LCD_ShowString(24, 30, "LCD_W:", RED, WHITE, 16, 0);
  // LCD_ShowIntNum(72, 30, LCD_W, 3, RED, WHITE, 16);
  // LCD_ShowString(24, 50, "LCD_H:", RED, WHITE, 16, 0);
  // LCD_ShowIntNum(72, 50, LCD_H, 3, RED, WHITE, 16);
  // LCD_ShowFloatNum1(20, 80, t, 4, RED, WHITE, 16);
  // t += 0.11;
  // LCD_ShowPicture(0, 0, 128, 160, gImage_cat);
}
void uart_rx()
{
  if (rx_pointer == 3)
  {
    if (rxdatas[0] == 1 && rxdatas[1] == 2)
    {
      if (rxdatas[2] == 0)
      {
        motor.flag_stop = 1; // stop
      }
      if (rxdatas[2] == 1)
      {
        motor.flag_stop = 0; // run
      }
      rx_pointer = 0;
      memset(rxdatas, 0, 30);
    }
    else
    {
      rx_pointer = 0;
      memset(rxdatas, 0, 30);
    }
  }
  else
  {

    rx_pointer = 0;
    memset(rxdatas, 0, 30);
  }
}

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
