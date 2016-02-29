/*
 * uart_print_red.c
 *
 * @author Franchino Gianluca
 * @date September 2015
 */
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
#ifdef __GNUC__
int _write(int fd, char *ptr, int len)
{
	  /* Write "len" of char from "ptr" to file id "fd"
	   * Return number of char written.
	   * Need implementing with UART here. */
	uint32_t i;

	for (i = 0; i < len; i++) {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
		USART_SendData(EVAL_COM1, (uint8_t) ptr[i]);
	/* Loop until the end of transmission */
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	}

	return len;
}
#else
int fputc(int ch, FILE *f)
{

	USART_SendData(EVAL_COM1, (uint8_t) ch);
	while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);

	return ch;

}
#endif /* __GNUC__ */

USART_InitTypeDef USART_InitStructure;

void uart_init(void)
{
	/* USARTx configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM_EVAL_COMInit(COM1, &USART_InitStructure);
}



