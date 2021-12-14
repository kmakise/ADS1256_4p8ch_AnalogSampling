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
#ifndef __KMFILTER_H
#define __KMFILTER_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Exported define -----------------------------------------------------------*/
#define MEAN_FILTER_QUEUE_LEN_MAX    0xFF
#define MEAN_FILTER_DATA_TYPE				 int32_t
#define MEAN_FILTER_SUMN_TYPE				 int32_t
/* Exported types ------------------------------------------------------------*/
typedef struct 
{
	MEAN_FILTER_DATA_TYPE histVal[MEAN_FILTER_QUEUE_LEN_MAX];	//历史点
	MEAN_FILTER_DATA_TYPE meanVal;														//均值
	MEAN_FILTER_DATA_TYPE	wrcur;															//环形队列写入点
	MEAN_FILTER_SUMN_TYPE	meanNum;														//均值次数
}MeanFilterTypedef;	//队列均值滤波

/* Exported functions prototypes ---------------------------------------------*/
void meanFilterSingleWrite(MeanFilterTypedef * mea,MEAN_FILTER_DATA_TYPE data);

#endif /* __KMFILTER_H */

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/
