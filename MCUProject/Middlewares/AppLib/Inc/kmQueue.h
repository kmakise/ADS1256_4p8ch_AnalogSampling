/**
  ******************************************************************************
  * @file           : kmQueue.h
  * @brief          : Header for queue file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KMQUEUE_H
#define __KMQUEUE_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Exported define -----------------------------------------------------------*/
#define RQ_MAXSIZE  		64
#define RQ_DATATYPE 		uint8_t

/* Exported types ------------------------------------------------------------*/

typedef struct
{
	volatile RQ_DATATYPE 				data[RQ_MAXSIZE];
	volatile uint32_t 					pw;
	volatile uint32_t						pr;
	volatile uint32_t 					errornum;
}RingQueueTypedef;



/* Exported functions prototypes ---------------------------------------------*/
uint8_t enRingQueue(RingQueueTypedef * rq,RQ_DATATYPE data);
uint8_t deRingQueue(RingQueueTypedef * rq,RQ_DATATYPE  * data);



#endif /* __KMQUEUE_H */

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/
