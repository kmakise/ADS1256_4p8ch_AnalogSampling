/**
  ******************************************************************************
  * @file           : Global.h
  * @brief          : Header for Data Type or Extern file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) kmakise.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KMGLOBAL_H
#define __KMGLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Exported defines ----------------------------------------------------------*/
#define USART_BUFFER_LEN_MAX 64


/* Exported types ------------------------------------------------------------*/
typedef struct
{
	GPIO_TypeDef 		 	 *Port;
	uint16_t 						Pin;
}GPIO_OptTypedef;


/* Exported variables --------------------------------------------------------*/



/* Exported functions prototypes ---------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /*__GLOBAL_H*/
/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/
