/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define UART1_HW_AVAILABLE    1

#if UART1_HW_AVAILABLE
#define UART1_USE_DMA         1
#endif
#if UART2_HW_AVAILABLE
#define UART2_USE_DMA         1
#endif

#if UART3_HW_AVAILABLE
#define UART3_USE_DMA        	1
#endif


#define UART_DMA_BUF_SIZE     512
#define UART_RINGBUF_SIZE     1024


/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

#define USART1_DMA_REC_SIE 256
#define USART1_REC_SIE 512


/* USER CODE BEGIN Private defines */
		
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */
 
uint32_t 	uart1_send(const void *buf ,uint32_t len);
void 			uart1_putstr(const char *str); 
uint32_t 	uart1_buflen(void);
uint32_t 	uart1_read(void *buf, uint32_t len);
uint32_t  uart1_blocking_send(void *buf ,uint32_t len);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
