#include "pid.h"
#include "interrupt.h"

float Kp = -3000;
float Kd =-0 ;
// float VKp =26;
// float VKi =26/200;
float err = 0;
float last_err = 0;
float err_sum = 0;
float err_difference;
// extern short gyrox, gyroy, gyroz;
// float filt_velocity = 0, velocity_sum = 0, last_filt_velocity = 0;
// extern float Trans[3];
float out = 0;

int vertical_PID_value(float measure, float calcu)
{
    err = measure - calcu;
    err_sum += err;
    // xianfu
    err_difference = err - last_err;
    out = Kp * err + Kd * (err - last_err);
    last_err = err;
    return out;
}

// int velocity_PID_value(int velocity)
//{

//    float a = 0.3;
//    filt_velocity = a * velocity + (1 - a) * last_filt_velocity;
//    velocity_sum += filt_velocity;
//    if (velocity_sum > 2000)
//        velocity_sum =2000;
//    if (velocity_sum < -2000)
//        velocity_sum = -2000;
//		if(Trans[0]>20||Trans[0]<-20)velocity_sum=0;
//    last_filt_velocity = filt_velocity;
//    return VKp * filt_velocity + VKi * velocity_sum;
//}
