#ifndef __L294N_H
#define __L294N_H
 
 
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"
#include "stdbool.h" 



//���1�ı�������������
#define MOTO1_ENCODER1_PORT GPIOA
#define MOTO1_ENCODER1_PIN  GPIO_PIN_0
#define MOTO1_ENCODER2_PORT GPIOA
#define MOTO1_ENCODER2_PIN  GPIO_PIN_1

//��ʱ����
#define PWM_TIM     htim1
#define ENCODER_TIM htim2
#define GAP_TIM     htim3

#define MOTOR_SPEED_RERATIO 45u    //������ٱ�
#define PULSE_PRE_ROUND 11 //һȦ���ٸ�����
#define RADIUS_OF_TYRE 34 //��̥�뾶����λ����
#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14
#define RELOADVALUE __HAL_TIM_GetAutoreload(&ENCODER_TIM)    //��ȡ�Զ�װ��ֵ,������Ϊ20000
#define COUNTERNUM __HAL_TIM_GetCounter(&ENCODER_TIM)        //��ȡ��������ʱ���еļ���ֵ

typedef struct _Motor
{
    int32_t lastCount;   //��һ�μ���ֵ
    int32_t totalCount;  //�ܼ���ֵ
    int16_t overflowNum; //�������
    float speed;         //���ת��
    uint8_t direct;      //��ת����
}Motor;


void stop(void);
void start(void);
void restart(void);
void delay_ms_tim(uint16_t nms);
void user_delaynus_tim(uint32_t nus);
void ms_Delay(uint16_t t_ms);
void Motor_Init(void); 
void R(void);
void L(void);
void Rstr(void);
void Lstr(void);
bool Dir(void);
bool read_pin(void);
int Mean_Filter(int sensor);
float Get_D_Angle_Balance(float Angle_Balance);
float averageFilter(float in_data);

#endif
