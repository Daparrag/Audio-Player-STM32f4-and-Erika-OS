#ifndef _TIMERCONF
#define _TIMERCONF

#define OUT_FREQ 44100 // Output waveform frequency
#define WAVE_RES 1 // Waveform resolution
#define CNT_FREQ 84000000 // TIM6 counter clock (prescaled APB1)
#define TIM_PERIOD ((CNT_FREQ)/((WAVE_RES)*(OUT_FREQ))) // Autoreload reg value

//Functions of timer

void init_timer_Setup(uint32_t AudioFreq);
void init_timer_Start(void);
void init_timer_Stop(void);

#endif //_TIMERCONF

