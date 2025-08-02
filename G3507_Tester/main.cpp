#include "ti_msp_dl_config.h"
#include "delay.h"
#include "oled.h"
#include "motor.h"
#include "encoder.h"
#include "jy901s.h"

// Encoder encoder1(GPIOA_INT_IRQn, TIMER_ENC_INST_INT_IRQN);
// Encoder encoder2(GPIOA_INT_IRQn, TIMER_ENC_INST_INT_IRQN);

int32_t count1 = 0, count2 = 0;
Encoder::Direction dir1, dir2;
uint16_t spd_cm_per_sec1 = 0, spd_cm_per_sec2 = 0;
uint16_t dis_cm1 = 0, dis_cm2 = 0;

float motor_duty = 20.0;
float yaw = 0.0;

OLED oled(64, I2C_0_INST);
JY901S jy(UART_JY901S_INST_INT_IRQN);
Motor motor(MOTOR_DIR_PORT, MOTOR_DIR_IN1_PIN, MOTOR_DIR_IN2_PIN, MOTOR_PWM_INST, DL_TIMER_CC_0_INDEX);

int main() {

    SYSCFG_DL_init();
    delay(10);
    oled.begin();
    jy.begin();

    motor.begin();

    encoder1.begin();

    oled.printText(0, 4, "MotorDuty:", 8);
    oled.printText(0, 5, "MotorCCR:", 8);
    oled.printText(0, 2, "DUT:", 8);
    oled.printText(0, 3, "DIR:", 8);
    oled.printText(0, 4, "SPD:", 8);
    oled.printText(0, 5, "DIS:", 8);
    oled.printText(0, 7, "YAW:        deg", 8);
    oled.printText(0, 0, "Init OK!", 16);

    while (1) {

        if (jy.decode()) {
            yaw = jy.getYaw();
        }

        dir1 = encoder1.getDirection();
        spd_cm_per_sec1 = encoder1.getSpeed();
        dis_cm1 = encoder1.getDistance();

        motor_duty += 0.03;
        if (motor_duty > 100.0) {
            motor_duty = 20.0;
        }
        motor.setDuty(motor_duty);
        oled.printVar(30, 2, motor_duty, "float", 5, false);
        oled.printVar(30, 3, static_cast<int>(dir1), "int", 5, false);
        oled.printVar(30, 4, spd_cm_per_sec1, "int", 5, false);
        oled.printVar(30, 5, dis_cm1, "int", 4, false);
        oled.printVar(30, 7, yaw, "float", 5, false);

        delay(10);
    }
}



