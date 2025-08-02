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


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define GPIO_LFXT_PORT                                                     GPIOA
#define GPIO_LFXIN_PIN                                             DL_GPIO_PIN_3
#define GPIO_LFXIN_IOMUX                                          (IOMUX_PINCM8)
#define GPIO_LFXOUT_PIN                                            DL_GPIO_PIN_4
#define GPIO_LFXOUT_IOMUX                                         (IOMUX_PINCM9)
#define CPUCLK_FREQ                                                     80000000



/* Defines for MOTOR_PWM */
#define MOTOR_PWM_INST                                                     TIMA0
#define MOTOR_PWM_INST_IRQHandler                               TIMA0_IRQHandler
#define MOTOR_PWM_INST_INT_IRQN                                 (TIMA0_INT_IRQn)
#define MOTOR_PWM_INST_CLK_FREQ                                         10000000
/* GPIO defines for channel 0 */
#define GPIO_MOTOR_PWM_C0_PORT                                             GPIOA
#define GPIO_MOTOR_PWM_C0_PIN                                     DL_GPIO_PIN_21
#define GPIO_MOTOR_PWM_C0_IOMUX                                  (IOMUX_PINCM46)
#define GPIO_MOTOR_PWM_C0_IOMUX_FUNC                 IOMUX_PINCM46_PF_TIMA0_CCP0
#define GPIO_MOTOR_PWM_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_MOTOR_PWM_C1_PORT                                             GPIOA
#define GPIO_MOTOR_PWM_C1_PIN                                     DL_GPIO_PIN_22
#define GPIO_MOTOR_PWM_C1_IOMUX                                  (IOMUX_PINCM47)
#define GPIO_MOTOR_PWM_C1_IOMUX_FUNC                 IOMUX_PINCM47_PF_TIMA0_CCP1
#define GPIO_MOTOR_PWM_C1_IDX                                DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 2 */
#define GPIO_MOTOR_PWM_C2_PORT                                             GPIOB
#define GPIO_MOTOR_PWM_C2_PIN                                     DL_GPIO_PIN_20
#define GPIO_MOTOR_PWM_C2_IOMUX                                  (IOMUX_PINCM48)
#define GPIO_MOTOR_PWM_C2_IOMUX_FUNC                 IOMUX_PINCM48_PF_TIMA0_CCP2
#define GPIO_MOTOR_PWM_C2_IDX                                DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 3 */
#define GPIO_MOTOR_PWM_C3_PORT                                             GPIOB
#define GPIO_MOTOR_PWM_C3_PIN                                     DL_GPIO_PIN_24
#define GPIO_MOTOR_PWM_C3_IOMUX                                  (IOMUX_PINCM52)
#define GPIO_MOTOR_PWM_C3_IOMUX_FUNC                 IOMUX_PINCM52_PF_TIMA0_CCP3
#define GPIO_MOTOR_PWM_C3_IDX                                DL_TIMER_CC_3_INDEX



/* Defines for TIMER_ENC */
#define TIMER_ENC_INST                                                   (TIMG0)
#define TIMER_ENC_INST_IRQHandler                               TIMG0_IRQHandler
#define TIMER_ENC_INST_INT_IRQN                                 (TIMG0_INT_IRQn)
#define TIMER_ENC_INST_LOAD_VALUE                                        (9999U)




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
#define GPIO_I2C_1_SDA_PORT                                                GPIOA
#define GPIO_I2C_1_SDA_PIN                                        DL_GPIO_PIN_16
#define GPIO_I2C_1_IOMUX_SDA                                     (IOMUX_PINCM38)
#define GPIO_I2C_1_IOMUX_SDA_FUNC                      IOMUX_PINCM38_PF_I2C1_SDA
#define GPIO_I2C_1_SCL_PORT                                                GPIOA
#define GPIO_I2C_1_SCL_PIN                                        DL_GPIO_PIN_17
#define GPIO_I2C_1_IOMUX_SCL                                     (IOMUX_PINCM39)
#define GPIO_I2C_1_IOMUX_SCL_FUNC                      IOMUX_PINCM39_PF_I2C1_SCL


