#include "STP.h"
#include <math.h> 
#include <string.h>
#include "PID.H"

extern pid_typedef pidx;
extern pid_typedef pidy;

static float last_freq_x = 0;
static float last_freq_y = 0;
float freq_x = 0;
float freq_y = 0;

// ���巽����Ʊ���
_Bool cntDir = 0;

//char tx_buff[256];

extern volatile uint32_t step_target_X;   // Ŀ�경��
extern volatile uint32_t step_counter_X;  // ��ǰ����

extern volatile uint32_t step_target_Y ;   // Ŀ�경��
extern volatile uint32_t step_counter_Y ;  // ��ǰ����

void uart1_send_string(const char *str)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

int fputc(int ch,FILE *f)
{
	uint8_t temp[1] = {ch};
	
	HAL_UART_Transmit(&huart1,temp,1,2);
	return ch;
}

// ��������Ƶ�ʵ���ʱ
void delay_cnt(uint32_t cnt)
{
    for (uint32_t i = 0; i < cnt; i++) {
        for (uint32_t j = 0; j < 100; j++) {
            __NOP();
        }
    }
}

/// �޷�������ȷ���Ƕ�����Ч��Χ��
float clamp(float val, float min, float max)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

// ������ʱ����
void delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

// X������
void STP_StepAngle_X(float angle_deg, _Bool dir)
{
   step_target_X = (uint32_t)round(angle_deg / STEP_ANGLE);
   step_counter_X = 0;

   HAL_GPIO_WritePin(DIR_X_GPIO_Port, DIR_X_Pin, dir ? GPIO_PIN_SET : GPIO_PIN_RESET);
	
	    // ���� TIM2 �� ARR�����ڼĴ�����
   uint32_t timer_clk = HAL_RCC_GetPCLK1Freq() * 2;  
   uint32_t psc = htim2.Init.Prescaler + 1;
   uint32_t arr = (uint32_t)((float)timer_clk / (psc * 300)) - 1;

   // ���� arr �Ϸ���Χ
   if (arr > 0xFFFF) arr = 0xFFFF;
   if (arr < 10) arr = 10;
	
		__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);      // ���ø����ж�
	  __HAL_TIM_SET_AUTORELOAD(&htim2, arr);
   HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
   __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, __HAL_TIM_GET_AUTORELOAD(&htim2) / 2);
}

//// Y������
//void STP_PWM_Start_Y(float angle_deg, _Bool dir)
//{
//    step_target_Y = (uint32_t)round(angle_deg / STEP_ANGLE);
//    step_counter_Y = 0;

//    HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, dir ? GPIO_PIN_SET : GPIO_PIN_RESET);

//		__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);      // ���ø����ж�
//    HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
//    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, __HAL_TIM_GET_AUTORELOAD(&htim3) / 2);
//}

