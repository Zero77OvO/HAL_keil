#include "main.h"
#include "pid.h"

#define PID_SPEED_K_PRO 85.0
#define PID_SPEED_K_INT 2.0
#define PID_SPEED_K_DIF -30.0

#define PID_ANGLE_K_PRO 0.70
#define PID_ANGLE_K_INT 0.5
#define PID_ANGLE_K_DIF -0.1

pid pid_speed;
pid pid_angle;

void pid_speed_init()
{
	pid_speed.i = 0;
	pid_speed.k_dif = PID_SPEED_K_DIF;
	pid_speed.k_int = PID_SPEED_K_INT;
	pid_speed.k_pro = PID_SPEED_K_PRO;
	pid_speed.max_int = 180;
	pid_speed.tar_value = 0;
	pid_speed.true_value = 0;
	pid_speed.pre_error = 0;

	pid_speed.output_limit_min = -999;
	pid_speed.output_limit_max = 999;
	pid_speed.output = 0;
}
void pid_angle_init()
{
	pid_angle.i = 0;
	pid_angle.k_dif = PID_ANGLE_K_DIF;
	pid_angle.k_int = PID_ANGLE_K_INT;
	pid_angle.k_pro = PID_ANGLE_K_PRO;
	pid_angle.max_int = 200;

	pid_angle.tar_value = TAR_ANGLE;

	pid_angle.true_value = 0;
	pid_angle.pre_error = 0;

	pid_angle.output_limit_min = -65535;
	pid_angle.output_limit_max = 65535;
	pid_angle.output = 0;
}

void pid_set_tarspeed(uint32_t tar)
{
	pid_speed.tar_value = tar;
}
extern uint32_t adc_raw;

void pid_angle_cal()
{
	int error = pid_angle.tar_value - pid_angle.true_value;

	if (pid_angle.true_value < TAR_ANGLE - 250 || pid_angle.true_value > TAR_ANGLE + 250)
		;
	else
		pid_angle.i += error;
	// printf("T:%d\n", pid_speed.tar_value);
	// printf("E:%d\n", error);
	int delta_error = error - pid_angle.pre_error;
	pid_angle.pre_error = error;

	pid_angle.output = pid_angle.k_pro * error + pid_angle.k_int * pid_angle.i + pid_angle.k_dif * delta_error;
	// printf("O:%d\n", pid_speed.output);
	if (pid_angle.output > pid_angle.output_limit_max)
		pid_angle.output = pid_angle.output_limit_max;
	else if (pid_angle.output < pid_angle.output_limit_min)
		pid_angle.output = pid_angle.output_limit_min;
	// printf("AO:%d\n", pid_angle.output);
}

void pid_speed_cal()
{
	int error = pid_speed.tar_value - pid_speed.true_value;

	if (pid_angle.true_value < TAR_ANGLE - 250 || pid_angle.true_value > TAR_ANGLE + 250)
		;
	else
		pid_speed.i += error;

	if (pid_speed.i > pid_speed.max_int)
		pid_speed.i = pid_speed.max_int;
	
	else if (pid_speed.i < -pid_speed.max_int)
		pid_speed.i = -pid_speed.max_int;

	int delta_error = error - pid_speed.pre_error;
	pid_speed.pre_error = error;

	pid_speed.output = pid_speed.k_pro * error + pid_speed.k_int * pid_speed.i + pid_speed.k_dif * delta_error;

	// printf("P:%d ", (int)(pid_speed.k_pro * error));
	// printf("P:%d\n",(int)(pid_speed.k_int * pid_speed.i));
	if (pid_speed.output > pid_speed.output_limit_max)
		pid_speed.output = pid_speed.output_limit_max;
	else if (pid_speed.output < pid_speed.output_limit_min)
		pid_speed.output = pid_speed.output_limit_min;
}
