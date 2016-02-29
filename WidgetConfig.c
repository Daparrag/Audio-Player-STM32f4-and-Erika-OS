/*
 * WidgetConfig.c
 *
 *  Created on: 21/ott/2015
 *      Author: admim
 */

#include "WidgetConfig.h"
#include "pictures.h"
#include <stdio.h>
#include "stm32f4_discovery_lcd.h"
#include "fonts.h"

//ButtonIcon buttontime = {
//		icontime_on, icontime_off, TIMEMODE
//};

//ButtonIcon buttontimeset = {
//		icontimeset_on, icontimeset_off, TIMESETMODE
//};

ButtonIcon bagkmode = {
		0, 0, MKMODE
};

ButtonIcon buttonPlay = {
		PlayOn, PlayOff, PLAY
};


ButtonIcon buttonNextSong = {
		0, 0, NEXT
		//icontime_on, icontime_off, SWCHRONOPLAY
};

ButtonIcon buttonBackSong = {
		0, 0, BACK
};

ButtonIcon buttonDisk = {
		DiskOn, DiskOff, DISK
};


ButtonIcon buttonUP = {
		0, 0, UP
};

ButtonIcon buttonDown = {
		0, 0, DOWN
};

ButtonIcon buttonLeft = {
		0, 0, LEFT
};

ButtonIcon buttonRight = {
		0, 0, RIGHT
};


Text txt = {
		&Font16x24, White
};

Image backg = {
		Font1
};


Image Playbackg = {
		ImagePlay
};


const Widget MyWatchScr[NUMWIDGETS] = {
		{0, 0, 320, 240, BACKGROUND, (void *)&backg},
		{268, 160, 20, 15, BUTTONICON, (void *)&buttonUP},
		{268, 210, 20, 15, BUTTONICON, (void *)&buttonDown},
		{250, 190, 20, 15, BUTTONICON, (void *)&buttonLeft},
		{290, 190, 20, 15, BUTTONICON, (void *)&buttonRight}
};

const Widget PlayScr[NUMWIDGETSPLY] = {
		{0, 0, 320, 240, BACKGROUND, (void *)&Playbackg},
		{14, 0, 114, 110, BUTTONICON, (void *)&buttonDisk},
		{139, 132, 68, 42, BUTTONICON, (void *)&buttonPlay},
		{92,128, 40, 40, BUTTONICON, (void *)&buttonBackSong},
		{210,128, 38, 38, BUTTONICON, (void *)&buttonNextSong},
		{22,135, 30, 30, BUTTONICON, (void *)&bagkmode}
		//{10, 130,50, 50, BUTTONICON, (void *)&buttonplus},
		//{63, 126, 50, 50, BUTTONICON, (void *)&buttonminus},
		//{250, 25, 50, 50, BUTTONICON, (void *)&buttonleft},
		//{250, 90, 50, 50, BUTTONICON, (void *)&buttonrigth},
//		Controls Chrono


		//{200, 126, 54, 55, BUTTONICON, (void *)&buttonChronoPlay},
		//{142, 125, 58, 45, BUTTONICON, (void *)&buttonChronoPauseplay},
		//{202, 120, 58, 53, BUTTONICON, (void *)&buttonChronoStop},

//		{26, 76, 100, 32, RECTANGLE, (void *)&rectangle}
		//{29, 70, 40, 40, TEXT, (void *)&txt},
		//{99, 70, 40, 40, TEXT, (void *)&txt},
		//{168, 70, 40, 40, TEXT, (void *)&txt},
		//{243, 70, 40, 40, TEXT, (void *)&txt},
		//{80, 70, 40, 40, TEXT, (void *)&txt},
		//{149, 70, 40, 40, TEXT, (void *)&txt},
};



