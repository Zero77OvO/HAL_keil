/***********************************************

***********************************************/
#include "exti.h"
#include "key.h"
/**************************************************************************
函数功能：外部中断初始化
入口参数：无
返回  值：无 
**************************************************************************/
void MiniBalance_EXTI_Init(void)
{	
	 EXTI_InitTypeDef EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	 //按键初始化
	 KEY_Init();
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource14);
	 EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	 
//	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
//	 EXTI_InitStructure.EXTI_Line=EXTI_Line7;
//	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
//	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	 EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	 
//	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);
//	 EXTI_InitStructure.EXTI_Line=EXTI_Line11;
//	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
//	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	 EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	 
//	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);
//	 EXTI_InitStructure.EXTI_Line=EXTI_Line12;
//	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
//	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	 EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	 
//	 NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//使能按键所在的外部中断通道
//	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
//	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//   NVIC_Init(&NVIC_InitStructure);
	 
	 NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//使能按键所在的外部中断通道
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
   NVIC_Init(&NVIC_InitStructure);
}


//外部中断9~5服务程序
//void EXTI9_5_IRQHandler(void)
//{			
//	delay_ms(5);   //消抖			 
//   if(KEY5==0)	// 
//	{
//		Flag_Stop=!Flag_Stop;
//		if(Flag_Stop==0) Swing_up=0;
//	}		
//	if(KEY7==0)	///Menu 
//	{
//		if(Menu++==4) Menu=1;
//	}		
// 	EXTI_ClearITPendingBit(EXTI_Line5); //清除LINE5上的中断标志位
//	EXTI_ClearITPendingBit(EXTI_Line7); //清除LINE7上的中断标志位
//}
//外部中断15~10服务程序
void EXTI15_10_IRQHandler(void)
{			
//	delay_ms(5);   //消抖

  if(KEY14 == 0)	//PID+
	{
		
	}		
//	delay_ms(100);
  EXTI_ClearITPendingBit(EXTI_Line14); //清除LINE11上的中断标志位  
}





