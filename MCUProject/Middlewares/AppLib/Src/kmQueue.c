/**
  ******************************************************************************
  * File Name          : kmQueue.c
  * Description        : Code for queue lib
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-12-13
  * @brief   
	******************************************************************************
  * @attention
  * <h2><center>&copy; Copyright (c) kmakise
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "kmQueue.h"



/* Private function prototypes -----------------------------------------------*/
//进队列
uint8_t enRingQueue(RingQueueTypedef * rq,RQ_DATATYPE data)
{
	if((rq->pw + 1) != rq->pr)
	{
		rq->data[rq->pw] = data;
		rq->pw = (rq->pw < (RQ_MAXSIZE - 1)) ? rq->pw + 1 : 0;
		return 1;
	}
	else
	{
		rq->errornum++;
		return 0;
	}
	return 0;
}
//出队列
uint8_t deRingQueue(RingQueueTypedef * rq,RQ_DATATYPE  * data)
{
	if(rq->pr != rq->pw)
	{
		*data = rq->data[rq->pr];
		rq->pr = (rq->pr < (RQ_MAXSIZE - 1)) ? rq->pr + 1 : 0;
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}

/* Private application code --------------------------------------------------*/

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/


