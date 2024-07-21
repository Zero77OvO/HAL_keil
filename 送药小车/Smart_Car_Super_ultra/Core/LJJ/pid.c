#include "interrupt.h"
#include "usart.h"
//#include "adcc.h"
//#include "adc.h"
#include "tim.h"
#include "pid.h"

extern float Kp_x_v;  
extern float Ki_x_v;
extern float Kd_x_v;   

extern float Kp_x_x; 
extern float Ki_x_x;
extern float Kd_x_x;

extern float Kp_y_v;  
extern float Ki_y_v;
extern float Kd_y_v;  

extern float Kp_y_x; 
extern float Ki_y_x;
extern float Kd_y_x;





float err_x_v = 0;     
float last_err_x_v = 0;
float err_sum_x_v = 0;
float err_difference_x_v;


float err_x_x = 0;      
float last_err_x_x = 0;
float err_sum_x_x = 0;
float err_difference_x_x;



float err_y_v = 0;      
float last_err_y_v = 0;
float err_sum_y_v = 0;
float err_difference_y_v;

float err_y_x = 0;     
float last_err_y_x = 0;
float err_sum_y_x = 0;
float err_difference_y_x;



float X_v_out = 0;    
float X_x_out = 0;   

float Y_v_out = 0;    
float Y_x_out = 0;   

float last_X_X;
float last_Y_X;



int target_location=30000; 
int target_angle=3456;     


int X_PID_V_value(float measure, float calcu)   
{
    err_x_v = measure - calcu;
    err_sum_x_v += err_x_v;
    // xianfu	
	  // if(err_sum_v > 1000)
		// err_sum_v = 1000;
	  // else if(err_sum_v < -1000)
		// err_sum_v = -1000;
    err_difference_x_v = err_x_v - last_err_x_v;
    X_v_out = Kp_x_v * err_x_v +Kd_x_v * (err_x_v - last_err_x_v)+ Ki_x_v*err_sum_x_v;
    last_err_x_v = err_x_v;

  // if(X_v_out<500){X_v_out=500;}
	// if(X_v_out>2500){X_v_out=2500;}

    return X_v_out;
}

int X_PID_X_value(float measure, float calcu)   
{
    err_x_x = measure - calcu;
    err_sum_x_x += err_x_x;
    // xianfu	
	  if(err_sum_x_x > 500)
		err_sum_x_x = 500;
	  else if(err_sum_x_x < -500)
		err_sum_x_x = -500;
    err_difference_x_x = err_x_x - last_err_x_x;
    X_x_out = Kp_x_x * err_x_x + Kd_x_x * (err_x_x - last_err_x_x)+ Ki_x_x*err_sum_x_x;
    last_err_x_x = err_x_x;
    // if(X_x_out-last_X_X>300||X_x_out-last_X_X<-200){ X_x_out=last_X_X;}
  if(X_x_out<-500){X_x_out=-500;}
	if(X_x_out>500){X_x_out=500;}
    

    return X_x_out;
}


int Y_PID_V_value(float measure, float calcu) 
{
    err_y_v = measure - calcu;
    err_sum_y_v += err_y_v;
    // xianfu

   
    err_difference_y_v = err_y_v - last_err_y_v;
    Y_v_out = Kp_y_v * err_y_v + Kd_y_v * (err_y_v - last_err_y_v)+ Ki_y_v*err_sum_y_v;;
    last_err_y_v = err_y_v;
	// if(Y_v_out<1000){Y_v_out=1000;}
	// if(Y_v_out>3000){Y_v_out=3000;}
	//HAL_Delay(10);
    return Y_v_out;
}

int Y_PID_X_value(float measure, float calcu)  
{
    err_y_x = measure - calcu;
    err_sum_y_x += err_y_x;
    // xianfu
      if(err_sum_y_x > 500)
		err_sum_y_x = 500;
	  else if(err_sum_y_x < -500)
		err_sum_y_x = -500;
    err_difference_y_x = err_y_x - last_err_y_x;
    Y_x_out = Kp_y_x * err_y_x + Kd_y_x * (err_y_x - last_err_y_x)+ Ki_y_x*err_sum_y_x;;
    last_err_y_x = err_y_x;
	if(Y_x_out<-500){Y_x_out=-500;}
	if(Y_x_out>500){Y_x_out=500;}
	//HAL_Delay(10);
    return Y_x_out;
}
//200x200


