/**
  ******************************************************************************
  * File Name          : comProtocol.c
  * Description        : Code for comProtocol lib
  ******************************************************************************
  * @author  kmakise
  * @version V1.0.0
  * @date    2021-12-13
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
#include "comProtocol.h"
#include "kmGlobal.h"
#include "kmQueue.h"
#include "ADS1256.h"
#include "ADS1256_cfg.h"
#include "usart.h"
#include "stdio.h"
/* Private define ------------------------------------------------------------*/
#define USART1_RX_USTA    0x0A
#define USART1_RX_UEND		0x0D
#define CMD_NUM_MAX				3
#define CMD_LEN_MAX				4
/* Private variables ---------------------------------------------------------*/
const uint8_t COMCMD [CMD_NUM_MAX][CMD_LEN_MAX + 1] = {
	"AMP:",	//0
	"AVG:",	//1
	"FCH:"	//2
};

COM_DataTypedef pComHandle = {
	.huart 	= &huart1,
	.uSta 	= USART1_RX_USTA,
	.uEnd 	= USART1_RX_UEND,
};

int32_t pADCFilterBuf[32];
uint8_t pTXBuffer[512];
uint8_t gTxDMAOver = 0;
/* Private function prototypes -----------------------------------------------*/
//获取指令编号
uint8_t getCmdNum(const uint8_t (*cmdlist)[CMD_LEN_MAX + 1],uint8_t * pData)
{
	for(int i = 0;i < CMD_NUM_MAX;i++)
	{
		if(cmdlist[i][0] == pData[0] &&
			 cmdlist[i][1] == pData[1] &&
		   cmdlist[i][2] == pData[2] &&
		   cmdlist[i][3] == pData[3] )
		{
			return i;
		}
	}
	return 0xff;
}

//放大倍率设定
void comCmdAMP(uint8_t ch,uint8_t num)
{
	uint8_t port,nch;
	
	port = ch / 8;
	nch = ch % 8;
	pCfgADCParam.gain[port][nch] = num;
	pCfgADCParam.update = ADS1256_CFG_WW;
}
//平均次数
void comCmdAVG(uint8_t ch,uint8_t num)
{
	uint8_t port,nch;
	
	port = ch / 8;
	nch = ch % 8;
	pCfgADCParam.mean[port][nch] = num;
	pCfgADCParam.update = ADS1256_CFG_WW;
}
//RMS / RSSI 选择
void comCmdFCH(uint8_t ch,uint8_t num)
{
	uint8_t port,nch;
	
	port = ch / 8;
	nch = ch % 8;
	pCfgADCParam.mode[port][nch] = num;
	pCfgADCParam.update = ADS1256_CFG_WW;
}

//包内容解析
void comPackageAnalyze(uint8_t * pData)
{
	switch(getCmdNum(COMCMD,&(pData[0])))
	{
		case 0://AMP
		{
			uint16_t ch,num;
			sscanf((char *)&(pData[3]),":%02X:%02X",(int *)&ch,(int *)&num);
			comCmdAMP(ch,num);
			break;
		}
		case 1://AVG
		{
			uint16_t ch,num;
			sscanf((char *)&(pData[3]),":%02X:%02X",(int *)&ch,(int *)&num);
			comCmdAVG(ch,num);
			break;
		}
		case 2://FCH
		{
			uint16_t ch,num;
			sscanf((char *)&(pData[3]),":%02X:%02X",(int *)&ch,(int *)&num);
			comCmdFCH(ch,num);
			break;
		}
		default:break;
	}
}
//队列字节流接收解析
void comQueueReceive(COM_DataTypedef * com)
{
	uint8_t udata = 0;
	while(deRingQueueSingleOut(&(com->qrx),&udata))
	{
		if(udata == com->uSta)
		{
			com->qrx.pd = 0;
		}
		else if(udata == com->uEnd)
		{
			comPackageAnalyze((uint8_t *)(com->qrx.data));
			com->qrx.pd = 0;
		}
		else
		{
			com->qrx.data[com->qrx.pd] = udata;
			com->qrx.pd = (com->qrx.pd + 1) % RQ_DATA_MAXSIZE;
		}
	}
}

//串口中断接收
void comISRWriteData(COM_DataTypedef * com,uint8_t data)
{
	enRingQueueSingle(&(com->qrx),data);
}

//串口发送
void comTransmit(COM_DataTypedef * com,uint8_t * pData,uint32_t size)
{
	HAL_UART_Transmit(com->huart,pData,size,10);
}


//AD测量数据发送
void comADDataUpdate(void)
{
	static uint8_t packnum = 0;
	uint8_t * pTxBufInst = pTXBuffer;
	
	//包头+ LL +  XH + AAAAAAAA+BBBBBBBB+…+checksum+包尾
	// 1 + 2~3 + 4~5 +        6~262       +263~264 + 265
	
	if(gTxDMAOver == 0)
	{
		//读取各个滤波器计算数值
		for(int i = 0;i < 4;i++)
		{
			for(int j = 0;j < 8;j++)
			{
				pADCFilterBuf[i * 8 + j] = pADCHandle[i].filter[j].meanVal;
			}
		}
		
		//包头包长度
		*pTxBufInst++ = 0x0A;
		sprintf((char *)pTxBufInst,"%02X",0xFF);
		pTxBufInst += 2;
		sprintf((char *)pTxBufInst,"%02X",packnum++);
		pTxBufInst += 2;
		
		//ADC数据
		for(int i = 0;i < 32;i++)
		{
			sprintf((char *)pTxBufInst,"%08X",pADCFilterBuf[i]);
			pTxBufInst += 8; 
		}
		
		//校验和
		uint8_t cheaksum = 0;
		for(int i = 1;i < 260;i++)
		{
			cheaksum += pTXBuffer[i];
		}
		sprintf((char *)pTxBufInst,"%02X",cheaksum);
		pTxBufInst += 2;
		
		//包尾
		*pTxBufInst++ = 0x0D;
		
		HAL_UART_Transmit_DMA(&huart1,pTXBuffer,264);
		gTxDMAOver = 1;
	}
	else
	{
		while(0);
	}
}



/* Private application code --------------------------------------------------*/
void comISRCall(void)
{
	if(pComHandle.huart->Instance->ISR & UART_IT_RXNE)
	{
		comISRWriteData(&pComHandle,(pComHandle.huart->Instance->RDR&(uint8_t)0x00FF));
	}
}

void comLoopRec(void)
{
	comADDataUpdate();
	comQueueReceive(&pComHandle);
}


void comDMAOver(void)
{
	gTxDMAOver = 0;
}

/************************ (C) COPYRIGHT kmakise ****************END OF FILE****/


