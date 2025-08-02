#include "encoder.h"
#include "math.h"

Encoder::Encoder(IRQn_Type EXTI_IRQn, IRQn_Type TIMER_IRQn) : 
    _EXTI_IRQn(EXTI_IRQn), _TIMER_IRQn(TIMER_IRQn) {}

void Encoder::begin() {
    NVIC_ClearPendingIRQ(_EXTI_IRQn);
    NVIC_EnableIRQ(_EXTI_IRQn);

    // Timer for speed counting, 50Hz
    NVIC_ClearPendingIRQ(_TIMER_IRQn);
    NVIC_EnableIRQ(_TIMER_IRQn);
    DL_TimerG_startCounter(TIMER_ENC_INST);
}

int32_t Encoder::getCount() const {
    return _cnt;
}

void Encoder::update() {
    _cnt = abs(cnt_IRQ);
    _cnt_integral += abs(cnt_IRQ);

    _spd = (float)_cnt * CNT2CM_PARAM / SAMPLE_INTERVAL_SEC;
    _dist = (float)_cnt_integral * CNT2CM_PARAM;

    _dir = (cnt_IRQ >= 0) ? Direction::FORWARD : Direction::BACKWARD;

    cnt_IRQ = 0;
}

float Encoder::getSpeed() const {
    return _spd;
}

float Encoder::getDistance() const {
    return _dist;
}

void Encoder::clearDistance() {
    _cnt_integral = 0;
    _dist = 0;
}

Encoder::Direction Encoder::getDirection() const {
    return _dir;
}
