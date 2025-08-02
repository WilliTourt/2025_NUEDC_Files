/*
 * delay.h - Delay functions for MSPM0G3507
 * 
 * Provides delay() and delayMicroseconds() functions based on 80MHz CPU clock
 */

#ifndef DELAY_H
#define DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Delay for specified microseconds
 * @param us Number of microseconds to delay
 * @note CPU frequency is assumed to be 80MHz (12.5ns per cycle)
 */
static inline void delayMicroseconds(uint32_t us) {
    // 1us = 80 cycles at 80MHz
    delay_cycles(us * 80);
}

/**
 * @brief Delay for specified milliseconds
 * @param ms Number of milliseconds to delay
 * @note CPU frequency is assumed to be 80MHz (12.5ns per cycle)
 */
static inline void delay(uint32_t ms) {
    // 1ms = 80,000 cycles at 80MHz
    while (ms--) {
        delay_cycles(80000);
    }
}

#ifdef __cplusplus
}
#endif

#endif // DELAY_H
