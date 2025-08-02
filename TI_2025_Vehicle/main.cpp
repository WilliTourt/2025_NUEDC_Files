#include "ti_msp_dl_config.h"
#include "delay.h"
#include "oled.h"
#include "motor.h"
#include "encoder.h"
#include "jy901s.h"
#include "pid.h"
#include "mpu6050.h"

#define TURNING_SPD 60.0f
#define BASE_SPD 33.0f

float yaw = 0.0;
float dist, spd;
float angle_output, speed_output;
float target = 0.0;

Encoder enc_br(GPIOA_INT_IRQn, TIMER_ENC_INST_INT_IRQN);
// Encoder enc_bl(GPIOA_INT_IRQn, TIMER_ENC_INST_INT_IRQN);

Motor motor_fr(GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_FR_IN1_PIN, 
                GPIO_MOTOR_DIR_FR_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_0_INDEX);
Motor motor_br(GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_BR_IN1_PIN, 
                GPIO_MOTOR_DIR_BR_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_1_INDEX);
Motor motor_fl(GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_FL_IN1_PIN, 
                GPIO_MOTOR_DIR_FL_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_2_INDEX);
Motor motor_bl(GPIO_MOTOR_DIR_PORT, GPIO_MOTOR_DIR_BL_IN1_PIN, 
                GPIO_MOTOR_DIR_BL_IN2_PIN, TIMA0_PWM_INST, DL_TIMER_CC_3_INDEX);

MPU6050 mpu(I2C_0_INST);
OLED oled(64, I2C_1_INST);

PID pid_ang(4.6, 0.0, 2.8);

float SPD_Get() {
    // return ((enc_bl.getSpeed() + enc_br.getSpeed()) / 2.0);
    return enc_br.getSpeed();
}

float DIST_Get() {
    // return ((enc_bl.getDistance() + enc_br.getDistance()) / 2.0);
    return enc_br.getDistance();
}

// extern "C" {

// //串口发送单个字符
// void uart0_send_char(char ch) {
//     //当串口0忙的时候等待，不忙的时候再发送传进来的字符
//     while( DL_UART_isBusy(UART0_DEBUG_INST) == true );
//     //发送单个字符
//     DL_UART_Main_transmitData(UART0_DEBUG_INST, ch);
// }
// //串口发送字符串
// void uart0_send_string(char* str) {
//     //当前字符串地址不在结尾 并且 字符串首地址不为空
//     while(*str!=0&&str!=0) {
//         //发送字符串首地址中的字符，并且在发送完成之后首地址自增
//         uart0_send_char(*str++);
//     }
// }

// char buf[50];

// }

void turn() {
    float current_yaw = mpu.getYaw();

    motor_bl.setDuty(-TURNING_SPD);
    motor_fl.setDuty(-TURNING_SPD);
    motor_br.setDuty(TURNING_SPD);
    motor_fr.setDuty(TURNING_SPD);

    while (mpu.getYaw() < current_yaw + 86.0) {
        mpu.updateEuler();
        oled.printVar(10, 4, mpu.getYaw(), "float", 6, false);
    }

    target += 90.0;
    pid_ang.setTarget(target);

    
    motor_bl.setDuty(BASE_SPD);
    motor_fl.setDuty(BASE_SPD);
    motor_br.setDuty(BASE_SPD);
    motor_fr.setDuty(BASE_SPD);

}






