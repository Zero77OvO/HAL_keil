/*
 * @Author: WSY
 * @Date: 2023-08-02 17:35:56
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-06 16:28:08
 * @FilePath: \8_5Code\Core\Src\Task.c
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

    TIM3->CCR1 = LRMIDPWM;
    TIM3->CCR2 = UDMIDPWM;
    HAL_Delay(2000);
}

void TaskOne_s(void)
{
    // KEY1 按键按下触发复位

    TIM3->CCR1 = LRMIDPWM_S;
    TIM3->CCR2 = UDMIDPWM_s;
    HAL_Delay(2000);
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
/**
 * @description: 基础任务三 建议使用TaskTwo方法给他闭死
 * @return {*}
// */

// 任务2备用
////////////////////////////////////////////////////////////////////////////////////////////////
void TaskTwo_s(void)
{
    // 左上 右上 右下 左下 左上 归中
    while (ServeTaskTwo_s(LEFTPWM_s, UPPWM_s) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskTwo_s(RIGHTPWM_s, UPPWM_s) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskTwo_s(RIGHTPWM_s, DOWNPWM_s) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskTwo_s(LEFTPWM_s, DOWNPWM_s) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskTwo_s(LEFTPWM_s, UPPWM_s) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskTwo_s(LRMIDPWM, UDMIDPWM) == TASK_ERR)
        HAL_Delay(10);
}
/**
 * @description: 任务二服务函数，仅限任务二调度
 * @param {uint32_t} target1 目标左右位置
 * @param {uint32_t} target2 目标上下位置
 * @return {TASK_OK | TASK_ERR } OK代表运行结束 ERR代表运行中
 */
int ServeTaskTwo_s(uint32_t target1, uint32_t target2)
{
    static volatile uint32_t lastPWM_2[2] = {LRMIDPWM, UDMIDPWM};
    // 还没有执行到目标位置
    if (target1 != lastPWM_2[0] || target2 != lastPWM_2[1])
    {
        if (target1 > lastPWM_2[0])
            lastPWM_2[0]++;
        else if (target1 < lastPWM_2[0])
            lastPWM_2[0]--;
        if (target2 > lastPWM_2[1])
            lastPWM_2[1]++;
        else if (target2 < lastPWM_2[1])
            lastPWM_2[1]--;
        TIM3->CCR1 = lastPWM_2[0];
        TIM3->CCR2 = lastPWM_2[1];
        return TASK_ERR;
    }
    else
    {
        return TASK_OK;
    }
}
/**
 * @description: 基础任务三 建议使用TaskTwo方法给他闭死
 * @return {*}
// */
////////////////////////////////////////////////////////////////////////////////////////////////

void TaskThree(void)
{
    // KEY0 按键按下触发运动

    // 左上 右上 右下 左下 左上 归中
    while (ServeTaskThree(LEFTPWM_3, UPPWM_3) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskThree(RIGHTPWM_3, UPPWM_3) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskThree(RIGHTPWM_3, DOWNPWM_3) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskThree(LEFTPWM_3, DOWNPWM_3) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskThree(LEFTPWM_3, UPPWM_3) == TASK_ERR)
        HAL_Delay(10);
    while (ServeTaskThree(LRMIDPWM, UDMIDPWM) == TASK_ERR)
        HAL_Delay(10);
}

///**
// * @description: 任务二服务函数，仅限任务二调度
// * @param {uint32_t} target1 目标左右位置
// * @param {uint32_t} target2 目标上下位置
// * @return {TASK_OK | TASK_ERR } OK代表运行结束 ERR代表运行中
// */
int ServeTaskThree(uint32_t target1, uint32_t target2)
{
    static volatile uint32_t lastPWM_3[2] = {LRMIDPWM, UDMIDPWM};
    // 还没有执行到目标位置
    if (target1 != lastPWM_3[0] || target2 != lastPWM_3[1])
    {
        if (target1 > lastPWM_3[0])
            lastPWM_3[0]++;
        else if (target1 < lastPWM_3[0])
            lastPWM_3[0]--;
        if (target2 > lastPWM_3[1])
            lastPWM_3[1]++;
        else if (target2 < lastPWM_3[1])
            lastPWM_3[1]--;
        TIM3->CCR1 = lastPWM_3[0];
        TIM3->CCR2 = lastPWM_3[1];
        return TASK_ERR;
    }
    else
    {
        return TASK_OK;
    }
}

int maxLeft = 0;
void TaskFour(void)
{
    static int start = 0;
    if (start == 0)
    {
        start = 1;
        openmvTxState = 1;
        TaskFourInit();
        TIM3->CCR1 = LRMIDPWM;
        TIM3->CCR2 = UDMIDPWM;
        HAL_UART_Receive_IT(&huart2, &openmvTx, 1);
        HAL_Delay(500);
        HAL_TIM_Base_Start_IT(&htim5);
    }
    if (reciveState == MSG_OK && openmvTxState == 1)
    {
        HAL_UART_Receive_IT(&huart2, &openmvTx, 1);
    }
}

#define COMPENSATE 1
void TaskFourInit(void)
{
    // 接收成功 进行数据解算
    // 数据方向是逆时针
    // 进入第二步采集 获得红点坐标
    // 在这里对PID参数进行初始化
    lrControl.P = 0.04;
    lrControl.I = 0.02;
    lrControl.D = 0.00;
    lrControl.Out = LRMIDPWM;
    upControl.P = 0.04;
    upControl.I = 0.02;
    upControl.D = 0.00;
    upControl.Out = UDMIDPWM;

    // 调整坐标往外扩张
    int avgx = 0, avgy = 0;
    avgx = (rectPosition[0] + rectPosition[2] + rectPosition[4] + rectPosition[6]) / 4.0;
    avgy = (rectPosition[1] + rectPosition[3] + rectPosition[5] + rectPosition[7]) / 4.0;

    for (int i = 0; i < 4; i++)
    {
        if (rectPosition[i * 2] > avgx + 5)
            rectPosition[i * 2] = rectPosition[i * 2] + COMPENSATE;
        else if (rectPosition[i * 2] < avgx - 5)
            rectPosition[i * 2] = rectPosition[i * 2] - COMPENSATE;
    }
    for (int i = 0; i < 4; i++)
    {
        if (rectPosition[i * 2 + 1] > avgy + 5)
            rectPosition[i * 2 + 1] = rectPosition[i * 2 + 1] + COMPENSATE;
        else if (rectPosition[i * 2 + 1] < avgy - 5)
            rectPosition[i * 2 + 1] = rectPosition[i * 2 + 1] - COMPENSATE;
    }
}
