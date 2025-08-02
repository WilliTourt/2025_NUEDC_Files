#pragma once

#include "ti_msp_dl_config.h"

#define HALL_ENC_PULSE_PER_TURN 26.0f
#define MOTOR_REDUCTION_RATIO 28.0f
#define WHEEL_PERIMETER 21.6f

#define CNT2CM_PARAM (WHEEL_PERIMETER / HALL_ENC_PULSE_PER_TURN / MOTOR_REDUCTION_RATIO)
#define SAMPLE_INTERVAL_SEC 0.02f

class Encoder {
    public:
        enum class Direction {
            BACKWARD,
            FORWARD
        };

        Encoder(IRQn_Type EXTI_IRQn, IRQn_Type TIMER_IRQn);

        void begin();
        int32_t getCount() const;
        float getSpeed() const;
        float getDistance() const;
        void clearDistance();
        Direction getDirection() const;

        void update();

        volatile int32_t cnt_IRQ = 0;

    private:
        IRQn_Type _EXTI_IRQn;
        IRQn_Type _TIMER_IRQn;
        
        int32_t _cnt = 0;
        uint32_t _cnt_integral = 0;
        float _spd = 0.0;
        float _dist = 0.0;
        Direction _dir = Direction::FORWARD;
};
