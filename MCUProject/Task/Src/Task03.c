/**
  ******************************************************************************
  * File Name          : Task03.c
  * Description        : Code for freeRTOS Task03 Application
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
#include "Task03.h"

/* Private includes ----------------------------------------------------------*/
#include "stdio.h"
#include "usart.h"
#include "comProtocol.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/





/* Private function prototypes -----------------------------------------------*/

void Task03Main(void)
{
	
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	for(;;)
	{
		comLoopRec();
		//osDelay(5);
	}
}

/* Private application code --------------------------------------------------*/

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/


