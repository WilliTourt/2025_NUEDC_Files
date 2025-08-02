#ifndef __STP_H
#define __STP_H

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>
#include "tim.h"

// ���岽�����������Ʊ���
extern _Bool cntDir;

// ��������
//void STP(uint32_t pulse_delay, uint32_t step_count);
//void STP(uint32_t pulse_delay, float target_angle, _Bool direction);
//void X_STP_PWM_Start(float angle_deg, _Bool dir);

void STP_StepAngle_X(float angle_deg, _Bool dir);
//void STP_PWM_Start_Y(float angle_deg, _Bool dir);

void STP_PWM_Start_X(int freq, float err);
void STP_PWM_Start_Y(int freq, float err);

void X_STP_PWM_SpeedControl(float pid_output);
void Y_STP_PWM_SpeedControl(float pid_output);

void delay_cnt(uint32_t cnt);
void delay_ms(uint32_t ms);
int fputc(int ch,FILE *f);
void uart1_send_string(const char *str);
float clamp(float val, float min, float max);
	
// �����ò������ֱ���������ͷ�ӽǣ�
#define IMAGE_WIDTH        800
#define IMAGE_HEIGHT       480
#define CAMERA_HFOV_DEG    65.0f
#define CAMERA_VFOV_DEG    40.0f

#define STEP_ANGLE 0.01125f

#endif
