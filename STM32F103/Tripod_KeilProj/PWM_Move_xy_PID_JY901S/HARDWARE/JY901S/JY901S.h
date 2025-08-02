#ifndef __JY901S_H
#define __JY901S_H
 
#include "usart.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include <stdbool.h>
#include <stdio.h>
#include "tim.h"

#define JY901S_FRAME_LEN 11

#define JY901S_FRAME_HEAD1 0x55
#define JY901S_FRAME_HEAD2 0x53
 
bool JY901S_Decode();
float JY901S_GetYaw();
float JY901S_GetPitch();
float JY901S_GetRoll();
	
#endif     