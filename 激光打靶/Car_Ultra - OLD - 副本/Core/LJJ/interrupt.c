#include "interrupt.h"
#include "string.h"
#include "usart.h"

//#include "adc.h"
#include "tim.h"
#include "pid.h"
#include "vofa.h"
#include "L298N.h"



//usart1 k210
#define USART1_REC_LEN  200
uint8_t USART1_RX_BUF[USART1_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART1_RX_STA=0;//接收状态标记//bit15：接收完成标志，bit14~0：接收到的有效字节数目
uint8_t USART1_NewData;//当前串口中断接收的1个字节数据的缓存
uint8_t RxState1 = 0;

extern int mubiao_x;
extern int mubiao_BF;


//usart2 bluetooth
#define USART2_REC_LEN  200
uint8_t USART2_RX_BUF[USART2_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART2_RX_STA=0;//接收状态标记//bit15：接收完成标志，bit14~0：接收到的有效字节数目
uint8_t USART2_NewData;//当前串口中断接收的1个字节数据的缓存
uint8_t RxState2 = 0; 

int target=0;





//usart3 openmv

#define USART3_REC_LEN  200//定义USART2最大接收字节数
uint8_t  USART3_RX_BUF[USART3_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.末字节为校验和
uint16_t USART3_RX_STA;//接收状态标记
uint8_t USART3_NewData;//当前串口中断接收的1个字节数据的缓存
uint8_t RxState3 = 0; 

int theta;
int cv_x;
int cv_y;
extern int road_flag;




//usart6 vofa
#define RXSTRSIZE 256		  
uint8_t rx_string[RXSTRSIZE]; 
uint8_t rx_cnt = 0;			  
uint8_t rx_buff;			  
uint8_t RxBuff;
unsigned char shujv[12];
int vofa_i = 0, vofa_I = 0;
float vofa_float;




float x_pid_v_out;
float x_pid_x_out=0;
float y_pid_v_out;
float y_pid_x_out=0;



float Kp_x_v=2.5;  
float Ki_x_v=0.4;
float Kd_x_v=0;   


float Kp_x_x=0;    //数据
float Ki_x_x=0;
float Kd_x_x=0;

// float Kp_x_x=0.0; 
// float Ki_x_x=0.0;
// float Kd_x_x=0.0;

float Kp_y_v=0.0;  
float Ki_y_v=0.0;
float Kd_y_v=0.0;   

// float Kp_y_v=0.0;  
// float Ki_y_v=0.0;
// float Kd_y_v=0.0;  

float Kp_y_x=0; 
float Ki_y_x=0;
float Kd_y_x=0;



int left_counter;
int right_counter;

int left_pwm;
int right_pwm;
int speed_pwm;
extern int mubiao;
extern int liucheng;
extern int stop;
extern int target;
extern int target1;
extern int turn_flag;
extern int move_flag;
extern int road_flag;
extern int counter_flag;
extern int mubiao1_flag;
extern int line_flag;

extern int cv_x;
extern int cv_y;


int mid=80;
int ori;

          //x  30   81  117
          //y  12   53  87



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//100ms
	if (htim->Instance == TIM2)
    { 
    // left_counter=__HAL_TIM_GET_COUNTER(&htim5);
   	// right_counter=__HAL_TIM_GET_COUNTER(&htim4);


	
		
		}
	//10ms
	if (htim->Instance == TIM8)
    { 
		move_wasd(target,0);

		if(stop==1){
		Reset();
		stop=0;
		turn_flag=0;
		counter_flag=0;
		road_flag=0;
		mubiao1_flag=0;
	//move_flag=0;
	}



	
	










	}
	//1ms
	if (htim->Instance == TIM9)
	{ 
    left_counter=__HAL_TIM_GET_COUNTER(&htim5);
   	right_counter=__HAL_TIM_GET_COUNTER(&htim4);
	
	if(road_flag==1||road_flag==2){

		turn_flag=1;


	}

//HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1);

	speed_pwm=X_PID_V_value(128,theta);
	
	if((liucheng==99||target1==2)&&line_flag==0&&liucheng!=18){
	ori=mid-cv_x;
	Kp_x_v=2;  
	Ki_x_v=0.2;
	Kd_x_v=0;  

  	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,1850*1.8+speed_pwm);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1950*1.8-speed_pwm);
	}
	else if((liucheng==1||liucheng==10||liucheng==6)&&line_flag==0&&mubiao>2){
	 Kp_x_v=4;  
	 Ki_x_v=0.4;
	 Kd_x_v=0;  

  	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,1850*2.5+speed_pwm);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1950*2.5-speed_pwm);

	}
	else if((liucheng==1||liucheng==10||liucheng==6)&&line_flag==0&&mubiao<=2){
	 Kp_x_v=2;  
	 Ki_x_v=0.2;
	 Kd_x_v=0;  

  	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,1850*1.5+speed_pwm);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1950*1.5-speed_pwm);

	}
	else{
	if(liucheng!=18&&liucheng!=6){
	Kp_x_v=2;  
	Ki_x_v=0.2;
	Kd_x_v=0;
  	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4,1850*1.2);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3,1950*1.2);}
	}
		






	}




}










