/*
 * touch.c
 *
 *  Created on: 20/ott/2015
 *      Author: admim
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "STMPE811QTR.h"
#include "touch.h"
#include <stdio.h>

#define TOUCH_AD_VALUE_MAX    (4500)
#define TOUCH_AD_VALUE_MIN    (30)
#define CALIBRATION_RANGE      (10)
#define CURSOR_LEN    (10)

#define xScreenSize (320)
#define yScreenSize (240)
#define xCalMargin (20)
#define yCalMargin (20)

TCal tcs;

static TPoint point_Base[5] = {
  {xCalMargin,yCalMargin},
  {xScreenSize-xCalMargin,yCalMargin},
  {xCalMargin,yScreenSize-yCalMargin},
  {xScreenSize-xCalMargin,yScreenSize-yCalMargin},
  {xScreenSize/2,yScreenSize/2}
};

TPoint touch_points[5];

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void delay(volatile uint32_t nCount)
{
  volatile uint32_t index = 0;
  for (index = (100000 * nCount); index != 0; index--);
}

void Draw_Calibration_Mark(unsigned int xm, unsigned int ym)
{
	LCD_DrawUniLine( xm - CURSOR_LEN, ym, xm + CURSOR_LEN, ym);
	LCD_DrawUniLine( xm, ym - CURSOR_LEN, xm, ym + CURSOR_LEN);
}

extern void delay(__IO uint32_t nCount);

unsigned char  Lcd_Touch_Calibration()
{
	int xt, yt;
	unsigned char res;
	float dCalTouch, dCalScreen;
	unsigned char k;

    delay(200);
	/* 4 Calibration points at extremes */
	for (k = 0;k < 4;k++) {
		Draw_Calibration_Mark(point_Base[k].x, point_Base[k].y);
	    res = GetTouch_TC_Sync(&xt, &yt);
	    touch_points[k].x = xt;
	    touch_points[k].y = yt;
	    delay(200);
	}

	dCalScreen = xScreenSize - 2.0*xCalMargin;
	dCalTouch = (float)((touch_points[1].x - touch_points[0].x) + (touch_points[3].x - touch_points[2].x)) / 2.0;
	tcs.xScale = dCalScreen / dCalTouch;

	dCalScreen = yScreenSize - 2.0*yCalMargin;
	dCalTouch = (float)((touch_points[2].y - touch_points[0].y) + (touch_points[3].y - touch_points[1].y)) / 2.0;
	tcs.yScale = dCalScreen / dCalTouch;

	tcs.xOffset = (((float)touch_points[1].x * tcs.xScale - (float)point_Base[1].x)
	             + ((float)touch_points[0].x * tcs.xScale - (float)point_Base[0].x)) / 2.0;

	tcs.yOffset = (((float)touch_points[1].y * tcs.yScale - (float)point_Base[1].y)
	             + ((float)touch_points[0].y * tcs.yScale - (float)point_Base[0].y)) / 2.0;

	/*Draw cross sign for calibration points*/
	Draw_Calibration_Mark(point_Base[4].x, point_Base[4].y);
	res = GetTouch_SC_Sync(&xt, &yt);
	if (xt > (point_Base[4].x + CALIBRATION_RANGE)
	    || xt < (point_Base[4].x - CALIBRATION_RANGE)
	    || yt > (point_Base[4].y + CALIBRATION_RANGE)
	    || yt < (point_Base[4].y - CALIBRATION_RANGE)) {
		return 0;
	} else {
	    return 1;
	}
}

unsigned char  GetTouch_TC_Async(int *xs, int *ys)
{
	int tpx, tpy;
	TS_STATE *pstate = NULL;

    pstate = IOE_TS_GetState();
	if (pstate->TouchDetected) {
	    /*Read AD convert result*/
	    /* no filtering */
	    *xs = IOE_TS_Read_X();
	    *ys = IOE_TS_Read_Y();
	    if ((*xs > TOUCH_AD_VALUE_MAX)
	        || (*xs < TOUCH_AD_VALUE_MIN)
	        || (*ys > TOUCH_AD_VALUE_MAX)
	        || (*ys < TOUCH_AD_VALUE_MIN))
	    	return 0;
	    else
	    	return 1;
    } else
    	return 0;
}

unsigned char  GetTouch_TC_Sync(int *xs, int *ys)
{
	int tpx, tpy;

	TS_STATE *pstate = NULL;
    do {
      pstate = IOE_TS_GetState();
      delay(5);
    } while(!pstate->TouchDetected);

    /*Read AD convert result*/
    /* no filtering */
    *xs = IOE_TS_Read_X();
    *ys = IOE_TS_Read_Y();
    if ((*xs > TOUCH_AD_VALUE_MAX)
        || (*xs < TOUCH_AD_VALUE_MIN)
        || (*ys > TOUCH_AD_VALUE_MAX)
        || (*ys < TOUCH_AD_VALUE_MIN))
    	return 0;
    else
    	return 1;
}


unsigned char  GetTouch_SC_Async(unsigned int *xs, unsigned int *ys)
{
	int tpx, tpy;
	TS_STATE *pstate = NULL;
	char str[30];

	if (GetTouch_TC_Async(&tpx, &tpy)) {
	    *xs = (unsigned int)(tpx * tcs.xScale - tcs.xOffset);
	    *ys = (unsigned int)(tpy * tcs.yScale - tcs.yOffset);
		if ((*xs > xScreenSize)
	        || (*xs < 0)
	        || (*ys > yScreenSize)
	        || (*ys < 0))
	    	return 0;
	    else
	    	return 1;
    } else
    	return 0;
}

unsigned char  GetTouch_SC_Sync(unsigned int *xs, unsigned int *ys)
{
	int tpx, tpy;

	if (GetTouch_TC_Sync(&tpx, &tpy)) {
		*xs = (int)(tpx * tcs.xScale - tcs.xOffset);
		*ys = (int)(tpy * tcs.yScale - tcs.yOffset);
		if ((*xs > xScreenSize) || (*xs < 0)
        || (*ys > yScreenSize) || (*ys < 0))
			return 0;
		else
			return 1;
	} else
		return 0;
}

void InitTouch(float xs, float ys, int16_t xo, int16_t yo)
{
	tcs.xOffset = xo;
	tcs.yOffset = yo;
	tcs.xScale = xs;
	tcs.yScale = ys;
}
