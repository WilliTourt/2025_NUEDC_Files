#include "ti_msp_dl_config.h"
#include "delay.h"
#include "oled.h"
// #include "mpu6050.h"
// #include "inv_mpu.h"
#include "encoder.h"
#include "motor.h"
#include "pid.h"
#include "ir.h"
#include <stdlib.h>

#define FIXED_SPD 46.0f

#define BASE_SPD 46.0f
#define TURNING_SPD 20.0f

#define TURNING_DELAY 159
// #define RIGHT_ANGLE_TURN_TIME 1105

bool isMissionSet = false;

bool isTrackingCplted = false;
uint8_t target_test = 0;
uint8_t target_loop = 1;

OLED_t oled;
MOTOR_t motor_bl, motor_fl, motor_br, motor_fr;
ENCODER_t encoder_bl, encoder_fr;
PID_t pid_spd, pid_irline;

// float pitch, roll, yaw;
// float delta_yaw = 0.0;
float dist, spd;
int8_t line_error;
float speed_output, irline_output;
bool last_right_angle = false;
bool last_left_angle = false;
bool finish_buzzered = false;

// float yaw_stable;
// bool yaw_stablized = false;
uint8_t turning_count = 0;
uint8_t tim_general_cnt = 0;

int main() {

    SYSCFG_DL_init();
    delay(10);

    PID_Init(&pid_spd, 0.5, 0.0, 0.4);
    PID_SetTarget(&pid_spd, BASE_SPD);
    PID_Init(&pid_irline, 5.8, 0.0, 1.9);
    PID_SetTarget(&pid_irline, 0.0f);

    MOTOR_Init(&motor_bl, GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_BL_IN1_PIN, 
               GPIO_MOTOR_DIR_BL_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_3_INDEX);
    MOTOR_Init(&motor_br, GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_BR_IN1_PIN, 
               GPIO_MOTOR_DIR_BR_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_1_INDEX);
    MOTOR_Init(&motor_fl, GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_FL_IN1_PIN, 
               GPIO_MOTOR_DIR_FL_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_2_INDEX);
    MOTOR_Init(&motor_fr, GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_FR_IN1_PIN, 
               GPIO_MOTOR_DIR_FR_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_0_INDEX);
    MOTOR_Begin(&motor_bl);
    MOTOR_Begin(&motor_br);
    MOTOR_Begin(&motor_fl);
    MOTOR_Begin(&motor_fr);

    ENCODER_Init(&encoder_bl, GPIOA_INT_IRQn, TIMER_ENC_INST_INT_IRQN);
    ENCODER_Init(&encoder_fr, GPIOA_INT_IRQn, TIMER_ENC_INST_INT_IRQN);
    ENCODER_Begin(&encoder_bl);
    ENCODER_Begin(&encoder_fr);

    NVIC_ClearPendingIRQ(TIMER_ENC_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_ENC_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_ENC_INST);

    NVIC_ClearPendingIRQ(TIMER_General_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_General_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_General_INST);

    OLED_Init(&oled, 64, I2C_0_INST);
    OLED_Begin(&oled);

    DL_GPIO_writePins(GPIO_PERIPH_BUZZER_PORT, GPIO_PERIPH_BUZZER_PIN);
    delay(200);
    DL_GPIO_clearPins(GPIO_PERIPH_BUZZER_PORT, GPIO_PERIPH_BUZZER_PIN);
    
    OLED_PrintText(&oled, 0, 0, "Selecting Loops", 16);
    OLED_PrintText(&oled, 0, 2, "Mission Num:", 8);
    OLED_PrintText(&oled, 0, 3, "Loops to run:", 8);
    while (!isMissionSet) {
        OLED_PrintVar(&oled, 84, 2, target_test, "int", 1, false);
        OLED_PrintVar(&oled, 84, 3, target_loop, "int", 1, false);

        if (DL_GPIO_readPins(GPIO_PERIPH_S_TEST_PORT, GPIO_PERIPH_S_TEST_PIN) == 0) {
            delay(10);
            if (DL_GPIO_readPins(GPIO_PERIPH_S_TEST_PORT, GPIO_PERIPH_S_TEST_PIN) == 0) {
                target_test++;
                target_test %= 3;
                while (DL_GPIO_readPins(GPIO_PERIPH_S_TEST_PORT, GPIO_PERIPH_S_TEST_PIN) == 0);
            }
        }

        if (DL_GPIO_readPins(GPIO_PERIPH_S_LOOP_PORT, GPIO_PERIPH_S_LOOP_PIN) == 0) {
            delay(10);
            if (DL_GPIO_readPins(GPIO_PERIPH_S_LOOP_PORT, GPIO_PERIPH_S_LOOP_PIN) == 0) {
                target_loop++;
                target_loop %= 6;
                while (DL_GPIO_readPins(GPIO_PERIPH_S_LOOP_PORT, GPIO_PERIPH_S_LOOP_PIN) == 0);
            }
        }

        if (DL_GPIO_readPins(GPIO_PERIPH_S_PORT, GPIO_PERIPH_S_PIN) == 0) {
            delay(10);
            if (DL_GPIO_readPins(GPIO_PERIPH_S_PORT, GPIO_PERIPH_S_PIN) == 0) {
                isMissionSet = true;
                while (DL_GPIO_readPins(GPIO_PERIPH_S_PORT, GPIO_PERIPH_S_PIN) == 0);
            }
        }
    }

    OLED_Clear(&oled);

    DL_GPIO_writePins(GPIO_PERIPH_BUZZER_PORT, GPIO_PERIPH_BUZZER_PIN);
    delay(600);
    DL_GPIO_clearPins(GPIO_PERIPH_BUZZER_PORT, GPIO_PERIPH_BUZZER_PIN);

    while (1) {
        static float left_output, right_output;

        dist = (ENCODER_GetDistance(&encoder_fr) + ENCODER_GetDistance(&encoder_bl)) / 2.0;
        spd = (ENCODER_GetSpeed(&encoder_fr) + ENCODER_GetSpeed(&encoder_bl)) / 2.0;
        line_error = IR_LineError();



        if (!isTrackingCplted) {
            bool is_right_angle_left = IR_ChkRightAngle_Left();
            bool is_right_angle_right = IR_ChkRightAngle_Right();

            if (is_right_angle_left && !last_left_angle) {

                // DL_UART_Main_transmitData(UART1_JY901S_INST, 1);
                delay(TURNING_DELAY);
                MOTOR_SetDuty(&motor_bl, -TURNING_SPD, false);
                MOTOR_SetDuty(&motor_fl, -TURNING_SPD, true);
                MOTOR_SetDuty(&motor_br, TURNING_SPD, false);
                MOTOR_SetDuty(&motor_fr, TURNING_SPD, true);
                turning_count++;

                while (!IR_Read(3));
                delay(18);
                // delay(RIGHT_ANGLE_TURN_TIME);

                if (isTrackingCplted) {
                    ENCODER_ClearDistance(&encoder_bl);
                    ENCODER_ClearDistance(&encoder_fr);
                }

                last_left_angle = true;
                last_right_angle = false;
                continue;
            } else if (is_right_angle_right && !last_right_angle) {

                // delay(TURNING_DELAY);
                // MOTOR_SetDuty(&motor_bl, TURNING_SPD, false);
                // MOTOR_SetDuty(&motor_fl, TURNING_SPD, true);
                // MOTOR_SetDuty(&motor_br, -TURNING_SPD, false);
                // MOTOR_SetDuty(&motor_fr, -TURNING_SPD, true);
                // delay(RIGHT_ANGLE_TURN_TIME);

                // last_right_angle = true;
                // last_left_angle = false;
                continue;
            } else if (!is_right_angle_left && !is_right_angle_right) {
                last_left_angle = false;
                last_right_angle = false;
            }
        } else {
            if (dist > 30.0) {
                PID_SetTarget(&pid_spd, 0.0);
                PID_SetParam(&pid_spd, 0, 0, 0);
                PID_SetParam(&pid_irline, 0, 0, 0);
                #ifdef FIXED_SPD
                MOTOR_SetDuty(&motor_bl, 0.0, false);
                MOTOR_SetDuty(&motor_fl, 0.0, true);
                MOTOR_SetDuty(&motor_br, 0.0, false);
                MOTOR_SetDuty(&motor_fr, 0.0, true);
                #endif // FIXED_SPD
            }
            if (!finish_buzzered) {
                DL_GPIO_writePins(GPIO_PERIPH_BUZZER_PORT, GPIO_PERIPH_BUZZER_PIN);
                delay(100);
                DL_GPIO_clearPins(GPIO_PERIPH_BUZZER_PORT, GPIO_PERIPH_BUZZER_PIN);
                finish_buzzered = true;
            }
        }

        if (abs(line_error) > 3) {
            PID_SetTarget(&pid_spd, TURNING_SPD);
        } else {
            PID_SetTarget(&pid_spd, BASE_SPD);
        }

        irline_output= PID_Calc(&pid_irline, (float)line_error, 20, -20, PID_INTEGRAL_LIMIT);
        #ifndef FIXED_SPD
        speed_output = PID_Calc(&pid_spd, spd, 100.0, -100.0, PID_INTEGRAL_LIMIT);
        #endif // FIXED_SPD
        #ifdef FIXED_SPD
        speed_output = FIXED_SPD;
        #endif // FIXED_SPD

        left_output = speed_output + irline_output;
        right_output = speed_output - irline_output;
        MOTOR_SetDuty(&motor_bl, left_output, false);
        MOTOR_SetDuty(&motor_fl, left_output, true);
        MOTOR_SetDuty(&motor_br, right_output, false);
        MOTOR_SetDuty(&motor_fr, right_output, true);

        // DEBUG
        // OLED_PrintVar(&oled, 30, 0, spd, "float", 4, false);
        // OLED_PrintVar(&oled, 30, 1, dist, "float", 5, false);
        // OLED_PrintVar(&oled, 30, 2, line_error, "int", 2, false);
    }
}

