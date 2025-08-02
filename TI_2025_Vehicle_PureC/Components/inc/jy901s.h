#pragma once

#include "ti_msp_dl_config.h"

#define JY901S_FRAME_LEN 11
#define JY901S_FRAME_HEAD1 0x55
#define JY901S_FRAME_HEAD2 0x53

// Angles结构体定义
typedef struct {
    float roll;
    float pitch;
    float yaw;
} JY901S_Angles_t;

// JY901S结构体定义
typedef struct {
    IRQn_Type _JY901S_IRQn;
    UART_Regs *_JY901S_INST;
    JY901S_Angles_t _angles;
} JY901S_t;

// 公共变量声明
extern uint8_t jy901s_rx_index;
extern bool jy901s_frame_ready;
extern uint8_t jy901s_rx_data[JY901S_FRAME_LEN];

// 函数声明
void JY901S_Init(JY901S_t* jy, IRQn_Type JY901S_IRQn, UART_Regs *UART_INST);
void JY901S_Begin(JY901S_t* jy);
bool JY901S_Decode(JY901S_t* jy);
float JY901S_GetPitch(JY901S_t* jy);
float JY901S_GetRoll(JY901S_t* jy);
float JY901S_GetYaw(JY901S_t* jy);
