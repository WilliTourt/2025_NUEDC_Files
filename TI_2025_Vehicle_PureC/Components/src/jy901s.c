#include "jy901s.h"

uint8_t jy901s_rx_index = 0;
bool jy901s_frame_ready = false;
uint8_t jy901s_rx_data[JY901S_FRAME_LEN];

void JY901S_Init(JY901S_t* jy, IRQn_Type JY901S_IRQn, UART_Regs *UART_INST) {
    jy->_JY901S_IRQn = JY901S_IRQn;
    jy->_JY901S_INST = UART_INST;
    jy->_angles.roll = 0;
    jy->_angles.pitch = 0;
    jy->_angles.yaw = 0;
}

void JY901S_Begin(JY901S_t* jy) {
    NVIC_ClearPendingIRQ(jy->_JY901S_IRQn);
    NVIC_EnableIRQ(jy->_JY901S_IRQn);
    // Ensure UART RX interrupt is enabled
    DL_UART_Main_enableInterrupt(jy->_JY901S_INST, DL_UART_MAIN_INTERRUPT_RX);
}

bool JY901S_Decode(JY901S_t* jy) {
    if (jy901s_frame_ready) {
        uint8_t sum = 0;
        for (int i = 0; i < JY901S_FRAME_LEN - 1; i++) {
            sum += jy901s_rx_data[i];
        }
        if (sum != jy901s_rx_data[JY901S_FRAME_LEN - 1]) {
            return false;
        }

        int16_t roll_raw  = (jy901s_rx_data[3] << 8) | jy901s_rx_data[2];
        int16_t pitch_raw = (jy901s_rx_data[5] << 8) | jy901s_rx_data[4];
        int16_t yaw_raw   = (jy901s_rx_data[7] << 8) | jy901s_rx_data[6];
        jy->_angles.roll  = (float)roll_raw  / 32768.0f * 180.0f;
        jy->_angles.pitch = (float)pitch_raw / 32768.0f * 180.0f;
        jy->_angles.yaw   = (float)yaw_raw   / 32768.0f * 180.0f;

        jy901s_frame_ready = false;
        
        return true;
    } else {
        return false;
    }
}

float JY901S_GetPitch(JY901S_t* jy) {
    return jy->_angles.pitch;
}

float JY901S_GetRoll(JY901S_t* jy) {
    return jy->_angles.roll;
}

float JY901S_GetYaw(JY901S_t* jy) {
    return jy->_angles.yaw;
}
