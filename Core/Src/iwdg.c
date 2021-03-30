/**********************************************************************
 * @File      	: iwdg.c
 * @ChangeLogs	:
 * Date          Author       Notes
 * 2020-2-28     ccl 
 **********************************************************************/
#include <main.h>
#include "iwdg.h"
#include "stm32l1xx_hal_iwdg.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

IWDG_HandleTypeDef hiwdg;

/* IWDG init function */
void MX_IWDG_Init(void)
{

  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
  hiwdg.Init.Reload = 550;

}


void Start_IWDG(void)
{
  __HAL_IWDG_START(&hiwdg);		//开启独立看门狗	
}

  
//喂独立看门狗
void Feed_Dog(void)
{     
	__HAL_IWDG_RELOAD_COUNTER(&hiwdg); 	//喂狗
}




/********** (C) COPYRIGHT 2020 CCL *****END OF FILE**************/
