#include "pid.h"

/**
 * @brief PID constructor
 * @param kp Proportional coefficient
 * @param ki Integral coefficient
 * @param kd Derivative coefficient
 */
PID::PID(float kp, float ki, float kd) 
    : kp_(kp), ki_(ki), kd_(kd),
      target_(0.0f),
      err_prev_(0.0f), err_curr_(0.0f), err_integral_(0.0f) {
}

/**
 * @brief Set P.I.D. Parameters
 * @param kp Proportional coefficient
 * @param ki Integral coefficient
 * @param kd Derivative coefficient
 */
void PID::setParam(float kp, float ki, float kd) {
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

/**
 * @brief Set PID target value
 * @param target Target value for PID controller
 */
void PID::setTarget(float target) {
    target_ = target;
}

/**
 * @brief Calculate PID output
 * @param actual Actual value of controlled object
 * @param upper_limit Upper limit of output value
 * @param lower_limit Lower limit of output value
 * @param option PID integral options (INTEGRAL_LIMIT / INTEGRAL_SEPERATION)
 * @return PID output value
 * @note Typical usage: Input current encoder count, output to motor PWM duty cycle.
 */
float PID::calc(float actual, float upper_limit, float lower_limit, Option option) {
    err_prev_ = err_curr_;
    err_curr_ = target_ - actual;
    err_integral_ += err_curr_;

    if (option == INTEGRAL_LIMIT) {
        if (fabs(err_integral_) > MAX_ERROR_INTEGRAL) {
            err_integral_ = MAX_ERROR_INTEGRAL * (err_integral_ / fabs(err_integral_));
        }
    } else if (option == INTEGRAL_SEPERATION) {
        if (fabs(err_curr_) < MAX_ERROR_DIFFERENCE) {
            err_integral_ += err_curr_;
        } else {
            err_integral_ = 0;
        }
    }
    
    float output = kp_ * err_curr_
                 + ki_ * err_integral_
                 + kd_ * (err_curr_ - err_prev_);

    if (output > upper_limit) { output = upper_limit; }
    if (output < lower_limit) { output = lower_limit; }

    return output;
}
