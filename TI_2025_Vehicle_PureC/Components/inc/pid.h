#ifndef __PID_H__
#define __PID_H__

// PID选项枚举
typedef enum {
    PID_INTEGRAL_LIMIT,
    PID_INTEGRAL_SEPERATION
} PID_Options_t;

// PID结构体定义
typedef struct {
    float kp_;
    float ki_;
    float kd_;
    float target_;
    float err_prev_;
    float err_curr_;
    float err_integral_;
} PID_t;

// 函数声明
void PID_Init(PID_t* pid, float kp, float ki, float kd);
void PID_SetParam(PID_t* pid, float kp, float ki, float kd);
void PID_SetTarget(PID_t* pid, float target);
float PID_Calc(PID_t* pid, float actual, float upper_limit, float lower_limit, PID_Options_t option);

#endif
