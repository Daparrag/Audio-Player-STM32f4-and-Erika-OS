#ifndef _DMACONF
#define _DMACONF
//REGISTERS
#define   DAC_DHR12R1_ADDR  0x40007408                           // DMA writes into this reg on every request
#define   DAC_DHR12R2_ADDR	0x40007414
#define   DAC_DHR8R1_ADDR   0x40007410 //0x10//base adress:0x400074

#define MAXSIZE 512
extern unsigned char BufferDMA[MAXSIZE];
//functions
void init_dma(void);

#endif //_DMACONF