int main() {

    SYSCFG_DL_init();
    delay(10);

    mpu.begin(0x06, 0x01, 0x00);
    if (mpu.getID() != 0x68) { while (1); }
    mpu.calibrate(8000);

	pid_ang.setTarget(target);

    // enc_bl.begin();
    enc_br.begin();

    motor_bl.begin();
    motor_br.begin();
    motor_fl.begin();
    motor_fr.begin();

    NVIC_ClearPendingIRQ(TIMER_General_INST_INT_IRQN);
    NVIC_EnableIRQ(TIMER_General_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_General_INST);

    oled.begin();
    oled.printText(0, 0, "Init OK!", 16);
    oled.printText(0, 6, "SPD:", 8);
    oled.printText(0, 7, "DIS:", 8);

    while (1) {
        static float left_output, right_output;

        dist = DIST_Get();
        spd = SPD_Get();
        yaw = mpu.getYaw();

        angle_output = pid_ang.calc(yaw, 10.0, -10.0, PID::INTEGRAL_LIMIT);

		left_output = BASE_SPD + angle_output;
		right_output = BASE_SPD - angle_output;

        motor_bl.setDuty(left_output);
        motor_fl.setDuty(left_output);
        motor_br.setDuty(right_output);
        motor_fr.setDuty(right_output);

        mpu.updateEuler();
        oled.printVar(10, 4, yaw, "float", 6, false);

        if (dist >= 99.0) {
            turn();
            dist = 0.0;
            enc_br.clearDistance();
        }

        oled.printVar(30, 7, dist, "float", 6, false);
        oled.printVar(30, 6, spd, "float", 6, false);

        delay(3);
    }
}



extern "C" {

void TIMER_General_INST_IRQHandler() {
    if (DL_TimerG_getPendingInterrupt(TIMER_General_INST) == DL_TIMER_IIDX_ZERO) {
        mpu.updateEuler();
    }
    DL_TimerG_clearInterruptStatus(TIMER_General_INST, DL_TIMER_IIDX_ZERO);
}

void GROUP1_IRQHandler() {
    uint32_t gpio_status = DL_GPIO_getEnabledInterruptStatus(GPIO_MOTOR_ENC_PORT, 
                            // GPIO_MOTOR_ENC_BL_A_PIN | GPIO_MOTOR_ENC_BL_B_PIN |
                            GPIO_MOTOR_ENC_BR_A_PIN | GPIO_MOTOR_ENC_BR_B_PIN);

    // Handle enc_br
    if ((gpio_status & GPIO_MOTOR_ENC_BR_A_PIN) == GPIO_MOTOR_ENC_BR_A_PIN) {
        if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BR_B_PIN) & GPIO_MOTOR_ENC_BR_B_PIN) {
            enc_br.cnt_IRQ--;
        } else {
            enc_br.cnt_IRQ++;
        }
        DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BR_A_PIN);
    }
    if ((gpio_status & GPIO_MOTOR_ENC_BR_B_PIN) == GPIO_MOTOR_ENC_BR_B_PIN) {
        if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BR_A_PIN) & GPIO_MOTOR_ENC_BR_A_PIN) {
            enc_br.cnt_IRQ++;
        } else {
            enc_br.cnt_IRQ--;
        }
        DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BR_B_PIN);
    }

//     // Handle enc_bl
//     if ((gpio_status & GPIO_MOTOR_ENC_BL_A_PIN) == GPIO_MOTOR_ENC_BL_A_PIN) {
//         if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_B_PIN) & GPIO_MOTOR_ENC_BL_B_PIN) {
//             enc_bl.cnt_IRQ--;
//         } else {
//             enc_bl.cnt_IRQ++;
//         }
//         DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_A_PIN);
//     }
//     if ((gpio_status & GPIO_MOTOR_ENC_BL_B_PIN) == GPIO_MOTOR_ENC_BL_B_PIN) {
//         if (DL_GPIO_readPins(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_A_PIN) & GPIO_MOTOR_ENC_BL_A_PIN) {
//             enc_bl.cnt_IRQ++;
//         } else {
//             enc_bl.cnt_IRQ--;
//         }
//         DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, GPIO_MOTOR_ENC_BL_B_PIN);
//     }
//     DL_GPIO_clearInterruptStatus(GPIO_MOTOR_ENC_PORT, gpio_status); 
// }
}

void TIMER_ENC_INST_IRQHandler() {
    if (DL_TimerG_getPendingInterrupt(TIMER_ENC_INST) == DL_TIMER_IIDX_ZERO) {
        enc_br.update();
        // enc_bl.update();
    }
    DL_TimerG_clearInterruptStatus(TIMER_ENC_INST, DL_TIMER_IIDX_ZERO);
}

} // extern "C"
