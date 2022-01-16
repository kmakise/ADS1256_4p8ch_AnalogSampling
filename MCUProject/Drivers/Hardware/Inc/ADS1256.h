/**
  ******************************************************************************
  * @file           : ADS1256.h
  * @brief          : Header for ADS1256 file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADS1256_H
#define __ADS1256_H

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "kmGlobal.h"
#include "MAX308.h"
#include "kmFilter.h"
/* Exported defines -----------------------------------------------------------*/

// define commands 
#define ADS1256_CMD_WAKEUP   0x00 
#define ADS1256_CMD_RDATA    0x01 
#define ADS1256_CMD_RDATAC   0x03 
#define ADS1256_CMD_SDATAC   0x0f 
#define ADS1256_CMD_RREG     0x10 
#define ADS1256_CMD_WREG     0x50 
#define ADS1256_CMD_SELFCAL  0xf0 
#define ADS1256_CMD_SELFOCAL 0xf1 
#define ADS1256_CMD_SELFGCAL 0xf2 
#define ADS1256_CMD_SYSOCAL  0xf3 
#define ADS1256_CMD_SYSGCAL  0xf4 
#define ADS1256_CMD_SYNC     0xfc 
#define ADS1256_CMD_STANDBY  0xfd 
#define ADS1256_CMD_REST     0xfe 
 
// define the ADS1256 register values 
#define ADS1256_STATUS       0x00   
#define ADS1256_MUX          0x01   
#define ADS1256_ADCON        0x02   
#define ADS1256_DRATE        0x03   
#define ADS1256_IO           0x04   
#define ADS1256_OFC0         0x05   
#define ADS1256_OFC1         0x06   
#define ADS1256_OFC2         0x07   
#define ADS1256_FSC0         0x08   
#define ADS1256_FSC1         0x09   
#define ADS1256_FSC2         0x0A 
 
// define multiplexer codes 
#define ADS1256_MUXP_AIN0   0x00 
#define ADS1256_MUXP_AIN1   0x10 
#define ADS1256_MUXP_AIN2   0x20 
#define ADS1256_MUXP_AIN3   0x30 
#define ADS1256_MUXP_AIN4   0x40 
#define ADS1256_MUXP_AIN5   0x50 
#define ADS1256_MUXP_AIN6   0x60 
#define ADS1256_MUXP_AIN7   0x70 
#define ADS1256_MUXP_AINCOM 0x80 
 
#define ADS1256_MUXN_AIN0   0x00 
#define ADS1256_MUXN_AIN1   0x01 
#define ADS1256_MUXN_AIN2   0x02 
#define ADS1256_MUXN_AIN3   0x03 
#define ADS1256_MUXN_AIN4   0x04 
#define ADS1256_MUXN_AIN5   0x05 
#define ADS1256_MUXN_AIN6   0x06 
#define ADS1256_MUXN_AIN7   0x07 
#define ADS1256_MUXN_AINCOM 0x08   

// define gain codes 
#define ADS1256_GAIN_1      0x00 
#define ADS1256_GAIN_2      0x01 
#define ADS1256_GAIN_4      0x02 
#define ADS1256_GAIN_8      0x03 
#define ADS1256_GAIN_16     0x04 
#define ADS1256_GAIN_32     0x05 
#define ADS1256_GAIN_64     0x06 
//#define ADS1256_GAIN_64     0x07 
 
// define drate codes 
#define ADS1256_DRATE_30000SPS   0xF0 
#define ADS1256_DRATE_15000SPS   0xE0 
#define ADS1256_DRATE_7500SPS   0xD0 
#define ADS1256_DRATE_3750SPS   0xC0 
#define ADS1256_DRATE_2000SPS   0xB0 
#define ADS1256_DRATE_1000SPS   0xA1 
#define ADS1256_DRATE_500SPS    0x92 
#define ADS1256_DRATE_100SPS    0x82 
#define ADS1256_DRATE_60SPS     0x72 
#define ADS1256_DRATE_50SPS     0x63 
#define ADS1256_DRATE_30SPS     0x53 
#define ADS1256_DRATE_25SPS     0x43 
#define ADS1256_DRATE_15SPS     0x33 
#define ADS1256_DRATE_10SPS     0x23 
#define ADS1256_DRATE_5SPS      0x13 
#define ADS1256_DRATE_2_5SPS    0x03


#define ADS1256_INIT_OK 				0xAA
#define ADS1256_CH_NUM 					8
#define ADS1256_PORT_NUM 				4
#define ADS1256_ADC_UV					0.596046518808



/* Exported types ------------------------------------------------------------*/
//硬件接口
typedef struct
{
	SPI_HandleTypeDef  *hspi;					//spi接口
	AG_OptTypedef 			agt;					//放大倍数与采样接口
	GPIO_OptTypedef		 	drdy;					//ADC转换完成
	
}ADC_HWInterface;

//ADC句柄
typedef struct
{
	ADC_HWInterface			hwinfc;													//硬件接口
	MeanFilterTypedef 	filter[ADS1256_CH_NUM];					//均值滤波器
	AutoGainDataTypedef atgain[ADS1256_CH_NUM];					//自动比例调节器
	int32_t 						adcVal[ADS1256_CH_NUM];					//ADC值
	double_t 						uV[ADS1256_CH_NUM];							//uV电压值
	uint32_t 						tTick;													//扫描总时间
	uint32_t 						lTick;													//读取时间戳
	uint8_t  						state;													//配置状态
	uint8_t  						ch;															//读取通道
	uint8_t 						id;															//句柄id	
	
}ADC_DataTypedef;
/* Exported constants --------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern ADC_DataTypedef pADCHandle[ADS1256_PORT_NUM];

/* Exported functions prototypes ---------------------------------------------*/
void ADS1256_Init(ADC_DataTypedef * adc);
void EXIT_ADC_DRDY_A(void);

/* Private defines -----------------------------------------------------------*/

#endif /* __ADS1256_H */

/************************ (C) COPYRIGHT kmakise ***************END OF FILE****/
