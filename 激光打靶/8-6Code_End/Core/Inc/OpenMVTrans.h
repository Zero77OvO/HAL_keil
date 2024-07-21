/*
 * @Author: WSY
 * @Date: 2023-08-03 13:27:16
 * @LastEditors: WSY
 * @LastEditTime: 2023-08-03 20:02:13
 * @FilePath: \MDK-ARMd:\Proj\mixue\82mixue\Core\Inc\OpenMVTrans.h
 * @Description: ...
 * 日落飞景秀长河,天地壮我行色
 * Copyright (c) 2023 by WSY, All Rights Reserved.
 */
#ifndef __OPENMVTRANS_H
#define __OPENMVTRANS_H

#include "main.h"

//使用串口2 PA2->TX PA3->RX
extern uint8_t openmvTx;
extern int reciveState;
extern uint8_t rectPosition[8];
extern uint8_t pointPosition[2];
extern uint8_t openmvTxState;
// 帧头 配合OPENMV修改
#define SIGNAL_1 0X2C
#define SIGNAL_2 0X12
// 帧尾
#define SIGANL_TAIL 0X5B

#define MSG_OK 0
#define MSG_ERR 1
#endif
