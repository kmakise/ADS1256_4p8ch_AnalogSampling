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
#include "ADS1256_cfg.h"
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/* Private application code --------------------------------------------------*/

void Task02Main(void)
{
	pCfgADCParamInit();
	for(;;)
	{
		pCfgADCParamUpdate(&pCfgADCParam);
		osDelay(10);
	}
}


/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/



