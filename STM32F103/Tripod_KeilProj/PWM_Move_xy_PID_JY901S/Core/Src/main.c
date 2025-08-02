/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "STP.h"
#include "PID.H"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "JY901S.H"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

void uart3_send_string(const char *str)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

extern uint8_t g_ucUsart1ReceiveData;

extern pid_typedef pidx;
extern pid_typedef pidy;
// X轴
volatile uint32_t step_target_X = 0;
volatile uint32_t step_counter_X = 0;

// Y轴
volatile uint32_t step_target_Y = 0;
volatile uint32_t step_counter_Y = 0;

extern uint16_t center_x_pixel, now_x_pixel, now_y_pixel;
extern uint16_t center_y_pixel;
extern uint16_t target_x_pixel;
extern uint16_t target_y_pixel;

extern float freq_x;
extern float freq_y;

extern bool points_rcvd_now;
extern bool points_rcvd_target;
extern bool task3_start;

bool entered_from_task3 = false;

bool laser_locked = false;

float yaw = 0;
float last_yaw = 0;
float yaw_change = 0;
extern uint8_t flagjy;
extern uint8_t jy901s_rx_buffer;

// 任务标志位
uint8_t task_flag = 0;
bool PID_is_initialized = false;

#define NOW_X2 397
#define NOW_Y2 251

#define NOW_X3 404
#define NOW_Y3 240

#define TASK3_FINDING_SPD 20000

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	HAL_UART_Receive_IT(&huart1, &g_ucUsart1ReceiveData, 1);

	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
	HAL_UART_Receive_IT(&huart3, &jy901s_rx_buffer, 1);

	static uint8_t stable_counter = 0;

	unsigned char rx_buff[256] = {0};
	sprintf((char *)rx_buff, "hello_world!\r\n");
	uart1_send_string((char *)rx_buff);

	//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // 翻转LED确认代码走到这里

	//// 转90°，方向逆时针
	//		STP_PWM_Start(90.0f, 0);
	// HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin , GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN_X_GPIO_Port, EN_X_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		static uint8_t choosed_task = 0;
		if ((!choosed_task) && (HAL_GPIO_ReadPin(F4_PIN_GPIO_Port, F4_PIN_Pin))) {
			choosed_task = task_flag;
		}
		////JY901S_code开始
		//		if (JY901S_Decode())
		//		{
		//			static float yaw_read = 0;
		//			static float last_yaw_read = 0;
		//			yaw_read = JY901S_GetYaw();
		//
		//			yaw = yaw_read;
		//			if (last_yaw_read - yaw_read > 300) {
		//				yaw += 360;
		//			}
		//
		//			yaw_change = yaw - last_yaw;
		//
		//			last_yaw = yaw;
		//			last_yaw_read = yaw_read;
		//
		//			if(flagjy){
		//				flagjy = 0;
		//			char msg2[32];
		//							 sprintf(msg2, "yaw_read=%f\r\n",
		//										yaw_read);
		//							uart3_send_string((char *)msg2);
		//							memset(msg2,0,32);}
		//		}
		//		HAL_Delay(5);

		if (choosed_task == 2)
		{
			if (!PID_is_initialized) {
				X_PID_init(0.15, 0, 0.004);
				Y_PID_init(0.08, 0, 0.002);
				PID_is_initialized = true;		
			}

			// 如果目标坐标未更新，停电机，防止乱跑
			if (!points_rcvd_target)
			{
				HAL_GPIO_WritePin(EN_X_GPIO_Port, EN_X_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET);

				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
				HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
				continue; // 直接跳过本轮循环
			}

			if (points_rcvd_target)
			{
				// 计算 PID 输出
				float out_x = PIDx_realize((entered_from_task3 ? NOW_X3 : NOW_X2), target_x_pixel);
				float out_y = PIDy_realize((entered_from_task3 ? NOW_Y3 : NOW_Y2), target_y_pixel);
				// 当两轴都进入死区，视为命中
				if (fabs(pidx.err) < 4.0f && fabs(pidy.err) < 4.0f)
				{
					HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin, GPIO_PIN_SET);
					points_rcvd_target = false;
					//							stable_counter++;
					//								if (stable_counter >= 3) // 连续 3 帧都在误差范围内
					//								{
					pidx.err_sum = 0;
					pidy.err_sum = 0;
					pidx.err = 0;
					pidy.err = 0;

					HAL_GPIO_WritePin(EN_X_GPIO_Port, EN_X_Pin, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(EN_Y_GPIO_Port, EN_Y_Pin, GPIO_PIN_RESET);
					HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
					choosed_task = 0;
					stable_counter = 0;
					laser_locked = true;
					//									HAL_Delay(2000);
					//									HAL_GPIO_WritePin(LASER_GPIO_Port, LASER_Pin , GPIO_PIN_RESET);

					//					char msg_hit[64];
					//					sprintf(msg_hit, ">>> HIT target STABLE\r\n");
					//					uart1_send_string(msg_hit);
					//							}
				}
				else
				{
					stable_counter = 0;
					// 正在接近	中
					X_STP_PWM_SpeedControl(out_x);
					Y_STP_PWM_SpeedControl(out_y);
				}
			}
		}

		if (choosed_task == 3)
		{
			if (!points_rcvd_target)
			{
				STP_PWM_Start_X(1500, 1);
				delay_ms(400);
				STP_PWM_Start_X(TASK3_FINDING_SPD, 1);
				delay_ms(300);
			}

			if (points_rcvd_target)
			{
				entered_from_task3 = true;
				choosed_task = 2;
			}

		}

		if (choosed_task == 4)
		{
			if (!points_rcvd_target)
			{
				STP_PWM_Start_X(2000, 0);
				delay_ms(400);
				STP_PWM_Start_X(TASK3_FINDING_SPD, 0);
				delay_ms(290);
			}

			if (points_rcvd_target)
			{
				entered_from_task3 = true;
				choosed_task = 2;
			}

		}

		if (points_rcvd_target == true)
		{
			points_rcvd_target = false;
			char msg2[85];
			sprintf(msg2, "target_x_pixel=%d,target_y_pixel=%d,freq_x=%f,freq_y=%f\r\n",
					target_x_pixel, target_y_pixel, freq_x, freq_y);
			uart1_send_string((char *)msg2);
			memset(msg2, 0, 85);
		}

		HAL_Delay(1); // 控制刷新频率

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
