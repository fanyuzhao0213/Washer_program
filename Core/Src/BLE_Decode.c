/**********************************************************************
 * @File      	: BLE_Decode.c
 * @ChangeLogs	:
 * Date           Author       Notes
 * 2020-5-4       CCL	       the first version
 **********************************************************************/
#include <main.h>
#include <rtthread.h>
#include "utils.h"
#include "BLE_Decode.h"
#include "usart.h"
enum
{
    RX_HEADER_0XAA = 0,
    RX_HEADER_0XAA_1,
    RX_FUNTIONCODE,
    RX_PAYLOAD,
    RX_MSG_DATA,
    RX_MSG_CHK
} eMCURxStatus;


extern struct rt_semaphore rtSemUart1Rx;

#ifdef TEST_DATA
// uint8_t  TestData[75] ={0x01,0x00,0x00,0xEE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                         0x02,0x00,0x00,0xEE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                         0x03,0x00,0x00,0xEE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//                         0x68,0x00,0x00,0x01,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0xE9,0x00,
//                         0x04,0x00,0x00,0xEE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t TestData[11] = {0x68, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00, 0xE9, 0x00};

#endif
/** ================================================================ **/
ALIGN(RT_ALIGN_SIZE)


/**=====================================================================*
 * @brief  	BLEUartSend
 * @param  	None
 * @retval 	None	
 **=====================================================================*/
void BLEUartSend(uint8_t *SendBuf, uint32_t Len)
{
    uart1_send((uint8_t *)SendBuf, Len);
}

/**=====================================================================*
 * @brief  	BLEUartRead
 * @param  	buf,maxreadcnt
 * @retval 	uint32_t read cnt already	
 **=====================================================================*/
uint32_t BLEUartRead(uint8_t *RcvBuf, uint32_t MaxReadCnt)
{

    uint32_t ReadCnt = 0;
    uint32_t BufDataVaild;

    rt_sem_take(&rtSemUart1Rx, 0);
    BufDataVaild = uart1_buflen();
    if (BufDataVaild)
    {
        ReadCnt = uart1_read(RcvBuf, MaxReadCnt);
    }
    return ReadCnt;
}

/**=====================================================================*
 * @brief  	BLEUartInit
 * @param  	buf,maxreadcnt
 * @retval 	uint32_t read cnt already	
 **=====================================================================*/
uint32_t BLEGetRxLen(void)
{
    return (uart1_buflen());
}

void Resetble(void)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET); 
	rt_thread_delay(2000);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET);		
}
/**=====================================================================*
 * @brief  	RevceiveNewBLEMessage
 *          接收的新的蓝牙数据并进行解析。 BLE_Decode调用此函数
 * @param  	DataBuffer  指向蓝牙数据Buffer的指针
 *          DataLen     蓝牙数据的长度
 * @retval 	uint8_t	    蓝牙数据的解析结果 （True / False）（暂时没有使用）
 **=====================================================================*/
uint8_t RevceiveNewBLEMessage(uint8_t *DataBuffer, uint16_t DataLen)
{
	static uint8_t i;
								for( i = 0; i <DataLen; i++)
										rt_kprintf("%02X ", DataBuffer[i]);
										rt_kprintf("\n");        
										rt_kprintf("******************************************************\n ");
										rt_kprintf("\n");
}


/******************* (C) COPYRIGHT 2020 CCL*****END OF FILE************/
