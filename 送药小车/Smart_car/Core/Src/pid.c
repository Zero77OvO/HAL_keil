#include "pid.h"
#include  "main.h"
 float set_Speed;
extern  float t;
//定义一个结构体类型变量
 tPid pidMotor1Speed;//电机1速度PID闭环参数
//给结构体类型变量赋初值
void PID_init()
{
	pidMotor1Speed.actual_val=t;
	pidMotor1Speed.target_val = set_Speed;//要用一个volatile 型定义啊的变量,用于中断控制
	pidMotor1Speed.err=0.0;
	pidMotor1Speed.err_last=0.0;
	pidMotor1Speed.err_sum=0.0;
	pidMotor1Speed.Kp=1.0;
	pidMotor1Speed.Ki=10.5;
	pidMotor1Speed.Kd=0.05;
	
}
float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//传递真实值
	pid->err = pid->target_val - pid->actual_val;////当前误差=目标值-真实值
	pid->err_sum += pid->err;//误差累计值 = 当前误差累计和
	//使用PID控制 输出 = Kp*当前误差  +  Ki*误差累计值 + Kd*(当前误差-上次误差)
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
	//保存上次误差: 这次误差赋值给上次误差
	pid->err_last = pid->err;
	return pid->actual_val;
}




float err_x = 0.0;											//x误差
float err_y = 0.0;											//y误差
float integral_x = 0.0;									//x积分
float integral_y = 0.0;									//y积分
float err_last_x = 0.0;									//x上一误差值
float err_last_y = 0.0;									//y上一误差值
float actual_value = 0.0;								//驱动值


/*************************************
*函  数  名	：PID_x()
*函数功能	：将X轴的各个参数进行PID运算
*输	入	：目标值，实际值 ,kp_x ,ki_x ,kd_x
*输	出	：PID运算后的驱动值
*************************************/
float PID_x(float target_value, float temp_val, float kp_x, float ki_x, float kd_x)
{
	/*位置式PID*/
	/*误差 = 目标值 - 输入的实际值*/
	err_x = target_value - temp_val;
	
	/*误差累计*/
	integral_x += err_x;
	
	
	/*积分限幅*/
	if(integral_x > 1000)
		integral_x = 1000;
	else if(integral_x < -1000)
		integral_x = -1000;
	
	/*PID算法实现*/
	actual_value = kp_x*err_x + ki_x*integral_x + kd_x*(err_x - err_last_x);
	
	/*记录上一误差值*/
	err_last_x = err_x;
	
	
	/*返回当前实际值*/
	return actual_value;
}

/*************************************
*函  数  名	：PID_y()
*函数功能	：将Y轴的各个参数进行PID运算
*输	入	：目标值，实际值 ,kp_y ,ki_y ,kd_y
*输	出	：PID运算后的驱动值
*************************************/
float PID_y(float target_value, float temp_val, float kp_y, float ki_y, float kd_y)
{
	/*位置式PID*/
	/*误差 = 目标值 - 输入的实际值*/
	err_y = target_value - temp_val;
	
	/*误差累计*/
	integral_y += err_y;
	
	
	/*积分限幅*/
	if(integral_y > 1000)
		integral_y = 1000;
	else if(integral_y < -1000)
		integral_y = -1000;
	
	/*PID算法实现*/
	actual_value = kp_y*err_y + ki_y*integral_y + kd_y*(err_y - err_last_y);
	
	/*记录上一误差值*/
	err_last_y = err_y;
	
	
	/*返回当前实际值*/
	return actual_value;
}