/* Defines for UART_DEBUG */
#define UART_DEBUG_INST                                                    UART0
#define UART_DEBUG_INST_FREQUENCY                                        4000000
#define UART_DEBUG_INST_IRQHandler                              UART0_IRQHandler
#define UART_DEBUG_INST_INT_IRQN                                  UART0_INT_IRQn
#define GPIO_UART_DEBUG_RX_PORT                                            GPIOA
#define GPIO_UART_DEBUG_TX_PORT                                            GPIOA
#define GPIO_UART_DEBUG_RX_PIN                                    DL_GPIO_PIN_11
#define GPIO_UART_DEBUG_TX_PIN                                    DL_GPIO_PIN_10
#define GPIO_UART_DEBUG_IOMUX_RX                                 (IOMUX_PINCM22)
#define GPIO_UART_DEBUG_IOMUX_TX                                 (IOMUX_PINCM21)
#define GPIO_UART_DEBUG_IOMUX_RX_FUNC                  IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_DEBUG_IOMUX_TX_FUNC                  IOMUX_PINCM21_PF_UART0_TX
#define UART_DEBUG_BAUD_RATE                                            (115200)
#define UART_DEBUG_IBRD_4_MHZ_115200_BAUD                                    (2)
#define UART_DEBUG_FBRD_4_MHZ_115200_BAUD                                   (11)
/* Defines for UART_JY901S */
#define UART_JY901S_INST                                                   UART1
#define UART_JY901S_INST_FREQUENCY                                       4000000
#define UART_JY901S_INST_IRQHandler                             UART1_IRQHandler
#define UART_JY901S_INST_INT_IRQN                                 UART1_INT_IRQn
#define GPIO_UART_JY901S_RX_PORT                                           GPIOB
#define GPIO_UART_JY901S_TX_PORT                                           GPIOB
#define GPIO_UART_JY901S_RX_PIN                                    DL_GPIO_PIN_5
#define GPIO_UART_JY901S_TX_PIN                                    DL_GPIO_PIN_4
#define GPIO_UART_JY901S_IOMUX_RX                                (IOMUX_PINCM18)
#define GPIO_UART_JY901S_IOMUX_TX                                (IOMUX_PINCM17)
#define GPIO_UART_JY901S_IOMUX_RX_FUNC                 IOMUX_PINCM18_PF_UART1_RX
#define GPIO_UART_JY901S_IOMUX_TX_FUNC                 IOMUX_PINCM17_PF_UART1_TX
#define UART_JY901S_BAUD_RATE                                           (115200)
#define UART_JY901S_IBRD_4_MHZ_115200_BAUD                                   (2)
#define UART_JY901S_FBRD_4_MHZ_115200_BAUD                                  (11)





/* Port definition for Pin Group DEBUG */
#define DEBUG_PORT                                                       (GPIOB)

/* Defines for LED: GPIOB.14 with pinCMx 31 on package pin 2 */
#define DEBUG_LED_PIN                                           (DL_GPIO_PIN_14)
#define DEBUG_LED_IOMUX                                          (IOMUX_PINCM31)
/* Port definition for Pin Group ENCODER */
#define ENCODER_PORT                                                     (GPIOA)

/* Defines for A1: GPIOA.13 with pinCMx 35 on package pin 6 */
// pins affected by this interrupt request:["A1","B1","A2","B2"]
#define ENCODER_INT_IRQN                                        (GPIOA_INT_IRQn)
#define ENCODER_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define ENCODER_A1_IIDX                                     (DL_GPIO_IIDX_DIO13)
#define ENCODER_A1_PIN                                          (DL_GPIO_PIN_13)
#define ENCODER_A1_IOMUX                                         (IOMUX_PINCM35)
/* Defines for B1: GPIOA.14 with pinCMx 36 on package pin 7 */
#define ENCODER_B1_IIDX                                     (DL_GPIO_IIDX_DIO14)
#define ENCODER_B1_PIN                                          (DL_GPIO_PIN_14)
#define ENCODER_B1_IOMUX                                         (IOMUX_PINCM36)
/* Defines for A2: GPIOA.8 with pinCMx 19 on package pin 54 */
#define ENCODER_A2_IIDX                                      (DL_GPIO_IIDX_DIO8)
#define ENCODER_A2_PIN                                           (DL_GPIO_PIN_8)
#define ENCODER_A2_IOMUX                                         (IOMUX_PINCM19)
/* Defines for B2: GPIOA.9 with pinCMx 20 on package pin 55 */
#define ENCODER_B2_IIDX                                      (DL_GPIO_IIDX_DIO9)
#define ENCODER_B2_PIN                                           (DL_GPIO_PIN_9)
#define ENCODER_B2_IOMUX                                         (IOMUX_PINCM20)
/* Port definition for Pin Group MOTOR_DIR */
#define MOTOR_DIR_PORT                                                   (GPIOA)

/* Defines for IN1: GPIOA.23 with pinCMx 53 on package pin 24 */
#define MOTOR_DIR_IN1_PIN                                       (DL_GPIO_PIN_23)
#define MOTOR_DIR_IN1_IOMUX                                      (IOMUX_PINCM53)
/* Defines for IN2: GPIOA.24 with pinCMx 54 on package pin 25 */
#define MOTOR_DIR_IN2_PIN                                       (DL_GPIO_PIN_24)
#define MOTOR_DIR_IN2_IOMUX                                      (IOMUX_PINCM54)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_MOTOR_PWM_init(void);
void SYSCFG_DL_TIMER_ENC_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_I2C_1_init(void);
void SYSCFG_DL_UART_DEBUG_init(void);
void SYSCFG_DL_UART_JY901S_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
