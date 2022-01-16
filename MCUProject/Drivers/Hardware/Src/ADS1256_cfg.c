/**
  ******************************************************************************
  * File Name          : ADS1256_cfg.c
  * Description        : Code for Filter lib
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-12-14
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
#include "ADS1256_cfg.h"

/* Private includes ----------------------------------------------------------*/
#include "ADS1256.h"
/* Private variables ---------------------------------------------------------*/
ADC_ConfigTypedef pCfgADCParam;

/* Private function prototypes -----------------------------------------------*/
//参数配置到句柄
void ADCHandleCfg(ADC_DataTypedef * adc)
{
	for(int i = 0;i < 8;i++)
	{
		adc->filter[i].meanNum  = pCfgADCParam.mean[adc->id][i];
		adc->atgain[i].cfg_mode = pCfgADCParam.mode[adc->id][i];
		adc->atgain[i].cfg_gain = pCfgADCParam.gain[adc->id][i];
		adc->atgain[i].ngain		= 1;
		adc->atgain[i].en = 0;
	}
	adc->atgain[0].en = 1;
	adc->atgain[2].en = 1;
	adc->atgain[4].en = 1;
	adc->atgain[6].en = 1;
}

//ADC配置参数初始化
void pCfgADCParamInit(void)
{
	//从存储区读取参数
	
	
	//port 读取失败
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
	//配置参数到句柄
	ADCHandleCfg(&pADCHandle[0]);
	ADCHandleCfg(&pADCHandle[1]);
	ADCHandleCfg(&pADCHandle[2]);
	ADCHandleCfg(&pADCHandle[3]);
	//配置完成
	pCfgADCParam.update = ADS1256_INIT_OK;
}	

//参数更新轮训
void pCfgADCParamUpdate(ADC_ConfigTypedef * param)
{
	if(param->update == ADS1256_CFG_WW)
	{
		//配置参数到句柄
		ADCHandleCfg(&pADCHandle[0]);
		ADCHandleCfg(&pADCHandle[1]);
		ADCHandleCfg(&pADCHandle[2]);
		ADCHandleCfg(&pADCHandle[3]);
		//写入参数到存储器
		
		//完成写入
		param->update = ADS1256_CFG_OK;
	}
}

//等待参数配置
void waitCfgReading(void)
{
	while(pCfgADCParam.update != ADS1256_CFG_OK);
}


/* Private application code --------------------------------------------------*/

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/


