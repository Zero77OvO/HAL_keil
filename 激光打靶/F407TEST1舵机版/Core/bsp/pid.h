 #ifndef _PID_H
 #define _PID_H


float X_PID_V_value(float measure, float calcu);
float X_PID_X_value(float measure, float calcu);
float Y_PID_V_value(float measure, float calcu);
float Y_PID_X_value(float measure, float calcu);






typedef struct {
    float kp;
    float ki;
    float kd;
    
    float pwm;
    float last_pwm;
    float error;
    float last_error;
    float integral;
} IncrementalPID;


void IncrementalPID_init(IncrementalPID *pid, float kp, float ki, float kd);
float IncrementalPID_update(IncrementalPID *pid, float setpoint, float current_value);




extern float Kp_x_x; 
extern float Ki_x_x;
extern float Kd_x_x;


extern float Kp_y_x; 
extern float Ki_y_x;
extern float Kd_y_x;

 #endif
