/**
  ******************************************************************************
  * @file           : Filter.h
  * @brief          : Header for Filter file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMPROTOCOL_H
#define __COMPROTOCOL_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "kmGlobal.h"
#include "kmQueue.h"
/* Exported define -----------------------------------------------------------*/



/* Exported types ------------------------------------------------------------*/
typedef struct
{
	UART_HandleTypeDef *huart;
	RingQueueTypedef	 	qtx;
	RingQueueTypedef   	qrx;
	GPIO_OptTypedef		 	entx;
	uint8_t 						uSta;
	uint8_t							uEnd;
	
	
}COM_DataTypedef;
/* Exported variables --------------------------------------------------------*/



/* Exported functions prototypes ---------------------------------------------*/
void comPackageAnalyze(uint8_t * pData);
void comQueueReceive(COM_DataTypedef * com);
void comTransmit(COM_DataTypedef * com,uint8_t * pData,uint32_t size);
void comISRWriteData(COM_DataTypedef * com,uint8_t data);

void comISRCall(void);
void comLoopRec(void);
void comDMAOver(void);

#endif /* __COMPROTOCOL_H */

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/
