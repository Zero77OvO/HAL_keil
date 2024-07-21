#include "head_files.h"

int step=1;



void Servo_location_pid_cal(float target_x,float target_y,float stat_x,float stat_y){

	horizon_pid=X_PID_X_value(target_x,stat_x);
	vertical_pid=Y_PID_X_value(target_y,stat_y);
	
}

void Servo_incremental_pid_cal(IncrementalPID *ver, IncrementalPID *hor, float target_x,float target_y,float stat_x,float stat_y){


	
}

void move_step(){ //计算pid 切换四个点

	int location_pid_flag=0;


	
	if(location_pid_flag==2){
	if(point_step==1){
		
		Servo_location_pid_cal(x1,y1,x_green,y_green);
		if(fabs(x1-x_green)<=8){point_step=2;}
	}
	 if(point_step==2){
		
		Servo_location_pid_cal(x2,y2,x_green,y_green);
		if(fabs(x2-x_green)<=8){point_step=3;}
	}
	if(point_step==3){
		
		Servo_location_pid_cal(x3,y3,x_green,y_green);
		if(fabs(x3-x_green)<=8){point_step=4;}
	}
	if(point_step==4){
		
		Servo_location_pid_cal(x4,y4,x_green,y_green);
		if(fabs(x4-x_green)<=8){point_step=5;}
	}
	if(point_step==5){
	
		Servo_reset();
			
	}	
	
}
	
}

  
  

void horizon_move(int pwm){
	
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,pwm);
}

void vertical_move(int pwm){
	
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,pwm);
}




void PWM_work(void)
{ 		int f=1;
		if(f==1){
		for(int i =0;i<3000;i++){
				horizon_move(i);
				vertical_move(i);
		if(i==2900){f=2;}
			}}
		if(f==2){
		for( int i =3000;i>0;i--){
				horizon_move(i);
				vertical_move(i);
		if(i==10){f=1;}}
			}
}

//舵机复位
void Servo_reset(){
	
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3,585);
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4,425);
	
}











int t=0;

float i=595; 
float  j=445;
int x_green_last;
int y_green_last;

float hor_out;
float ver_out;

//舵机运动
void Servo_pid_move(IncrementalPID *ver, IncrementalPID *hor, float y1, float y_green, float x1, float x_green) {
	


	
	if(mode==3){
	if(horizon_pid!=0&&vertical_pid!=0&&x1!=0&&x_green!=0){


		t++;

///////////////卡尔曼滤波//////////
		KFPTypeS_Struct kfpVar = {
        .P = 0.020, 
        .G = 0, 
        .Q = 0.001, 
        .R = 1.000, 
        .Output = 0 
    };

	KFPType_Struct kfp = &kfpVar;
		hor_out= KalmanFilter(kfp,horizon_pid);
		ver_out=KalmanFilter(kfp, vertical_pid);
///////////////卡尔曼滤波//////////

		//pid运算20次，舵机执行一次 控制周期
		if(t==12){
		

		//没用到
		x_green_last=x_green;
		y_green_last=y_green;

		//如果pid为正则 pwm ++ 或者 -- 	
		if(horizon_pid>0){
			i-=1;
		}
		if(horizon_pid<0){
			i+=1;
		}
		if(vertical_pid>0){
			j+=1;
		}
		if(vertical_pid<0){
			j-=1;
		}

		//运动控制
		if(fabs(horizon_pid)>1){
		horizon_move(i-hor_out);}
		if(fabs(vertical_pid)>1){
		vertical_move(j+ver_out);}


		
		t=0;
		}

		if(j>675||j<340){j=425;}

		if(i<500||i>680){i=595;}	
	

	
}
}

	if(mode==1){
	if(horizon_pid!=0&&vertical_pid!=0&&x1!=0&&x_green!=0){


		t++;

///////////////卡尔曼滤波//////////
		KFPTypeS_Struct kfpVar = {
        .P = 0.020, 
        .G = 0, 
        .Q = 0.001, 
        .R = 1.000, 
        .Output = 0 
    };

	KFPType_Struct kfp = &kfpVar;
		hor_out= KalmanFilter(kfp,horizon_pid);
		ver_out=KalmanFilter(kfp, vertical_pid);
///////////////卡尔曼滤波//////////

		//pid运算20次，舵机执行一次 控制周期
		if(t==8){
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);

		//没用到
		x_green_last=x_green;
		y_green_last=y_green;

		//如果pid为正则 pwm ++ 或者 -- 	
		if(horizon_pid>0){
			i-=1;
		}
		if(horizon_pid<0){
			i+=1;
		}
		if(vertical_pid>0){
			j+=1;
		}
		if(vertical_pid<0){
			j-=1;
		}

		//运动控制
		if(fabs(horizon_pid)>1){
		horizon_move(i-hor_out);}
		if(fabs(vertical_pid)>1){
		vertical_move(j+ver_out);}		
		
		
		t=0;
		}

		if(j>675||j<340){j=425;}

		if(i<500||i>680){i=595;}	
	

	
}
}




}







//定点 打靶
void Servo_start(){  
	int i=660;int j =425;
	
	
	if(step==1){		
		for(i=660,j=505;i>=525;t++){
			
			if(t==30000){i-=1,j--;t=0;}
			
			if(j<=495){j=495;}
			
			vertical_move(j);			
			horizon_move(i);
			
		
		}
		
			if(i<=525){
			step=2;
			
			}
		
	}
	
	if(step==2){
		
		for(i=525,j =495;j>=382;t++){
			
			if(t==30000){i++,j-=1;t=0;}
			
			if(i>=530){i=530;}
			
			horizon_move(i);
			vertical_move(j);	
						
		}
		
		if(j<=382){
				step=3;
			}
	}
	
	if(step==3){
		
		
	for(i=530,j=382;i<=670;t++){
		
		if(t==30000){i+=1,j-=1;t=0;}
			if(j<360){j=360;}
			
			horizon_move(i);
			vertical_move(j);
					
			
	
		}

		if(i>=670){
			step=4;
			}
	}
	
	if(step==4){
		
	for(i=670,j=360;j<=505;t++){
		
		if(t==30000){i-=1,j+=1;t=0;}
		
			if(i<=660){i=660;}
			
			horizon_move(i);
			vertical_move(j);
					
			
	
		}

		if(j>=505){
			step=5;
			}
	}	
		
		
	
		if(step==5){
			
			
		Servo_reset();
			
	}	
	


}

