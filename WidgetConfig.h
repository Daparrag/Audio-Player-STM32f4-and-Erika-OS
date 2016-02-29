/*
 * WidgetConfig.h
 *
 *  Created on: 22/ott/2015
 *      Author: admim
 */
#include "Widget.h"

#ifndef WIDGETCONFIG_H_
#define WIDGETCONFIG_H_

#define NUMWIDGETS 5
#define NUMWIDGETSPLY 6


#define BAKCG 0
#define BPLAY 2
#define BDISK 1

//#define SELECTMODE 0x08

#define UP 0x01
#define DOWN 0x02
#define LEFT 0x04
#define RIGHT 0x08
#define BACK 0x10
#define NEXT 0x20
#define PLAY 0x40
#define MKMODE 0x80
#define DISK 0x100

//#define UP 0x010
//#define MINUS 0X200//0x020
//#define WLEFT 0X400//0x040
//#define WRIGTH 0x080
//#define SWCHRONOPAUSEPLAY 0x020
//#define SWCHRONOPAUSE 0X400
//#define SWCHRONOSTOP 0x040


extern const Widget MyWatchScr[NUMWIDGETS];
extern const Widget PlayScr[NUMWIDGETSPLY];

#endif /* WIDGETCONFIG_H_ */
