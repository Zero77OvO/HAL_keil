#include "control.h"
#include "key.h"
#include "encoder.h"
#include "motor.h"
#include "adc.h"
#include "sys.h"
#include "delay.h"	 

int Encoder,Position_Zero=10000;            //�������ĳ�ʼ�������
int Moto;                                   //���PWM���� Ӧ��Motor�� ��Moto�¾�	
int Voltage;                                //��ص�ѹ������صı���
float Angle_Balance;                        //��λ�ƴ���������

u8 auto_run=0;//ģʽ
u8 autorun_step0=0;//�Զ���ڵ�1�����ڸ��ṩһ����ʼ����

int k=0,kk=0;//������������־λ
int Balance_Pwm,Position_Pwm; //Ŀ��Ƕ�PWM��Ŀ��λ��PWM
u8 Position_Target;//���ڱ��λ�ÿ��Ƶ�ʱ��

//���PD�������õ��Ĳ���
float D_Angle_Balance; //�ڸ˽Ƕȱ仯��
long D_Count;//���ڸ�����ȡ�ڸ˽Ƕȱ仯�ʵ��м����
float Last_Angle_Balance; //���ڻ�ȡ�ڸ˽Ƕȱ仯�ʺ����У�������һ�νǶ�
float Bias;//���ƫ��
float Last_Bias,D_Bias;  //PID��ر���
int balance;//PWM����ֵ 

//λ�û�PD�������õ��Ĳ���
float Position_PWM,Last_Position,Position_Bias,Position_Differential;
float Position_Least;

//float Balance_KP=230,Balance_KD=170,Position_KP=6,Position_KD=160;//PID����
float Balance_KP=170,Balance_KD=170,Position_KP=6,Position_KD=160;//PID����
/**************************************************************************
�������ܣ�TIM1���Ƶ�5ms��ʱ�ж� 
**************************************************************************/
int TIM1_UP_IRQHandler(void)  //5ms��ʱ�ж�
{    
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ //5ms��ʱ�ж�
	{   
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );//�����ʱ��1�жϱ�־λ	                     
	
		Encoder=Read_Encoder(4);//���±�����λ����Ϣ	 
		Angle_Balance=Get_Adc_Average(6,10);//������̬	
		Get_D_Angle_Balance();//��ðڸ˽��ٶ�
		//***********�Զ����ģʽ
		if(auto_run==1)
		{
			//***********���ڸ�һ����ʼ����
			if((autorun_step0==0)&&(Encoder<=11000))Moto=-3000;
			else {Moto=0;autorun_step0=1;}
			
			//�������Ӱڸ�����
			if(autorun_step0==1&&Encoder<10500&&((ZHONGZHI-2106)-Angle_Balance>2||Angle_Balance-ZHONGZHI>700))
			{
				Moto=-3000;	
			}
			else if(autorun_step0==1&&Encoder>9500&&Angle_Balance-(ZHONGZHI-2106)>2&&Angle_Balance-ZHONGZHI<-700)
			{
				Moto=3000;
			}

			//�жϰڸ��Ƿ������Ȱ�����
			if((Angle_Balance-ZHONGZHI)<100&&(Angle_Balance-ZHONGZHI)>-100)autorun_step0=2,auto_run=2;
			if(autorun_step0==2)Moto=0;
			
			//������λ�ñ���
			if(Encoder>12000|Encoder<8000){Moto=0;}
			
			Set_Pwm(Moto);//��ֵ��PWM�Ĵ���
		}
		
		//***********�ֶ����(�Ȱ�)ģʽ
		if(auto_run==2)
		{
			
			Balance_Pwm =Balance(Angle_Balance);//===�Ƕ�PD����	
			if(++Position_Target>4) {Position_Pwm=Position(Encoder),Position_Target=0; }//λ��PD���� 25ms����һ��λ�ÿ���
			Moto=Balance_Pwm-Position_Pwm;//===����������PWM
			Xianfu_Pwm();//PWM�޷� ��ֹռ�ձ�100%������ϵͳ���ȶ�����
			
			//�ڸ˽Ƕȱ���
			if((Angle_Balance-ZHONGZHI)>400|(Angle_Balance-ZHONGZHI)<-400|D_Angle_Balance>100|D_Angle_Balance<-100)
				{
			Moto=0;auto_run=3;
				}
				
			if(Encoder>11800|Encoder<8200){Moto=0;auto_run=3;}//������λ�ñ���
			Set_Pwm(Moto);//===��ֵ��PWM�Ĵ���			
		}
		
		//***********����ģʽ
		if(auto_run==3)
		{

			if((Angle_Balance-ZHONGZHI)<500&&(Angle_Balance-ZHONGZHI)>-500&&D_Angle_Balance<60&&D_Angle_Balance>-60){
				auto_run=2;}//�ж��Ƿ������Ȱ�����
			
			if(Encoder<9000)//����������
			{
					Moto=1300;	
			}
			else if(Encoder>11000)//����������
			{
					Moto=-1300;
			}
			else Moto=0;
			
			Set_Pwm(Moto);//===��ֵ��PWM�Ĵ���
		}
		Key();//����ɨ���ӳ���
	} 
	return 0;	
}

