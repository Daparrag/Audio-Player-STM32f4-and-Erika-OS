/**
  ******************************************************************************
  * @file    stm32f4_discovery_audio_dac.c
  * @author  Diego Alejandro Parra Guzman
  * @version
  * @date    Feb-2016
  * @brief   This file includes the low layer driver for CS43L22 Audio Codec
  *          available on STM32F4-Discovery Kit.  
  ******************************************************************************
  */


/*INCLUDES-------------------------------------------------------------------*/
#include "stm32f4_discovery_audio_dac.h"




/*DEFINITIONS*****************************************************************/
#define AUDIO_PAUSE                   0
#define AUDIO_RESUME                  1
/*****************************************************************************/  
  
/*Structures-----------------------------------------------------------------*/
DMA_InitTypeDef DMA_InitStructure;
/*---------------------------------------------------------------------------*/
/*Private Variables----------------------------------------------------------*/
uint32_t AudioTotalSize = 0xFFFF; /* This variable holds the total size of the audio file */
uint32_t AudioRemSize   = 0xFFFF; /* This variable holds the remaining data in audio file */
uint16_t * CurrentPos ;           /* This variable holds the current position of audio pointer */
__IO uint8_t OutputDev = 0;

/*---------------------------------------------------------------------------*/

void AudioPlayerInit(uint32_t sampleRate){
	Codec_GPIO_Init();
	Codec_TIMER_Init(sampleRate);
	Codec_DAC_Init();
	Codec_DMA_Init();
	
}
void AudioPlayerDeInit(){
	Codec_DMA_DeInit();
	Codec_TIMER_DeInit();
	Codec_DAC_DeInit();
	Codec_GPIO_DeInit();
}

/**
  * @brief  Starts playing audio stream from a data buffer for a determined size. 
  * @param  pBuffer: Pointer to the buffer 
  * @param  Size: Number of audio data BYTES.
  * @retval 0 if correct communication, else wrong communication
  */

void AudioPlayerStart(uint16_t* pBuffer, uint32_t Size){
	AudioTotalSize = Size;
	/* Update the Media layer and enable it for play */
	Audio_DMA_Play_SetUp((uint32_t)pBuffer, (uint32_t)(DMA_MAX(Size/4)));
	/* Update the remaining number of data to be played */
	AudioRemSize = (Size/2) - DMA_MAX(AudioTotalSize);
	/* Update the current audio pointer position */
	CurrentPos = pBuffer + DMA_MAX(AudioTotalSize);
}

/**
  * @brief  This function Pauses or Resumes the audio file stream. In case
  *         of using DMA, the DMA Pause feature is used.
  * 
  * @WARNING When calling EVAL_AUDIO_PauseResume() funct
  * 
  * @param  Cmd: AUDIO_PAUSE (or 0) to pause, AUDIO_RESUME (or any value different
  *         from 0) to resume. 
  * @retval 0 if correct communication, else wrong communication
  */
uint32_t AudioPlayer_PauseResume(uint32_t Cmd){
	if (Cmd == AUDIO_PAUSE)
  {   

    /* Pause the I2S DMA Stream 
        Note. For the STM32F40x devices, the DMA implements a pause feature, 
              by disabling the stream, all configuration is preserved and data 
              transfer is paused till the next enable of the stream.
              This feature is not available on STM32F40x devices. */
    DMA_Cmd(CODEC_DMA_STREAM, DISABLE);
  }else{
		/* Resume the I2S DMA Stream 
        Note. For the STM32F40x devices, the DMA implements a pause feature, 
              by disabling the stream, all configuration is preserved and data 
              transfer is paused till the next enable of the stream.
              This feature is not available on STM32F40x devices. */
    DMA_Cmd(CODEC_DMA_STREAM, ENABLE);
  }
  return 0;
}

uint32_t AudioPlayer_STOP(){
		/* Stop the Transfer on the I2S side: Stop and disable the DMA stream */
	DMA_Cmd(CODEC_DMA_STREAM, DISABLE);
		/* Clear all the DMA flags for the next transfer */
	DMA_ClearFlag(CODEC_DMA_STREAM, AUDIO_DAC_DMA_FLAG_TC |AUDIO_DAC_DMA_FLAG_HT | \
			AUDIO_DAC_DMA_FLAG_FE | AUDIO_DAC_DMA_FLAG_TE);
/* In all modes, disable the DAC peripheral */
	Codec_DAC_DeInit();
	return 0;
}


