#include "ir.h"

bool IR_Data[4] = { false };
bool IR_Left = false;

void IR_Update() {
    IR_Left =    (DL_GPIO_readPins(GPIO_IR_PIN_0_PORT, GPIO_IR_PIN_0_PIN) != 0);
    IR_Data[0] = (DL_GPIO_readPins(GPIO_IR_PIN_1_PORT, GPIO_IR_PIN_1_PIN) != 0);
    IR_Data[1] = (DL_GPIO_readPins(GPIO_IR_PIN_2_PORT, GPIO_IR_PIN_2_PIN) != 0);
    IR_Data[2] = (DL_GPIO_readPins(GPIO_IR_PIN_3_PORT, GPIO_IR_PIN_3_PIN) != 0);
    IR_Data[3] = (DL_GPIO_readPins(GPIO_IR_PIN_4_PORT, GPIO_IR_PIN_4_PIN) != 0);
}

// int8_t IR_Output() { 
//     if (IR_Data[1] && IR_Data[2]) {
//         return 0;
//     }
//     else if (IR_Data[0] || IR_Data[1]) {
//         return IR_Data[0] ? -12 : -5;
//     }
//     else if (IR_Data[2] || IR_Data[3]) {
//         return IR_Data[3] ? 12 : 5;
//     }
//     else if (!IR_Data[0] && !IR_Data[1] && !IR_Data[2] && !IR_Data[3]) {
//         return 0;
//     }
    
//     return 0;
// }

int8_t IR_LineError() {
    int8_t error = 0;
    if (IR_Data[0]) { error -= 3; }
    if (IR_Data[1]) { error -= 1; }
    if (IR_Data[2]) { error += 1; }
    if (IR_Data[3]) { error += 3; }
    return error;
}

bool IR_ChkRightAngle_Right() {
    return (!IR_Data[0] && IR_Data[1] && IR_Data[2] && IR_Data[3]);
}

bool IR_ChkRightAngle_Left() {
    return (IR_Left && IR_Data[0] && !IR_Data[3]);
}

bool IR_Read(uint8_t pin) {
    if (pin > 3) { pin = 3; }
    return IR_Data[pin];
}