#include "stm32f10x.h"
#include "key.h"
#include "delay.h"  

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能PORTC时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14;//KEY0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC14
}


u8 KEY_Scan(u8 mode)//读取按键状态
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //mode:0,不支持连续按;1,支持连续按;		  
	if(key_up&&KEY0==0)
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
	}
	else if(KEY0==1)
	{
		key_up=1;
	} 	    
 	return 0;// 无按键按下
}

