/*-----------------------------------------------------------------------*/
/* This file Setup the configuration of the Timer as a trigger of the DAC channels 1,2 or both*/
/* in order to  convert the digital values to analog values*/

#include "stm32f4xx.h"
#include "Timer_Conf.h"


// TIM6 configuration is based on CPU @168MHz and APB1 @84MHz
// TIM6 Update event occurs each 84Mhz/44Khz ~= 1909 ticks (44,002 Hz)
void init_timer_Setup(uint32_t AudioFreq){
	TIM_TimeBaseInitTypeDef tim_init;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Period =((CNT_FREQ)/((WAVE_RES)*(AudioFreq)));//45 // Autoreload reg value; //44Khz DAC update rate, 8 bit period on TIM6;
	tim_init.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM6, &tim_init);
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
	//TIM_Cmd(TIM6, ENABLE);
	TIM_Cmd(TIM6, DISABLE);
}

void init_timer_Start(void){
	TIM_Cmd(TIM6, ENABLE);
}

void init_timer_Stop(void){
	TIM_Cmd(TIM6, DISABLE);
}
