#include "pid.h"
#include  "main.h"
 float set_Speed;
extern  float t;
//����һ���ṹ�����ͱ���
 tPid pidMotor1Speed;//���1�ٶ�PID�ջ�����
//���ṹ�����ͱ�������ֵ
void PID_init()
{
	pidMotor1Speed.actual_val=t;
	pidMotor1Speed.target_val = set_Speed;//Ҫ��һ��volatile �Ͷ��尡�ı���,�����жϿ���
	pidMotor1Speed.err=0.0;
	pidMotor1Speed.err_last=0.0;
	pidMotor1Speed.err_sum=0.0;
	pidMotor1Speed.Kp=1.0;
	pidMotor1Speed.Ki=10.5;
	pidMotor1Speed.Kd=0.05;
	
}
float PID_realize(tPid * pid,float actual_val)
{
	pid->actual_val = actual_val;//������ʵֵ
	pid->err = pid->target_val - pid->actual_val;////��ǰ���=Ŀ��ֵ-��ʵֵ
	pid->err_sum += pid->err;//����ۼ�ֵ = ��ǰ����ۼƺ�
	//ʹ��PID���� ��� = Kp*��ǰ���  +  Ki*����ۼ�ֵ + Kd*(��ǰ���-�ϴ����)
	pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
	//�����ϴ����: �����ֵ���ϴ����
	pid->err_last = pid->err;
	return pid->actual_val;
}




float err_x = 0.0;											//x���
float err_y = 0.0;											//y���
float integral_x = 0.0;									//x����
float integral_y = 0.0;									//y����
float err_last_x = 0.0;									//x��һ���ֵ
float err_last_y = 0.0;									//y��һ���ֵ
float actual_value = 0.0;								//����ֵ


/*************************************
*��  ��  ��	��PID_x()
*��������	����X��ĸ�����������PID����
*��	��	��Ŀ��ֵ��ʵ��ֵ ,kp_x ,ki_x ,kd_x
*��	��	��PID����������ֵ
*************************************/
float PID_x(float target_value, float temp_val, float kp_x, float ki_x, float kd_x)
{
	/*λ��ʽPID*/
	/*��� = Ŀ��ֵ - �����ʵ��ֵ*/
	err_x = target_value - temp_val;
	
	/*����ۼ�*/
	integral_x += err_x;
	
	
	/*�����޷�*/
	if(integral_x > 1000)
		integral_x = 1000;
	else if(integral_x < -1000)
		integral_x = -1000;
	
	/*PID�㷨ʵ��*/
	actual_value = kp_x*err_x + ki_x*integral_x + kd_x*(err_x - err_last_x);
	
	/*��¼��һ���ֵ*/
	err_last_x = err_x;
	
	
	/*���ص�ǰʵ��ֵ*/
	return actual_value;
}

/*************************************
*��  ��  ��	��PID_y()
*��������	����Y��ĸ�����������PID����
*��	��	��Ŀ��ֵ��ʵ��ֵ ,kp_y ,ki_y ,kd_y
*��	��	��PID����������ֵ
*************************************/
float PID_y(float target_value, float temp_val, float kp_y, float ki_y, float kd_y)
{
	/*λ��ʽPID*/
	/*��� = Ŀ��ֵ - �����ʵ��ֵ*/
	err_y = target_value - temp_val;
	
	/*����ۼ�*/
	integral_y += err_y;
	
	
	/*�����޷�*/
	if(integral_y > 1000)
		integral_y = 1000;
	else if(integral_y < -1000)
		integral_y = -1000;
	
	/*PID�㷨ʵ��*/
	actual_value = kp_y*err_y + ki_y*integral_y + kd_y*(err_y - err_last_y);
	
	/*��¼��һ���ֵ*/
	err_last_y = err_y;
	
	
	/*���ص�ǰʵ��ֵ*/
	return actual_value;
}
