/**
  ******************************************************************************
  * File Name          : ADS1256.c
  * Description        : Code for ADS1256 bsp
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
#include "main.h"
#include "stdio.h"
#include "ADS1256.h"
#include "spi.h"
/* Private variables ---------------------------------------------------------*/
ADC_ConfigTypedef pCfgADCParam;
ADC_DataTypedef pADCHandle[ADS1256_PORT_NUM] = {
	
	[0].id 												= 0,
	[0].hwinfc.hspi 							= &hspi1,
	[0].hwinfc.drdy.Port					= DRDY_A_GPIO_Port,
	[0].hwinfc.drdy.Pin						=	DRDY_A_Pin,
	[0].hwinfc.agt.asw.A.Port			= NULL,
	[0].hwinfc.agt.asw.A.Pin			= NULL,
	[0].hwinfc.agt.asw.B.Port			= NULL,
	[0].hwinfc.agt.asw.B.Pin			= NULL,
	[0].hwinfc.agt.asw.C.Port			= NULL,
	[0].hwinfc.agt.asw.C.Pin			= NULL,
	[0].hwinfc.agt.rl.RMS.Port		= NULL,
	[0].hwinfc.agt.rl.RMS.Pin			= NULL,
	[0].hwinfc.agt.rl.LOG.Port		= NULL,
	[0].hwinfc.agt.rl.LOG.Pin			= NULL,
	
};

/* Private function prototypes -----------------------------------------------*/
//写寄存器
void ADS1256WREG(ADC_HWInterface * hi,uint8_t regaddr,uint8_t databyte)
{
	uint8_t cmd;
	while(HAL_GPIO_ReadPin(hi->drdy.Port,hi->drdy.Pin));
	//向寄存器写入数据地址
	cmd = ADS1256_CMD_WREG|(regaddr & 0x0F);
	HAL_SPI_Transmit(hi->hspi, &cmd, 1, 10);
  //写入数据的个数n-1
	cmd = 0x00;
	HAL_SPI_Transmit(hi->hspi, &cmd, 1, 10);
  //向regaddr地址指向的寄存器写入数据databyte
  HAL_SPI_Transmit(hi->hspi, &databyte, 1, 10);
}
//写命令
void ADS1256WCMD(ADC_HWInterface * hi,uint8_t cmd)
{
	HAL_SPI_Transmit(hi->hspi, &cmd, 1, 10);
}

//读取AD值并设置通道
int32_t ADS1256ReadData(ADC_HWInterface * hi,uint8_t channel)  
{
	int32_t sum;
  uint8_t data[3];

  while(HAL_GPIO_ReadPin(hi->drdy.Port,hi->drdy.Pin));
  //切换通道 注意：本次写入的新通道在下次读取时才会生效，本次读到的是上一次的值
  switch(channel)
  {
    case 0:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN0 | ADS1256_MUXN_AINCOM);break;
    case 1:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN1 | ADS1256_MUXN_AINCOM);break; 
    case 2:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN2 | ADS1256_MUXN_AINCOM);break; 
    case 3:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN3 | ADS1256_MUXN_AINCOM);break; 
    case 4:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN4 | ADS1256_MUXN_AINCOM);break; 
    case 5:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN5 | ADS1256_MUXN_AINCOM);break; 
    case 6:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN6 | ADS1256_MUXN_AINCOM);break; 
    case 7:ADS1256WREG(hi,ADS1256_MUX, ADS1256_MUXP_AIN7 | ADS1256_MUXN_AINCOM);break; 
  }
  ADS1256WCMD(hi,ADS1256_CMD_SYNC);
  ADS1256WCMD(hi,ADS1256_CMD_WAKEUP);
  ADS1256WCMD(hi,ADS1256_CMD_RDATA);
  HAL_SPI_Receive(hi->hspi, data, 3, 10);
  sum = (unsigned int)(data[0]<<16)|(data[1]<<8)|data[2];
	sum |= (sum & 0x800000) ? 0xFF000000 : 0;
  return sum;
}
//参数配置
void ADCHandleCfgInit(ADC_DataTypedef * adc)
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
	
	adc->state = ADS1256_INIT_OK;
}

//初始化ADS1256
void ADS1256_Init(ADC_DataTypedef * adc)
{
	ADS1256WREG(&(adc->hwinfc),ADS1256_STATUS,0x00);//高位在前、禁用自校准、禁用缓冲
	ADS1256WREG(&(adc->hwinfc),ADS1256_ADCON,ADS1256_GAIN_1 );// 放大倍数1
	ADS1256WREG(&(adc->hwinfc),ADS1256_DRATE,ADS1256_DRATE_30000SPS);
	ADS1256WREG(&(adc->hwinfc),ADS1256_MUX, ADS1256_MUXP_AIN0 | ADS1256_MUXN_AINCOM);// 初始化端口A0为‘+’，AINCOM位‘-’
	ADCHandleCfgInit(adc);
}
/* Private application code --------------------------------------------------*/

//外部中断扫描读取
void ADC_ISR_Read(ADC_DataTypedef * adc)
{
	int32_t ulResult = 0;
	
	if(adc->state == ADS1256_INIT_OK)
	{
		//计算扫描时间
		if(adc->ch == 0)
		{
			adc->tTick = HAL_GetTick() - adc->lTick;
			adc->lTick = HAL_GetTick();
		}
		//读取ADC并切换通道
		ulResult = ADS1256ReadData(&(adc->hwinfc),(adc->ch + 1) % ADS1256_CH_NUM);
		// 保存ADC
		adc->adcVal[adc->ch] = ulResult;
		//均值滤波器
		meanFilterSingleWrite(&(adc->filter[adc->ch]),ulResult);
		//计算电压 vref2.5v uV
		adc->uV[adc->ch] = (long double)adc->filter[adc->ch].meanVal *ADS1256_ADC_UV;
		//自动增益器 0 2 4 6 自动增益
		autoGainScanSingle(&(adc->hwinfc.agt),&(adc->atgain[adc->ch]),adc->ch,adc->uV[adc->ch]);
		//移动扫描通道
		adc->ch = (adc->ch < (ADS1256_CH_NUM - 1)) ? adc->ch + 1:0;
	}
}

//0组外部中断
void EXIT_ADC_DRDY_A(void)
{
	ADC_ISR_Read(&pADCHandle[0]);
}

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/

