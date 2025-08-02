#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "ti_msp_dl_config.h"

#define PWM_PERIOD_COUNT 1000

typedef enum {
    MOTOR_DIR_FORWARD,
    MOTOR_DIR_BACKWARD,
    MOTOR_DIR_STOP
} MOTOR_Dir_t;

typedef struct {
    GPIO_Regs* in_gpio_port_;
    uint32_t in1_pin_;
    uint32_t in2_pin_;
    GPTIMER_Regs* pwm_timer_;
    DL_TIMER_CC_INDEX cc_index_;
    float duty_cycle_;
} MOTOR_t;

void MOTOR_Init(MOTOR_t* motor, GPIO_Regs* in_gpio_port, uint32_t in1_pin, uint32_t in2_pin,
                GPTIMER_Regs* gptimer, DL_TIMER_CC_INDEX cc_index);
void MOTOR_Begin(MOTOR_t* motor);
void MOTOR_SetDuty(MOTOR_t* motor, float dutyCycle, bool isFront);
float MOTOR_GetDuty(const MOTOR_t* motor);
uint32_t MOTOR_getCCR_for_debug(const MOTOR_t* motor);

#endif
