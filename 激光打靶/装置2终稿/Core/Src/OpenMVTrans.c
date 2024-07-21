/*
 * @Author: WSY
 * @Date: 2023-08-03 13:27:03
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-07 11:55:59
 * @FilePath: \8-7-10-52\Core\Src\OpenMVTrans.c
 * @Description: ...
 * 日落飞景秀长河,天地壮我行色
 * Copyright (c) 2023 by WSY, All Rights Reserved.
 */
#include "OpenMVTrans.h"
#include "usart.h"
#include "Task.h"
uint8_t openmvTx = '0';
uint8_t pointPosition[2];
int reciveState = MSG_ERR;
/**
 * @description: 串口接收中断函数
 * @param {UART_HandleTypeDef} *huart
 * @return {*}
 */
int beepEnable = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static int step = 0;
    static int i = 0;
    reciveState = MSG_ERR;
    // 进行帧头判断 如果帧头判断正常才进行数据接收
    if (openmvTx == SIGNAL_1 && step == 0)
        step++;
    else if (openmvTx == SIGNAL_2 && step == 1)
    {
        step++;
        i = 0;
    }
    // 帧头判断成功进入
    else if (step == 2)
    {
        // 如果不为帧尾进行数据处理
        if (openmvTx != SIGANL_TAIL)
        {
            // 小于2位时正常处理
            if (i < 2)
                pointPosition[i++] = openmvTx;
            // 大于2位说明数据异常 退出接收
            else if (i >= 2)
                step = 0;
        }
        // 帧尾 数据处理完成
        else
        {
            step = 0;
            // 如果仅为八位则传输正常 少位数则数据异常
            if (i == 2)
						{
							reciveState = MSG_OK;
							beepEnable = 0;
						}
						else
						{
							pointPosition[0] = 109;
							pointPosition[1] = 86;
							beepEnable = 1;
						}
        }
    }
    else
        step = 0;
    if (reciveState == MSG_ERR)
        HAL_UART_Receive_IT(&huart2, &openmvTx, 1);
}
