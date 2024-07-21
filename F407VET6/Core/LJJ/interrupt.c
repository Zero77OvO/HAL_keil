#include "head_files.h"


//usart1 cam
#define USART1_REC_LEN_1  200
uint8_t USART1_RX_BUF_1[USART1_REC_LEN_1];
uint16_t USART1_RX_STA_1=0;
uint8_t USART1_NewData_1;
uint8_t RxState1_1 = 0;

float x1=0; 
float y1=0;

float last_x1=1; 
float last_y1=1;

float x2=1;
float y2=1;

float x3=1;
float y3=1;

float x4=1;
float y4=1;

int dma_flag=0;
 
float horizon_pid=0;
float vertical_pid=0;





#define USART1_REC_LEN_2  200
uint8_t USART1_RX_BUF_2[USART1_REC_LEN_2];
uint16_t USART1_RX_STA_2=0;
uint8_t USART1_NewData_2;
uint8_t RxState1_2 = 0; 

float x_red=1;
float y_red=1;


#define USART1_REC_LEN_3  200
uint8_t  USART1_RX_BUF_3[USART1_REC_LEN_3];
uint16_t USART1_RX_STA_3;
uint8_t USART1_NewData_3;
uint8_t RxState1_3 = 0; 

float x_green=0;
float y_green=0;

//usart2

#define USART2_REC_LEN  200
uint8_t  USART2_RX_BUF[USART2_REC_LEN];
uint16_t USART2_RX_STA;
uint8_t USART2_NewData;
uint8_t RxState2;

#define USART3_REC_LEN  200
uint8_t  USART3_RX_BUF[USART3_REC_LEN];
uint16_t USART3_RX_STA;
uint8_t USART3_NewData;
uint8_t RxState3;



//usart6 vofa
#define RXSTRSIZE 256		  
uint8_t rx_string[RXSTRSIZE]; 
uint8_t rx_cnt = 0;			  
uint8_t rx_buff;			  
uint8_t RxBuff;
unsigned char shujv[12];
int vofa_i = 0, vofa_I = 0;
float vofa_float;



int mode=3;
int move_flag=0;
int x,y;

int point_step=0;		//记录边
int move_step_total=2;	//每条边细分的步数
int move_step_now=0; 	//记录激光走的点



#define MAX_POINTS 10  // 最大历史坐标数

// 存储红点的历史坐标
int x_history[MAX_POINTS];
int y_history[MAX_POINTS];
int num_points = 0;  // 当前历史坐标数

