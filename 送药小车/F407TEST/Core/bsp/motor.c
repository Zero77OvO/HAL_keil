/*
 * @Author: yyl
 * @Date: 2024-04-27 15:07:58
 * @LastEditors: yyl
 * @FilePath: \MDK-ARMc:\Users\vanilla\Desktop\F407TEST\Core\bsp\motor.c
 * @LastEditTime: 2024-05-08 20:26:13
 * @Descripttion:
 * code bless us
 */

#include "motor.h"
#include "tim.h"

MOTOR motor;

int motor_speed(void)
{
    motor.speed_L = __HAL_TIM_GET_COUNTER(&htim3);
    motor.speed_R = __HAL_TIM_GET_COUNTER(&htim1);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    // 倒转
    if (motor.speed_L > 60000)
        motor.speed_L = 65535 - motor.speed_L;
    if (motor.speed_R > 60000)
        motor.speed_R = 65535 - motor.speed_R;
    motor.speed = (motor.speed_L + motor.speed_R) / 2;

    return motor.speed;
}

void motor_set(int pwm)
{
    // 限幅
    //    if (pwm > 900)
    //        pwm = 900;
    // 输出
    if (motor.flag_stop == 0)
    {
        if (pwm > 0)
        {
            __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm);
            __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
        }
        else
        {
            __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, -pwm);
            __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, -pwm);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
        }
    }
}

void motor_stop()
{
    motor.flag_stop = 1;
    // stop
    if (motor.flag_stop == 1)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}