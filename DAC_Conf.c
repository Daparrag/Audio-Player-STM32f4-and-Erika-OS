/*-----------------------------------------------------------------------*/
/* This file Setup the configuration of the DAC channel 1 or two for convert WAV data receiving by the DMA */
/**/
/*-----------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "DAC_Conf.h"


void init_dac_Ch1(void) { //channel 1 config
DAC_InitTypeDef dac_init;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
DAC_StructInit(&dac_init);
dac_init.DAC_Trigger = DAC_Trigger_T6_TRGO;
dac_init.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
dac_init.DAC_WaveGeneration = DAC_WaveGeneration_None;
DAC_Init(DAC_Channel_1, &dac_init);
}

void init_dac_Ch2(void) { //channel 1 config
DAC_InitTypeDef dac_init;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
DAC_StructInit(&dac_init);
dac_init.DAC_Trigger = DAC_Trigger_T6_TRGO;
dac_init.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
dac_init.DAC_WaveGeneration = DAC_WaveGeneration_None;
DAC_Init(DAC_Channel_2, &dac_init);
}

void dac_Ch1_start(void){
	DAC_Cmd(DAC_Channel_1, ENABLE);
}

void dac_Ch1_stop(void){
	DAC_Cmd(DAC_Channel_1, DISABLE);
}


void dac_Ch2_start(void){
	DAC_Cmd(DAC_Channel_2, ENABLE);
}

void dac_Ch2_stop(void){
	DAC_Cmd(DAC_Channel_2, DISABLE);
}
