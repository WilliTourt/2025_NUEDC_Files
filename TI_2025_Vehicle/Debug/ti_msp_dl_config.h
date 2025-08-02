/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     80000000



/* Defines for TIMA0_PWM */
#define TIMA0_PWM_INST                                                     TIMA0
#define TIMA0_PWM_INST_IRQHandler                               TIMA0_IRQHandler
#define TIMA0_PWM_INST_INT_IRQN                                 (TIMA0_INT_IRQn)
#define TIMA0_PWM_INST_CLK_FREQ                                         10000000
/* GPIO defines for channel 0 */
#define GPIO_TIMA0_PWM_C0_PORT                                             GPIOB
#define GPIO_TIMA0_PWM_C0_PIN                                      DL_GPIO_PIN_8
#define GPIO_TIMA0_PWM_C0_IOMUX                                  (IOMUX_PINCM25)
#define GPIO_TIMA0_PWM_C0_IOMUX_FUNC                 IOMUX_PINCM25_PF_TIMA0_CCP0
#define GPIO_TIMA0_PWM_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_TIMA0_PWM_C1_PORT                                             GPIOB
#define GPIO_TIMA0_PWM_C1_PIN                                      DL_GPIO_PIN_9
#define GPIO_TIMA0_PWM_C1_IOMUX                                  (IOMUX_PINCM26)
#define GPIO_TIMA0_PWM_C1_IOMUX_FUNC                 IOMUX_PINCM26_PF_TIMA0_CCP1
#define GPIO_TIMA0_PWM_C1_IDX                                DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 2 */
#define GPIO_TIMA0_PWM_C2_PORT                                             GPIOB
#define GPIO_TIMA0_PWM_C2_PIN                                     DL_GPIO_PIN_12
#define GPIO_TIMA0_PWM_C2_IOMUX                                  (IOMUX_PINCM29)
#define GPIO_TIMA0_PWM_C2_IOMUX_FUNC                 IOMUX_PINCM29_PF_TIMA0_CCP2
#define GPIO_TIMA0_PWM_C2_IDX                                DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 3 */
#define GPIO_TIMA0_PWM_C3_PORT                                             GPIOB
#define GPIO_TIMA0_PWM_C3_PIN                                     DL_GPIO_PIN_13
#define GPIO_TIMA0_PWM_C3_IOMUX                                  (IOMUX_PINCM30)
#define GPIO_TIMA0_PWM_C3_IOMUX_FUNC                 IOMUX_PINCM30_PF_TIMA0_CCP3
#define GPIO_TIMA0_PWM_C3_IDX                                DL_TIMER_CC_3_INDEX



/* Defines for TIMER_ENC */
#define TIMER_ENC_INST                                                   (TIMG0)
#define TIMER_ENC_INST_IRQHandler                               TIMG0_IRQHandler
#define TIMER_ENC_INST_INT_IRQN                                 (TIMG0_INT_IRQn)
#define TIMER_ENC_INST_LOAD_VALUE                                        (9999U)
/* Defines for TIMER_General */
#define TIMER_General_INST                                               (TIMG6)
#define TIMER_General_INST_IRQHandler                           TIMG6_IRQHandler
#define TIMER_General_INST_INT_IRQN                             (TIMG6_INT_IRQn)
#define TIMER_General_INST_LOAD_VALUE                                   (24999U)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C0
#define I2C_0_INST_IRQHandler                                    I2C0_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C0_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                         DL_GPIO_PIN_0
#define GPIO_I2C_0_IOMUX_SDA                                      (IOMUX_PINCM1)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                       IOMUX_PINCM1_PF_I2C0_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                         DL_GPIO_PIN_1
#define GPIO_I2C_0_IOMUX_SCL                                      (IOMUX_PINCM2)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                       IOMUX_PINCM2_PF_I2C0_SCL

/* Defines for I2C_1 */
#define I2C_1_INST                                                          I2C1
#define I2C_1_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_1_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_1_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_1_SDA_PORT                                                GPIOB
#define GPIO_I2C_1_SDA_PIN                                         DL_GPIO_PIN_3
#define GPIO_I2C_1_IOMUX_SDA                                     (IOMUX_PINCM16)
#define GPIO_I2C_1_IOMUX_SDA_FUNC                      IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_1_SCL_PORT                                                GPIOB
#define GPIO_I2C_1_SCL_PIN                                         DL_GPIO_PIN_2
#define GPIO_I2C_1_IOMUX_SCL                                     (IOMUX_PINCM15)
#define GPIO_I2C_1_IOMUX_SCL_FUNC                      IOMUX_PINCM15_PF_I2C1_SCL


