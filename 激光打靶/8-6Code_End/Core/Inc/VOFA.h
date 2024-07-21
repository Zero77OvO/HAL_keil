/*
 * @Author: 不会是Wsy吧
 * @Date: 2023-07-24 17:53:28
 * @LastEditTime: 2023-08-03 20:28:42
 * @FilePath: \MDK-ARMd:\Proj\mixue\82mixue\Core\Inc\VOFA.h
 * @Description:
 * 十年生死两茫茫，写程序，到天亮。千行代码，Bug何处藏。||QQ：123010257
 */
#ifndef __VOFA_H
#define __VOFA_H

#include "main.h"

void VOFAFloat2Byte(float f, uint8_t byte[], int Lcnt);
void VOFATransmit(void);
void VOFATrail(uint8_t byte[], int Lcnt);

#endif

