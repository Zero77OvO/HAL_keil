#include "interrupt.h"
#include "string.h"
#include "usart.h"

//#include "adc.h"
#include "tim.h"
#include "pid.h"
#include "vofa.h"





float x_pid_v_out;
float x_pid_x_out=0;
float y_pid_v_out;
float y_pid_x_out=0;



float Kp_x_v=0.0;  
float Ki_x_v=0.0;
float Kd_x_v=0.0;   

float Kp_x_x=7.5; 
float Ki_x_x=0.35;
float Kd_x_x=70.0;

// float Kp_x_x=0.0; 
// float Ki_x_x=0.0;
// float Kd_x_x=0.0;

float Kp_y_v=0.0;  
float Ki_y_v=0.0;
float Kd_y_v=0.0;   

// float Kp_y_v=0.0;  
// float Ki_y_v=0.0;
// float Kd_y_v=0.0;  

float Kp_y_x=7.0; 
float Ki_y_x=0.35;
float Kd_y_x=70.0;



          //x  30   81  117
          //y  12   53  87

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	//100ms
	if (htim->Instance == TIM2)
    { 
    
		
		}
	//10ms
	if (htim->Instance == TIM8)
    { 
    
		
		}		
		
	//1ms
	if (htim->Instance == TIM9)
	{ 


	}
		





}




//usart1 bluetooth

uint8_t USART1_RX_BUF[USART1_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART1_RX_STA=0;//接收状态标记//bit15：接收完成标志，bit14~0：接收到的有效字节数目
uint8_t USART1_NewData;//当前串口中断接收的1个字节数据的缓存

uint8_t RxState = 0; 
char num;
char num2;
char num3;



//usart2 vofa
#define RXSTRSIZE 256		  
uint8_t rx_string[RXSTRSIZE]; 
uint8_t rx_cnt = 0;			  
uint8_t rx_buff;			  
uint8_t RxBuff;
unsigned char shujv[12];
int vofa_i = 0, vofa_I = 0;
float vofa_float;



//usart3 raspi



#define USART3_REC_LEN  200//定义USART2最大接收字节数

uint8_t  USART3_RX_BUF[USART3_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.末字节为校验和
uint16_t USART3_RX_STA;//接收状态标记
uint8_t USART3_NewData;//当前串口中断接收的1个字节数据的缓存


uint8_t RxState3 = 0; 
char pinum;
char pinum2;
char pinum3;
char pinum4;
char pinum5;






void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{  //vofa
		 
   if(huart ==&huart2){
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
		
	
	 //bluetooth
  if(huart ==&huart1) 
 { 
	 if(RxState ==0){
     USART1_RX_BUF[USART1_RX_STA++]=USART1_NewData; 					
     USART1_RX_STA++; 
     RxState = 1;			
	}
	 else if(RxState ==1){
     USART1_RX_BUF[USART1_RX_STA++]=USART1_NewData; 
	 	if(USART1_RX_STA >0||USART1_RX_BUF[USART1_RX_STA-1]== 0x12)
		 {

//			target = USART1_RX_BUF[USART1_RX_STA-3]-48;			
			//num2 = USART1_RX_BUF[USART1_RX_STA-4];
			//	num3 = USART1_RX_BUF[USART1_RX_STA-5];	
				
			USART1_RX_STA=0;
			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
			RxState=2;
				
		}	
			}
			
	 if(USART1_RX_STA>(USART1_REC_LEN-1)){
		memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
		USART1_RX_STA=0;	
	  }
	 else if(RxState ==2)   //接收异常
	 {
		USART1_RX_STA=0;
		memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
		RxState=0;
		}		
   }
 	
			
	 //raspi
	  if(huart ==&huart3)
  { 
			if(RxState3 ==0){
     USART3_RX_BUF[USART3_RX_STA&0X7FFF]=USART3_NewData; 					
     USART3_RX_STA++; 
     RxState3 = 1;			
			}
			else if(RxState3 ==1){
     USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData; 

				
				
     if(USART3_RX_STA>(USART3_REC_LEN-1)){
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			USART3_RX_STA=0;
			}
			
			if(USART3_RX_BUF[USART3_RX_STA-1]== 0x0a&&USART3_RX_STA>16) //计数器好像是假的，明天测测阈值是多少
			{
				
			 pinum = USART3_RX_BUF[USART3_RX_STA-6];			
			pinum2 = USART3_RX_BUF[USART3_RX_STA-5];
			pinum3 = USART3_RX_BUF[USART3_RX_STA-4];
     		pinum4 = USART3_RX_BUF[USART3_RX_STA-3];
			pinum5 = USART3_RX_BUF[USART3_RX_STA-2];	
				
			USART3_RX_STA=0;
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			RxState3=0;
				
			}
		/*	else if(USART3_RX_BUF[USART3_RX_STA-1]== 0x0a&&USART3_RX_STA>15)
			{
				
				
			pinum = USART3_RX_BUF[USART3_RX_STA-5];
			pinum2 = USART3_RX_BUF[USART3_RX_STA-4];
     pinum3 = USART3_RX_BUF[USART3_RX_STA-3];
			pinum4 = USART3_RX_BUF[USART3_RX_STA-2];	
				
			USART3_RX_STA=0;
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			RxState3=0;
				
			}
   	else if(USART3_RX_BUF[USART3_RX_STA-1]== 0x0a&&USART3_RX_STA>14)
			{
				
				
			pinum = USART3_RX_BUF[USART3_RX_STA-4];
			pinum2 = USART3_RX_BUF[USART3_RX_STA-3];
     pinum3 = USART3_RX_BUF[USART3_RX_STA-2];
			
				
			USART3_RX_STA=0;
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			RxState3=0;
				
			}*/
			
			
			}
			
			if(USART3_RX_STA>(USART3_REC_LEN-1)){
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			USART3_RX_STA=0;
			
			}
			else if(RxState3 ==2)   //接收异常
			{
				USART3_RX_STA=0;
			  memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
				}
			
			
			
   }

	 
		
		
//    if(huart ==&huart2) //openmv
//   { 
//	 if(RxState3 ==0&&USART3_NewData==0x2C){				
//      USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//      RxState3 = 1;			
//			}

//	 else if(RxState3 ==1&&USART3_NewData==0x12){
//      USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//      RxState3 = 2; 
//      }

//      else if(RxState3 ==2){
//      USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//      if(USART3_RX_BUF[USART3_RX_STA-1]== 0x5B){
//      		x_ball = USART3_RX_BUF[USART3_RX_STA-5];
//			y_ball = USART3_RX_BUF[USART3_RX_STA-3];	
//			RxState3=3; }
//      }

//      else if(RxState3==3){
//			USART3_RX_STA=0;
//			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
//			RxState3=0;

//      
//      }
//      if(USART3_RX_STA>(USART3_REC_LEN-1)){
//		   USART3_RX_STA=0;
//			 memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
//			  RxState3=0;
//			}



//   }
		
		
		
		
  HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData,1);
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_buff, 1);  
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
}	
		


			
	


	