/* Defines for UART0_DEBUG */
#define UART0_DEBUG_INST                                                   UART0
#define UART0_DEBUG_INST_FREQUENCY                                      40000000
#define UART0_DEBUG_INST_IRQHandler                             UART0_IRQHandler
#define UART0_DEBUG_INST_INT_IRQN                                 UART0_INT_IRQn
#define GPIO_UART0_DEBUG_RX_PORT                                           GPIOA
#define GPIO_UART0_DEBUG_TX_PORT                                           GPIOA
#define GPIO_UART0_DEBUG_RX_PIN                                   DL_GPIO_PIN_11
#define GPIO_UART0_DEBUG_TX_PIN                                   DL_GPIO_PIN_10
#define GPIO_UART0_DEBUG_IOMUX_RX                                (IOMUX_PINCM22)
#define GPIO_UART0_DEBUG_IOMUX_TX                                (IOMUX_PINCM21)
#define GPIO_UART0_DEBUG_IOMUX_RX_FUNC                 IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART0_DEBUG_IOMUX_TX_FUNC                 IOMUX_PINCM21_PF_UART0_TX
#define UART0_DEBUG_BAUD_RATE                                           (115200)
#define UART0_DEBUG_IBRD_40_MHZ_115200_BAUD                                 (21)
#define UART0_DEBUG_FBRD_40_MHZ_115200_BAUD                                 (45)
/* Defines for UART1_JY901S */
#define UART1_JY901S_INST                                                  UART1
#define UART1_JY901S_INST_FREQUENCY                                     40000000
#define UART1_JY901S_INST_IRQHandler                            UART1_IRQHandler
#define UART1_JY901S_INST_INT_IRQN                                UART1_INT_IRQn
#define GPIO_UART1_JY901S_RX_PORT                                          GPIOA
#define GPIO_UART1_JY901S_TX_PORT                                          GPIOA
#define GPIO_UART1_JY901S_RX_PIN                                   DL_GPIO_PIN_9
#define GPIO_UART1_JY901S_TX_PIN                                   DL_GPIO_PIN_8
#define GPIO_UART1_JY901S_IOMUX_RX                               (IOMUX_PINCM20)
#define GPIO_UART1_JY901S_IOMUX_TX                               (IOMUX_PINCM19)
#define GPIO_UART1_JY901S_IOMUX_RX_FUNC                IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART1_JY901S_IOMUX_TX_FUNC                IOMUX_PINCM19_PF_UART1_TX
#define UART1_JY901S_BAUD_RATE                                          (115200)
#define UART1_JY901S_IBRD_40_MHZ_115200_BAUD                                (21)
#define UART1_JY901S_FBRD_40_MHZ_115200_BAUD                                (45)
/* Defines for UART2_LCD */
#define UART2_LCD_INST                                                     UART2
#define UART2_LCD_INST_FREQUENCY                                        40000000
#define UART2_LCD_INST_IRQHandler                               UART2_IRQHandler
#define UART2_LCD_INST_INT_IRQN                                   UART2_INT_IRQn
#define GPIO_UART2_LCD_RX_PORT                                             GPIOB
#define GPIO_UART2_LCD_TX_PORT                                             GPIOB
#define GPIO_UART2_LCD_RX_PIN                                     DL_GPIO_PIN_16
#define GPIO_UART2_LCD_TX_PIN                                     DL_GPIO_PIN_15
#define GPIO_UART2_LCD_IOMUX_RX                                  (IOMUX_PINCM33)
#define GPIO_UART2_LCD_IOMUX_TX                                  (IOMUX_PINCM32)
#define GPIO_UART2_LCD_IOMUX_RX_FUNC                   IOMUX_PINCM33_PF_UART2_RX
#define GPIO_UART2_LCD_IOMUX_TX_FUNC                   IOMUX_PINCM32_PF_UART2_TX
#define UART2_LCD_BAUD_RATE                                             (115200)
#define UART2_LCD_IBRD_40_MHZ_115200_BAUD                                   (21)
#define UART2_LCD_FBRD_40_MHZ_115200_BAUD                                   (45)
/* Defines for UART3_K230 */
#define UART3_K230_INST                                                    UART3
#define UART3_K230_INST_FREQUENCY                                       80000000
#define UART3_K230_INST_IRQHandler                              UART3_IRQHandler
#define UART3_K230_INST_INT_IRQN                                  UART3_INT_IRQn
#define GPIO_UART3_K230_RX_PORT                                            GPIOA
#define GPIO_UART3_K230_TX_PORT                                            GPIOA
#define GPIO_UART3_K230_RX_PIN                                    DL_GPIO_PIN_13
#define GPIO_UART3_K230_TX_PIN                                    DL_GPIO_PIN_14
#define GPIO_UART3_K230_IOMUX_RX                                 (IOMUX_PINCM35)
#define GPIO_UART3_K230_IOMUX_TX                                 (IOMUX_PINCM36)
#define GPIO_UART3_K230_IOMUX_RX_FUNC                  IOMUX_PINCM35_PF_UART3_RX
#define GPIO_UART3_K230_IOMUX_TX_FUNC                  IOMUX_PINCM36_PF_UART3_TX
#define UART3_K230_BAUD_RATE                                            (115200)
#define UART3_K230_IBRD_80_MHZ_115200_BAUD                                  (43)
#define UART3_K230_FBRD_80_MHZ_115200_BAUD                                  (26)





