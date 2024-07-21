#ifndef __L294N_H
#define __L294N_H
 
 

#include "stm32f4xx_hal.h"
#include "tim.h"
#include "gpio.h"

void move_wasd(int target,int distance);
void Reset(void);
void Forward(void);
void Left(void);
void Left_light(void);
void Left_RElight(void);
void Right(void);
void Back(void);
void Walk(void);
void zhuanquan(void);
void Line_Detection(void);
void Restart(void);

void Red(void);
void DERed(void);
void Green(void);
void DEGreen(void);
void Yellow(void);
void DEYellow(void);

#endif
