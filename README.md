# SD_DAC_AudioPlayerERIKA
Audio Player implementation over STM32F4 discovery board

This Project repesent an implementation of an audio player over the operating system ERIKA and the STM32f4 discovery Board 
                        
The implementation consist of read the wav file from the SDcard using the SDIO and DMA2, then independently the DMA1 is able to acces to the memory
and transffer data directly from the flash memory and put it into the dac which automatically convert to analog values and then generate the sound. 