/* Port definition for Pin Group GPIO_MOTOR_DIR */
#define GPIO_MOTOR_DIR_PORT                                              (GPIOB)

/* Defines for FR_IN1: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_MOTOR_DIR_FR_IN1_PIN                               (DL_GPIO_PIN_18)
#define GPIO_MOTOR_DIR_FR_IN1_IOMUX                              (IOMUX_PINCM44)
/* Defines for FR_IN2: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GPIO_MOTOR_DIR_FR_IN2_PIN                               (DL_GPIO_PIN_19)
#define GPIO_MOTOR_DIR_FR_IN2_IOMUX                              (IOMUX_PINCM45)
/* Defines for BR_IN1: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_MOTOR_DIR_BR_IN1_PIN                               (DL_GPIO_PIN_20)
#define GPIO_MOTOR_DIR_BR_IN1_IOMUX                              (IOMUX_PINCM48)
/* Defines for BR_IN2: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_MOTOR_DIR_BR_IN2_PIN                               (DL_GPIO_PIN_21)
#define GPIO_MOTOR_DIR_BR_IN2_IOMUX                              (IOMUX_PINCM49)
/* Defines for FL_IN1: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_MOTOR_DIR_FL_IN1_PIN                               (DL_GPIO_PIN_22)
#define GPIO_MOTOR_DIR_FL_IN1_IOMUX                              (IOMUX_PINCM50)
/* Defines for FL_IN2: GPIOB.23 with pinCMx 51 on package pin 22 */
#define GPIO_MOTOR_DIR_FL_IN2_PIN                               (DL_GPIO_PIN_23)
#define GPIO_MOTOR_DIR_FL_IN2_IOMUX                              (IOMUX_PINCM51)
/* Defines for BL_IN1: GPIOB.25 with pinCMx 56 on package pin 27 */
#define GPIO_MOTOR_DIR_BL_IN1_PIN                               (DL_GPIO_PIN_25)
#define GPIO_MOTOR_DIR_BL_IN1_IOMUX                              (IOMUX_PINCM56)
/* Defines for BL_IN2: GPIOB.26 with pinCMx 57 on package pin 28 */
#define GPIO_MOTOR_DIR_BL_IN2_PIN                               (DL_GPIO_PIN_26)
#define GPIO_MOTOR_DIR_BL_IN2_IOMUX                              (IOMUX_PINCM57)
/* Port definition for Pin Group GPIO_MOTOR_ENC */
#define GPIO_MOTOR_ENC_PORT                                              (GPIOA)

