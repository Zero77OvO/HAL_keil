#ifndef __L298N_H
#define __L298N_H
 
 



void horizon_move(int pwm);
void vertical_move(int pwm);
void PWM_Init(void);
void PWM_work(void);
void Servo_start(void);

void move_step(void);

void Servo_reset(void);

void Servo_pid_move(IncrementalPID *ver, IncrementalPID *hor, float y1, float y_green, float x1, float x_green);

void Servo_location_pid_cal(float target_x,float target_y,float stat_x,float stat_y);
void Servo_incremental_pid_cal(IncrementalPID *ver, IncrementalPID *hor,float target_x,float target_y,float stat_x,float stat_y);

extern struct {
    float set_speed; 
    float actual_speed;
    float ek;
    float ek_1;
    float ek_2;
    float kp,ki,kd;
     
}hor,ver;
extern float i;
extern float j;

extern float hor_out;
extern float ver_out;
extern int point_step;
extern int step;
extern int t;


#endif





