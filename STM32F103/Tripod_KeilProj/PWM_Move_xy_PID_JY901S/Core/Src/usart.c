/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
	
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "STP.h"
#include "JY901S.H"

#define MAX_POINTS 200

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

uint8_t g_ucUsart1ReceiveData;
uint8_t jy901s_rx_buffer;
uint8_t g_ucUsart2ReceiveCounter1,g_ucUsart2ReceiveCounter2;
uint8_t g_ucUsart2CenterBuf[20];
uint8_t g_ucUsart1TargetBuf[20];
uint16_t center_x_pixel = 0;
uint16_t now_x_pixel = 0;
uint16_t now_y_pixel = 0;
uint16_t center_y_pixel = 0;
uint16_t point_count = 0;
uint16_t target_x_pixel = 0;
uint16_t target_y_pixel = 0;
uint8_t flag1,flag2;
uint8_t flagjy = 0;
bool points_rcvd_now = false;
bool points_rcvd_target = false;
bool task3_start = false;

extern bool jy901s_frame_ready;
extern uint8_t jy901s_rx_data[JY901S_FRAME_LEN];
extern uint8_t task_flag;

uint16_t target_points[MAX_POINTS][2];

void usartCamera_Receive_Data(uint8_t data);

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
	if (huart == &huart1) 
	{
//HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // 翻转LED确认代码走到这里
		static uint8_t i = 0;
		if (g_ucUsart1ReceiveData == '\n') //0x0A
		{ 
			g_ucUsart1TargetBuf[i] = '\0';// 结束当前字符串
			
			uint16_t x, y,z;
			
// 解析接收到的数据，根据格式 "c,%hu,%hu"
		if (sscanf((char*)g_ucUsart1TargetBuf, "c,%hu,%hu", &x, &y) == 2) 
		{
			now_x_pixel = 800 - x;
			now_y_pixel = 480 - y;
			points_rcvd_now = true;
		}
		else if (sscanf((char*)g_ucUsart1TargetBuf, "t,%hu,%hu", &x, &y) == 2) 
		{
			target_x_pixel = 800 - x;
			target_y_pixel = 480 - y;
			points_rcvd_target = true;
		}
		else if (sscanf((char*)g_ucUsart1TargetBuf, "f,%hu", &x) == 1) //切换任务
		{
			task_flag = x;
		}
		else if(sscanf((char*)g_ucUsart1TargetBuf, "s,%hu", &x) == 1) //基础任务3中识别到框停止自转
		{
			if(x == 1)
			{
				task3_start = true;
			}
		}
			i = 0;// 重置索引
		} 
		else 
		{
			g_ucUsart1TargetBuf[i] = g_ucUsart1ReceiveData;// 存储接收到的字符
			i++;// 增加索引
		}
		HAL_UART_Receive_IT(&huart1, &g_ucUsart1ReceiveData, 1);
	}
	
   if (huart == &huart3)  {
					static uint8_t jy901s_rx_index = 0;
        // 查找帧头 0x55 0x53
        if (jy901s_rx_index == 0) {
            if (jy901s_rx_buffer == JY901S_FRAME_HEAD1) {
                jy901s_rx_data[jy901s_rx_index++] = jy901s_rx_buffer;
            }
        } else if (jy901s_rx_index == 1) {
            if (jy901s_rx_buffer == JY901S_FRAME_HEAD2) {
                jy901s_rx_data[jy901s_rx_index++] = jy901s_rx_buffer;
            } else {
                jy901s_rx_index = 0;
            }
        } else {
            jy901s_rx_data[jy901s_rx_index++] = jy901s_rx_buffer;
            if (jy901s_rx_index >= JY901S_FRAME_LEN) {
                jy901s_frame_ready = true;
							  flagjy = 1;
                jy901s_rx_index = 0;
            }
        }
        HAL_UART_Receive_IT(&huart3, &jy901s_rx_buffer, 1);
    }
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart == &huart1)//判断中断源 是否来自串口一
//	{
//		//这里增加解析函数		
//		usartCamera_Receive_Data(g_ucUsart1ReceiveData);
//		HAL_UART_Receive_IT(&huart1,&g_ucUsart1ReceiveData,1); //启动串口一接收数据
//	}
//}

//void usartCamera_Receive_Data(uint8_t data)
//{
//	
//////当前坐标
////
//	
////	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//    static uint8_t state1 = 0;//定义静态static1 变量
//	  static uint8_t state2 = 0;//定义静态static 变量
////		static uint8_t COU = 0;//定义静态static 变量
//    if(state1==0&&data==0xFF) //判断第一个是不是帧头FRAME_HEADER 0xFF
//    {
//        state1=1;//是帧头FRAME_HEADER 0xFF 赋值state=1 表示接收下一个数据
//        //数据存储在数组中 "g_ucUsart2ReceivCounter++",这里是先用后加，比如g_ucUsart2ReceivCounter 初值为0，执行这个是先g_ucaUsart2ReceiveBuffer[0]=data，然后g_ucUsart2ReceivCounter++，即后g_ucUsart2ReceivCounter = 1的
//        g_ucUsart2CenterBuf[g_ucUsart2ReceiveCounter1++] = data;
//    }
//    else if(state1==1&&data==0xFF) //第二个是不是帧头FRAME_MID 0xFF
//    {
////				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        state1=2;//如果第二个是帧头0xFF 赋值state=2 表示接收下一个数据
//        g_ucUsart2CenterBuf[g_ucUsart2ReceiveCounter1++] = data;//保存数据
//    }
//    else if(state1==2)//然后确定开头是0XFF 0XFF 就开始接收
//    {
////				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        g_ucUsart2CenterBuf[g_ucUsart2ReceiveCounter1++]=data;
//        if(data==0xFE) 
//				{
//					state1 = 0;					//这里就可以处理数据了、处理完记得清空数组和重置标志位与计数值
//					flag1 = 1;
//					g_ucUsart2ReceiveCounter1 = 0;//清零计数值
//				
//					now_x_pixel = ((g_ucUsart2CenterBuf[2]<<8)|g_ucUsart2CenterBuf[3]);
//					now_y_pixel = ((g_ucUsart2CenterBuf[4]<<8)|g_ucUsart2CenterBuf[5]);					

