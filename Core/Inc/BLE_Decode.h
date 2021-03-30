/**********************************************************************
 * @File      	: BLE_Deconde.h
 * @ChangeLogs	:
 * Date           Author       Notes
 * 2020-03-07     CCL    the first version
 **********************************************************************/
/* MODULE app. */
#ifndef __BLE_DECODE___H
#define __BLE_DECODE___H
#include <main.h>


#define BLE_RXDATABUFFER_LEN                 1024
#define LOG_TAG_BLE                          "BLE"
#define BLE_DECODE_DELAY__                   200//ms
 
#define BLE_FRAME_HEADER_LEN                 2 //��ͷ����
#define BLE_FRAME_HEADER_1                   0xAA
#define BLE_FRAME_HEADER_2                   0xAA

#define BLE_FRAME_CHECK_LEN                  1 //У��λ����
#define BLE_FRAME_LEN_LEN                    1 //�����ֽڳ���

/************************* ������������ **********************************/

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           UpdateSensorCmd;   
  uint8_t           MAC[6];
	uint32_t          Number; 
	uint8_t           Bat; 
	char              TimeStamp[14]; 
	uint8_t           OrderCode[8];
	uint8_t           GoodsID[8];
	uint8_t           State;
	uint8_t           Check;
}__attribute__((packed))  BLEUpdateSensor;

#define BLEUpdateSensorPtr         BLEUpdateSensor*
#define BLEUpdateSensorFrameLen   (sizeof(BLEUpdateSensor))
#define BLEUpdateSensorPayLoadLen (sizeof(BLEUpdateSensor) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	
typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           AckBatRcvCmd;   
	uint8_t           State;
	uint8_t           Check;
}__attribute__((packed))  BLEAckBatRcv;

#define BLEAckBatRcvPtr         BLEAckBatRcv*
#define BLEAckBatRcvFrameLen   (sizeof(BLEAckBatRcv))
#define BLEAckBatRcvPayLoadLen (sizeof(BLEAckBatRcv) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           SensorErrorCmd; 
	uint8_t           MAC[6];  
	uint8_t           State;
	uint8_t           Check;
}__attribute__((packed))  BLESensorError;

#define BLESensorErrorPtr         BLESensorError*
#define BLESensorErrorFrameLen   (sizeof(BLESensorError))
#define BLESensorErrorPayLoadLen (sizeof(BLESensorError) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)


typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           AddSensorCmd; 
	uint8_t           MAC[6];  
	uint8_t           State;
	uint8_t           MotherID[2];
	uint8_t           Check;
}__attribute__((packed))  BLEAddSensor;

#define BLEAddSensorPtr         BLEAddSensor*
#define BLEAddSensorFrameLen    (sizeof(BLEAddSensor))
#define BLEAddSensorPayLoadLen  (sizeof(BLEAddSensor) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           DeleteSensorCmd; 
	uint8_t           MAC[6];  
	uint8_t           State;
	uint8_t           MotherID[2];
	uint8_t           Check;
}__attribute__((packed))  BLEDeleteSensor;

#define BLEDeleteSensorPtr         BLEDeleteSensor*
#define BLEDeleteSensorFrameLen    (sizeof(BLEDeleteSensor))
#define BLEDeleteSensorPayLoadLen  (sizeof(BLEDeleteSensor) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)


typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           BLENetRecombinationCmd; 
	uint8_t           CurrentNetState;  
	uint8_t           CurrentNetID[2];
	uint8_t           Check;
}__attribute__((packed))  BLENetRecombination;

#define BLENetRecombinationPtr         BLENetRecombination*
#define BLENetRecombinationFrameLen    (sizeof(BLENetRecombination))
#define BLENetRecombinationPayLoadLen  (sizeof(BLENetRecombination) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)


typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           DeleteNetCmd;  
	uint8_t           State;
	uint8_t           MotherID[2];
	uint8_t           Check;
}__attribute__((packed))  BLEDeleteNet;

