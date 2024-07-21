#include "pid.h"
#include  "main.h"
extern  float set_Speed;
//����һ���ṹ�����ͱ���
  tPid pidMotor1Speed;//���1�ٶ�PID�ջ�����
//���ṹ�����ͱ�������ֵ
void PID_init()
{
	pidMotor1Speed.actual_val=0.0;
	pidMotor1Speed.target_val = set_Speed;//Ҫ��һ��volatile �Ͷ��尡�ı���,�����жϿ���
	pidMotor1Speed.err=0.0;
	pidMotor1Speed.err_last=0.0;
	pidMotor1Speed.err_sum=0.0;
	pidMotor1Speed.Kp=0.5;
	pidMotor1Speed.Ki=0.2;
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

