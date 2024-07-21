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
//新建工程 实验  



int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();//延时初始化
	delay_ms(1000);//=====延时启动，等待系统稳定
	LED_Init();  //LED初始化
	KEY_Init();  //按键初始化
	OLED_Init();  //OLED初始化
	uart_init(115200);	//串口初始化为115200
	MiniBalance_PWM_Init(7199,0);  //=====初始化PWM 10KHZ，用于驱动电机 
	Encoder_Init_TIM4();  //=====初始化编码器（TIM4的编码器接口模式） 
	Adc_Init();  //ADC初始化
	Timer1_Init(49,7199);  //=====定时中断初始化 

  	while(1)
	{
		OLED_Show();  //OLED显示
	}	 
} 






