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
extern int left_counter;
extern int right_counter;
extern int mubiao1_flag;
extern int counter;
extern int time;
extern int dir_buff;
int line_flag;
void move_wasd(int target,int distance){
	//直行一定距离 
	if(target==1){
    move_flag=0;
   	if(counter_flag==0&&move_flag==0){
  	__HAL_TIM_SET_COUNTER(&htim4, 65535);
  	__HAL_TIM_SET_COUNTER(&htim5, 65535);
      counter_flag=1; 
	}
    if(right_counter<=distance&&counter_flag==1&&right_counter>=distance-1000){Restart();HAL_Delay(200);move_wasd(5,0);counter_flag=0;move_flag=1;
	if(liucheng==1){liucheng=22;}
	if(liucheng==3){liucheng=4;}
	if(liucheng==5){liucheng=11;}

	if(liucheng==10){liucheng=5;}


	if(liucheng==15){stop_flag=11;}
	if(liucheng==17){if(stop_flag==0){stop_flag=1;}}
	
	
	}
    else{if(move_flag==0){Forward();}}
  	}

	
    //直行	
	if(target==2){
	Forward();
	}

	
    
	//后退
	if(target==8){
	Back();
	}

	
	

	//停止
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

    //左转并直行
	if(target==7){
	move_flag=0;
	if(counter_flag==0){
	Reset();
  	__HAL_TIM_SET_COUNTER(&htim4, 12000);
  	__HAL_TIM_SET_COUNTER(&htim5, 12000);
	counter_flag=1;
	}
	//right_counter<=10450&&right_counter>=10000 (12000-left_counter)+(12000-right_counter)>=1600
  	if(12000-right_counter>=1520&&counter_flag==1){Restart();stop=1;counter_flag=0;move_flag=1;target1=2;}
	else{if(move_flag==0){Left();}}
	}
	//右转并直行
	if(target==9){
	move_flag=0;
 	if(counter_flag==0){
	Reset();
  	__HAL_TIM_SET_COUNTER(&htim4, 50000);
  	__HAL_TIM_SET_COUNTER(&htim5, 50000);
	counter_flag=1;
	}
	//left_counter>=36800&&left_counter<=37200
 	if(left_counter-50000>=1400&&counter_flag==1){Restart();stop=1;counter_flag=0;move_flag=1;target1=2;}
	else{if(move_flag==0){Right();}}
	}				
	//左小转
	if(target==10){
	move_flag=0;
	if(counter_flag==0){
	Reset();
  	__HAL_TIM_SET_COUNTER(&htim4, 30000);
  	__HAL_TIM_SET_COUNTER(&htim5, 30000);
	counter_flag=1;
	}

  	if(left_counter<=29880&&counter_flag==1&&left_counter>=29530){move_wasd(5,0);counter_flag=0;move_flag=1;
	
	if(liucheng==11){liucheng=12;Reset();}
	
	}
	else{if(move_flag==0){Left_light();}}
	}
	//右小转
	if(target==11){
	move_flag=0;
	if(counter_flag==0){
	Reset();
  	__HAL_TIM_SET_COUNTER(&htim4, 30000);
  	__HAL_TIM_SET_COUNTER(&htim5, 30000);
	counter_flag=1;
	}

  	if(left_counter>=30170&&counter_flag==1&&left_counter<=30500){move_wasd(5,0);counter_flag=0;move_flag=1;
	
	if(liucheng==12){liucheng=13;}
	
	}
	else{if(move_flag==0&&(time>65||dir_buff==1)){Left_RElight();}}
	}






}
  //检测到线往前走一段再停
void Line_Detection(){
	line_flag=1;
  if(turn_flag==1){
      move_flag=0;
   if(counter_flag==0&&move_flag==0){
  	// __HAL_TIM_SET_COUNTER(&htim4, 20000);			//编码器会出现更新不及时的情况。。
  	// __HAL_TIM_SET_COUNTER(&htim5, 20000);
	counter=0;
    counter_flag=1;
	}
   //12病房
    // if(counter>=20800&&liucheng==3&&counter_flag==1){if(counter_flag==1){Reset();counter_flag=0;move_flag=1;move_wasd(5,0);

	// if(liucheng==1){liucheng=2;}
    // if(liucheng==3){liucheng=4;}
	// if(liucheng==11){liucheng=12;}
	// if(liucheng==13){liucheng=14;}
	// //if(liucheng=15){liucheng=16;}
	// }
    // }
	if(liucheng==1||liucheng==3||liucheng==22){ //病房12 且 返程
	if(counter>=1&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);move_flag=1;move_wasd(5,0);

	if(liucheng==22){liucheng=2;}
    if(liucheng==3){liucheng=4;}
	

	}
    } 
    else{if(move_flag==0){Forward();counter++;}} 
 }

 	if(time>30&&time<1200&&liucheng==5){ //病房34
	if(counter>=7&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);move_flag=1;move_wasd(5,0);



	if(liucheng==5){liucheng=6;}
	}
    } 
    else{if(move_flag==0){Forward();counter++;}} 
 }

  	if(time>30&&time<1200&&liucheng==13){ //病房789
	if(counter>=3&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);move_flag=1;move_wasd(5,0);

	if(liucheng==13){liucheng=14;move_wasd(5,0);}
	
	if(liucheng==15){target1=7;}
	}
    } 
    else{if(move_flag==0){Forward();counter++;}} 
 }
   	if(time>30&&time<1200&&liucheng==15){ //病房789
	if(counter>=2&&counter_flag==1){if(counter_flag==1){Restart();HAL_Delay(200);move_flag=1;move_wasd(5,0);

	if(liucheng==13){liucheng=14;move_wasd(5,0);}
	
	if(liucheng==15){target1=7;}
	}
    } 
    else{if(move_flag==0){Forward();counter++;}} 
 }


}

}

void Restart()
{
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);//左倒转
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);//左正转
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);//右正转
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);//右倒转

}

void Reset()
{
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);//左倒转
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);//左正转
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);//右正转
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);//右倒转

}

void Forward(){
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}


void Back(){

HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);	


}

void Left(){
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}

void Left_light(){
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
}

void Left_RElight(){
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
}

void zhuanquan(){
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);


}

void Right(){
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);	
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
}

void Walk(){
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}