extern "C" {

void UART_JY901S_INST_IRQHandler() {
    switch ( DL_UART_getPendingInterrupt(UART_JY901S_INST) ) {
        case DL_UART_IIDX_RX: {
            uint8_t rxByte = DL_UART_Main_receiveData(UART_JY901S_INST);

            // 查找帧头 0x55 0x53
            if (jy.jy901s_rx_index == 0) {
                if (rxByte == JY901S_FRAME_HEAD1) {
                    jy.jy901s_rx_data[jy.jy901s_rx_index++] = rxByte;
                }
            } else if (jy.jy901s_rx_index == 1) {
                if (rxByte == JY901S_FRAME_HEAD2) {
                    jy.jy901s_rx_data[jy.jy901s_rx_index++] = rxByte;
                } else {
                    jy.jy901s_rx_index = 0;
                }
            } else {
                jy.jy901s_rx_data[jy.jy901s_rx_index++] = rxByte;
                if (jy.jy901s_rx_index >= JY901S_FRAME_LEN) {
                    jy.jy901s_frame_ready = true;
                    jy.jy901s_rx_index = 0;
                }
            }
            
            break;
        }

        default: break;
    }

    DL_UART_clearInterruptStatus(UART_JY901S_INST, DL_UART_IIDX_RX);
}



void GROUP1_IRQHandler() {
    uint32_t gpio_status = DL_GPIO_getEnabledInterruptStatus(ENCODER_PORT, 
                          ENCODER_A1_PIN | ENCODER_B1_PIN | ENCODER_A2_PIN | ENCODER_B2_PIN);
    
    // Handle encoder1 (A1/B1 pins)
    if ((gpio_status & ENCODER_A1_PIN) == ENCODER_A1_PIN) {
        DL_GPIO_togglePins(DEBUG_PORT, DEBUG_LED_PIN);
        if (!DL_GPIO_readPins(ENCODER_PORT, ENCODER_B1_PIN)) {
            encoder1.cnt_IRQ--;
        } else {
            encoder1.cnt_IRQ++;
        }
    } else if ((gpio_status & ENCODER_B1_PIN) == ENCODER_B1_PIN) {
        if (!DL_GPIO_readPins(ENCODER_PORT, ENCODER_A1_PIN)) {
            encoder1.cnt_IRQ++;
        } else {
            encoder1.cnt_IRQ--;
        }
    }

    // Handle encoder2 (A2/B2 pins)
    // if ((gpio_status & ENCODER_A2_PIN) == ENCODER_A2_PIN) {
    //     if (!DL_GPIO_readPins(ENCODER_PORT, ENCODER_B2_PIN)) {
    //         encoder2.cnt_IRQ--;
    //     } else {
    //         encoder2.cnt_IRQ++;
    //     }
    // } else if ((gpio_status & ENCODER_B2_PIN) == ENCODER_B2_PIN) {
    //     if (!DL_GPIO_readPins(ENCODER_PORT, ENCODER_A2_PIN)) {
    //         encoder2.cnt_IRQ++;
    //     } else {
    //         encoder2.cnt_IRQ--;
    //     }
    // }

    DL_GPIO_clearInterruptStatus(ENCODER_PORT, 
        ENCODER_A1_PIN | ENCODER_B1_PIN | ENCODER_A2_PIN | ENCODER_B2_PIN);
}

void TIMER_ENC_INST_IRQHandler() {
    if (DL_TimerA_getPendingInterrupt(TIMER_ENC_INST) == DL_TIMER_IIDX_ZERO) {
        encoder1.update();
        // encoder2.update();
    }
}


// void NMI_Handler(void)
// {
//     __BKPT();
// }

// void HardFault_Handler(void)
// {
//     __BKPT();
// }

// void SVC_Handler(void)
// {
//     __BKPT();
// }

// void PendSV_Handler(void)
// {
//     __BKPT();
// }

// void SysTick_Handler(void)
// {
//     __BKPT();
// }

// void GROUP0_IRQHandler(void)
// {
//     __BKPT();
// }

// void GROUP1_IRQHandler(void)
// {
//     __BKPT();
// }

// void TIMG8_IRQHandler(void)
// {
//     __BKPT();
// }

// void UART3_IRQHandler(void)
// {
//     __BKPT();
// }

// void ADC0_IRQHandler(void)
// {
//     __BKPT();
// }

// void ADC1_IRQHandler(void)
// {
//     __BKPT();
// }

// void CANFD0_IRQHandler(void)
// {
//     __BKPT();
// }

// void DAC0_IRQHandler(void)
// {
//     __BKPT();
// }

// void SPI0_IRQHandler(void)
// {
//     __BKPT();
// }

// void SPI1_IRQHandler(void)
// {
//     __BKPT();
// }

// void UART1_IRQHandler(void)
// {
//     __BKPT();
// }

// void UART2_IRQHandler(void)
// {
//     __BKPT();
// }

// void TIMG0_IRQHandler(void)
// {
//     __BKPT();
// }

// void TIMG6_IRQHandler(void)
// {
//     __BKPT();
// }

// void TIMA0_IRQHandler(void)
// {
//     __BKPT();
// }

// void TIMA1_IRQHandler(void)
// {
//     __BKPT();
// }

// void TIMG7_IRQHandler(void)
// {
//     __BKPT();
// }

// void TIMG12_IRQHandler(void)
// {
//     __BKPT();
// }

// void I2C0_IRQHandler(void)
// {
//     __BKPT();
// }

// void I2C1_IRQHandler(void)
// {
//     __BKPT();
// }

// void AES_IRQHandler(void)
// {
//     __BKPT();
// }

// void RTC_IRQHandler(void)
// {
//     __BKPT();
// }

// void DMA_IRQHandler(void)
// {
//     __BKPT();
// }

} // extern "C"