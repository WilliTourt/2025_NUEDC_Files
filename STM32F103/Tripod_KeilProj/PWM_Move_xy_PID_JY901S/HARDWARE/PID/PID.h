#ifndef __PID_H
#define __PID_H
 
#include "STP.h"
 
typedef struct
{
	float target_val;//�趨ֵ
	float actual_val;//ʵ��ֵ
	float err;//���
	float err_last;//�ϴ����
	float Kp;
	float Ki;
	float Kd;
	float out;//ִ�����ı���
	float err_sum;//����ֵ
}pid_typedef;
 
//void PID_init(float Kp,float Ki,float Kd);

void X_PID_init(float Kp,float Ki,float Kd);

void Y_PID_init(float Kp,float Ki,float Kd);

float PIDx_realize(float actual_val,float target_val);
float PIDy_realize(float actual_val,float target_val);
 
#endif     