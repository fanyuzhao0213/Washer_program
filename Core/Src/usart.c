/**
  ******************************************************************************
  * File Name          : USART.c
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <rtthread.h>
#include "ringbuffer.h"
#include <string.h>
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;



#if UART1_HW_AVAILABLE
UART_HandleTypeDef  huart1;
DMA_HandleTypeDef   hdma_uart1_rx;
uint8_t             aDMABuf_uart1_rx[UART_DMA_BUF_SIZE]    = {0};
ring_buf_t          tRingBuf_uart1_rx;
ring_buf_t          tRingBuf_uart1_tx;
uint8_t             aRxBuf_Uart1[UART_RINGBUF_SIZE]    = {0};
uint8_t 						aTxBuf_Uart1[UART_RINGBUF_SIZE]    = {0};
struct 							rt_semaphore rtSemUart1Rx;
#endif



/* USART1 init function */

void MX_USART1_UART_Init(void)
{
	static uint8_t uart1_init_clpt_flag = 0;
	if(uart1_init_clpt_flag == 0)
	{
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
			ring_buf_create(&tRingBuf_uart1_rx, aRxBuf_Uart1, sizeof(aRxBuf_Uart1));
			ring_buf_create(&tRingBuf_uart1_tx, aTxBuf_Uart1, sizeof(aTxBuf_Uart1));
			
			rt_sem_init(&rtSemUart1Rx, "uart1 rx",0,RT_IPC_FLAG_FIFO);
			#if (UART1_USE_DMA)
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
			HAL_UART_Receive_DMA(&huart1,aDMABuf_uart1_rx,UART_DMA_BUF_SIZE);
			#else
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
			#endif
			uart1_init_clpt_flag = 1;	
	}		
}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

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
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

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
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

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

  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}
/* USER CODE BEGIN 1 */
int fputc (int ch,FILE* f)
{
 uint8_t temp[1]={ch};
 {
  HAL_UART_Transmit(&huart3,temp,1,2);
 }
 return HAL_OK;
}
void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    __HAL_UNLOCK(&huart3);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&huart3, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&huart3, (uint8_t *)(str + i), 1, 1);
    }
}

char rt_hw_console_getchar(void)
{
        int ch = -1;
        if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE) != RESET)
        {
        		//notice stm32f429 and stm32f475 is different
				//stm32l475£ºch = huart1.Instance->RDR
				//stm32f429£ºch = huart1.Instance->DR
                ch = huart3.Instance->DR & 0xff;
        }
        else
        {
                if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE) != RESET)
                {
                        __HAL_UART_CLEAR_OREFLAG(&huart3);
                }
                rt_thread_mdelay(10);
        }
        return ch;
}

//static void atcmd(int argc, char**argv)
//{
//    if (argc < 2)
//    {
//        rt_kprintf("Please input'atcmd <server|client>'\n");
//        return;
//    }

//    if (!rt_strcmp(argv[1], "server"))
//    {
//        rt_kprintf("AT server!\n");
//    }
//    else if (!rt_strcmp(argv[1], "client"))
//    {
//        rt_kprintf("AT client!\n");
//    }
//    else
//    {
//        rt_kprintf("Please input'atcmd <server|client>'\n");
//    }
//}

//MSH_CMD_EXPORT(atcmd, atcmd sample: atcmd <server|client>);



#if UART1_HW_AVAILABLE
void USART1_IRQHandler(void)
{
    rt_interrupt_enter();
    
    uint8_t     u8Data = 0;
	
#if (UART1_USE_DMA)
    uint16_t rx_len = 0; 
    if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!= RESET)
    { 
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        HAL_UART_DMAStop(&huart1); 
			
        rx_len = __HAL_DMA_GET_COUNTER(&hdma_uart1_rx);
        rx_len = UART_DMA_BUF_SIZE - rx_len; 
			
        ring_buf_put(&tRingBuf_uart1_rx, aDMABuf_uart1_rx, rx_len);
			
        HAL_UART_Receive_DMA(&huart1,aDMABuf_uart1_rx,UART_DMA_BUF_SIZE);
			
        rt_sem_release(&rtSemUart1Rx);
    }      
#else
    if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!= RESET)
    { 
        u8Data = USART1->DR & 0xff;
        ring_buf_put(&tRingBuf_uart1_rx, &u8Data, 1);
        //rt_sem_release(&rtSemUart1Rx);

    }
    if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!= RESET)
    { 
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        rt_sem_release(&rtSemUart1Rx);
    }    
#endif
    if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE)!= RESET)
    { 
        if(ring_buf_get(&tRingBuf_uart1_tx, &u8Data, 1))
        {
            USART1->DR = u8Data;
        }
        else
        {
            __HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE); 
        }
    }

    HAL_UART_IRQHandler(&huart1);

    rt_interrupt_leave();
}
#endif

#if (UART1_USE_DMA)
void DMA1_Channel5_IRQHandler(void)
{
	rt_interrupt_enter();
	
  HAL_DMA_IRQHandler(&hdma_uart1_rx);
	
	rt_interrupt_leave();
}
#endif
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
#if (UART1_USE_DMA)
        ring_buf_put(&tRingBuf_uart1_rx, aDMABuf_uart1_rx, UART_DMA_BUF_SIZE);
        rt_sem_release(&rtSemUart1Rx);
#endif
    }
    else if(huart->Instance==USART2)
    {
#if (UART2_USE_DMA)       
				ring_buf_put(&tRingBuf_uart2_rx, aDMABuf_uart2_rx, UART_DMA_BUF_SIZE);
        rt_sem_release(&rtSemUart2Rx);
#endif
    }
    else if(huart->Instance==USART3)
    {
#if (UART3_USE_DMA)         
				ring_buf_put(&tRingBuf_uart3_rx, aDMABuf_uart3_rx, UART_DMA_BUF_SIZE);
        rt_sem_release(&rtSemUart3Rx);
#endif
    }
}
#if UART1_HW_AVAILABLE

uint32_t uart1_send(const void *buf ,uint32_t len)
{
    uint32_t ret;
	
    ret = ring_buf_put(&tRingBuf_uart1_tx, (uint8_t *)buf, len); 
	
		if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE) != RESET)
		{
			__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
		}
			
    return ret;
}

void uart1_putstr(const char *str)
{
    uint32_t  u32Len = 0;
	
    u32Len = strlen(str);
    char cAA = '\r';
	
    uart1_send((void *)str, u32Len - 1);
    if(*(str+u32Len - 1) == '\n')
    {
        uart1_send(&cAA, 1);
    }
    uart1_send((void *)(str + u32Len - 1), 1);
}
uint32_t uart1_buflen(void)
{
    return ring_buf_len(&tRingBuf_uart1_rx);
}
uint32_t uart1_read(void *buf, unsigned int len)
{	
	return ring_buf_get(&tRingBuf_uart1_rx, (uint8_t *)buf, len);
}

uint32_t uart1_blocking_send(void *buf ,uint32_t len)
{
	while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE)== RESET);
	HAL_UART_Transmit(&huart1,(uint8_t *)buf,len,0xffffffff);
	while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TXE)== RESET);
	
	return 0;
}


#endif
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
