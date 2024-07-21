#include "interrupt.h"
#include "usart.h"
#include "adcc.h"
#include "adc.h"
#include "tim.h"
#include "pid.h"


//float Kp_v =38.8;
//float Kd_v =0.86 ;

//float Kp_x = 0.018;
//float Kd_x = 0.007;

float Kp_v =24.8;
float Kd_v =8.86 ;

float Kp_x = 0.025;
float Kd_x = 0.000

//float Kp_v =408*0.3;
//float Kd_v =324*3.1 ;

//float Kp_x = 0.050;
//float Kd_x = 0.005;

//float Kp_v =408*1.05*1.2;
;
//float Kd_v =324*0.73*0.6;

//float Kp_v =250;
//float Kd_v =0 ;
//float Kp_v =0;
//float Kd_v =0 ;


//float Kp_v =200;
//float Kd_v =0 ;


// float VKp =26;
// float VKi =26/200;


float Ki_v;
float err_v = 0;
float last_err_v = 0;
float err_sum_v = 0;
float err_difference_v;


extern int location;


// float VKp =26;
// float VKi =26/200;
float err_x = 0;
float last_err_x = 0;
float err_sum_x = 0;
float err_difference_x;

// extern short gyrox, gyroy, gyroz;
// float filt_velocity = 0, velocity_sum = 0, last_filt_velocity = 0;
// extern float Trans[3];
float x_out = 0;
float v_out = 0;


extern int timer_sign;
extern int c,b;
extern int  raw_filter;
extern int  num_counter;
extern int true_speed;

int target_location=30000;
int target_angle=3456;


int vertical_PID_value(float measure, float calcu)
{
    err_v = measure - calcu;
    err_sum_v += err_v;
    // xianfu	
	  if(err_sum_v > 1000)
		err_sum_v = 1000;
	  else if(err_sum_v < -1000)
		err_sum_v = -1000;
    err_difference_v = err_v - last_err_v;
    v_out = Kp_v * err_v + Kd_v * (err_v - last_err_v)+ Ki_v*err_sum_v;
    last_err_v = err_v;
    return v_out;
}


int location_PID_value(float measure, float calcu)
{
    err_x = measure - calcu;
    err_sum_x += err_x;
    // xianfu
    err_difference_x = err_x - last_err_x;
    x_out = Kp_x * err_x + Kd_x * (err_x - last_err_x);
    last_err_x = err_x;
	if(x_out>500){x_out=500;}
	if(x_out<-500){x_out=-500;}
	//HAL_Delay(10);
    return x_out;
}



static float pwm;
//位置环和角度环结合控制
float banlance_pid()
{   
	
//	if(timer_sign)
//		{
//			//每45ms进行一次位置控制
////			if(c%3==0) 	pwm=0.8*vertical_PID_value((raw_filter), target_angle)+ location_PID_value(true_speed, 30000);;
////			if(c%3!=0)  pwm=0.8*vertical_PID_value((raw_filter), target_angle);
//			
//			if(b%3==0) 	location= location_PID_value((num_counter), target_location);
//			if(b%3!=0)  pwm=0.8*vertical_PID_value((raw_filter-location), target_angle);
//			timer_sign=!timer_sign;
//		}
//	return pwm;
		
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
