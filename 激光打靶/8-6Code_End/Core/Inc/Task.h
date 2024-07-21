/*
 * @Author: WSY
 * @Date: 2023-08-02 17:36:08
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-06 16:26:28
 * @FilePath: \8_5Code\Core\Inc\Task.h
 * @Description: ...
 * 日落飞景秀长河,天地壮我行色
 * Copyright (c) 2023 by WSY, All Rights Reserved.
 */
#ifndef __TASK_H
#define __TASK_H

#include "main.h"
// 注意接线
// PA6为 TIM3 CH1 接上下舵机
// PA7为 TM3 CH2 接左右电机
// 宏定义 UD代表上下舵机 LR代表左右舵机
////////////////////////////////
void TaskOne(void);
#define UDMIDPWM 1685
#define LRMIDPWM 1522

void TaskOne_s(void);
#define UDMIDPWM_s 1699
#define LRMIDPWM_S 1530

////////////////////////////////

// 往左 增大 往右 减小
// 往上 增大 往下 减小
void TaskTwo(void);
#define LEFTPWM 1674
#define RIGHTPWM 1372
#define UPPWM 1823
#define DOWNPWM 1549

void TaskTwo_s(void);
int ServeTaskTwo_s(uint32_t target1, uint32_t target2);
#define LEFTPWM_s 1677
#define RIGHTPWM_s 1377
#define UPPWM_s 1830
#define DOWNPWM_s 1558

///////////////////////////////

void TaskThree(void);
#define LEFTPWM_3 1625
#define RIGHTPWM_3 1556
#define UPPWM_3 1724
#define DOWNPWM_3 1534

////////////////////////////////

void TaskFourInit(void);
void TaskFour(void);
#define TASK_OK 1
#define TASK_ERR 0
int ServeTaskTwo(uint32_t target1, uint32_t target2);
int ServeTaskThree(uint32_t target1, uint32_t target2);
#endif
