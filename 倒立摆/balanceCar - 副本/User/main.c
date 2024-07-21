#include "sys.h"

u8 res;

u8 T0Cound,T1Cound;

short ECPULSE1;                      //�����ַ����ٶ�
short ECPULSE2;                      //���ַ����ٶ�

float Pitch,Roll,Yaw;						//�Ƕ�
short gyrox,gyroy,gyroz;				//������--���ٶ�
short aacx,aacy,aacz;						//���ٶ�

short BLDCduty;                      //��ˢ���pwm

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
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

