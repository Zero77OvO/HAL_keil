#include "moto.h"
#include "stm32f10x.h"

/**************************************************************************
�������ܣ����������ת
��ڲ�����mode   mode=0ʱΪ��ת  mode=1ʱ��ת
����  ֵ����
**************************************************************************/


void moto(int mode)
{
	if(mode==1)    //��ת
	{
	 GPIO_SetBits(GPIOB, GPIO_Pin_12);	 // �ߵ�ƽ      PB7 --- AIN2      1   
	 GPIO_ResetBits(GPIOB, GPIO_Pin_13);	 // �͵�ƽ}   PB8 --- AIN1      0
		
	}
	 if(mode==0)   //����
	{
	 GPIO_SetBits(GPIOB, GPIO_Pin_13);	 // �ߵ�ƽ       PB8 --- AIN1     1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_12);	 // �͵�ƽ}    PB7 --- AIN2     0
		
	 }
	if(mode==2)   //ֹͣ
	{

		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	 // �͵�ƽ}    PB7 --- AIN2     0
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	 }
 
}

/*

��������������������������������������
AIN1  |   0     |   1     |    0   |
��������������������������������������
AIN2  |   0     |   0     |    1   |
��������������������������������������
      |  ֹͣ   |  ��ת    |  ��ת  |
��������������������������������������

*/
