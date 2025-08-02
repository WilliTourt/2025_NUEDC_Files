#ifndef __PID_H__
#define __PID_H__

#include <stdint.h>
#include <math.h>

class PID {
public:
    enum Option {
        INTEGRAL_LIMIT,
        INTEGRAL_SEPERATION
    };

    PID(float kp = 0.0f, float ki = 0.0f, float kd = 0.0f);
    
    void setParam(float kp, float ki, float kd);
    void setTarget(float target);
    float calc(float actual, float upper_limit, float lower_limit, Option option);

private:
    float kp_;
    float ki_;
    float kd_;
    float target_;
    float err_prev_;
    float err_curr_;
    float err_integral_;

    static constexpr float MAX_ERROR_INTEGRAL = 200.0f;
    static constexpr float MAX_ERROR_DIFFERENCE = 70.0f;
};

#endif
