#include "sys.h"

u8 res;

u8 T0Cound,T1Cound;

short ECPULSE1;                      //动量轮反馈速度
short ECPULSE2;                      //后轮反馈速度

float Pitch,Roll,Yaw;						//角度
short gyrox,gyroy,gyroz;				//陀螺仪--角速度
short aacx,aacy,aacz;						//加速度

short BLDCduty;                      //无刷电机pwm

//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
    USART3->DR = (u8) ch;      
	return ch;
}


int main()
{	
	delay_init(72);
	USART3Communication_Init(115200);
	
//	TIM2_Init(9,15999);
	
	Motor_Init();
	
	PWM_Init_TIM1(0,7199);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	while(1)
	{
		MAin1 = 1;
		MAin2 = 0;
		MBin1 = 0;
		MBin2 = 0;
		delay_us(500);
		MAin1 = 1;
		MAin2 = 0;
		MBin1 = 1;
		MBin2 = 0;
		delay_us(500);
		MAin1 = 0;
		MAin2 = 0;
		MBin1 = 1;
		MBin2 = 0;
		delay_us(500);
		MAin1 = 0;
		MAin2 = 1;
		MBin1 = 1;
		MBin2 = 0;
		delay_us(500);
		MAin1 = 0;
		MAin2 = 1;
		MBin1 = 0;
		MBin2 = 0;
		delay_us(500);
		MAin1 = 0;
		MAin2 = 1;
		MBin1 = 0;
		MBin2 = 1;
		delay_us(500);
		MAin1 = 0;
		MAin2 = 0;
		MBin1 = 0;
		MBin2 = 1;
		delay_us(500);
		MAin1 = 1;
		MAin2 = 0;
		MBin1 = 0;
		MBin2 = 1;
		delay_us(500);
  }
}

void TIM2_IRQHandler(void)
{
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

