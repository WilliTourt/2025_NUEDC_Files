#include "JY901S.H"

typedef struct {
    float roll;
    float pitch;
    float yaw;
} Angles;

uint8_t jy901s_rx_index = 0;
bool jy901s_frame_ready = false;
uint8_t jy901s_rx_data[JY901S_FRAME_LEN];

Angles angle;


bool JY901S_Decode() {
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
//				if(yaw_raw <= -179) {
//					yaw_raw += 360;
//				}
        angle.roll  = (float)roll_raw  / 32768.0f * 180.0f;
        angle.pitch = (float)pitch_raw / 32768.0f * 180.0f;
        angle.yaw   = (float)yaw_raw   / 32768.0f * 180.0f;

        jy901s_frame_ready = false;
        
        return true;
    } else {
        return false;
    }
}

float JY901S_GetPitch() {
    return angle.pitch;
}

float JY901S_GetRoll() {
    return angle.roll;
}

float JY901S_GetYaw() {
    return angle.yaw;
}