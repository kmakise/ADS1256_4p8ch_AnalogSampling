/**
  ******************************************************************************
  * File Name          : Task02.c
  * Description        : Code for freeRTOS Task02 Application
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-12-11
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
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "Task02.h"

/* Private includes ----------------------------------------------------------*/
#include "ADS1256.h"



//ADC配置参数初始化
void pCfgADCParamInit(void)
{
	//port
	for(int i = 0;i < 4;i++)
	{
		//ch
		for(int j = 0;j < 8;j++)
		{
			pCfgADCParam.gain[i][j] = 0;//自动
			pCfgADCParam.mean[i][j] = 8;//8次
			pCfgADCParam.mode[i][j] = 0;//RMS
		}
	}
	pCfgADCParam.update = ADS1256_INIT_OK;
}	


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void Task02Main(void)
{
	pCfgADCParamInit();
	for(;;)
	{
		osDelay(10);
	}
}
/* Private application code --------------------------------------------------*/

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/



