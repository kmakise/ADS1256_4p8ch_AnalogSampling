/**
  ******************************************************************************
  * File Name          : Task01.c
  * Description        : Code for freeRTOS Task01 Application
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
#include "Task01.h"
#include "spi.h"
/* Private includes ----------------------------------------------------------*/
#include "ADS1256.h"
#include "ADS1256_cfg.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Task01Main(void)
{
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
	
	waitCfgReading();
	ADS1256_Init(&pADCHandle[0]);
	
	for(;;)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		osDelay(50);
	}
}

/* Private application code --------------------------------------------------*/

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/

