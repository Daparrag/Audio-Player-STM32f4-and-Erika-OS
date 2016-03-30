/*-----------------------------------------------------------------------*/
/* This file Setup the configuration of the ports of the DAC */
/**/
/*-----------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "GPIO_Conf.h"


void init_gpio(void) {
GPIO_InitTypeDef gpio_init;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
gpio_init.GPIO_Mode = GPIO_Mode_AN;
gpio_init.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
gpio_init.GPIO_OType = GPIO_OType_PP;
gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOA, &gpio_init);
}
