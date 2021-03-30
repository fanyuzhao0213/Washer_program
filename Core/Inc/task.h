/**
  ******************************************************************************
  * File Name          : I2C.h
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __task_H
#define __task_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "rtthread.h"

typedef struct 
{
	//动态创建线程时使用的线程参数结构体
	char *name;
  void (*entry)(void *parameter);
  void       *parameter;
  rt_uint32_t stack_size;
	rt_uint8_t  priority;
	rt_uint32_t tick;
}TaskStruct;


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include  "rtthread.h"
#include <rthw.h>

void TaskInit(void);

#endif /*__ task_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
