#include "L298N.h"  
#include "main.h"
#include "adc.h"
#include "OLED.h" 

#define FILTERING_TIMES  4

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;


float Angle_Balance;    
uint16_t ADC_Value;
Motor motor1;
float angle;
float Angle;

float D_Angle_Balance; //�ڸ˽Ƕȱ仯��
long D_Count;//���ڸ�����ȡ�ڸ˽Ƕȱ仯�ʵ��м����
float Last_Angle_Balance; //���ڻ�ȡ�ڸ˽Ƕȱ仯�ʺ����У�������һ�νǶ�

int t1;
int t2;

float time=0;

bool Dir(){
	
t1=t2;
ms_Delay(5);

t2=angle;
	
if(t2-t1>5){return 0;}
else{return 1;}
	

}


void start(){
	
	
 Lstr();Rstr();

}
void stop(){
	
	
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_RESET);

}


bool read_pin(void){
if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13)==1){

return 0;}
else{ return 1;}




}
void RER(void){
	
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_SET);

}
void L(void){
	
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_RESET);
	
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_SET);



}
void R(void){
	
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_RESET);
	
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_SET);

}
void Lstr(void){

HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_SET);
HAL_Delay(200);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_RESET);

}
void Rstr(void){

HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_SET);
HAL_Delay(330);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12,GPIO_PIN_RESET);
	
		
}




void restart(void){

HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_SET);
ms_Delay(1200);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_RESET);

}

void Motor_Init(void)
{
    HAL_TIM_Base_Start_IT(&ENCODER_TIM);
    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //����100ms��ʱ���ж�

}
float data[10];
 
float averageFilter(float in_data)
{
	float sum = 0;
	for(int i=0; i<3; i++)
	{
		data[i]=data[i+1];
		sum = sum + data[i];
	}
	data[3] = in_data;
	sum = sum + data[3];
	
	return(sum/3);
 
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//��ʱ���ص����������ڼ����ٶ�
{
    /*if(htim->Instance==ENCODER_TIM.Instance)//���������붨ʱ������жϣ����ڷ����                   
    {      
      
//			R();
//			L();
    }*/
    if(htim->Instance==GAP_TIM.Instance)//�����ʱ���жϣ���ʱ������ٶ���
    {
        /*motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
        motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 100;//���ÿ�����ת
        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//��ó������ٶ�ÿ����ٺ���
        motor1.lastCount = motor1.totalCount; //��¼��һ�εļ���ֵ*/
			
		  	//
				HAL_ADCEx_Calibration_Start(&hadc1);   //ADCУ׼
        HAL_ADC_Start(&hadc1);                 //����ADCת��
        HAL_ADC_PollForConversion(&hadc1, 5); //�ȴ�ADC1ת����ϣ��������ȴ�50ms
        ADC_Value = HAL_ADC_GetValue(&hadc1);  //��ȡADC��ֵ����������ADC_Value����
			  Angle=ADC_Value ;
			  
			  
			  time+=0.01;
			
		    angle=averageFilter(Angle)* 265.1/4095;
			  
			  
    }
}
void ms_Delay(uint16_t t_ms)
{
	uint32_t t=t_ms*3127;
	while(t--);
}





float Get_D_Angle_Balance(float Angle_Balance)
{
	if(++D_Count>5) //��ȡ�Ƕȱ仯�ʣ���� ʱ�䳣��25ms
	{
		D_Angle_Balance=Mean_Filter(Angle_Balance-Last_Angle_Balance);	//ƽ���˲��õ�������С�İڸ˽��ٶ���Ϣ			
		Last_Angle_Balance=Angle_Balance; //������ʷ����
		D_Count=0;	//����������
	}
	return D_Angle_Balance;
}


int Mean_Filter(int sensor)
{
	uint8_t  i;
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

