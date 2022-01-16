
/**
  ******************************************************************************
  * @file           : ADS1256_cfg.h
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
#ifndef __ADS1256_CFG_H
#define __ADS1256_CFG_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "ADS1256.h"
/* Exported define -----------------------------------------------------------*/
#define ADS1256_CFG_CH					8
#define ADS1256_CFG_PORT				4

#define ADS1256_CFG_NG					0x00
#define ADS1256_CFG_OK					0xAA	
#define ADS1256_CFG_WW					0x55
/* Exported types ------------------------------------------------------------*/
//配置参数
typedef struct
{
	uint8_t 		gain[ADS1256_CFG_PORT][ADS1256_CFG_CH];	//放大倍率  0:自动 1:1V/V 2:10V/V 3:100V/V
	uint8_t 		mean[ADS1256_CFG_PORT][ADS1256_CFG_CH]; //平均次数	XX 0-255
	uint8_t 		mode[ADS1256_CFG_PORT][ADS1256_CFG_CH]; //采样方式	0 RMS 1 LOG
	uint8_t     update;																	//更新标志  0x00:等待 0xAA:完成
	
}ADC_ConfigTypedef;

/* Exported variables --------------------------------------------------------*/
extern ADC_ConfigTypedef pCfgADCParam;


/* Exported functions prototypes ---------------------------------------------*/
void pCfgADCParamInit(void);
void pCfgADCParamUpdate(ADC_ConfigTypedef * param);
void waitCfgReading(void);

#endif /* __ADS1256_CFG_H */

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/
