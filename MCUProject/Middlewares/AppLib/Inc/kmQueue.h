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
#define RQ_QUEUE_MAXSIZE  		64
#define RQ_DATA_MAXSIZE  			32
#define RQ_DATATYPE 					uint8_t

/* Exported types ------------------------------------------------------------*/

typedef struct
{
	volatile RQ_DATATYPE 		buffer[RQ_QUEUE_MAXSIZE];		//队列缓冲区
	volatile RQ_DATATYPE 		data[RQ_DATA_MAXSIZE];			//提取数据
	volatile uint32_t				pd;													//提取数据下标
	volatile uint32_t 			pw;													//队列缓冲区写入点
	volatile uint32_t				pr;													//队列缓冲区读取点
	volatile uint32_t 			errornum;										//丢失数
}RingQueueTypedef;



/* Exported functions prototypes ---------------------------------------------*/
uint32_t enRingQueueSingle(RingQueueTypedef * rq,RQ_DATATYPE data);
uint32_t enRingQueuePlural(RingQueueTypedef * rq,RQ_DATATYPE * pData,uint32_t size);
uint32_t deRingQueueSingleOut(RingQueueTypedef * rq,RQ_DATATYPE * pData);
uint32_t deRingQueueSingle(RingQueueTypedef * rq);
uint32_t deRingQueuePlural(RingQueueTypedef * rq);


#endif /* __KMQUEUE_H */

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/