void Audio_DMA_Play_SetUp(uint32_t Addr, uint32_t Size){
	/* Configure the buffer address and size */
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Addr;
	DMA_InitStructure.DMA_BufferSize = (uint32_t)Size/2;
	/* Configure the DMA Stream with the new parameters */
	DMA_Init(CODEC_DMA_STREAM, &DMA_InitStructure);
	/* Enable the  MEMORY TO DAC DMA Stream*/
	DMA_Cmd(CODEC_DMA_STREAM, ENABLE);
	/* Enable DAC Channel 1&2 */
	DAC_Cmd(CODEC_DAC_CHANNEL1_ID, ENABLE);
	DAC_Cmd(CODEC_DAC_CHANNEL2_ID, ENABLE);
	/* Enable DMA for DAC Channel 1 & 2 */
	DAC_DMACmd(CODEC_DAC_CHANNEL1_ID, ENABLE);
	DAC_DMACmd(CODEC_DAC_CHANNEL2_ID, ENABLE);
}
void Codec_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	//Configuration of the output registers for DAC 
	RCC_AHB1PeriphClockCmd(CODEC_DACx_GPIO_CLK, ENABLE); //Enable The clock for GPIO Port
	GPIO_InitStructure.GPIO_Pin = CODEC_DACx_GPIO_CH1OUT | CODEC_DACx_GPIO_CH2OUT;
	GPIO_InitStructure.GPIO_Mode = CODEC_DACx_GPIO_MODE;
	GPIO_InitStructure.GPIO_PuPd = CODEC_DACx_GPIO_PULL;
	GPIO_Init(CODEC_DACx_GPIO_PORT, &GPIO_InitStructure);
	
}
void Codec_GPIO_DeInit(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(CODEC_DACx_GPIO_CLK, DISABLE); //Enable The clock for GPIO Port
	GPIO_InitStructure.GPIO_Pin = CODEC_DACx_GPIO_CH1OUT | CODEC_DACx_GPIO_CH2OUT;
	GPIO_InitStructure.GPIO_Mode = CODEC_DACx_GPIO_MODE;
	GPIO_InitStructure.GPIO_PuPd = CODEC_DACx_GPIO_PULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(CODEC_DACx_GPIO_PORT, &GPIO_InitStructure);
	//GPIO_DeInit(CODEC_DACx_GPIO_PORT, CODEC_DACx_GPIO_CH1OUT);
	//GPIO_DeInit(CODEC_DACx_GPIO_PORT, CODEC_DACx_GPIO_CH2OUT);
	
}
void Codec_DMA_Init(void){
	RCC_AHB1PeriphClockCmd(CODEC_DMAx_CLK , ENABLE);
	DMA_Cmd(CODEC_DMA_STREAM, DISABLE);
	DMA_DeInit(CODEC_DMA_STREAM);//Desable the Stream5
	DMA_InitStructure.DMA_Channel = CODEC_DMAx_CHANNEL_DEF;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)CODEC_DMAx_PHERIPHERAL_BASE_ADD;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)0;//BUFFER ADDRESSES Will be configure In play function
	DMA_InitStructure.DMA_DIR = CODEC_DMAx_DIR;
	DMA_InitStructure.DMA_BufferSize = (uint32_t)0xFFFE;//BUFFER SIZE will be configure in play fuction
	DMA_InitStructure.DMA_PeripheralInc = CODEC_DMAx_PHERIPHERAL_INC_STATUS;
	DMA_InitStructure.DMA_MemoryInc = CODEC_DMAx_MEMORY_INC_STATUS;
	DMA_InitStructure.DMA_PeripheralDataSize = CODEC_DMAx_PHERIPHERAL_DATA_SIZE;
	DMA_InitStructure.DMA_MemoryDataSize = CODEC_DMAx_MEMORY_DATA_SIZE;
	DMA_InitStructure.DMA_Mode = CODEC_DMAx_MODE;
	DMA_InitStructure.DMA_Priority = CODEC_DMAx_STREAM_PRIORITY;
	DMA_InitStructure.DMA_FIFOMode = CODEC_DMA_MODE;
	DMA_InitStructure.DMA_FIFOThreshold = CODEC_DMAx_FIFO_THRESHOLD;
	DMA_InitStructure.DMA_MemoryBurst = CODEC_DMAx_MEMORY_BURST;
	DMA_InitStructure.DMA_PeripheralBurst = CODEC_DMAx_PHERISPHERAL_BURST;
	DMA_Init(CODEC_DMA_STREAM, &DMA_InitStructure);
	
	
	 /* Enable the selected DMA interrupts (selected in "stm32f4_discovery_eval_audio_codec.h" defines) */
