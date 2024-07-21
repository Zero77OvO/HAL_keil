#include "interrupt.h"
#include "string.h"
#include "usart.h"
#include "adcc.h"
//#include "adc.h"
#include "tim.h"
#include "pid.h"

int time_1s = 0;
int tx_pid;
int ty_pid;

int time_x_v_out;
int time_x_x_out;
int time_y_v_out;
int time_y_x_out;


float x_pid_v_out;
float x_pid_x_out=0;
float y_pid_v_out;
float y_pid_x_out=0;

extern int x_ball;
extern int y_ball;

int x_ball_aver;
int y_ball_aver;

float v_x_ball;
float v_y_ball;


int x_x;
int y_x;

int time_y_v;

float Kp_x_v=0.0;  
float Ki_x_v=0.0;
float Kd_x_v=0.0;   


// float Kp_x_x=3.5; 
// float Ki_x_x=0.35;
// float Kd_x_x=50.0;

float Kp_x_x=2.0; 
float Ki_x_x=0.25;
float Kd_x_x=50.8;

float Kp_y_v=0.0;  
float Ki_y_v=0.0;
float Kd_y_v=0.0;   

// float Kp_y_v=0.0;  
// float Ki_y_v=0.0;
// float Kd_y_v=0.0;  

float Kp_y_x=2; 
float Ki_y_x=0.25;
float Kd_y_x=56.8;

// float Kp_y_x=0.0; 
// float Ki_y_x=0.0;
// float Kd_y_x=0.0;

int target=5;

int target_flag_x=0;
int target_flag_y=0;

int PID_flag_x=0;
int PID_flag_y=0;

int target_x;
int target_y;

int move_flag=0;


          //x  30   81  117
          //y  12   53  87

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	
	
	

	  if (htim->Instance == TIM4)
    { tx_pid++;
      if(ty_pid>=1){

              y_ball_aver=averagelocation_y(y_ball);

              // if (x_ball-x_ball_2>2&&x_ball_2!=0)
              // {
              //   x_ball=x_ball_2;
              // }
              // if (y_ball-y_ball_2>2&&y_ball_2!=0)
              // {
              //   y_ball=y_ball_2;
              // }
              // x_ball_2=x_ball;
              // y_ball_2=y_ball;
              

          // x_pid_v_out=X_PID_V_value((0),v_x_ball);
          // y_pid_v_out=Y_PID_V_value((0),v_y_ball);

          x_pid_x_out=X_PID_X_value((target_x), x_ball);
          y_pid_x_out=Y_PID_X_value((target_y), y_ball_aver);
          // x_pid_x_out=averageFilter( x_pid_x_out);
          // y_pid_x_out=averageFilter( y_pid_x_out);
          // if(y_pid_v_out>2500){y_pid_v_out=2500;}
          // if(y_pid_v_out<1000){y_pid_v_out=1000;}
      

          ty_pid=0;}
      // if(PID_flag_x==1){
      //   Kp_x_x=3.0; 
      //   Ki_x_x=0.35;
      //   Kd_x_x=50.0;}
      // else{
      //   Kp_x_x=8.5; 
      //   Ki_x_x=0.55;
      //   Kd_x_x=70.0;


      //   }  
    
		
		}
		
		
	
	  if (htim->Instance == TIM3)
		{ ty_pid++;time_x_v_out++;time_x_x_out++;time_y_x_out++;time_y_v_out++;
          //x  30   81  117
          //y  12   53  87
          //
      // if(time_x_v_out>=1){__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1080+x_pid_v_out);time_x_v_out=0;}  
      if(time_x_x_out>=1&&target_flag_x==0){__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1040+x_pid_x_out);time_x_x_out=0;move_flag=1;} 
      // if(time_y_v_out>=1){__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 1500-y_pid_v_out);time_y_v_out=0;}      
      if(time_y_x_out>=1&&target_flag_y==0){__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1520-y_pid_x_out);time_y_x_out=0;move_flag=0;}                
                                                                                                  
                                                                                                    

 // 500 45    1000 90     1500 2000 
 //1000 45 1250  1500 90 2000 2500

 // 42 106 178
 // 41 106 175
		}
		
    if (htim->Instance == TIM1)
    {  
       time_y_v++;time_x_v_out++;
       //¼ÆËãËÙ¶È
     if(time_y_v>=10){
      v_x_ball=(x_ball-x_x);x_x=x_ball;
      v_y_ball=(y_ball-y_x);y_x=y_ball;
     
      time_y_v=0;} 

         if(target==1){target_x=50;target_y=41;}
         if(target==2){target_x=106;target_y=45;}
         if(target==3){target_x=178;target_y=41;}
         if(target==4){target_x=60;target_y=106;}
         if(target==5){target_x=106;target_y=106;}
         if(target==6){target_x=178;target_y=106;}
         if(target==7){target_x=60;target_y=178;}
         if(target==8){target_x=126;target_y=155;}
         if(target==9){target_x=178;target_y=178;}
         if(x_ball-target_x>-3&&x_ball-target_x<3){target_flag_x=1;x_pid_x_out=0;}else{target_flag_x=0;}
         if(y_ball-target_y>-3&&y_ball-target_y<3){target_flag_y=1;y_pid_x_out=0;}else{target_flag_y=0;}
         if(x_ball-target_x>-10&&x_ball-target_x<10){PID_flag_x=1;}else{PID_flag_x=0;}
         if(y_ball-target_y>-10&&y_ball-target_y<10){PID_flag_y=1;}else{PID_flag_y=0;}
     
			 






        if (++time_1s == 100)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            time_1s = 0;
        }
        
    }




}




	
		

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// { 
  
  
    
//     if(huart ==&huart3)
//    { 
// 			if(RxState3 ==0&&USART3_NewData==0x2C){				
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       RxState3 = 1;			
// 			}

// 			else if(RxState3 ==1&&USART3_NewData==0x12){
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       RxState3 = 2; 
//       }

//       else if(RxState3 ==2){
//       USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData;
//       if(USART3_RX_BUF[USART3_RX_STA-1]== 0x5B){
//       x_ball = USART3_RX_BUF[USART3_RX_STA-5];
// 			y_ball = USART3_RX_BUF[USART3_RX_STA-3];	
// 			RxState3=3; }
//       }

//       else if(RxState3==3){
// 			USART3_RX_STA=0;
// 			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
// 			RxState3=0;

      
//       }
//       if(USART3_RX_STA>(USART3_REC_LEN-1)){
// 		   USART3_RX_STA=0;
// 			 memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
// 			  RxState3=0;
// 			}



//    }
//    HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
   
//    }
   
			
	


	
//char rxdatas[30];
//uint8_t rxdata;
//unsigned char rx_pointer;

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    rxdatas[rx_pointer++] = rxdata - 48;
//	 HAL_UART_Receive_IT(&huart3, &rxdata, 1);

//}
