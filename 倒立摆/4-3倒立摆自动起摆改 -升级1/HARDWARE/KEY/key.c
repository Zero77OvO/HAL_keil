#include "stm32f10x.h"
#include "key.h"
#include "delay.h"  

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTCʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//KEY0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC14
}


u8 KEY_Scan(u8 mode)//��ȡ����״̬
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //mode:0,��֧��������;1,֧��������;		  
	if(key_up&&KEY0==0)
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
	}
	else if(KEY0==1)
	{
		key_up=1;
	} 	    
 	return 0;// �ް�������
}

