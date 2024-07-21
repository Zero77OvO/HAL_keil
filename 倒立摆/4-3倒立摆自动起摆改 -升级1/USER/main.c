#include "sys.h"
#include "usart.h"		
#include "delay.h"	 
#include "led.h"  
#include "key.h" 
#include "oled.h" 
#include "motor.h"
#include "encoder.h"
#include "motor.h"
#include "adc.h"
#include "timer.h"
#include "control.h"
#include "stm32f10x.h"
#include "DataScope_DP.h"
//�½����� ʵ��  



int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();//��ʱ��ʼ��
	delay_ms(1000);//=====��ʱ�������ȴ�ϵͳ�ȶ�
	LED_Init();  //LED��ʼ��
	KEY_Init();  //������ʼ��
	OLED_Init();  //OLED��ʼ��
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	MiniBalance_PWM_Init(7199,0);  //=====��ʼ��PWM 10KHZ������������� 
	Encoder_Init_TIM4();  //=====��ʼ����������TIM4�ı������ӿ�ģʽ�� 
	Adc_Init();  //ADC��ʼ��
	Timer1_Init(49,7199);  //=====��ʱ�жϳ�ʼ�� 

  	while(1)
	{
		OLED_Show();  //OLED��ʾ
	}	 
} 






