#include "stm32f10x.h"
#include "led.h"  

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);// πƒ‹ ±÷”
	
	
	GPIO_InitTypeDef gpio_InitTypeDef;
	
	gpio_InitTypeDef.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_InitTypeDef.GPIO_Pin=GPIO_Pin_15;
	gpio_InitTypeDef.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&gpio_InitTypeDef);
	
//	GPIO_SetBits(GPIOC, GPIO_Pin_15);
}



void LED_On(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);
}

void LED_Off(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_15);
}

void LED_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15) == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_15);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);
	}
}
