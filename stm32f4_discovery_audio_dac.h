/**
  ******************************************************************************
  * @file    stm32f4_discovery_audio_dac.h
  * @author  Diego Alejandro Parra Guzman
  * @version
  * @date    Feb 2016
  * @brief   This file contains all the functions prototypes for the 
  *          stm32f4_discovery_audio_dac.c 
  *****************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4_DISCOVERY_AUDIOCODEC_H
#define __STM32F4_DISCOVERY_AUDIOCODEC_H
 

 /*Macros ---------------------------------------------------------------------*/
 #define DMA_MAX(x)           (((x) <= CODEC_DMA_MAX_SZE)? (x):CODEC_DMA_MAX_SZE)
 /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_rcc.h" 
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dac.h"


/* For the DMA modes select the interrupt that will be used */
#define AUDIO_MAL_DMA_IT_TC_EN        /* Uncomment this line to enable DMA Transfer Complete interrupt */
/*#define AUDIO_MAL_DMA_IT_HT_EN   /* Uncomment this line to enable DMA Half Transfer Complete interrupt */
/* #define AUDIO_MAL_DMA_IT_TE_EN */  /* Uncomment this line to enable DMA Transfer Error interrupt */

/*-----------------------------------------------------------
                           DAC DHR Registers Address Definitions----------------------------------------------------------------*/
#define DAC_DHR12R2_ADDRESS    0x40007414 //Address Offset 0x14
#define DAC_DHR8R1_ADDRESS     0x40007410 //Address Offset 0x10
#define DAC_DHR12RD_ADRESSS    0x40007420 //Address Offset 0x20
#define DAC_DHR12LD_ADRESSS    0x40007424 //Address Offset 0x24
#define DAC_DHR8RD_ADRESSS     0x40007428 //Address Offset 0x28
#define DAC_DOR1_ADRESSS       0x4000742C //Address Offset 0x2C
#define DAC_DOR2_ADRESSS       0x40007430 //Address Offset 0x2C



/*-----------------------------------
                    Hardware Configuration defines parameters
                                     -----------------------------------------*/
/* TIMER peripheral configuration defines */
#define CODEC_TIMER_ID                      TIM6
#define CODEC_TIMER_CLK                     RCC_APB1Periph_TIM6
#define CODEC_TIMER_PERIOD                  0xFF
#define CODEC_TIMER_PRESCALE                0x00
#define CODEC_TIMER_DIVISION                0x00
#define CODEC_TIMER_COUNTERMODE             TIM_CounterMode_Up
#define CODEC_TIMER_TRGOMODE                TIM_TRGOSource_Update
/* DAC peripheral configuration defines */
#define CODEC_DAC_ID                        DAC1
#define CODEC_DAC_CLK                       RCC_APB1Periph_DAC
#define CODEC_DAC_TRIGGER                   DAC_Trigger_T6_TRGO
#define CODEC_DAC_WAVEMODE                  DAC_WaveGeneration_None
#define CODEC_DAC_BUFFERMODE                DAC_OutputBuffer_Enable
#define CODEC_DAC_CHANNEL1_ID               DAC_Channel_1
#define CODEC_DAC_CHANNEL2_ID               DAC_Channel_2

/* DMA peripheral configuration defines */

#define CODEC_DMAx_ID                      DMA1
#define CODEC_DMAx_CLK                     RCC_AHB1Periph_DMA1
#define CODEC_DMAx_CHANNEL_DEF             DMA_Channel_7
#define CODEC_DMAx_PHERIPHERAL_BASE_ADD    DAC_DHR12RD_ADRESSS
#define CODEC_DMAx_DIR                     DMA_DIR_MemoryToPeripheral
#define CODEC_DMAx_PHERIPHERAL_INC_STATUS  DMA_PeripheralInc_Disable
#define CODEC_DMAx_MEMORY_INC_STATUS       DMA_MemoryInc_Enable
#define CODEC_DMAx_PHERIPHERAL_DATA_SIZE   DMA_PeripheralDataSize_HalfWord
#define CODEC_DMAx_MEMORY_DATA_SIZE        DMA_MemoryDataSize_HalfWord
#define CODEC_DMAx_MODE                    DMA_Mode_Normal
#define CODEC_DMAx_STREAM_PRIORITY         DMA_Priority_High
#define CODEC_DMA_MODE                     DMA_FIFOMode_Disable
#define CODEC_DMAx_FIFO_THRESHOLD          DMA_FIFOThreshold_HalfFull
#define CODEC_DMAx_MEMORY_BURST            DMA_MemoryBurst_Single
#define CODEC_DMAx_PHERISPHERAL_BURST      DMA_PeripheralBurst_Single
#define CODEC_DMA_STREAM                   DMA1_Stream5
#define CODEC_DMA_MAX_SZE                    0xFFFF
//DMA flags 
#define AUDIO_DAC_DMA_FLAG_TC          DMA_FLAG_TCIF0
#define AUDIO_DAC_DMA_FLAG_HT          DMA_FLAG_HTIF0
#define AUDIO_DAC_DMA_FLAG_FE          DMA_FLAG_FEIF0
#define AUDIO_DAC_DMA_FLAG_TE          DMA_FLAG_TEIF0
#define AUDIO_DAC_DMA_FLAG_DME         DMA_FLAG_DMEIF0

/* GPIO peripheral configuration defines */
#define CODEC_DACx_GPIO_PORT               GPIOA
#define CODEC_DACx_GPIO_CLK                RCC_AHB1Periph_GPIOA
#define CODEC_DACx_GPIO_CH2OUT             GPIO_Pin_5
#define CODEC_DACx_GPIO_CH1OUT             GPIO_Pin_4
#define CODEC_DACx_GPIO_MODE               GPIO_Mode_AN
#define CODEC_DACx_GPIO_PULL               GPIO_PuPd_NOPULL
/* **********************************************************
**                                                          *
**----------------------Functions defines----------------- **
**                                                          *
*********************************************************** */
/*-----------------------------------
                           Audio Codec functions
                                    ------------------------------------------*/
/* High Layer codec functions */
void AudioPlayerInit(uint32_t sampleRate);
void AudioPlayerDeInit(void);
void AudioPlayerStart(uint16_t* pBuffer, uint32_t Size);
void Audio_DMA_Play_SetUp(uint32_t Addr, uint32_t Size);
uint32_t AudioPlayer_PauseResume(uint32_t Cmd);
uint32_t AudioPlayer_STOP(void);
void DMA1_Channel5_IRQHandler(void);
void Codec_GPIO_Init(void);
void Codec_GPIO_DeInit(void);
void Codec_DMA_Init(void);
void Codec_DMA_DeInit(void);
void Codec_DAC_Init(void);
void Codec_DAC_DeInit(void);
void Codec_TIMER_Init(uint32_t AudioFreq);
void Codec_TIMER_DeInit(void);
void DMA1_Channel5_IRQHandler(void);

#endif /* __STM32F4_DISCOVERY_AUDIOCODEC_H */
