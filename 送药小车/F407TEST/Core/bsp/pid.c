/*
 * @Author: yyl
 * @Date: 2024-04-26 18:56:16
 * @LastEditors: yyl
 * @FilePath: \MDK-ARMc:\Users\vanilla\Desktop\F407TEST\Core\bsp\pid.c
 * @LastEditTime: 2024-04-28 11:03:16
 * @Descripttion:   
 * code bless us
 */

#include "pid.h"

/*		关于增量式调参
 *    增量式I=位置式P
 *    增量式P=位置式D
 */

float Pout, Iout, Dout;

/********************PID参数初始化********************/
PID_TypeDef speed_PID; // PID参数结构体
void PID_Init(void)
{
    speed_PID.LastError = 0;  // Error[-1]
    speed_PID.PrevError = 0;  // Error[-2]
    speed_PID.Proportion = 0; // 比例常数 Proportional Const
    speed_PID.Integral = 0;   // 积分常数  Integral Const
    speed_PID.Derivative = 0; // 微分常数 Derivative Const
}

/********************PID算法实现********************/
/**
 * 输入参数：目标量   实际量
 * 返 回 值： 增量
 */
int32_t PID_IO(float Target, float Actual)
{

    float iError, iIncpid;    // 定义当前差值和要增加的值
    iError = Target - Actual; // 偏差

    Pout = speed_PID.Proportion * (iError - speed_PID.LastError);
    Iout = speed_PID.Integral * iError;
    Dout = speed_PID.Derivative * (iError - 2 * speed_PID.LastError + speed_PID.PrevError);

    iIncpid = Pout + Iout + Dout;

    speed_PID.PrevError = speed_PID.LastError; // 存储误差，用于下次计算
    speed_PID.LastError = iError;

    //			if(iIncpid>500)
    //			{
    //			iIncpid=500;
    //			}

    //			if(iIncpid<-500)  //可以不需要这句
    //			{
    //			iIncpid=-500;
    //			}

    return (iIncpid); // 返回增量值
}

void Set_Pid(float Kp, float Ki, float Kd)
{
    speed_PID.Proportion = Kp; // 比例常数 Proportional Const
    speed_PID.Integral = Ki;   // 积分常数  Integral Const
    speed_PID.Derivative = Kd; // 微分常数 Derivative Const
}
