#include "control.h"
#include "stdlib.h"

/*�����ʼ������*/
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//����ʱ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);	
}

void forword(void)
{
	MAin1 = 0;
	MAin2 = 1;
	MBin1 = 1;
	MBin2 = 0;
	
	TIM_SetCompare1(TIM1,5000);
	TIM_SetCompare2(TIM1,5000);
}

/*��ڲ�����PID������ɺ������PWMֵ*/
void Load(int moto1)
{
	//1.�о������ţ���Ӧ����ת
	if(moto1>0)		{MAin1 = 1;MAin2 = 0;MBin1 = 1;MBin2 = 0;}//��ת
	if(moto1<0)		{MAin1 = 0;MAin2 = 1;MBin1 = 0;MBin2 = 1;}//��ת
	//2.�о�PWMֵ
	TIM_SetCompare1(TIM1,abs(moto1));
	TIM_SetCompare2(TIM1,abs(moto1));
}


