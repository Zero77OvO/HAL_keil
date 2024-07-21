/*
 * @Author: WSY
 * @Date: 2023-08-02 17:36:08
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-07 15:22:44
 * @FilePath: \8-7-10-52\Core\Inc\Task.h
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
#define UDMIDPWM 1500
#define LRMIDPWM 1422

////////////////////////////////

// 往左 增大 往右 减小
// 往上 增大 往下 减小
void TaskTwo(void);
#define LEFTPWM 1800
#define RIGHTPWM 1200
#define UPPWM 1900
#define DOWNPWM 1400

////////////////////////////////
#define TASK_OK 1
#define TASK_ERR 0
int ServeTaskTwo(uint32_t target1, uint32_t target2);

#endif