// X������
void STP_PWM_Start_X(int freq, float err)
{
    HAL_GPIO_WritePin(DIR_X_GPIO_Port, DIR_X_Pin, (err > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	
	    // ���� TIM2 �� ARR�����ڼĴ�����
    uint32_t timer_clk = HAL_RCC_GetPCLK1Freq() * 2;  
    uint32_t psc = htim2.Init.Prescaler + 1;
    uint32_t arr = (uint32_t)((float)timer_clk / (psc * freq)) - 1;

    // ���� arr �Ϸ���Χ
    if (arr > 0xFFFF) arr = 0xFFFF;
    if (arr < 10) arr = 10;
	
	  __HAL_TIM_SET_AUTORELOAD(&htim2, arr);
    HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, __HAL_TIM_GET_AUTORELOAD(&htim2) / 2);
}

// Y������
void STP_PWM_Start_Y(int freq, float err)
{
    HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, (err > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	
		    // ���� TIM2 �� ARR�����ڼĴ�����
    uint32_t timer_clk = HAL_RCC_GetPCLK1Freq() * 2;  
    uint32_t psc = htim2.Init.Prescaler + 1;
    uint32_t arr = (uint32_t)((float)timer_clk / (psc * freq)) - 1;

    // ���� arr �Ϸ���Χ
    if (arr > 0xFFFF) arr = 0xFFFF;
    if (arr < 10) arr = 10;

		__HAL_TIM_SET_AUTORELOAD(&htim3, arr);
    HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, __HAL_TIM_GET_AUTORELOAD(&htim3) / 2);
}

void X_STP_PWM_SpeedControl(float pid_output)
{
    // ������PID ���̫С�Ͳ���
    if (fabs(pid_output) < 0.01f) {
				HAL_GPIO_WritePin(EN_X_GPIO_Port, EN_X_Pin, GPIO_PIN_RESET);
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
			  last_freq_x = 0;  // ����Ƶ��
        return;
    }

//		if (fabs(pidx.err) < 5) {
//        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
//        return;
//    }
		
    // ���÷���
		if (pid_output >= 0)
				HAL_GPIO_WritePin(DIR_X_GPIO_Port, DIR_X_Pin, GPIO_PIN_SET);
		else
				HAL_GPIO_WritePin(DIR_X_GPIO_Port, DIR_X_Pin, GPIO_PIN_RESET);

    // ӳ�� PID [-10, 10] ��Ƶ�� [3000, 7000] Hz
    float MIN_FREQ = 2000.0f;   // ��С�ٶ�
		float MAX_FREQ = 18000.0f;  // ����ٶ�

		float scale = fabs(pid_output) / 10.0f;
//	��	
		float freq = MIN_FREQ + scale * (MAX_FREQ - MIN_FREQ);
//		float freq = MIN_FREQ + pid_output * 20;
//float freq_raw = MIN_FREQ + scale * (MAX_FREQ - MIN_FREQ);

//// ƽ���˲�����ͨ��
//float alpha = 0.4f; // ƽ�����ӣ�ԽСԽ���
//float freq = last_freq_x + alpha * (freq_raw - last_freq_x);
		
// ����Ƶ�����䣨����������ɲ����
//    float delta = freq - last_freq_x;
//    if (delta > 1000) delta = 1000;
//    if (delta < -1000) delta = -1000;
//    freq = last_freq_x + delta;
//    last_freq_x = freq;

		if (freq < MIN_FREQ) freq = MIN_FREQ;  // ��С�ٶ�����
    if (freq > MAX_FREQ) freq = MAX_FREQ;
		
		freq_x = freq;
    // ���� TIM2 �� ARR�����ڼĴ�����
    uint32_t timer_clk = HAL_RCC_GetPCLK1Freq() * 2;  
    uint32_t psc = htim2.Init.Prescaler + 1;
    uint32_t arr = (uint32_t)((float)timer_clk / (psc * freq)) - 1;

    // ���� arr �Ϸ���Χ
    if (arr > 0xFFFF) arr = 0xFFFF;
    if (arr < 10) arr = 10;

    // ���� PWM
		HAL_GPIO_WritePin(EN_X_GPIO_Port, EN_X_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_AUTORELOAD(&htim2, arr);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr / 2); // ռ�ձ� 50%
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void Y_STP_PWM_SpeedControl(float pid_output)
{
    // ������PID ���̫С�Ͳ���
    if (fabs(pid_output) < 0.01f) {
        HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET);
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
        last_freq_y = 0;  // ����Ƶ��
        return;
    }

    // ���÷���
    if (pid_output >= 0)
        HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, GPIO_PIN_RESET);

    // ӳ�� PID [-10, 10] ��Ƶ�� [3000, 7000] Hz
    float MIN_FREQ = 2000.0f;   // ��С�ٶ�
    float MAX_FREQ = 10000.0f;  // ����ٶ�

    float scale = fabs(pid_output) / 10.0f;
    float freq = MIN_FREQ + scale * (MAX_FREQ - MIN_FREQ);

    if (freq < MIN_FREQ) freq = MIN_FREQ;  // ��С�ٶ�����
    if (freq > MAX_FREQ) freq = MAX_FREQ;

		freq_y = freq;

    // ���� TIM3 �� ARR�����ڼĴ�����
    uint32_t timer_clk = HAL_RCC_GetPCLK1Freq() * 2;  
    uint32_t psc = htim3.Init.Prescaler + 1;
    uint32_t arr = (uint32_t)((float)timer_clk / (psc * freq)) - 1;

    // ���� arr �Ϸ���Χ
    if (arr > 0xFFFF) arr = 0xFFFF;
    if (arr < 10) arr = 10;

    // ���� PWM
    HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_AUTORELOAD(&htim3, arr);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr / 2); // ռ�ձ� 50%
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}


//void Y_STP_PWM_SpeedControl(float pid_output)
//{
//    // ������PID ���̫С�Ͳ���
//    if (fabs(pid_output) < 0.01f) {
//				HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET);
//        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
//				last_freq_y = 0;  // ����Ƶ��
//        return;
//    }
//	
////		if (fabs(pidy.err) < 5) {
////        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
////        return;
////    }
//		
//    // ���÷���
//		if (pid_output >= 0)
//				HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, GPIO_PIN_SET);
//		else
//				HAL_GPIO_WritePin(DIR_Y_GPIO_Port, DIR_Y_Pin, GPIO_PIN_RESET);

//    // ӳ�� PID [-5, 5] ��Ƶ�� [800, 3000] Hz
//    float MIN_FREQ = 800.0f;   // ��С�ٶ�
//		float MAX_FREQ = 2500.0f;  // ����ٶ�

//		float scale = fabs(pid_output) / 5.0f;
////	��	float freq = MIN_FREQ + scale * (MAX_FREQ - MIN_FREQ);
//float freq_raw = MIN_FREQ + scale * (MAX_FREQ - MIN_FREQ);

//// ƽ���˲�����ͨ��
//float alpha = 0.2f; // ƽ�����ӣ�ԽСԽ���
//float freq = last_freq_y + alpha * (freq_raw - last_freq_y);
// // ����Ƶ�����䣨����������ɲ����
//    float delta = freq - last_freq_y;
//    if (delta > 600) delta = 600;
//    if (delta < -600) delta = -600;
//    freq = last_freq_y + delta;
//    last_freq_y = freq;
//		if (freq < MIN_FREQ) freq = MIN_FREQ;  // ��С�ٶ�����
//    if (freq > MAX_FREQ) freq = MAX_FREQ;
//		
//		freq = 2500;
//		
//		freq_y = freq;
//		
//    // ���� TIM2 �� ARR�����ڼĴ�����
//    uint32_t timer_clk = HAL_RCC_GetPCLK1Freq() * 2;  
//    uint32_t psc = htim3.Init.Prescaler + 1;
//    uint32_t arr = (uint32_t)((float)timer_clk / (psc * freq)) - 1;

//    // ���� arr �Ϸ���Χ
//    if (arr > 0xFFFF) arr = 0xFFFF;
//    if (arr < 10) arr = 10;

//    // ���� PWM
//		HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_SET);
//    __HAL_TIM_SET_AUTORELOAD(&htim3, arr);
//    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr / 2); // ռ�ձ� 50%
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//}


