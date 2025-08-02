#ifndef __PID_H
#define __PID_H
 
#include "STP.h"
 
typedef struct
{
	float target_val;//设定值
	float actual_val;//实际值
	float err;//误差
	float err_last;//上次误差
	float Kp;
	float Ki;
	float Kd;
	float out;//执行器的变量
	float err_sum;//积分值
}pid_typedef;
 
//void PID_init(float Kp,float Ki,float Kd);

void X_PID_init(float Kp,float Ki,float Kd);

void Y_PID_init(float Kp,float Ki,float Kd);

float PIDx_realize(float actual_val,float target_val);
float PIDy_realize(float actual_val,float target_val);
 
#endif     