/**************************************************************************
�������ܣ������޸Ŀ���
**************************************************************************/
void Key(void)
{
	if(KEY0==0||k!=0)
	{
		k++;
		if(KEY0==1&&kk==0)//�����̰�
		{
			k=0;
			auto_run=2;
		}
		if(k==80)//��������
		{
			k=0;
			kk++;
			if(KEY0==1){kk=0;}
			auto_run=1;
		}
	}
}

/**************************************************************************
�������ܣ����PD����
**************************************************************************/
int Balance(float Angle)
{  
	Bias=Angle-ZHONGZHI;              //���ƽ��ĽǶ���ֵ �ͻ�е���
	D_Bias=Bias-Last_Bias;            //���ƫ���΢�� ����΢�ֿ���
	balance=Balance_KP*Bias+D_Bias*Balance_KD;   //������ǿ��Ƶĵ��PWM  PD����
	Last_Bias=Bias;                   //������һ�ε�ƫ��
	 return balance;
}

/**************************************************************************
�������ܣ�λ��PD���� 
**************************************************************************/
int Position(int Encoder)
{  
  	Position_Least =Encoder-Position_Zero;
    Position_Bias *=0.8;		   
    Position_Bias += Position_Least*0.2;//һ�׵�ͨ�˲���  
	Position_Differential=Position_Bias-Last_Position;
	Last_Position=Position_Bias;
	Position_PWM=Position_Bias*Position_KP+Position_Differential*Position_KD;//�ٶȿ���		
	  return Position_PWM;
}

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
**************************************************************************/
void Set_Pwm(int moto)
{
	if(moto<0)	BIN2=1,	BIN1=0;
	else 		BIN2=0,	BIN1=1;
	PWMB=myabs(moto);
}

/**************************************************************************
�������ܣ�����PWM��ֵ 
**************************************************************************/
void Xianfu_Pwm(void)
{	
	int Amplitude=6900;//PWM������7200 ������6900
	if(Moto<-Amplitude) Moto=-Amplitude;	
	if(Moto>Amplitude)  Moto=Amplitude;		
}

/**************************************************************************
�������ܣ�����ֵ����
**************************************************************************/
int myabs(int a)
{ 		   
	int temp;
	if(a<0)  temp=-a;  
	else temp=a;
	return temp;
}

/**************************************************************************
�������ܣ���ȡ�ڸ˽Ƕȱ仯��
**************************************************************************/
void Get_D_Angle_Balance(void)
{
	if(++D_Count>5) //��ȡ�Ƕȱ仯�ʣ���� ʱ�䳣��25ms
	{
		D_Angle_Balance=Mean_Filter(Angle_Balance-Last_Angle_Balance);	//ƽ���˲��õ�������С�İڸ˽��ٶ���Ϣ			
		Last_Angle_Balance=Angle_Balance; //������ʷ����
		D_Count=0;	//����������
	}
}

/**************************************************************************
�������ܣ�ƽ�� �˲�
**************************************************************************/
int Mean_Filter(int sensor)
{
	u8 i;
	s32 Sum_Speed = 0;     
	s16 Filter_Speed;   
	static  s16 Speed_Buf[FILTERING_TIMES]={0};
	for(i = 1 ; i<FILTERING_TIMES; i++)
	{
		Speed_Buf[i - 1] = Speed_Buf[i];
	}
	Speed_Buf[FILTERING_TIMES - 1] =sensor;

	for(i = 0 ; i < FILTERING_TIMES; i++)
	{
		Sum_Speed += Speed_Buf[i];
	}
	Filter_Speed = (s16)(Sum_Speed / FILTERING_TIMES);//
	return Filter_Speed;
}

