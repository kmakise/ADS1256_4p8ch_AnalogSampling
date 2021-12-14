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


/* Exported functions prototypes ---------------------------------------------*/



#endif /* __COMPROTOCOL_H */

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/
