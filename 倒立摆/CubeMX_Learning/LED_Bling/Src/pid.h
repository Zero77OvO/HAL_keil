#ifndef __pid_H_
#define __pid_H_
#include "main.h"
#include "pid.h"

#define TAR_ANGLE 1422

typedef struct{
		float k_pro;	//��������	
		float k_int;	//���ֲ���
		float k_dif;	//΢�ֲ���
		long max_int;	//�����޷�
		long i;	//����
		int tar_value;	//Ŀ��ֵ
		int true_value; //��ʵֵ
		int pre_error;	//�ϴ����
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
