/**
  ******************************************************************************
  * File Name          : kmFilter.c
  * Description        : Code for Filter lib
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-12-12
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
#include "kmFilter.h"



/* Private function prototypes -----------------------------------------------*/

//队列均值滤波单点写入
void meanFilterSingleWrite(MeanFilterTypedef * mea,MEAN_FILTER_DATA_TYPE data)
{
	MEAN_FILTER_SUMN_TYPE uDataSum = 0;

	mea->histVal[mea->wrcur] = data;
	mea->wrcur = (mea->wrcur < (mea->meanNum - 1)) ? mea->wrcur + 1 : 0;
	for(int i = 0;i < mea->meanNum;i++)
	{
		uDataSum += mea->histVal[i];
	}
	mea->meanVal = uDataSum / mea->meanNum;
}




/* Private application code --------------------------------------------------*/

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/


