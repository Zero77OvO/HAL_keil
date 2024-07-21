#include "head_files.h"

//usart1 k210
#define USART1_REC_LEN  200
uint8_t USART1_RX_BUF[USART1_REC_LEN];
uint16_t USART1_RX_STA=0;
uint8_t USART1_NewData;
uint8_t RxState1 = 0;

extern int mubiao_x;
extern int mubiao_BF;


//usart2 bluetooth
#define USART2_REC_LEN  200
uint8_t USART2_RX_BUF[USART2_REC_LEN];
uint16_t USART2_RX_STA=0;
uint8_t USART2_NewData;
uint8_t RxState2 = 0; 

int target=0;





//usart3 openmv

#define USART3_REC_LEN  200
uint8_t  USART3_RX_BUF[USART3_REC_LEN];
uint16_t USART3_RX_STA;
uint8_t USART3_NewData;
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








int target_speed=70;
int speed_now=0;


int speed_out;
int speed_reality;

int speed_flag_t=0;
int location_flag_t=0;
float KP_R=250.0;float KI_R=4;float KD_R=0;

int location_R;
IncrementalPID RT;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance == TIM2)
{ 	  
	speed_flag_t++;
	location_flag_t++;
  	    IncrementalPID_init(&RT, KP_R, KI_R, KD_R);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		if(speed_flag_t>2){

		speed_now=motor_speed_R();
		speed_out=IncrementalPID_update(&RT,location_R, speed_now);
		speed_flag_t=0;
		motor_set_R(speed_out);
		}
		if(location_flag_t>4){
		location_R=Y_PID_X_value(40000,motor.speed_R); 
		location_flag_t=0;
		}
		
		
	}


	if(htim->Instance == TIM1){

	if(motor.speed_R-motor.speed_R_last>0){
		overflow_R++;}
	else if(motor.speed_R-motor.speed_R_last<0){{overflow_R--;}

	}
	}
	if(htim->Instance == TIM3){


	if(motor.speed_L-motor.speed_L_last<0){
		overflow_L++;}
	else if(motor.speed_L-motor.speed_L_last>0){{overflow_L--;}

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
 	if(huart ==&huart2) 
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


//	if(huart ==&huart3) //openmv
//  { 
//	 if(RxState3 ==0&&USART3_NewData==0x2C){				
//     USART3_RX_BUF[USART3_RX_STA]=USART3_NewData;
//     RxState3 = 1;			
//			}

//	 else if(RxState3 ==1&&USART3_NewData==0x12){
//     USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//     RxState3 = 2; 
//     }

//     else if(RxState3 ==2){
//     USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//     if(USART3_RX_BUF[USART3_RX_STA-1]== 0x5B){
//			theta=USART3_RX_BUF[USART3_RX_STA-5];
//			cv_x= USART3_RX_BUF[USART3_RX_STA-4];
//			cv_y= USART3_RX_BUF[USART3_RX_STA-3];
//			road_flag = USART3_RX_BUF[USART3_RX_STA-2];	
//			RxState3=3; }
//     }

//     else if(RxState3==3){
//			USART3_RX_STA=0;
//			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
//			RxState3=0;

//     
//     }
//     if(USART3_RX_STA>(USART3_REC_LEN-1)){
//		   USART3_RX_STA=0;
//			 memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
//			  RxState3=0;
//			}

//  }

	if(huart ==&huart3){
		  uint8_t dat;
		  if (rx_cnt++ >= RXSTRSIZE - 1) 
		  {
			  rx_cnt = 0;
			memset(rx_string, 0x00, sizeof(rx_string));
		}
		else
		{
			dat = rx_buff; 

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
					
					case 'A'://VOFA
						target_speed= vofa_float; //keil
						break;
					case 'P':
						KP_R = vofa_float;
						break;
					case 'I':
						KI_R = vofa_float;
						break;
					case 'D':
						KD_R = vofa_float;
						break;
					// case 'B':
					// 	Ki_y_x = vofa_float;
					// 	break;
					// case 'C':
					// 	Kd_y_x = vofa_float;
					// 	break;


					
					}
				}
			}
			memset(rx_string, 0x00, sizeof(rx_string)); 
			rx_cnt = 0;									
		}

  }


	 
		
		

		
		
		
		
  	HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData,1);
//	HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); 
//	HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rx_buff, 1); 

}



		


			
	


	