#ifdef AUDIO_MAL_DMA_IT_TC_EN
    DMA_ITConfig(CODEC_DMA_STREAM, DMA_IT_TC, ENABLE);
#endif /* AUDIO_MAL_DMA_IT_TC_EN */
#ifdef AUDIO_MAL_DMA_IT_HT_EN
    DMA_ITConfig(CODEC_DMA_STREAM, DMA_IT_HT, ENABLE);
#endif /* AUDIO_MAL_DMA_IT_HT_EN */
#ifdef AUDIO_MAL_DMA_IT_TE_EN
    DMA_ITConfig(CODEC_DMA_STREAM, DMA_IT_TE | DMA_IT_FE | DMA_IT_DME, ENABLE);
#endif /* AUDIO_MAL_DMA_IT_TE_EN */
  

}
void Codec_DMA_DeInit(void){
	DMA_Cmd(CODEC_DMA_STREAM, DISABLE);
	DMA_DeInit(CODEC_DMA_STREAM);//Desable the Stream5
}
void Codec_DAC_Init(void){
	DAC_InitTypeDef  DAC_InitStructure;
	RCC_APB1PeriphClockCmd(CODEC_DAC_CLK, ENABLE);
	/* DAC channel2 Configuration */
	DAC_InitStructure.DAC_Trigger = CODEC_DAC_TRIGGER; //DAC trigger bit the TIM6
	DAC_InitStructure.DAC_WaveGeneration = CODEC_DAC_WAVEMODE;
	DAC_InitStructure.DAC_OutputBuffer = CODEC_DAC_BUFFERMODE;
	DAC_Init(CODEC_DAC_CHANNEL1_ID, &DAC_InitStructure);
	DAC_Init(CODEC_DAC_CHANNEL2_ID, &DAC_InitStructure);
}
void Codec_DAC_DeInit(void){
	DAC_DMACmd(CODEC_DAC_CHANNEL1_ID,DISABLE);
	DAC_DMACmd(CODEC_DAC_CHANNEL2_ID,DISABLE);
}
void Codec_TIMER_Init(uint32_t AudioFreq){
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	/* TIM6 Periph clock enable */
	RCC_APB1PeriphClockCmd(CODEC_TIMER_CLK, ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = ((uint32_t)SystemCoreClock/(uint32_t)AudioFreq) - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = CODEC_TIMER_COUNTERMODE;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
		/* TIM6 TRGO selection */
	TIM_SelectOutputTrigger(TIM6, CODEC_TIMER_TRGOMODE);//Used For update Events for the DAC Pherisferical
	/* TIM6 enable counter */
	TIM_Cmd(TIM6, ENABLE);
}
void Codec_TIMER_DeInit(void){
	TIM_Cmd(TIM6, DISABLE);
} 

void DMA1_Channel5_IRQHandler(void){
uint16_t *pAddr = (uint16_t *)CurrentPos;
 uint32_t Size = AudioRemSize;	
#ifdef AUDIO_MAL_DMA_IT_TC_EN /* Transfer complete interrupt */
  /* Transfer complete interrupt */
  if (DMA_GetFlagStatus(CODEC_DMA_STREAM, AUDIO_DAC_DMA_FLAG_TC) != RESET)
  {
#ifdef AUDIO_MAL_MODE_NORMAL
    /* Check if the end of file has been reached */
    if (AudioRemSize > 0)
    {
		/* Wait the DMA Stream to be effectively disabled */
      while (DMA_GetCmdStatus(CODEC_DMA_STREAM) != DISABLE)
      {}
		/* Clear the Interrupt flag */
		DMA_ClearFlag(CODEC_DMA_STREAM, AUDIO_DAC_DMA_FLAG_TC);
		/* Re-Configure the buffer address and size */
		DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) CurrentPos;
		DMA_InitStructure.DMA_BufferSize = (uint32_t) (DMA_MAX(AudioRemSize));
		/* Configure the DMA Stream with the new parameters */
		DMA_Init(CODEC_DMA_STREAM, &DMA_InitStructure);
		/* Enable DMA1_Stream5 */
		DMA_Cmd(CODEC_DMA_STREAM, ENABLE);

		/* Enable DAC Channel 1&2 */
		DAC_Cmd(CODEC_DAC_CHANNEL1_ID, ENABLE);
		DAC_Cmd(CODEC_DAC_CHANNEL2_ID, ENABLE);

		/* Enable DMA for DAC Channel 1&2 */
		DAC_DMACmd(CODEC_DAC_CHANNEL1_ID, ENABLE);
		DAC_DMACmd(CODEC_DAC_CHANNEL2_ID, ENABLE);
	}
	else
	{
		/* Disable DMA1_Stream5 */
		DMA_Cmd(CODEC_DMA_STREAM, DISABLE);
		/* Disable DAC Channel 1&2 */
		DAC_Cmd(CODEC_DAC_CHANNEL1_ID, DISABLE);
		DAC_Cmd(CODEC_DAC_CHANNEL2_ID, DISABLE);
      /* Clear the Interrupt flag */
		DMA_ClearFlag(CODEC_DMA_STREAM, AUDIO_DAC_DMA_FLAG_TC);
      /* Manage the remaining file size and new address offset: This function 
      should be coded by user (its prototype is already declared in stm32f4_discovery_audio_codec.h) */  
      Codec_DMA_DAC_TransferComplete_CallBack((uint32_t)CurrentPos, 0);       		
	}
#elif defined(AUDIO_MAL_MODE_CIRCULAR)
    /* Manage the remaining file size and new address offset: This function 
       should be coded by user (its prototype is already declared in stm32f4_discovery_audio_codec.h) */  
	Codec_DMA_DAC_TransferComplete_CallBack(pAddr, Size);    	
	 /* Clear the Interrupt flag */
    DMA_ClearFlag(CODEC_DMA_STREAM, AUDIO_DAC_DMA_FLAG_TC);
#endif /* AUDIO_MAL_MODE_NORMAL */  	
  }
#endif /* AUDIO_MAL_DMA_IT_TC_EN */

#ifdef AUDIO_MAL_DMA_IT_HT_EN /* Half Transfer complete interrupt */
  /* Half Transfer complete interrupt */
  if (DMA_GetFlagStatus(CODEC_DMA_STREAM, AUDIO_DAC_DMA_FLAG_HT) != RESET)
  {
    /* Manage the remaining file size and new address offset: This function 
       should be coded by user (its prototype is already declared in stm32f4_discovery_audio_codec.h) */  
    Codec_DMA_DAC__HalfTransfer_CallBack((uint32_t)pAddr, Size);    
   
    /* Clear the Interrupt flag */
    DMA_ClearFlag(CODEC_DMA_STREAM, AUDIO_DAC_DMA_FLAG_HT);    
  }
#endif /* AUDIO_MAL_DMA_IT_HT_EN */
#ifdef AUDIO_MAL_DMA_IT_TE_EN  /* FIFO Error interrupt */
  /* FIFO Error interrupt */
  if ((DMA_GetFlagStatus(CODEC_DMA_STREAM, AUDIO_MAL_DMA_FLAG_TE) != RESET) || \
     (DMA_GetFlagStatus(CODEC_DMA_STREAM, AUDIO_MAL_DMA_FLAG_FE) != RESET) ||  \
     (DMA_GetFlagStatus(CODEC_DMA_STREAM, AUDIO_MAL_DMA_FLAG_DME) != RESET))
    
  {
	/* Manage the error generated on DMA FIFO: This function 
       should be coded by user (its prototype is already declared in stm32f4_discovery_audio_codec.h) */  
    Codec_DMA_DAC_Error_CallBack((uint32_t*)&pAddr);      
    /* Clear the Interrupt flag */
    DMA_ClearFlag(CODEC_DMA_STREAM, AUDIO_MAL_DMA_FLAG_TE | AUDIO_MAL_DMA_FLAG_FE | \
                                        AUDIO_MAL_DMA_FLAG_DME);  
  }
#endif /* AUDIO_MAL_DMA_IT_TE_EN */	
}
