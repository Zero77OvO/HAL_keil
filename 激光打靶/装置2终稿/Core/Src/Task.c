/*
 * @Author: WSY
 * @Date: 2023-08-02 17:35:56
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-07 15:22:15
 * @FilePath: \8-7-10-52\Core\Src\Task.c
 * @Description: ...
 * 日落飞景秀长河,天地壮我行色
 * Copyright (c) 2023 by WSY, All Rights Reserved.
 */
#include "Task.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "OpenMVTrans.h"

void TaskOne(void)
{
    // KEY1 按键按下触发复位
		if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 0)//key1
		{
			// 定时器使能
			HAL_TIM_Base_Start_IT(&htim5);
		}
		if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0)//key1
		{
			// 定时器使能
			HAL_TIM_Base_Start_IT(&htim5);
		}
}

// PWM定义 找准正方形四个点 注意舵机放置位置
void TaskTwo(void)
{
    // KEY0 按键按下触发运动
    // 左上 右上 右下 左下 左上 归中
    
        while (ServeTaskTwo(LEFTPWM, UPPWM) == TASK_ERR)
            HAL_Delay(10);
        while (ServeTaskTwo(RIGHTPWM, UPPWM) == TASK_ERR)
            HAL_Delay(10);
        while (ServeTaskTwo(RIGHTPWM, DOWNPWM) == TASK_ERR)
            HAL_Delay(10);
        while (ServeTaskTwo(LEFTPWM, DOWNPWM) == TASK_ERR)
            HAL_Delay(10);
        while (ServeTaskTwo(LEFTPWM, UPPWM) == TASK_ERR)
            HAL_Delay(10);
        while (ServeTaskTwo(LRMIDPWM, UDMIDPWM) == TASK_ERR)
            HAL_Delay(10);
    
}
/**
 * @description: 任务二服务函数，仅限任务二调度
 * @param {uint32_t} target1 目标左右位置
 * @param {uint32_t} target2 目标上下位置
 * @return {TASK_OK | TASK_ERR } OK代表运行结束 ERR代表运行中
 */
int ServeTaskTwo(uint32_t target1, uint32_t target2)
{
    static volatile uint32_t lastPWM[2] = {LRMIDPWM, UDMIDPWM};
    // 还没有执行到目标位置
    if (target1 != lastPWM[0] || target2 != lastPWM[1])
    {
        if (target1 > lastPWM[0])
            lastPWM[0]++;
        else if (target1 < lastPWM[0])
            lastPWM[0]--;
        if (target2 > lastPWM[1])
            lastPWM[1]++;
        else if (target2 < lastPWM[1])
            lastPWM[1]--;
        TIM3->CCR1 = lastPWM[0];
        TIM3->CCR2 = lastPWM[1];
        return TASK_ERR;
    }
    else
    {
        return TASK_OK;
    }
}
