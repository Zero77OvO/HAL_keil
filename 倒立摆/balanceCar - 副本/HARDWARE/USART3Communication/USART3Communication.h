#ifndef __USART3Communication_H__
#define __USART3Communication_H__

#include "stm32f10x.h"

//void USART3_NVIC_Config(void);
void USART3Communication_Init(u32 BaudRate);
void USART3_IRQHandler(void);
	
#endif

