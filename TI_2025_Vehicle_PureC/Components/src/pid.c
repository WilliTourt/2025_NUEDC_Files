#include "pid.h"
#include <stdint.h>
#include <math.h>

// 常量定义
#define MAX_ERROR_INTEGRAL 200.0f
#define MAX_ERROR_DIFFERENCE 70.0f

// 初始化函数
void PID_Init(PID_t* pid, float kp, float ki, float kd) {
    pid->kp_ = kp;
    pid->ki_ = ki;
    pid->kd_ = kd;
    pid->target_ = 0.0f;
    pid->err_prev_ = 0.0f;
    pid->err_curr_ = 0.0f;
    pid->err_integral_ = 0.0f;
}

void PID_SetParam(PID_t* pid, float kp, float ki, float kd) {
    pid->kp_ = kp;
    pid->ki_ = ki;
    pid->kd_ = kd;
}

void PID_SetTarget(PID_t* pid, float target) {
    pid->target_ = target;
}

float PID_Calc(PID_t* pid, float actual, float upper_limit, float lower_limit, PID_Options_t option) {
    pid->err_prev_ = pid->err_curr_;
    pid->err_curr_ = pid->target_ - actual;
    pid->err_integral_ += pid->err_curr_;

    if (option == PID_INTEGRAL_LIMIT) {
        if (fabs(pid->err_integral_) > MAX_ERROR_INTEGRAL) {
            pid->err_integral_ = MAX_ERROR_INTEGRAL * (pid->err_integral_ / fabs(pid->err_integral_));
        }
    } else if (option == PID_INTEGRAL_SEPERATION) {
        if (fabs(pid->err_curr_) < MAX_ERROR_DIFFERENCE) {
            pid->err_integral_ += pid->err_curr_;
        } else {
            pid->err_integral_ = 0;
        }
    }
    
    float output = pid->kp_ * pid->err_curr_
                 + pid->ki_ * pid->err_integral_
                 + pid->kd_ * (pid->err_curr_ - pid->err_prev_);

    if (output > upper_limit) { output = upper_limit; }
    if (output < lower_limit) { output = lower_limit; }

    return output;
}