void TIMER_General_INST_IRQHandler(void) {
    if (DL_TimerG_getPendingInterrupt(TIMER_General_INST) == DL_TIMER_IIDX_ZERO) {
        // static float last_yaw = 999.9;
        // mpu_dmp_get_data(&pitch, &roll, &yaw);
        // tim_general_cnt++;
        // if (tim_general_cnt >= 100) {
        //     // if (!yaw_stablized) {
        //     //     if (fabs(last_yaw - yaw) < 0.01) {
        //     //         yaw_stablized = true;
        //     //         yaw_stable = yaw;
        //     //     } else {
        //     //         last_yaw = yaw;
        //     //     }
        //     // }
        //     tim_general_cnt = 0;
        // }

        if (turning_count >= target_loop * 4 ) {
            isTrackingCplted = true;
        }

        IR_Update();
    }
    DL_TimerG_clearInterruptStatus(TIMER_General_INST, DL_TIMER_IIDX_ZERO);
    NVIC_ClearPendingIRQ(TIMER_General_INST_INT_IRQN);
}

// void UART2_LCD_INST_IRQHandler() {
//     switch ( DL_UART_getPendingInterrupt(UART2_LCD_INST) ) {
//         case DL_UART_IIDX_RX: {
//             uint8_t rxByte = DL_UART_Main_receiveData(UART2_LCD_INST);
//             if (!isMissionSet) {
//                 target_test = (rxByte & 0xF0) >> 4;
//                 target_loop = rxByte & 0x0F;
//                 isMissionSet = true;
//                 break;
//             }
//         }
//         default: break;
//     }
//     DL_UART_clearInterruptStatus(UART2_LCD_INST, DL_UART_IIDX_RX);
// }



