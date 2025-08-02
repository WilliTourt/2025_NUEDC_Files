#include "motor.h"

void MOTOR_Init(MOTOR_t* motor, GPIO_Regs* in_gpio_port, uint32_t in1_pin, uint32_t in2_pin,
                GPTIMER_Regs* gptimer, DL_TIMER_CC_INDEX cc_index) {
    motor->in_gpio_port_ = in_gpio_port;
    motor->in1_pin_ = in1_pin;
    motor->in2_pin_ = in2_pin;
    motor->pwm_timer_ = gptimer;
    motor->cc_index_ = cc_index;
    motor->duty_cycle_ = 0.0;
}

void MOTOR_Begin(MOTOR_t* motor) {
    DL_TimerA_startCounter(motor->pwm_timer_);
}

void MOTOR_SetDir(MOTOR_t* motor, MOTOR_Dir_t dir) {
    switch (dir) {
        case MOTOR_DIR_FORWARD:
            DL_GPIO_setPins(motor->in_gpio_port_, motor->in1_pin_);
            DL_GPIO_clearPins(motor->in_gpio_port_, motor->in2_pin_);
            break;
        case MOTOR_DIR_BACKWARD:
            DL_GPIO_setPins(motor->in_gpio_port_, motor->in2_pin_);
            DL_GPIO_clearPins(motor->in_gpio_port_, motor->in1_pin_);
            break;
        case MOTOR_DIR_STOP:
            DL_GPIO_clearPins(motor->in_gpio_port_, motor->in1_pin_);
            DL_GPIO_clearPins(motor->in_gpio_port_, motor->in2_pin_);
            break;
    }
}

void MOTOR_SetDuty(MOTOR_t* motor, float dutyCycle, bool isFront) {
    motor->duty_cycle_ = dutyCycle;
    if (dutyCycle > 0.0) {
        if (isFront) {
            MOTOR_SetDir(motor, MOTOR_DIR_BACKWARD);
        } else {
            MOTOR_SetDir(motor, MOTOR_DIR_FORWARD);
        }
    } else if (dutyCycle == 0.0) {
        MOTOR_SetDir(motor, MOTOR_DIR_STOP);
    } else {
        if (isFront) {
            MOTOR_SetDir(motor, MOTOR_DIR_FORWARD);
        } else {
            MOTOR_SetDir(motor, MOTOR_DIR_BACKWARD);
        }
        dutyCycle = -dutyCycle;
    }
    if (dutyCycle > 100.0) { dutyCycle = 100.0; }
    
    uint16_t ccr = (uint16_t)((dutyCycle / 100.0) * PWM_PERIOD_COUNT);

    DL_TimerA_setCaptureCompareValue(motor->pwm_timer_, ccr, motor->cc_index_);
}

float MOTOR_GetDuty(const MOTOR_t* motor) {
    return motor->duty_cycle_;
}

uint32_t MOTOR_getCCR_for_debug(const MOTOR_t* motor) {
    return DL_Timer_getCaptureCompareValue(motor->pwm_timer_, motor->cc_index_);
}
