/*-----------------------------------------------------------------------*/
/* This file Setup the configuration of the DMA for transfer Data to DAC continously */
/**/
/*-----------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "DMA_Conf.h"

unsigned char BufferDMA[MAXSIZE];

void init_dma(void) {
	//STM_EVAL_LEDOn(LED3);
	DMA_InitTypeDef dma_init;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Stream5);
	dma_init.DMA_Channel = DMA_Channel_7;
	dma_init.DMA_PeripheralBaseAddr = DAC_DHR8R1_ADDR;
	dma_init.DMA_Memory0BaseAddr = (uint32_t)&BufferDMA;
	dma_init.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	dma_init.DMA_BufferSize = 512;
	dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma_init.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	dma_init.DMA_Mode = DMA_Mode_Circular;
	dma_init.DMA_Priority = DMA_Priority_High;
	dma_init.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma_init.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	dma_init.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	dma_init.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA1_Stream5, &dma_init);
	DMA_Cmd(DMA1_Stream5, ENABLE);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_DMACmd(DAC_Channel_1, ENABLE);
//	DAC_ITConfig(DAC_Channel_1, DMA_SxCR_HTIE,ENABLE);
//	DAC_ITConfig(DAC_Channel_1, DMA_SxCR_TCIE,ENABLE);
	}