//					//2.然后清空数组
//					for(int i=0;i<10;i++) g_ucUsart2CenterBuf[i]=0x00;//清空数组
//				}//接收到帧尾0XFE 就停止接收
//				else if(g_ucUsart2ReceiveCounter1>9) 
//				{
//					state1=0;
//					g_ucUsart2ReceiveCounter1 =0;
//					for(int i=0;i<10;i++) g_ucUsart2CenterBuf[i]=0x00;
//				}//接收大于9个 数据无效，清空

////			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//    }
//    else
//    {	//其他异常清空
//        state1=0;
//        g_ucUsart2ReceiveCounter1 =0;
//        for(int i=0;i<10;i++) g_ucUsart2CenterBuf[i]=0x00;//清空数组
//    }
//		

//////		目标
////		
//		
//    if(state2==0&&data==0xFD) //判断第一个是不是帧头FRAME_HEADER 0xFD
//    {
//        state2=1;//是帧头FRAME_HEADER 0xFD 赋值state=1 表示接收下一个数据
//        //数据存储在数组中 "g_ucUsart2ReceivCounter++",这里是先用后加，比如g_ucUsart2ReceivCounter 初值为0，执行这个是先g_ucaUsart2ReceiveBuffer[0]=data，然后g_ucUsart2ReceivCounter++，即后g_ucUsart2ReceivCounter = 1的
//        g_ucUsart1TargetBuf[g_ucUsart2ReceiveCounter2++] = data;
//    }
//    else if(state2==1&&data==0xFD) //第二个是不是帧头FRAME_MID 0xFD
//    {
////				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        state2=2;//如果第二个是帧头0xFD 赋值state=2 表示接收下一个数据
//        g_ucUsart1TargetBuf[g_ucUsart2ReceiveCounter2++] = data;//保存数据
//    }
//    else if(state2==2)//然后确定开头是0XFD 0XFD 就开始接收
//		{
////				HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        g_ucUsart1TargetBuf[g_ucUsart2ReceiveCounter2++]=data;
//        if(data==0xFC) 
//				{
//					state2 = 0;					//这里就可以处理数据了、处理完记得清空数组和重置标志位与计数值
//					flag2 = 1;
//					g_ucUsart2ReceiveCounter2 = 0;//清零计数值
//					
//				target_x_pixel = (g_ucUsart1TargetBuf[2]<<8)|g_ucUsart1TargetBuf[3];
//			  target_y_pixel = (g_ucUsart1TargetBuf[4]<<8)|g_ucUsart1TargetBuf[5];
//				
//					//2.然后清空数组
//					for(int i=0;i<10;i++) g_ucUsart1TargetBuf[i]=0x00;//清空数组
//				}//接收到帧尾0XFC 就停止接收
//				else if(g_ucUsart2ReceiveCounter2>9) 
//				{
//					state2=0;
//					g_ucUsart2ReceiveCounter2 =0;
//					for(int i=0;i<10;i++) g_ucUsart1TargetBuf[i]=0x00;
//				}//接收大于9个 数据无效，清空

////			HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//    }
//    else
//    {	//其他异常清空
//        state2=0;
//        g_ucUsart2ReceiveCounter2 =0;
//        for(int i=0;i<10;i++) g_ucUsart1TargetBuf[i]=0x00;//清空数组
//    }
//}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
//{
//	if (huart == &huart1) 
//	{
//		static uint8_t i,k;
//		k = 0;
//		i = 0;
//		if (g_ucUsart1ReceiveData == '\n') 
//		{
//			g_ucUsart1TargetBuf[i] = '\0';

//			uint16_t x, y,z;
//			if (sscanf((char*)g_ucUsart1TargetBuf, "c,%hu,%hu,%hu", &x, &y,&z) == 3) 
//			{
//				center_x_pixel = x;
//				center_y_pixel = y;
//				point_count = z;
//			} 
//			else if (sscanf((char*)g_ucUsart1TargetBuf, "t,%hu,%hu", &x, &y) == 2) 
//			{
//				target_points[k][0] = x; // X
//				target_points[k][1] = y; // Y	
//				k++;
//			}

//			i = 0;
//		} 
//		else if (g_ucUsart1ReceiveData == '\\') 
//		{
//      points_rcvd = true;
//		}
//		else 
//		{
//			g_ucUsart1TargetBuf[i] = g_ucUsart1ReceiveData;
//			i++;
//		}
//		HAL_UART_Receive_IT(&huart1, &g_ucUsart1ReceiveData, 1);
//	}
//}	

/* USER CODE END 1 */
