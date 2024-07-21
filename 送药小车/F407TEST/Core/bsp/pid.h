/*
 * @Descripttion: ????????????????????????
 * @Author: yyl
 * @Date: 2024-04-26 18:56:22
 * @LastEditors: yyl
 * @FilePath: \MDK-ARMc:\Users\vanilla\Desktop\F407TEST\Core\bsp\pid.h
 * @LastEditTime: 2024-04-26 19:12:45
 */
#ifndef __PID_H
#define __PID_H
#include "main.h"
/*????????*/
void PID_Init(void);
int32_t PID_IO(float Target, float Actual);
void Set_Pid(float Kp, float Ki, float Kd);
/*???ŽG??***/
typedef struct
{
    __IO float Proportion; // ???????? Proportional Const
    __IO float Integral;   // ??????? Integral Const
    __IO float Derivative; // ?????? Derivative Const
    __IO int LastError;    // Error[-1]
    __IO int PrevError;    // Error[-2]
} PID_TypeDef;

#endif
