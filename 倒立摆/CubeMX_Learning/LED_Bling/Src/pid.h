#ifndef __pid_H_
#define __pid_H_
#include "main.h"
#include "pid.h"

#define TAR_ANGLE 1422

typedef struct{
		float k_pro;	//比例参数	
		float k_int;	//积分参数
		float k_dif;	//微分参数
		long max_int;	//积分限幅
		long i;	//积分
		int tar_value;	//目标值
		int true_value; //真实值
		int pre_error;	//上次误差
		int output_limit_min;
		int output_limit_max;
		int output;
} pid;

void pid_speed_init();
void pid_set_tarspeed(uint32_t tar);
void pid_speed_cal();
void pid_angle_cal();

void pid_angle_init();



#endif /* __pid_H_ */
