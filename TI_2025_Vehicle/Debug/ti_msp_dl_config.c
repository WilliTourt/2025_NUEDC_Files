/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gTIMA0_PWMBackup;
DL_TimerG_backupConfig gTIMER_GeneralBackup;
DL_UART_Main_backupConfig gUART3_K230Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_TIMA0_PWM_init();
    SYSCFG_DL_TIMER_ENC_init();
    SYSCFG_DL_TIMER_General_init();
    SYSCFG_DL_I2C_0_init();
    SYSCFG_DL_I2C_1_init();
    SYSCFG_DL_UART0_DEBUG_init();
    SYSCFG_DL_UART1_JY901S_init();
    SYSCFG_DL_UART2_LCD_init();
    SYSCFG_DL_UART3_K230_init();
    /* Ensure backup structures have no valid state */
	gTIMA0_PWMBackup.backupRdy 	= false;
	gTIMER_GeneralBackup.backupRdy 	= false;
	gUART3_K230Backup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(TIMA0_PWM_INST, &gTIMA0_PWMBackup);
	retStatus &= DL_TimerG_saveConfiguration(TIMER_General_INST, &gTIMER_GeneralBackup);
	retStatus &= DL_UART_Main_saveConfiguration(UART3_K230_INST, &gUART3_K230Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(TIMA0_PWM_INST, &gTIMA0_PWMBackup, false);
	retStatus &= DL_TimerG_restoreConfiguration(TIMER_General_INST, &gTIMER_GeneralBackup, false);
	retStatus &= DL_UART_Main_restoreConfiguration(UART3_K230_INST, &gUART3_K230Backup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(TIMA0_PWM_INST);
    DL_TimerG_reset(TIMER_ENC_INST);
    DL_TimerG_reset(TIMER_General_INST);
    DL_I2C_reset(I2C_0_INST);
    DL_I2C_reset(I2C_1_INST);
    DL_UART_Main_reset(UART0_DEBUG_INST);
    DL_UART_Main_reset(UART1_JY901S_INST);
    DL_UART_Main_reset(UART2_LCD_INST);
    DL_UART_Main_reset(UART3_K230_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(TIMA0_PWM_INST);
    DL_TimerG_enablePower(TIMER_ENC_INST);
    DL_TimerG_enablePower(TIMER_General_INST);
    DL_I2C_enablePower(I2C_0_INST);
    DL_I2C_enablePower(I2C_1_INST);
    DL_UART_Main_enablePower(UART0_DEBUG_INST);
    DL_UART_Main_enablePower(UART1_JY901S_INST);
    DL_UART_Main_enablePower(UART2_LCD_INST);
    DL_UART_Main_enablePower(UART3_K230_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_TIMA0_PWM_C0_IOMUX,GPIO_TIMA0_PWM_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_TIMA0_PWM_C0_PORT, GPIO_TIMA0_PWM_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_TIMA0_PWM_C1_IOMUX,GPIO_TIMA0_PWM_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_TIMA0_PWM_C1_PORT, GPIO_TIMA0_PWM_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_TIMA0_PWM_C2_IOMUX,GPIO_TIMA0_PWM_C2_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_TIMA0_PWM_C2_PORT, GPIO_TIMA0_PWM_C2_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_TIMA0_PWM_C3_IOMUX,GPIO_TIMA0_PWM_C3_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_TIMA0_PWM_C3_PORT, GPIO_TIMA0_PWM_C3_PIN);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_0_IOMUX_SDA,
        GPIO_I2C_0_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_0_IOMUX_SCL,
        GPIO_I2C_0_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_0_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_0_IOMUX_SCL);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_1_IOMUX_SDA,
        GPIO_I2C_1_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_1_IOMUX_SCL,
        GPIO_I2C_1_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_1_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_1_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART0_DEBUG_IOMUX_TX, GPIO_UART0_DEBUG_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART0_DEBUG_IOMUX_RX, GPIO_UART0_DEBUG_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART1_JY901S_IOMUX_TX, GPIO_UART1_JY901S_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART1_JY901S_IOMUX_RX, GPIO_UART1_JY901S_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART2_LCD_IOMUX_TX, GPIO_UART2_LCD_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART2_LCD_IOMUX_RX, GPIO_UART2_LCD_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART3_K230_IOMUX_TX, GPIO_UART3_K230_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART3_K230_IOMUX_RX, GPIO_UART3_K230_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_FR_IN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_FR_IN2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_BR_IN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_BR_IN2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_FL_IN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_FL_IN2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_BL_IN1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_MOTOR_DIR_BL_IN2_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_FR_A_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_FR_B_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_BR_A_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_BR_B_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_FL_A_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_FL_B_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_BL_A_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_MOTOR_ENC_BL_B_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_PERIPH_LED_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_PERIPH_BUZZER_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_PERIPH_S_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_PERIPH_PIN_2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_PERIPH_PIN_3_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_IR_PIN_0_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_IR_PIN_1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_clearPins(GPIOA, GPIO_PERIPH_BUZZER_PIN |
		GPIO_PERIPH_PIN_2_PIN |
		GPIO_PERIPH_PIN_3_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_PERIPH_BUZZER_PIN |
		GPIO_PERIPH_PIN_2_PIN |
		GPIO_PERIPH_PIN_3_PIN);
    DL_GPIO_setUpperPinsPolarity(GPIOA, DL_GPIO_PIN_16_EDGE_RISE |
		DL_GPIO_PIN_17_EDGE_RISE |
		DL_GPIO_PIN_21_EDGE_RISE |
		DL_GPIO_PIN_22_EDGE_RISE |
		DL_GPIO_PIN_23_EDGE_RISE |
		DL_GPIO_PIN_24_EDGE_RISE |
		DL_GPIO_PIN_26_EDGE_RISE |
		DL_GPIO_PIN_27_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_MOTOR_ENC_FR_A_PIN |
		GPIO_MOTOR_ENC_FR_B_PIN |
		GPIO_MOTOR_ENC_BR_A_PIN |
		GPIO_MOTOR_ENC_BR_B_PIN |
		GPIO_MOTOR_ENC_FL_A_PIN |
		GPIO_MOTOR_ENC_FL_B_PIN |
		GPIO_MOTOR_ENC_BL_A_PIN |
		GPIO_MOTOR_ENC_BL_B_PIN);
    DL_GPIO_enableInterrupt(GPIOA, GPIO_MOTOR_ENC_FR_A_PIN |
		GPIO_MOTOR_ENC_FR_B_PIN |
		GPIO_MOTOR_ENC_BR_A_PIN |
		GPIO_MOTOR_ENC_BR_B_PIN |
		GPIO_MOTOR_ENC_FL_A_PIN |
		GPIO_MOTOR_ENC_FL_B_PIN |
		GPIO_MOTOR_ENC_BL_A_PIN |
		GPIO_MOTOR_ENC_BL_B_PIN);
    DL_GPIO_clearPins(GPIOB, GPIO_MOTOR_DIR_FR_IN1_PIN |
		GPIO_MOTOR_DIR_FR_IN2_PIN |
		GPIO_MOTOR_DIR_BR_IN1_PIN |
		GPIO_MOTOR_DIR_BR_IN2_PIN |
		GPIO_MOTOR_DIR_FL_IN1_PIN |
		GPIO_MOTOR_DIR_FL_IN2_PIN |
		GPIO_MOTOR_DIR_BL_IN1_PIN |
		GPIO_MOTOR_DIR_BL_IN2_PIN |
		GPIO_PERIPH_LED_PIN);
    DL_GPIO_enableOutput(GPIOB, GPIO_MOTOR_DIR_FR_IN1_PIN |
		GPIO_MOTOR_DIR_FR_IN2_PIN |
		GPIO_MOTOR_DIR_BR_IN1_PIN |
		GPIO_MOTOR_DIR_BR_IN2_PIN |
		GPIO_MOTOR_DIR_FL_IN1_PIN |
		GPIO_MOTOR_DIR_FL_IN2_PIN |
		GPIO_MOTOR_DIR_BL_IN1_PIN |
		GPIO_MOTOR_DIR_BL_IN2_PIN |
		GPIO_PERIPH_LED_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_32_48_MHZ,
	.rDivClk2x              = 1,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_ENABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_SYSOSC,
	.qDiv                   = 4,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_1
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setHFCLKDividerForMFPCLK(DL_SYSCTL_HFCLK_MFPCLK_DIVIDER_10);
    DL_SYSCTL_enableMFCLK();
    DL_SYSCTL_enableMFPCLK();
	DL_SYSCTL_setMFPCLKSource(DL_SYSCTL_MFPCLK_SOURCE_SYSOSC);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);
    /* INT_GROUP1 Priority */
    NVIC_SetPriority(GPIOA_INT_IRQn, 1);

}


/*
 * Timer clock configuration to be sourced by  / 8 (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   10000000 Hz = 10000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gTIMA0_PWMClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gTIMA0_PWMConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 1000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMA0_PWM_init(void) {

    DL_TimerA_setClockConfig(
        TIMA0_PWM_INST, (DL_TimerA_ClockConfig *) &gTIMA0_PWMClockConfig);

    DL_TimerA_initPWMMode(
        TIMA0_PWM_INST, (DL_TimerA_PWMConfig *) &gTIMA0_PWMConfig);

    // Set Counter control to the smallest CC index being used
    DL_TimerA_setCounterControl(TIMA0_PWM_INST,DL_TIMER_CZC_CCCTL0_ZCOND,DL_TIMER_CAC_CCCTL0_ACOND,DL_TIMER_CLC_CCCTL0_LCOND);

    DL_TimerA_setCaptureCompareOutCtl(TIMA0_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(TIMA0_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);
    DL_TimerA_setCaptureCompareValue(TIMA0_PWM_INST, 0, DL_TIMER_CC_0_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(TIMA0_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(TIMA0_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(TIMA0_PWM_INST, 0, DL_TIMER_CC_1_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(TIMA0_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_2_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(TIMA0_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_2_INDEX);
    DL_TimerA_setCaptureCompareValue(TIMA0_PWM_INST, 0, DL_TIMER_CC_2_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(TIMA0_PWM_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_3_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(TIMA0_PWM_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_3_INDEX);
    DL_TimerA_setCaptureCompareValue(TIMA0_PWM_INST, 0, DL_TIMER_CC_3_INDEX);

    DL_TimerA_enableClock(TIMA0_PWM_INST);


    
    DL_TimerA_setCCPDirection(TIMA0_PWM_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT | DL_TIMER_CC2_OUTPUT | DL_TIMER_CC3_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (5000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   500000 Hz = 5000000 Hz / (8 * (9 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_ENCClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 9U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_ENC_INST_LOAD_VALUE = (0.02 * 500000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_ENCTimerConfig = {
    .period     = TIMER_ENC_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_ENC_init(void) {

    DL_TimerG_setClockConfig(TIMER_ENC_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_ENCClockConfig);

    DL_TimerG_initTimerMode(TIMER_ENC_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_ENCTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_ENC_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_ENC_INST_INT_IRQN, 2);
    DL_TimerG_enableClock(TIMER_ENC_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 10000000 Hz / (8 * (9 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_GeneralClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 9U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_General_INST_LOAD_VALUE = (0.025 * 1000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_GeneralTimerConfig = {
    .period     = TIMER_General_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_General_init(void) {

    DL_TimerG_setClockConfig(TIMER_General_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_GeneralClockConfig);

    DL_TimerG_initTimerMode(TIMER_General_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_GeneralTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_General_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_General_INST_INT_IRQN, 1);
    DL_TimerG_enableClock(TIMER_General_INST);





}


static const DL_I2C_ClockConfig gI2C_0ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_0_init(void) {

    DL_I2C_setClockConfig(I2C_0_INST,
        (DL_I2C_ClockConfig *) &gI2C_0ClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_0_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_0_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_0_INST);
    /* Set frequency to 400000 Hz*/
    DL_I2C_setTimerPeriod(I2C_0_INST, 9);
    DL_I2C_setControllerTXFIFOThreshold(I2C_0_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(I2C_0_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_0_INST);


    /* Enable module */
    DL_I2C_enableController(I2C_0_INST);


}
static const DL_I2C_ClockConfig gI2C_1ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_1_init(void) {

    DL_I2C_setClockConfig(I2C_1_INST,
        (DL_I2C_ClockConfig *) &gI2C_1ClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_1_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_1_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_1_INST);
    /* Set frequency to 400000 Hz*/
    DL_I2C_setTimerPeriod(I2C_1_INST, 9);
    DL_I2C_setControllerTXFIFOThreshold(I2C_1_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(I2C_1_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_1_INST);


    /* Enable module */
    DL_I2C_enableController(I2C_1_INST);


}

static const DL_UART_Main_ClockConfig gUART0_DEBUGClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART0_DEBUGConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART0_DEBUG_init(void)
{
    DL_UART_Main_setClockConfig(UART0_DEBUG_INST, (DL_UART_Main_ClockConfig *) &gUART0_DEBUGClockConfig);

    DL_UART_Main_init(UART0_DEBUG_INST, (DL_UART_Main_Config *) &gUART0_DEBUGConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(UART0_DEBUG_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART0_DEBUG_INST, UART0_DEBUG_IBRD_40_MHZ_115200_BAUD, UART0_DEBUG_FBRD_40_MHZ_115200_BAUD);



    DL_UART_Main_enable(UART0_DEBUG_INST);
}
static const DL_UART_Main_ClockConfig gUART1_JY901SClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART1_JY901SConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART1_JY901S_init(void)
{
    DL_UART_Main_setClockConfig(UART1_JY901S_INST, (DL_UART_Main_ClockConfig *) &gUART1_JY901SClockConfig);

    DL_UART_Main_init(UART1_JY901S_INST, (DL_UART_Main_Config *) &gUART1_JY901SConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(UART1_JY901S_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART1_JY901S_INST, UART1_JY901S_IBRD_40_MHZ_115200_BAUD, UART1_JY901S_FBRD_40_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART1_JY901S_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART1_JY901S_INST_INT_IRQN, 2);


    DL_UART_Main_enable(UART1_JY901S_INST);
}
static const DL_UART_Main_ClockConfig gUART2_LCDClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART2_LCDConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART2_LCD_init(void)
{
    DL_UART_Main_setClockConfig(UART2_LCD_INST, (DL_UART_Main_ClockConfig *) &gUART2_LCDClockConfig);

    DL_UART_Main_init(UART2_LCD_INST, (DL_UART_Main_Config *) &gUART2_LCDConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(UART2_LCD_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART2_LCD_INST, UART2_LCD_IBRD_40_MHZ_115200_BAUD, UART2_LCD_FBRD_40_MHZ_115200_BAUD);



    DL_UART_Main_enable(UART2_LCD_INST);
}
static const DL_UART_Main_ClockConfig gUART3_K230ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART3_K230Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART3_K230_init(void)
{
    DL_UART_Main_setClockConfig(UART3_K230_INST, (DL_UART_Main_ClockConfig *) &gUART3_K230ClockConfig);

    DL_UART_Main_init(UART3_K230_INST, (DL_UART_Main_Config *) &gUART3_K230Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115190.78
     */
    DL_UART_Main_setOversampling(UART3_K230_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART3_K230_INST, UART3_K230_IBRD_80_MHZ_115200_BAUD, UART3_K230_FBRD_80_MHZ_115200_BAUD);



    DL_UART_Main_enable(UART3_K230_INST);
}