// 添加新坐标到历史记录中
void add_point(int new_x, int new_y) {
    // 检查是否需要添加新点
    if (num_points > 0) {
        int last_x = x_history[num_points - 1];
        int last_y = y_history[num_points - 1];
        if (abs(new_x - last_x) < 3 && abs(new_y - last_y) < 3) {
            return;  // 移动不足3个单位，不添加新点
        }
    }

    // 如果历史记录已满，移除最末端的一个数字
    if (num_points >= MAX_POINTS) {
        for (int i = 0; i < MAX_POINTS - 1; i++) {
            x_history[i] = x_history[i + 1];
            y_history[i] = y_history[i + 1];
        }
        num_points = MAX_POINTS - 1;  // 保持最大历史坐标数
    }

    // 在数组末端存储新数字
    x_history[num_points] = new_x;
    y_history[num_points] = new_y;
    num_points++;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance == TIM2) // 20ms
{ 	
	
	
	
	IncrementalPID ver;
	IncrementalPID hor;
	if(mode==1){
		//我用的增量式，你可以先用位置式调一下，差别不是很大
		if(x1!=0&&x_green!=0){
			
			if(point_step==0){

			IncrementalPID_init(&ver, 0.1, 0.0, 0.5);// 设置PID参数
			IncrementalPID_init(&hor, 0.1, 0.0, 0.5);// 设置PID参数

			vertical_pid = IncrementalPID_update(&ver, y1, y_green);
			horizon_pid  = IncrementalPID_update(&hor, x1, x_green);
			//pid限幅
			if(vertical_pid>10){vertical_pid=10;}
			if(vertical_pid<-10){vertical_pid=-10;}
			if(horizon_pid>10){horizon_pid=10;}
			if(horizon_pid<-10){horizon_pid=-10;}

		}

			if(point_step>=1){
			calculate_inner_border(x1,y1,x2,y2,x3,y3,x4,y4,2);

			IncrementalPID_init(&ver, 0, 0, 0.5);// 设置PID参数
			IncrementalPID_init(&hor, 0, 0, 0.5);// 设置PID参数

			vertical_pid = IncrementalPID_update(&ver, y, y_green);
			horizon_pid  = IncrementalPID_update(&hor, x, x_green);

			if(vertical_pid>8){vertical_pid=8;}
			if(vertical_pid<-8){vertical_pid=-8;}
			if(horizon_pid>8){horizon_pid=8;}
			if(horizon_pid<-8){horizon_pid=-8;}
		}
		
		// printf("%f %f \r\n", vertical_pid,horizon_pid);	
		}
	}

	if(mode==3){
		if(x_red!=0&&x_green!=0){
			add_point(x_red,y_red);

			IncrementalPID_init(&ver, 0.01, 0, 0.5);// 设置PID参数
			IncrementalPID_init(&hor, 0.01, 0, 0.5);// 设置PID参数

			vertical_pid = IncrementalPID_update(&ver, y_red, y_green);
			horizon_pid  = IncrementalPID_update(&hor, x_red, x_green);

			
			// vertical_pid = IncrementalPID_update(&ver, y_red, y_green);
			// horizon_pid  = IncrementalPID_update(&hor, x_red, x_green);
			//pid限幅
			if(vertical_pid>10){vertical_pid=10;}
			if(vertical_pid<-10){vertical_pid=-10;}
			if(horizon_pid>10){horizon_pid=10;}
			if(horizon_pid<-10){horizon_pid=-10;}
			// printf("%f %f \r\n", vertical_pid,horizon_pid);	
	}
	}
	
	}

	if(htim->Instance == TIM5) //20ms
{ 
	
	IncrementalPID ver;
	IncrementalPID hor;

	if(mode==3){
		
		if(x_red!=0&&x_green!=0){

		Servo_pid_move(&ver, &hor, y_red, y_green, x_red,x_green);
		// Servo_pid_move(&ver, &hor, y_red, y_green, x_red,x_green);

		}
		}
	if(mode==2){Servo_start();}

	if(mode==1){
	//运动去第一个点
	if(move_flag==0){
		if(x1!=0&&x_green!=0){

		if(point_step==0){

			Servo_pid_move(&ver, &hor, iy1, y_green, ix1,x_green);


			if(fabs(vertical_pid)<=3&&fabs(horizon_pid)<=3){point_step=1;}


		}
		// 1-2
		if(point_step==1){

			//将一个边分成很多个点，细分，
			x=(ix2-ix1)/move_step_total*move_step_now+ix1;
			y=(iy2-iy1)/move_step_total*move_step_now+iy1;

			//舵机移动
			Servo_pid_move(&ver, &hor, y, y_green, x,x_green);

			if(fabs(y-y_green)<=3&&fabs(x-x_green)<3){move_step_now++;}

			if(move_step_now>move_step_total){move_step_now=0;point_step=2;}
		}
		if(point_step==2){
			
			x=(ix3-ix2)/move_step_total*move_step_now+ix2;
			y=(iy3-iy2)/move_step_total*move_step_now+iy2;

			Servo_pid_move(&ver, &hor, y, y_green, x,x_green);

			if(fabs(vertical_pid)<=3&&fabs(horizon_pid)<=3){move_step_now++;}

			if(move_step_now>move_step_total){move_step_now=0;point_step=3;}
		}


		if(point_step==3){
			
			x=(ix4-ix3)/move_step_total*move_step_now+ix3;
			y=(iy4-iy3)/move_step_total*move_step_now+iy3;

			Servo_pid_move(&ver, &hor, y, y_green, x,x_green);

			if(fabs(vertical_pid)<=3&&fabs(horizon_pid)<=3){move_step_now++;}

			if(move_step_now>move_step_total){move_step_now=0;point_step=4;}
		}
		if(point_step==4){
			
			
			x=(ix1-ix4)/move_step_total*move_step_now+ix4;
			y=(iy1-iy4)/move_step_total*move_step_now+iy4;

			
			Servo_pid_move(&ver, &hor, y, y_green, x,x_green);

			if(fabs(vertical_pid)<=3&&fabs(horizon_pid)<=3){move_step_now++;}

			if(move_step_now>move_step_total){move_step_now=0;point_step=5;}
		}

		//归中
		if(point_step==5){
		
			Servo_reset();
				
		}	
		}
		}	




	
		
	}	
}


}








