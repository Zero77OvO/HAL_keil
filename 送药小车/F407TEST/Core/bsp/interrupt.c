/*
 * @Author: yyl
 * @Date: 2024-04-20 13:09:54
 * @LastEditors: yyl
 * @FilePath: \MDK-ARMc:\Users\vanilla\Desktop\F407TEST\Core\bsp\interrupt.c
 * @LastEditTime: 2024-05-08 20:23:00
 * @Descripttion:   
 * code bless us
 */

// include
#include "interrupt.h"
#include "tim.h"
#include "usart.h"
#include "pid.h"
#include "motor.h"
// 内部变量定义
int speed_target = 35;
int t = 0;
int time_100ms = 0;
int speed_reality = 0, speed_out = 0;
// 外部变量

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /*10ms定时器*/
    if (htim->Instance == TIM2)
    {
        // 10ms
        speed_reality = motor_speed();
        speed_out = PID_IO(speed_target, speed_reality);
       // motor_set(speed_out);

        // 1s指示灯
        // if (++t == 100)
        // {
        //     HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        //     t = 0;
        // }
    }
}

char rxdatas[30] = {'0', '0', '0'};
uint8_t rxdata;
unsigned char rx_pointer;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    rxdatas[rx_pointer++] = rxdata - 48;
    HAL_UART_Receive_IT(&huart2, &rxdata, 1);
}