#define BLEDeleteNetPtr         BLEDeleteNet*
#define BLEDeleteNetFrameLen    (sizeof(BLEDeleteNet))
#define BLEDeleteNetPayLoadLen  (sizeof(BLEDeleteNet) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)


//��ȱ��2��Э��



#define BLE_UPDATE_SENSOR_CMD_CODE               0xE1
#define BLE_ACK_BATRCV_CMD_CODE                  0xE3
#define BLE_SENSOR_ERROR_CMD_CODE                0xE4
#define BLE_ADD_SENSOR_CMD_CODE                  0xE6
#define BLE_DELETE_SENSOR_CMD_CODE               0xE7
#define BLE_NET_RECOMBINATION_CMD_CODE           0xE2
#define BLE_DELETE_NET_CMD_CODE                  0xE9


typedef  struct{                            
	BLEUpdateSensor           BLEUpdateSensorData;  
	BLEAckBatRcv     					BLEAckBatRcvData;
	BLESensorError        		BLESensorErrorData;
	BLEAddSensor     					BLEAddSensorData;
	BLEDeleteSensor 					BLEDeleteSensorData;
	BLENetRecombination       BLENetRecombinationData;
	BLEDeleteNet   						BLEDeleteNetData;
//��ȱ��2��Э��	
	
}__attribute__((packed))  MCUUpStream;

#define MCUUpStreamPtr         MCUUpStream*
#define MCUUpStreamFrameLen    (sizeof(MCUUpStream))
	
/************************* ������������ **********************************/


/************************** MCU�������� ***********************************/

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           AckBLESensorStateCmd;  
	uint8_t           State;
	uint8_t           Check;
}__attribute__((packed))  MCUAckBLESensorState;

#define MCUAckBLESensorStatePtr         MCUAckBLESensorState*
#define MCUAckBLESensorStateFrameLen    (sizeof(MCUAckBLESensorState))
#define MCUAckBLESensorStatePayLoadLen  (sizeof(MCUAckBLESensorState) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           InquireSensorCmd;  
	uint8_t           MAC[6];
	uint8_t           Check;
}__attribute__((packed))  MCUInquireSensor;

#define InquireSensorPtr         MCUInquireSensor*
#define InquireSensorFrameLen    (sizeof(MCUInquireSensor))
#define InquireSensorPayLoadLen  (sizeof(MCUInquireSensor) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	
typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           UpdateBatCmd;  
	char              TimeStamp[14]; 
	uint8_t           ID[2]; 
	uint8_t           Bat; 
	uint8_t           SysPowerUSE; 
	uint8_t           LowPowerFlag; 
	uint8_t           Check;
}__attribute__((packed))  MCUUpdateBat;

#define MCUUpdateBatePtr         MCUUpdateBat*
#define MCUUpdateBatFrameLen    (sizeof(MCUUpdateBat))
#define MCUUpdateBatPayLoadLen  (sizeof(MCUUpdateBat) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           AckSensorErrorCmd;  
	uint8_t           MAC[6];
	uint8_t           State;
	uint8_t           Check;
}__attribute__((packed))  MCUAckSensorError;

#define MCUAckSensorErrorPtr         MCUAckSensorError*
#define MCUAckSensorErrorFrameLen    (sizeof(MCUAckSensorError))
#define MCUAckSensorErrorPayLoadLen  (sizeof(MCUAckSensorError) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)


typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           AddSensorCmd;  
	uint8_t           MAC[6];
	uint8_t           Check;
}__attribute__((packed))  MCUAddSensorCmd;

#define MCUAddSensorCmdPtr         MCUAddSensorCmd*
#define MCUAddSensorCmdFrameLen    (sizeof(MCUAddSensorCmd))
#define MCUAddSensorCmdPayLoadLen  (sizeof(MCUAddSensorCmd) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           DeleteSensorCmd;  
	uint8_t           MAC[6];
	uint8_t           Check;
}__attribute__((packed))  MCUDeleteSensorCmd;

#define MCUDeleteSensorCmdPtr         MCUDeleteSensorCmd*
#define MCUDeleteSensorCmdFrameLen    (sizeof(MCUDeleteSensorCmd))
#define MCUDeleteSensorCmdPayLoadLen  (sizeof(MCUDeleteSensorCmd) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	

typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           NetRecombinationCmd;  
	uint8_t           Check;
}__attribute__((packed))  MCUNetRecombinationCmd;

#define MCUNetRecombinationCmdPtr         MCUNetRecombinationCmd*
#define MCUNetRecombinationCmdFrameLen    (sizeof(MCUNetRecombinationCmd))
#define MCUNetRecombinationCmdPayLoadLen  (sizeof(MCUNetRecombinationCmd) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	


typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           NetDeleteCmd;  
	uint8_t           Check;
}__attribute__((packed))  MCUNetDeleteCmd;

#define MCUNetDeleteCmdPtr         MCUNetDeleteCmd*
#define MCUNetDeleteCmdFrameLen    (sizeof(MCUNetDeleteCmd))
#define MCUNetDeleteCmdPayLoadLen  (sizeof(MCUNetDeleteCmd) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	
typedef  struct{
  uint8_t           FrameHeader[BLE_FRAME_HEADER_LEN];     // 2bytes֡ͷ0xAAAA
	uint8_t           PayloadLen;                              // PayloadLen
	uint8_t           InquireNewDataCmd;  
	uint8_t           Check;
}__attribute__((packed))  MCUInquireNewDataCmd;

#define MCUInquireNewDataCmdPtr         MCUInquireNewDataCmd*
#define MCUInquireNewDataCmdFrameLen    (sizeof(MCUInquireNewDataCmd))
#define MCUInquireNewDataCmdPayLoadLen  (sizeof(MCUInquireNewDataCmd) - BLE_FRAME_HEADER_LEN - BLE_FRAME_CHECK_LEN - BLE_FRAME_LEN_LEN)
	
#define MCU_ACK_SENSOR_UPDATE_CMD_CODE           0xF1
#define MCU_INQUIRE_SENSOR_CMD_CODE              0xF2
#define MCU_UPDATE_BATRCV_CMD_CODE               0xF3
#define MCU_ACK_SENSOR_ERROR_CMD_CODE            0xF4
#define MCU_ADD_SENSOR_CMD_CODE                  0xF5
#define MCU_DELETE_SENSOR_CMD_CODE               0xF6
#define MCU_NET_RECOMBINATION_CMD_CODE           0xF7
#define MCU_DELETE_NET_CMD_CODE                  0xF8
#define MCU_INQUIRE_NEWDATA_CMD_CODE             0xF9


typedef  struct{
  MCUAckBLESensorState   MCUAckBLESensorStateData;     
	MCUInquireSensor       MCUInquireSensorData;                             
	MCUUpdateBat           MCUUpdateBatData;  
	MCUAckSensorError      MCUAckSensorErrorData;
	MCUAddSensorCmd        MCUAddSensorCmdData;
	MCUDeleteSensorCmd     MCUDeleteSensorCmdData;
	MCUNetRecombinationCmd MCUNetRecombinationCmdData;
	MCUNetDeleteCmd        MCUNetDeleteCmdData;
	MCUInquireNewDataCmd   MCUInquireNewDataCmdData;
}__attribute__((packed))  MCUDownStream;


#define MCUDownStreamPtr         MCUDownStream*
#define MCUDownStreamFrameLen    (sizeof(MCUDownStream))

/************************** MCU�������� ***********************************/

extern void App_BLE_TaskInit(uint8_t u8priority);
extern void App_BLE_ThreadEntry(void *param);
extern void ResetBLE(void);
extern void BLEUartSend(uint8_t *SendBuf, uint32_t Len);
extern uint32_t BLEGetRxLen(void);
extern uint32_t BLEUartRead(uint8_t *RcvBuf, uint32_t MaxReadCnt);
uint8_t RevceiveNewBLEMessage(uint8_t *DataBuffer, uint16_t DataLen);
#ifdef __cplusplus  // close out "C" linkage in case of c++ compiling
}
#endif
/** ================================================================ **/
#endif

/****** (C) COPYRIGHT 2020 CCL *****END OF FILE***********/
