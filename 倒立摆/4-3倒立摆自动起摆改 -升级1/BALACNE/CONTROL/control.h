#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************

**************************************************************************/
#define PI 3.14159265
#define ZHONGZHI 3740
#define FILTERING_TIMES  4

#define POSITION_MIDDLE 7925
#define ANGLE_ORIGIN 1020
#define ANGLE_MIDDLE 3100
extern	int Balance_Pwm,Velocity_Pwm;

extern float Bias;                       //倾角偏差
extern float Last_Bias,D_Bias;    //PID相关变量
extern int balance;                     //PWM返回值 


extern float Position_PWM,Last_Position,Position_Bias,Position_Differential;
extern float Position_Least;

int TIM1_UP_IRQHandler(void);
void Key(void);
int Balance(float angle);
int Position(int Encoder);
void Set_Pwm(int moto);
void Xianfu_Pwm(void);
int myabs(int a);
void Get_D_Angle_Balance(void);
int Mean_Filter(int sensor);

#endif
