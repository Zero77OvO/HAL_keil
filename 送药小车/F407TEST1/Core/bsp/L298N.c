#include "interrupt.h"
#include "string.h"
#include "usart.h"

//#include "adc.h"
#include "tim.h"
#include "pid.h"
#include "vofa.h"
#include "L298N.h"

int stop;
int target1;
extern int liucheng;
extern int target;
extern int stop_flag;
extern int turn_flag;
extern int move_flag;
extern int road_flag;
extern int counter_flag;
int left_counter;
int right_counter;
extern int mubiao1_flag;
extern int counter;
extern int time;
extern int dir_buff;
int line_flag;
int straight_flag;
int veer_flag;
int forward_flag;

void move_wasd(int target,int distance){
	//ֱ��һ������ 
	if(target==1){
	
   	if(counter_flag==0){
	straight_flag=1;
  	__HAL_TIM_SET_COUNTER(&htim1, 0);
  	__HAL_TIM_SET_COUNTER(&htim3, 0);
      counter_flag=1; 
	}
    if(right_counter<=distance+1000&&counter_flag==1&&right_counter>=distance){Restart();HAL_Delay(200);move_wasd(5,0);counter_flag=0;straight_flag=11;
	
	if(liucheng==1){liucheng=2;}
	if(liucheng==3){liucheng=4;}



	if(liucheng==5){liucheng=6;}

	if(liucheng==8){liucheng=9;}

	
	if(liucheng==10){liucheng=11;}
	if(liucheng==15){stop_flag=11;}
	if(liucheng==17){if(stop_flag==0){stop_flag=1;}}
	
	
	}
    else{if(straight_flag==1){Forward();straight_flag=1;}}
  	}

	
    //ֱ��	
	if(target==2){

	
	Forward();
	
	}
	if(target==4){

	
	Left();
	
	}
	if(target==6){

	
	Right();
	
	}


    
	//����
	if(target==8){
	Back();
	}

	
	

	//ֹͣ
	if(target==5){
	Reset();
	turn_flag=0;
	counter_flag=0;
	road_flag=0;
    target1=0;
	mubiao1_flag=0;
	line_flag=0;

	//move_flag=0;
	}

    //��ת��ֱ��
	if(target==7){
	
	if(counter_flag==0){
	Reset();
	veer_flag=1;
  	__HAL_TIM_SET_COUNTER(&htim1, 12000);
  	__HAL_TIM_SET_COUNTER(&htim3, 12000);
	counter_flag=1;
	// __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,1000);
	// __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,1000);
	}
	//right_counter<=10450&&right_counter>=10000 (12000-left_counter)+(12000-right_counter)>=1600
  	if(left_counter-12000>=1700&&counter_flag==1){Restart();stop=1;counter_flag=0;veer_flag=11;target1=2;}
	else{if(veer_flag==1){Left();veer_flag=1;}}
	}
	//��ת��ֱ��
	if(target==9){
	
 	if(counter_flag==0){
	Reset();
	veer_flag=1;
  	__HAL_TIM_SET_COUNTER(&htim1, 40000);
  	__HAL_TIM_SET_COUNTER(&htim3, 40000);
	counter_flag=1;
	// __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,1000);
	// __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,1000);
	}
	//left_counter>=36800&&left_counter<=37200
 	if(right_counter-40000>=1800&&counter_flag==1){Restart();stop=1;counter_flag=0;veer_flag=11;target1=2;}
	else{if(veer_flag==1){Right();veer_flag=1;}}
	}				
	//��Сת
	if(target==10){
	
	if(counter_flag==0){
	Reset();
	veer_flag=1;
  	__HAL_TIM_SET_COUNTER(&htim1, 30000);
  	__HAL_TIM_SET_COUNTER(&htim3, 30000);
	counter_flag=1;
	}

  	if(left_counter>=30100&&counter_flag==1&&left_counter<=30500){Restart();HAL_Delay(200);move_wasd(5,0);counter_flag=0;veer_flag=11;
	
	if(liucheng==11){liucheng=12;Reset();}
	
	}
	else{if(veer_flag==1){Left_light();veer_flag=1;}}
	}
	//��Сת
	if(target==11){
	
	if(counter_flag==0){
	Reset();
	veer_flag=1;
  	__HAL_TIM_SET_COUNTER(&htim1, 30000);
  	__HAL_TIM_SET_COUNTER(&htim3, 30000);
	counter_flag=1;
	}

  	if(left_counter<=29900&&counter_flag==1&&left_counter>=29530){Restart();HAL_Delay(200);move_wasd(5,0);counter_flag=0;veer_flag=11;
	
	if(liucheng==12){liucheng=13;}
	
	}
	else{if(veer_flag==1&&(time>350||dir_buff==1)){Left_RElight();veer_flag=1;}}
	}






}
  //��⵽����ǰ��һ����ͣ
void Line_Detection(){
	
  if(turn_flag==1){
      move_flag=0;
   if(counter_flag==0&&move_flag==0){
  	// __HAL_TIM_SET_COUNTER(&htim4, 20000);			//����������ָ��²���ʱ���������
  	// __HAL_TIM_SET_COUNTER(&htim5, 20000);
	counter=0;
    counter_flag=1;
	}

	if((time<30&&liucheng==1)||liucheng==3||liucheng==8){ //����12 �� ����
	if(counter>=9&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);move_flag=1;move_wasd(5,0);

	
    if(liucheng==3){liucheng=4;}

	if(liucheng==8){liucheng=9;}
	

	}
    } 
    else{if(move_flag==0){Forward();counter++;line_flag=1;}} 
 }

 	if(time>30&&time<1200&&liucheng==1||liucheng==6){ //����34
	if(counter>=21&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);move_flag=1;move_wasd(5,0);

	if(liucheng==1){liucheng=2;}
    if(liucheng==3){liucheng=4;}


	if(liucheng==6){liucheng=7;}
	}
    } 
    else{if(move_flag==0){Forward();counter++;line_flag=1;}} 
 }

  	if(time>30&&time<8000&&liucheng==13){ //����789
	if(counter>=6&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);move_flag=1;move_wasd(5,0);

	if(liucheng==13){liucheng=14;move_wasd(5,0);}
	
	if(liucheng==15){target1=7;}
	}
    } 
    else{if(move_flag==0){Forward();counter++;line_flag=1;}} 
 }
   	if(time>30&&time<8000&&liucheng==15){ //����789
	if(counter>=10&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);Reset();move_flag=1;move_wasd(5,0);

	if(liucheng==13){liucheng=14;move_wasd(5,0);}
	
	if(liucheng==15){target1=7;}
	}
    } 
    else{if(move_flag==0){Forward();counter++;line_flag=1;}} 
 }


}

}

void Restart()
{
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);

}
void Reset()
{
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);

}

void Forward(){
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);//LEFT_UP
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);//RIGHT
}


void Back(){

HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);	//RIGHT_DOWN


}

void Left(){
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);	
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
}

void Left_light(){
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);	
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
}

void Left_RElight(){
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);	
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
}

void zhuanquan(){
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);	
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);


}

void Right(){
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);	
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
}

void Walk(){
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
}

void Red(){
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7,GPIO_PIN_SET);
}
void DERed(){
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_7,GPIO_PIN_RESET);
}
void Green(){
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
}
void DEGreen(){
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);
}
void Yellow(){
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET);
}
void DEYellow(){
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);
}



