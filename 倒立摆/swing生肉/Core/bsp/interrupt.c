#include "interrupt.h"
#include "usart.h"
#include "adcc.h"
#include "adc.h"
#include "tim.h"
#include "pid.h"

int time_1s = 0;
int flag_stop = 0;
extern int flag_init;

extern float v_out;
extern float x_out;

int time_500ms = 0;
int flag_500ms = 0;
int test_flag = 0;
int flag_500ms2 = 0;
int time_500ms2 = 0;
int num_counter = 30000;

int start_mode =-188;

int raw_now = -1;


int alarm_left = 0;
int alarm_right = 0;

int a = 0;

int raw_filter;


extern int timer_sign;
extern int c,b;
int t;
int stat=0;

int true_speed=0;
float t1;
float t2;

extern int target_location;
extern int target_angle;

struct keys {
    int key_sta;
	  int key_judge;
    
};
int t_angle;
int t_location;
int location;

int t_speed;

int speed1;
int speed2;
int speed_end;

int speed_store;
	
int stat1=1;int stat2=1;

struct keys key[4]={0,0,0,0};

uint16_t timer2_counter = 0;	

extern int flag_jc12;
extern int flag_jc3;
extern int flag_fh;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	
	
	
	
	  if (htim->Instance == TIM4)
    {  
		 __HAL_TIM_CLEAR_FLAG(&htim4, TIM_FLAG_UPDATE);

		 timer_sign=!timer_sign;
			b++;
		
		
		}
	  if (htim->Instance == TIM3)
		{ t_angle++;t_location++;t_speed++;
			
			
			raw_now=(int)(get_adc(&hadc1) * 1000);
			raw_filter = moveAverageFilter(raw_now);
			
		
			
			//PID
			if(speed_end<-10&&speed_end>10){stat=1;}
			if(t_angle==5){ v_out=0.8*vertical_PID_value((raw_filter-location), target_angle);t_angle=0;}
			
			
			if(t_location==50){
				
				speed1=__HAL_TIM_GET_COUNTER(&htim2);
   			speed_end=(speed1-speed2);speed2=speed1;
        
			  

				
				if((speed_end<2&&speed_end>-2)){target_location=speed1;}
				
				if(speed1<29000){stat1 = 0;}
					
				if(stat1==0){
				target_angle=3446;}
				
			
				if(speed1>29500&&speed1<30500){target_angle=3457;stat1=1;stat2=1;}
				
				if(speed1>31000){stat2 = 0;}
				if(stat2==0){
				target_angle=3466;}

	
				location= location_PID_value((num_counter), target_location);
				t_location=0;
				
				 				
			}

			      if (start_mode == 2||flag_jc3==1)
            { 
							
              if (flag_stop == 0 && flag_init == 0)
                {    
										if (v_out < 40 && v_out > 0)
											v_out = 40;
										if (v_out > -40 && v_out < 0)
												v_out = -40;


										if(stat==0||stat==1){
											

										
									 if (v_out > 0)
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, v_out);
                    }
                    if (v_out < 0)
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -v_out);

										}

                }
            }
							
		     }
		
		
		}
    if (htim->Instance == TIM1)
    { 
			 

        num_counter = __HAL_TIM_GET_COUNTER(&htim2);
			
			  true_speed=30000-__HAL_TIM_GET_COUNTER(&htim2);
		  	
	
        if (num_counter > 32000 && a == 1) /////////////////////////////////边界保护
        {
            alarm_right = 1;
            start_mode = 1;
        }

        if (num_counter < 27000 && a == 1)
        {
            alarm_left = 1;
            start_mode = 1;
        }
        if (num_counter > 29000 && num_counter < 31000)
        {
				
            alarm_left = 0;
            alarm_right = 0;
        } /////////////////////////////////////////////////////////////////////////

        if (flag_init == 0 && flag_stop == 0) ////////////////运动
        {
					
					if(start_mode==-1){
						c++;
					if(c==120){ HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
                    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 400);}
					if(c==240){
										HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
                     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
                    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 400);}
					if(c==360){start_mode=0;c=0;}
					
					
					}
					
										

					
					
            if (start_mode == 0) ///////////////////////////////////////////第一阶段///超级起摆
            {
                if ((raw_filter > 100&& raw_filter < 200)||(raw_filter > 2900&& raw_filter < 3000)) //////////// 第二阶段低速起摆
                {
                    start_mode = 1;
                }
                //////////////////////////////////////////////////////////////////////////////////////
                if (raw_filter > 1600 && raw_filter < 3560) /////////////////////////杆在左侧
                {
                    if (alarm_left == 0) //////////////////////////////下落趋势向→→→→→→→→走
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 300);
                    }
                }
                else /////////////////杆在右侧
                {
                    if (alarm_right == 0) ////////////////////////////下落趋势向←←←←走
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 300);
                    }
                }
            }
            if (start_mode == 1)
            {
                if (raw_filter > 3250 && raw_filter < 3450) ///////////////////进入第三阶段
                {
                    start_mode = 2;
                }

                if (raw_filter > 1600 && raw_filter < 3560)  /////////////////////////杆在左侧
                {
                    if (alarm_left == 0) //////////////////////////////下落趋势向→→→→→→→→走
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 170);
                    }
                }
                else /////////////////杆在右侧
                {
                    if (alarm_right == 0) ////////////////////////////下落趋势向←←←←走
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 170);
                    }
                }
            }
						
						
						
						 if (flag_jc12 == 1)
            {

                if (raw_filter > 1600 && raw_filter < 3560)  /////////////////////////杆在左侧
                {
                    if (alarm_left == 0) //////////////////////////////下落趋势向→→→→→→→→走
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 170);
                    }
                }
                else /////////////////杆在右侧
                {
                    if (alarm_right == 0) ////////////////////////////下落趋势向←←←←走
                    {
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
                        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 170);
                    }
                }
            }






        if (++time_1s == 100)
        {
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
            time_1s = 0;
        }
        a = 1;
    }
}

	}

	
char rxdatas[30];
uint8_t rxdata;
unsigned char rx_pointer;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    rxdatas[rx_pointer++] = rxdata - 48;
	 HAL_UART_Receive_IT(&huart3, &rxdata, 1);

}
