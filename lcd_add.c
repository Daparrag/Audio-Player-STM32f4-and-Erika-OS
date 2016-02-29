/*
 * lcd_add.c
 *
 *  Created on: 24/ott/2015
 *      Author: admim
 */
#include "stm32f4_discovery_lcd.h"
#include "fonts.h"
#include "stm32f4xx.h"


void LCD_DrawCharNB(unsigned short int x, unsigned short int y, char c)
{
	  uint32_t index = 0, i = 0;
	  uint16_t curx = x;

	  c -= 32;
	  LCD_SetCursor(curx, y);

	  for(index = 0; index < LCD_Currentfonts->Height; index++)
	  {
	    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	    for(i = 0; i < LCD_Currentfonts->Width; i++)
	    {
	      if((((c[index] & ((0x80 << ((LCD_Currentfonts->Width / 12 ) * 8 ) ) >> i)) == 0x00) &&(LCD_Currentfonts->Width <= 12))||
	        (((c[index] & (0x1 << i)) == 0x00)&&(LCD_Currentfonts->Width > 12 )))
	      {
	    	  LCD_SetCursor(curx+i, y+index);
	    	  LCD_WriteRAM_Prepare();
	      }
	      else
	      {
	        LCD_WriteRAM(TextColor);
	      }
	    }
	    LCD_SetCursor(x, y+index);
	  }
}

void LCD_DrawStringNB(unsigned short int x, unsigned short int y, char *ptr)
{
	  /* Send the string character by character on lCD */
	  while (*ptr != 0)
	  {
	    /* Display one character on LCD */
	    LCD_DrawCharNB(x, y, *ptr);
	    /* Increase the x position by character width */
	    x += LCD_Currentfonts->Width;
		if (x >= LCD_PIXEL_WIDTH) {
			break;
		}
	    /* Point on the next character */
	    ptr++;
	  }
}