void GROUP1_IRQHandler(void) {
    uint32_t gpio_status = DL_GPIO_getEnabledInterruptStatus(GPIO_MOTOR_ENC_PORT, 
                            GPIO_MOTOR_ENC_BL_A_PIN | GPIO_MOTOR_ENC_BL_B_PIN |
                            GPIO_MOTOR_ENC_FR_A_PIN | GPIO_MOTOR_ENC_FR_B_PIN);
                            
    if ((gpio_status & GPIO_MOTOR_ENC_BL_A_PIN) == GPIO_MOTOR_ENC_BL_A_PIN) {
        if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_B_PIN) & GPIO_MOTOR_ENC_BL_B_PIN) {
            encoder_bl._cnt_IRQ--;
        } else {
            encoder_bl._cnt_IRQ++;
        }
        DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_A_PIN);
    }
    if ((gpio_status & GPIO_MOTOR_ENC_BL_B_PIN) == GPIO_MOTOR_ENC_BL_B_PIN) {
        if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_A_PIN) & GPIO_MOTOR_ENC_BL_A_PIN) {
            encoder_bl._cnt_IRQ++;
        } else {
            encoder_bl._cnt_IRQ--;
        }
        DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_B_PIN);
    }

    if ((gpio_status & GPIO_MOTOR_ENC_FR_A_PIN) == GPIO_MOTOR_ENC_FR_A_PIN) {
        if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_FR_B_PIN) & GPIO_MOTOR_ENC_FR_B_PIN) {
            encoder_fr._cnt_IRQ--;
        } else {
            encoder_fr._cnt_IRQ++;
        }
        DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_FR_A_PIN);
    }
    if ((gpio_status & GPIO_MOTOR_ENC_FR_B_PIN) == GPIO_MOTOR_ENC_FR_B_PIN) {
        if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_FR_A_PIN) & GPIO_MOTOR_ENC_FR_A_PIN) {
            encoder_fr._cnt_IRQ++;
        } else {
            encoder_fr._cnt_IRQ--;
        }
        DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_FR_B_PIN);
    }
}

void TIMER_ENC_INST_IRQHandler(void) {
    if (DL_TimerG_getPendingInterrupt(TIMER_ENC_INST) == DL_TIMER_IIDX_ZERO) {
        ENCODER_Update(&encoder_fr);
        ENCODER_Update(&encoder_bl);
    }
    DL_TimerG_clearInterruptStatus(TIMER_ENC_INST, DL_TIMER_IIDX_ZERO);
    NVIC_ClearPendingIRQ(TIMER_ENC_INST_INT_IRQN);
}