/* Defines for FR_A: GPIOA.16 with pinCMx 38 on package pin 9 */
// pins affected by this interrupt request:["FR_A","FR_B","BR_A","BR_B","FL_A","FL_B","BL_A","BL_B"]
#define GPIO_MOTOR_ENC_INT_IRQN                                 (GPIOA_INT_IRQn)
#define GPIO_MOTOR_ENC_INT_IIDX                 (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_MOTOR_ENC_FR_A_IIDX                            (DL_GPIO_IIDX_DIO16)
#define GPIO_MOTOR_ENC_FR_A_PIN                                 (DL_GPIO_PIN_16)
#define GPIO_MOTOR_ENC_FR_A_IOMUX                                (IOMUX_PINCM38)
/* Defines for FR_B: GPIOA.17 with pinCMx 39 on package pin 10 */
#define GPIO_MOTOR_ENC_FR_B_IIDX                            (DL_GPIO_IIDX_DIO17)
#define GPIO_MOTOR_ENC_FR_B_PIN                                 (DL_GPIO_PIN_17)
#define GPIO_MOTOR_ENC_FR_B_IOMUX                                (IOMUX_PINCM39)
/* Defines for BR_A: GPIOA.21 with pinCMx 46 on package pin 17 */
#define GPIO_MOTOR_ENC_BR_A_IIDX                            (DL_GPIO_IIDX_DIO21)
#define GPIO_MOTOR_ENC_BR_A_PIN                                 (DL_GPIO_PIN_21)
#define GPIO_MOTOR_ENC_BR_A_IOMUX                                (IOMUX_PINCM46)
/* Defines for BR_B: GPIOA.22 with pinCMx 47 on package pin 18 */
#define GPIO_MOTOR_ENC_BR_B_IIDX                            (DL_GPIO_IIDX_DIO22)
#define GPIO_MOTOR_ENC_BR_B_PIN                                 (DL_GPIO_PIN_22)
#define GPIO_MOTOR_ENC_BR_B_IOMUX                                (IOMUX_PINCM47)
/* Defines for FL_A: GPIOA.23 with pinCMx 53 on package pin 24 */
#define GPIO_MOTOR_ENC_FL_A_IIDX                            (DL_GPIO_IIDX_DIO23)
#define GPIO_MOTOR_ENC_FL_A_PIN                                 (DL_GPIO_PIN_23)
#define GPIO_MOTOR_ENC_FL_A_IOMUX                                (IOMUX_PINCM53)
/* Defines for FL_B: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_MOTOR_ENC_FL_B_IIDX                            (DL_GPIO_IIDX_DIO24)
#define GPIO_MOTOR_ENC_FL_B_PIN                                 (DL_GPIO_PIN_24)
#define GPIO_MOTOR_ENC_FL_B_IOMUX                                (IOMUX_PINCM54)
/* Defines for BL_A: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_MOTOR_ENC_BL_A_IIDX                            (DL_GPIO_IIDX_DIO26)
#define GPIO_MOTOR_ENC_BL_A_PIN                                 (DL_GPIO_PIN_26)
#define GPIO_MOTOR_ENC_BL_A_IOMUX                                (IOMUX_PINCM59)
/* Defines for BL_B: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_MOTOR_ENC_BL_B_IIDX                            (DL_GPIO_IIDX_DIO27)
#define GPIO_MOTOR_ENC_BL_B_PIN                                 (DL_GPIO_PIN_27)
#define GPIO_MOTOR_ENC_BL_B_IOMUX                                (IOMUX_PINCM60)
/* Defines for LED: GPIOB.14 with pinCMx 31 on package pin 2 */
#define GPIO_PERIPH_LED_PORT                                             (GPIOB)
#define GPIO_PERIPH_LED_PIN                                     (DL_GPIO_PIN_14)
#define GPIO_PERIPH_LED_IOMUX                                    (IOMUX_PINCM31)
/* Defines for BUZZER: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_PERIPH_BUZZER_PORT                                          (GPIOA)
#define GPIO_PERIPH_BUZZER_PIN                                  (DL_GPIO_PIN_12)
#define GPIO_PERIPH_BUZZER_IOMUX                                 (IOMUX_PINCM34)
/* Defines for S: GPIOA.2 with pinCMx 7 on package pin 42 */
#define GPIO_PERIPH_S_PORT                                               (GPIOA)
#define GPIO_PERIPH_S_PIN                                        (DL_GPIO_PIN_2)
#define GPIO_PERIPH_S_IOMUX                                       (IOMUX_PINCM7)
/* Defines for PIN_2: GPIOA.15 with pinCMx 37 on package pin 8 */
#define GPIO_PERIPH_PIN_2_PORT                                           (GPIOA)
#define GPIO_PERIPH_PIN_2_PIN                                   (DL_GPIO_PIN_15)
#define GPIO_PERIPH_PIN_2_IOMUX                                  (IOMUX_PINCM37)
/* Defines for PIN_3: GPIOA.18 with pinCMx 40 on package pin 11 */
#define GPIO_PERIPH_PIN_3_PORT                                           (GPIOA)
#define GPIO_PERIPH_PIN_3_PIN                                   (DL_GPIO_PIN_18)
#define GPIO_PERIPH_PIN_3_IOMUX                                  (IOMUX_PINCM40)
/* Port definition for Pin Group GPIO_IR */
#define GPIO_IR_PORT                                                     (GPIOB)

/* Defines for PIN_0: GPIOB.5 with pinCMx 18 on package pin 53 */
#define GPIO_IR_PIN_0_PIN                                        (DL_GPIO_PIN_5)
#define GPIO_IR_PIN_0_IOMUX                                      (IOMUX_PINCM18)
/* Defines for PIN_1: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_IR_PIN_1_PIN                                        (DL_GPIO_PIN_6)
#define GPIO_IR_PIN_1_IOMUX                                      (IOMUX_PINCM23)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMA0_PWM_init(void);
void SYSCFG_DL_TIMER_ENC_init(void);
void SYSCFG_DL_TIMER_General_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_I2C_1_init(void);
void SYSCFG_DL_UART0_DEBUG_init(void);
void SYSCFG_DL_UART1_JY901S_init(void);
void SYSCFG_DL_UART2_LCD_init(void);
void SYSCFG_DL_UART3_K230_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