void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
	if(huart ==&huart1) //k210
  { 
	 if(RxState1 ==0&&USART1_NewData==0xF3){				
     USART1_RX_BUF[USART1_RX_STA]=USART1_NewData;
     RxState1 = 1;			
			}

	 else if(RxState1 ==1&&USART1_NewData==0xF4){
     USART1_RX_BUF[USART1_RX_STA++]=USART1_NewData;
     RxState1 = 2; 
     }

     else if(RxState1 ==2){
     USART1_RX_BUF[USART1_RX_STA++]=USART1_NewData;
     if(USART1_RX_BUF[USART1_RX_STA-1]== 0xF5){

			mubiao_x= USART1_RX_BUF[USART1_RX_STA-3];
			mubiao_BF = USART1_RX_BUF[USART1_RX_STA-2];	
			RxState1=3; }
     }

     else if(RxState1==3){
			USART1_RX_STA=0;
			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
			RxState1=0;

     
     }
     if(USART1_RX_STA>(USART1_REC_LEN-1)){
		   USART1_RX_STA=0;
			 memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
			  RxState1=0;
			}



  }	
	
	 //bluetooth
 	if(huart ==&huart2) //蓝牙
   { 
 	 if(RxState2 ==0){
       USART2_RX_BUF[USART2_RX_STA]=USART2_NewData; 					
       USART2_RX_STA++; 
       RxState2 = 1;			
 	}
 	 else if(RxState2 ==1){
       USART2_RX_BUF[USART2_RX_STA++]=USART2_NewData; 
 	 	if(USART2_RX_STA >0||USART2_RX_BUF[USART2_RX_STA-1]== 0x12)
 		 {

 			target = USART2_RX_BUF[USART2_RX_STA-2]-48;			
 			//num2 = USART1_RX_BUF[USART1_RX_STA-4];
 			//	num3 = USART1_RX_BUF[USART1_RX_STA-5];	
				
 			USART2_RX_STA=0;
 			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
 			RxState2=2;
				
 		}	
 			}
			
 	 if(USART2_RX_STA>(USART2_REC_LEN-1)){
 		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
 		USART2_RX_STA=0;	
 	  }
 	 else if(RxState2 ==2)   //接收异常
 	 {
 		USART2_RX_STA=0;
 		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
 		RxState2=0;
 		}		
     }


	if(huart ==&huart3) //openmv
  { 
	 if(RxState3 ==0&&USART3_NewData==0x2C){				
     USART3_RX_BUF[USART3_RX_STA]=USART3_NewData;
     RxState3 = 1;			
			}

	 else if(RxState3 ==1&&USART3_NewData==0x12){
     USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
     RxState3 = 2; 
     }

     else if(RxState3 ==2){
     USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
     if(USART3_RX_BUF[USART3_RX_STA-1]== 0x5B){
			theta=USART3_RX_BUF[USART3_RX_STA-5];
			cv_x= USART3_RX_BUF[USART3_RX_STA-4];
			cv_y= USART3_RX_BUF[USART3_RX_STA-3];
			road_flag = USART3_RX_BUF[USART3_RX_STA-2];	
			RxState3=3; }
     }

     else if(RxState3==3){
			USART3_RX_STA=0;
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			RxState3=0;

     
     }
     if(USART3_RX_STA>(USART3_REC_LEN-1)){
		   USART3_RX_STA=0;
			 memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			  RxState3=0;
			}



  }

	if(huart ==&huart6){
		  uint8_t dat;
		  if (rx_cnt++ >= RXSTRSIZE - 1) // ???????
		  {
			  rx_cnt = 0;
			memset(rx_string, 0x00, sizeof(rx_string));
		}
		else
		{
			dat = rx_buff; // ???????????

			shujv[vofa_I++] = dat;

			if (dat == 0x0a)
			{

				for (vofa_i = 2, vofa_float = 0; vofa_i < vofa_I - 1; vofa_i++)
					vofa_float = 10 * vofa_float + (shujv[vofa_i] - '0');
				vofa_I = 0;

				if (shujv[1] == 0x3A)
				{
					switch (shujv[0])
					{
					// case 'S':my_dat.biaozhi =  shujv[2]  ; break;
					case 'P'://VOFA
						Kp_x_x= vofa_float; //keil
						break;
					case 'I':
						Ki_x_x = vofa_float;
						break;
					case 'D':
						Kd_x_x = vofa_float;
						break;
					case 'A':
						Kp_y_x = vofa_float;
						break;
					case 'B':
						Ki_y_x = vofa_float;
						break;
					case 'C':
						Kd_y_x = vofa_float;
						break;


					
					}
				}
			}
			memset(rx_string, 0x00, sizeof(rx_string)); 
			rx_cnt = 0;									
		}

  }


	 
		
		

		
		
		
		
  HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData,1);
	HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); 
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
	HAL_UART_Receive_IT(&huart6, (uint8_t *)&rx_buff, 1); 

}



		


			
	


	

