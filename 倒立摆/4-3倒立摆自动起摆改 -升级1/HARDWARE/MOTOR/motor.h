#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************

**************************************************************************/
#define PWMB   TIM3->CCR4    //�����ڽ�ʹ��һ·���� ʹ�õ�B·
#define BIN2   PBout(12)     //�����ڽ�ʹ��һ·���� ʹ�õ�B·
#define BIN1   PBout(13)     //�����ڽ�ʹ��һ·���� ʹ�õ�B·

void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
#endif
