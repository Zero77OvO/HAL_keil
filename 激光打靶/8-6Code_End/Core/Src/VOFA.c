/*
 * @Author: WSY
 * @Date: 2023-06-10 10:25:08
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-05 13:56:26
 * @FilePath: \82mixue(1)(1)\Core\Src\VOFA.c
 * @Description: ...
 * 日落飞景秀长河,天地壮我行色
 * Copyright (c) 2023 by WSY, All Rights Reserved.
 */
#include "VOFA.h"
#include <stdlib.h>
#include <string.h>
#include "usart.h"
#include "OpenMVTrans.h"

/**
 * @description: 联合体，使用强制类型转换会使得存储空间的数据发生变化
 * @return {*}
 */
 
typedef union
{
    float fdata;
    uint32_t ldata;
} FloatLongType;

/**
 * @description: 这里进行换算，把传入的浮点类型变量传递到数组前四位
 * @param {float} f 需要传输的数据
 * @param {uint8_t} byte[] 传递数组
 * @param {int} Lcnt 当前所在发送位数,从0开始
 * @return {*}
 */
void VOFAFloat2Byte(float f, uint8_t byte[], int Lcnt)
{
    Lcnt = Lcnt * 4;
    FloatLongType f1;
    f1.fdata = f;
    byte[Lcnt] = (uint8_t)f1.ldata;
    byte[Lcnt + 1] = (uint8_t)(f1.ldata >> 8);
    byte[Lcnt + 2] = (uint8_t)(f1.ldata >> 16);
    byte[Lcnt + 3] = (uint8_t)(f1.ldata >> 24);
}
/**
 * @description: 帧尾添加
 * @param {uint8_t} byte 传入数组
 * @param {int} Lcnt 所在位数, = 传递数据个数
 * @return {*}
 */
void VOFATrail(uint8_t byte[], int Lcnt)
{
    Lcnt = Lcnt * 4;
    byte[Lcnt] = 0x00;
    byte[Lcnt + 1] = 0x00;
    byte[Lcnt + 2] = 0x80;
    byte[Lcnt + 3] = 0x7f;
}
/**
 * @description: VOFA数据发送 宏定义更改传递数组大小
 * @return {*}
 */
#define USERDATANUM 13              // 数据位数
#define DATANUM USERDATANUM * 4 + 4 // 用户无需更改
uint8_t transData[DATANUM] = {0};
#include "OpenMVTrans.h"
#include "tim.h"
extern int step;
void VOFATransmit()
{
    // 主函数发送ADC采集数据
    //---------------用户数据--------------
    VOFAFloat2Byte(pointPosition[0], transData, 0);
    VOFAFloat2Byte(pointPosition[1], transData, 1);
    VOFAFloat2Byte(rectPosition[0], transData, 2);
    VOFAFloat2Byte(rectPosition[1], transData, 3);
    VOFAFloat2Byte(rectPosition[2], transData, 4);
    VOFAFloat2Byte(rectPosition[3], transData, 5);
    VOFAFloat2Byte(rectPosition[4], transData, 6);
    VOFAFloat2Byte(rectPosition[5], transData, 7);
    VOFAFloat2Byte(rectPosition[6], transData, 8);
    VOFAFloat2Byte(rectPosition[7], transData, 9);
    VOFAFloat2Byte(step, transData, 10);
    VOFAFloat2Byte(lrControl.Out, transData, 11);
    VOFAFloat2Byte(upControl.Out, transData, 12);
	
    //--------------- 结束 ----------------
    VOFATrail(transData, USERDATANUM);
    HAL_UART_Transmit_DMA(&huart3, transData, DATANUM);
}
