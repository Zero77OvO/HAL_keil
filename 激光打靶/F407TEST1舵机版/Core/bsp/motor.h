#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

typedef struct
{
    int flag_stop;
    int speed_L;
    int speed_R;
    int speed;
    /* data */
}MOTOR;

void motor_run(void);
void motor_set(int pwm);
int motor_speed(void);

#endif