void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
	if(huart ==&huart1) //k210
	 { 
		
		if(x1==last_x1&&y1==last_y1){dma_flag=1;}
	
 		USART1_NewData_2=USART1_NewData_3=USART1_NewData_1;

		if(dma_flag==0)	{

			if(RxState1_1 ==0&&USART1_NewData_1==0x1A){
				USART1_RX_BUF_1[USART1_RX_STA_1]=USART1_NewData_1;
				RxState1_1 = 1;
								}

				else if(RxState1_1 ==1&&USART1_NewData_1==0x2B){
				USART1_RX_BUF_1[USART1_RX_STA_1++]=USART1_NewData_1;
				RxState1_1 = 2;
				}

				else if(RxState1_1 ==2){
				USART1_RX_BUF_1[USART1_RX_STA_1++]=USART1_NewData_1;
				if(USART1_RX_BUF_1[USART1_RX_STA_1-1]== 0x3C){
					
						x1 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-9];
						y1 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-8];
						x2 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-7];
						y2 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-6];
						x3 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-5];
						y3 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-4];
						x4 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-3];
						y4 = (float) USART1_RX_BUF_1[USART1_RX_STA_1-2];

						last_x1=x1;
						last_y1=y1;
								RxState1_1=3; }
				}
				else if(RxState1_1==3){
								USART1_RX_STA_1=0;
								memset(USART1_RX_BUF_1,0,sizeof(USART1_RX_BUF_1));
								RxState1_1=0;
				}
				if(USART1_RX_STA_1>(USART1_REC_LEN-1)){
							USART1_RX_STA_1=0;
								memset(USART1_RX_BUF_1,0,sizeof(USART1_RX_BUF_1));
									RxState1_1=0;
					}
			}
			
		//red
		if(RxState1_2 ==0&&USART1_NewData_2==0x2B){
			USART1_RX_BUF_2[USART1_RX_STA_2]=USART1_NewData_2;
			RxState1_2 = 1;
						}

		else if(RxState1_2 ==1&&USART1_NewData_2==0x2C){
		USART1_RX_BUF_2[USART1_RX_STA_2++]=USART1_NewData_2;
		RxState1_2 = 2;
		}

		else if(RxState1_2==2){
		USART1_RX_BUF_2[USART1_RX_STA_2++]=USART1_NewData_2;
		if(USART1_RX_BUF_2[USART1_RX_STA_2-1]== 0x25){

				x_red = (float) USART1_RX_BUF_2[USART1_RX_STA_2-3]*2;
				y_red = (float) USART1_RX_BUF_2[USART1_RX_STA_2-2]*2;
						RxState1_2=3; }
		}
		else if(RxState1_2==3){
						USART1_RX_STA_2=0;
						memset(USART1_RX_BUF_2,0,sizeof(USART1_RX_BUF_2));
						RxState1_2=0;
		}
		if(USART1_RX_STA_2>(USART1_REC_LEN_2-1)){
					USART1_RX_STA_2=0;
						memset(USART1_RX_BUF_2,0,sizeof(USART1_RX_BUF_2));
							RxState1_2=0;
			}		



	//green
			
		if(RxState1_3==0&&USART1_NewData_3==0x3A){
		USART1_RX_BUF_3[USART1_RX_STA_3]=USART1_NewData_3;
		RxState1_3= 1;
						}

		else if(RxState1_3==1&&USART1_NewData_3==0x4C){
		USART1_RX_BUF_3[USART1_RX_STA_3++]=USART1_NewData_3;
		RxState1_3= 2;
		}

		else if(RxState1_3==2){
		USART1_RX_BUF_3[USART1_RX_STA_3++]=USART1_NewData_3;
		if(USART1_RX_BUF_3[USART1_RX_STA_3-1]== 0x5D){



				x_green = (float) USART1_RX_BUF_3[USART1_RX_STA_3-3]*2;
				y_green = (float) USART1_RX_BUF_3[USART1_RX_STA_3-2]*2;
						RxState1_3=3; }
		}
		else if(RxState1_3==3){
						USART1_RX_STA_3=0;
						memset(USART1_RX_BUF_3,0,sizeof(USART1_RX_BUF_3));
						RxState1_3=0;
		}
		if(USART1_RX_STA_3>(USART1_REC_LEN_3-1)){
					USART1_RX_STA_3=0;
						memset(USART1_RX_BUF_3,0,sizeof(USART1_RX_BUF_3));
							RxState1_3=0;
			}		



  }	
	
	 //bluetooth
  	if(huart ==&huart2) //����
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

//  			target = USART2_RX_BUF[USART2_RX_STA-2]-48;			
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
  	 else if(RxState2 ==2)   //�����쳣
  	 {
  		USART2_RX_STA=0;
  		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
  		RxState2=0;
  		}		
      }

//openmv
 	if(huart ==&huart3) 
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
				
// 			theta=USART3_RX_BUF[USART3_RX_STA-5];
// 			cv_x= USART3_RX_BUF[USART3_RX_STA-4];
// 			cv_y= USART3_RX_BUF[USART3_RX_STA-3];
// 			road_flag = USART3_RX_BUF[USART3_RX_STA-2];	
				
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


	 
		
		

		
		
		

	HAL_UART_Receive_DMA(&huart1,(uint8_t *)&USART1_NewData_1,1);
	// HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); 
	// HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
	// HAL_UART_Receive_IT(&huart6, (uint8_t *)&rx_buff, 1); 

}



		


			
	


	

