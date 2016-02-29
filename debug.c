/*
 * debug.c
 *
 *  Created on: 25/ott/2015
 *      Author: admim
 */
#include "stm32f4_discovery_lcd.h"
#include <stdio.h>

void debuginfo(int id, int a, int b, int c)
{
	char text[80];

    sprintf((char*)text,"a = %d b = %d c = %d", a, b, c);
	LCD_DisplayStringLine(LINE(id),text);
}
