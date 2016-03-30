#ifndef _DACCONF
#define _DACCONF

//DAC function

void init_dac_Ch1(void);  //Channel 1 config
void init_dac_Ch2(void);  //Channel 2 config
void dac_Ch1_start(void); //Start conversion of channel 1
void dac_Ch1_stop(void);  //Stop conversion of channel 1
void dac_Ch2_start(void); //Start conversion of channel 2
void dac_Ch2_stop(void); //Stop conversion of channel 2

#endif //_DACCONF
