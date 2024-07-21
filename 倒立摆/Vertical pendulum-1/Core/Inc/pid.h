#ifndef __PID_H
#define __PID_H

//����һ���ṹ������
typedef struct 
{
	float target_val;//Ŀ��ֵ
	float actual_val;//ʵ��ֵ
	float err;//��ǰƫ��
	float err_last;//�ϴ�ƫ��
	float err_sum;//����ۼ�ֵ
	float Kp,Ki,Kd;//���������֣�΢��ϵ��
	
} tPid;
 
//��������
float P_realize(tPid * pid,float actual_val);
void PID_init(void);
float PI_realize(tPid * pid,float actual_val);
float PID_realize(tPid * pid,float actual_val);



float PID_x(float target_value_x, float temp_val_x, float kp_x, float ki_x, float kd_x);
float PID_y(float target_value_y, float temp_val_y, float kp_y, float ki_y, float kd_y);

#endif
