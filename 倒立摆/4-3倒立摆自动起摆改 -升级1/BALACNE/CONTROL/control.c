#include "control.h"
#include "key.h"
#include "encoder.h"
#include "motor.h"
#include "adc.h"
#include "sys.h"
#include "delay.h"	 

int Encoder,Position_Zero=10000;            //编码器的初始脉冲计数
int Moto;                                   //电机PWM变量 应是Motor的 向Moto致敬	
int Voltage;                                //电池电压采样相关的变量
float Angle_Balance;                        //角位移传感器数据

u8 auto_run=0;//模式
u8 autorun_step0=0;//自动起摆第1步给摆杆提供一个初始动力

int k=0,kk=0;//计数、长按标志位
int Balance_Pwm,Position_Pwm; //目标角度PWM、目标位置PWM
u8 Position_Target;//用于标记位置控制的时间

//倾角PD控制所用到的参数
float D_Angle_Balance; //摆杆角度变化率
long D_Count;//用于辅助获取摆杆角度变化率的中间变量
float Last_Angle_Balance; //用于获取摆杆角度变化率函数中，保存上一次角度
float Bias;//倾角偏差
float Last_Bias,D_Bias;  //PID相关变量
int balance;//PWM返回值 

//位置环PD控制所用到的参数
float Position_PWM,Last_Position,Position_Bias,Position_Differential;
float Position_Least;

//float Balance_KP=230,Balance_KD=170,Position_KP=6,Position_KD=160;//PID参数
float Balance_KP=170,Balance_KD=170,Position_KP=6,Position_KD=160;//PID参数
/**************************************************************************
函数功能：TIM1控制的5ms定时中断 
**************************************************************************/
int TIM1_UP_IRQHandler(void)  //5ms定时中断
{    
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 //5ms定时中断
	{   
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );//清除定时器1中断标志位	                     
	
		Encoder=Read_Encoder(4);//更新编码器位置信息	 
		Angle_Balance=Get_Adc_Average(6,10);//更新姿态	
		Get_D_Angle_Balance();//获得摆杆角速度
		//***********自动起摆模式
		if(auto_run==1)
		{
			//***********给摆杆一个初始能量
			if((autorun_step0==0)&&(Encoder<=11000))Moto=-3000;
			else {Moto=0;autorun_step0=1;}
			
			//持续增加摆杆能量
			if(autorun_step0==1&&Encoder<10500&&((ZHONGZHI-2106)-Angle_Balance>2||Angle_Balance-ZHONGZHI>700))
			{
				Moto=-3000;	
			}
			else if(autorun_step0==1&&Encoder>9500&&Angle_Balance-(ZHONGZHI-2106)>2&&Angle_Balance-ZHONGZHI<-700)
			{
				Moto=3000;
			}

			//判断摆杆是否满足稳摆条件
			if((Angle_Balance-ZHONGZHI)<100&&(Angle_Balance-ZHONGZHI)>-100)autorun_step0=2,auto_run=2;
			if(autorun_step0==2)Moto=0;
			
			//编码器位置保护
			if(Encoder>12000|Encoder<8000){Moto=0;}
			
			Set_Pwm(Moto);//赋值给PWM寄存器
		}
		
		//***********手动起摆(稳摆)模式
		if(auto_run==2)
		{
			
			Balance_Pwm =Balance(Angle_Balance);//===角度PD控制	
			if(++Position_Target>4) {Position_Pwm=Position(Encoder),Position_Target=0; }//位置PD控制 25ms进行一次位置控制
			Moto=Balance_Pwm-Position_Pwm;//===计算电机最终PWM
			Xianfu_Pwm();//PWM限幅 防止占空比100%带来的系统不稳定因素
			
			//摆杆角度保护
			if((Angle_Balance-ZHONGZHI)>400|(Angle_Balance-ZHONGZHI)<-400|D_Angle_Balance>100|D_Angle_Balance<-100)
				{
			Moto=0;auto_run=3;
				}
				
			if(Encoder>11800|Encoder<8200){Moto=0;auto_run=3;}//编码器位置保护
			Set_Pwm(Moto);//===赋值给PWM寄存器			
		}
		
		//***********保护模式
		if(auto_run==3)
		{

			if((Angle_Balance-ZHONGZHI)<500&&(Angle_Balance-ZHONGZHI)>-500&&D_Angle_Balance<60&&D_Angle_Balance>-60){
				auto_run=2;}//判断是否满足稳摆条件
			
			if(Encoder<9000)//滑块向右走
			{
					Moto=1300;	
			}
			else if(Encoder>11000)//滑块向左走
			{
					Moto=-1300;
			}
			else Moto=0;
			
			Set_Pwm(Moto);//===赋值给PWM寄存器
		}
		Key();//按键扫描子程序
	} 
	return 0;	
}

/**************************************************************************
函数功能：按键修改控制
**************************************************************************/
void Key(void)
{
	if(KEY0==0||k!=0)
	{
		k++;
		if(KEY0==1&&kk==0)//按键短按
		{
			k=0;
			auto_run=2;
		}
		if(k==80)//按键长按
		{
			k=0;
			kk++;
			if(KEY0==1){kk=0;}
			auto_run=1;
		}
	}
}

/**************************************************************************
函数功能：倾角PD控制
**************************************************************************/
int Balance(float Angle)
{  
	Bias=Angle-ZHONGZHI;              //求出平衡的角度中值 和机械相关
	D_Bias=Bias-Last_Bias;            //求出偏差的微分 进行微分控制
	balance=Balance_KP*Bias+D_Bias*Balance_KD;   //计算倾角控制的电机PWM  PD控制
	Last_Bias=Bias;                   //保持上一次的偏差
	 return balance;
}

/**************************************************************************
函数功能：位置PD控制 
**************************************************************************/
int Position(int Encoder)
{  
  	Position_Least =Encoder-Position_Zero;
    Position_Bias *=0.8;		   
    Position_Bias += Position_Least*0.2;//一阶低通滤波器  
	Position_Differential=Position_Bias-Last_Position;
	Last_Position=Position_Bias;
	Position_PWM=Position_Bias*Position_KP+Position_Differential*Position_KD;//速度控制		
	  return Position_PWM;
}

/**************************************************************************
函数功能：赋值给PWM寄存器
**************************************************************************/
void Set_Pwm(int moto)
{
	if(moto<0)	BIN2=1,	BIN1=0;
	else 		BIN2=0,	BIN1=1;
	PWMB=myabs(moto);
}

/**************************************************************************
函数功能：限制PWM赋值 
**************************************************************************/
void Xianfu_Pwm(void)
{	
	int Amplitude=6900;//PWM满幅是7200 限制在6900
	if(Moto<-Amplitude) Moto=-Amplitude;	
	if(Moto>Amplitude)  Moto=Amplitude;		
}

/**************************************************************************
函数功能：绝对值函数
**************************************************************************/
int myabs(int a)
{ 		   
	int temp;
	if(a<0)  temp=-a;  
	else temp=a;
	return temp;
}

/**************************************************************************
函数功能：获取摆杆角度变化率
**************************************************************************/
void Get_D_Angle_Balance(void)
{
	if(++D_Count>5) //获取角度变化率，差分 时间常数25ms
	{
		D_Angle_Balance=Mean_Filter(Angle_Balance-Last_Angle_Balance);	//平滑滤波得到噪声更小的摆杆角速度信息			
		Last_Angle_Balance=Angle_Balance; //保存历史数据
		D_Count=0;	//计数器清零
	}
}

/**************************************************************************
函数功能：平滑 滤波
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

