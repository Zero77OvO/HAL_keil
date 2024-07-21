/***********************************************

***********************************************/
#include "exti.h"
#include "key.h"
/**************************************************************************
�������ܣ��ⲿ�жϳ�ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void MiniBalance_EXTI_Init(void)
{	
	 EXTI_InitTypeDef EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	 //������ʼ��
	 KEY_Init();
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource14);
	 EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	 
//	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
//	 EXTI_InitStructure.EXTI_Line=EXTI_Line7;
//	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
//	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	 EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//	 
//	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);
//	 EXTI_InitStructure.EXTI_Line=EXTI_Line11;
//	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
//	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	 EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//	 
//	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12);
//	 EXTI_InitStructure.EXTI_Line=EXTI_Line12;
//	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
//	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	 EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	 
//	 NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
//	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
//	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
//	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//   NVIC_Init(&NVIC_InitStructure);
	 
	 NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
   NVIC_Init(&NVIC_InitStructure);
}


//�ⲿ�ж�9~5�������
//void EXTI9_5_IRQHandler(void)
//{			
//	delay_ms(5);   //����			 
//   if(KEY5==0)	// 
//	{
//		Flag_Stop=!Flag_Stop;
//		if(Flag_Stop==0) Swing_up=0;
//	}		
//	if(KEY7==0)	///Menu 
//	{
//		if(Menu++==4) Menu=1;
//	}		
// 	EXTI_ClearITPendingBit(EXTI_Line5); //���LINE5�ϵ��жϱ�־λ
//	EXTI_ClearITPendingBit(EXTI_Line7); //���LINE7�ϵ��жϱ�־λ
//}
//�ⲿ�ж�15~10�������
void EXTI15_10_IRQHandler(void)
{			
//	delay_ms(5);   //����

  if(KEY14 == 0)	//PID+
	{
		
	}		
//	delay_ms(100);
  EXTI_ClearITPendingBit(EXTI_Line14); //���LINE11�ϵ��жϱ�־λ  
}





