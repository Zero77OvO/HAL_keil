#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************

**************************************************************************/
#define PWMB   TIM3->CCR4    //倒立摆仅使用一路驱动 使用的B路
#define BIN2   PBout(12)     //倒立摆仅使用一路驱动 使用的B路
#define BIN1   PBout(13)     //倒立摆仅使用一路驱动 使用的B路

void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
#endif
