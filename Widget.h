/*!	\file	Button.h
 	\author Daniel Casini
 	\date	10/03/2014
	\brief	Button handling file for the watch
*/

#ifndef WIDGET_H_
#define WIDGET_H_

#include "Event.h"
#include "Touch.h"
#include "fonts.h"

//#include "WigetsView.h"


typedef enum  {
	BACKGROUND, BUTTONICON, TEXT, IMAGE
} WidgetType;

typedef struct {
	unsigned char *image;
} Image;

typedef struct {
	unsigned char *iconp;
	unsigned char *iconr;
	Event		  onpress;
} ButtonIcon;

typedef struct {
	sFONT *font;
	unsigned short int	color;
} Text;

typedef struct {
	unsigned short int xl;
	unsigned short int yt;
	unsigned short int xw;
	unsigned short int yh;
	WidgetType wt;
	void     *ws;
} Widget;

#define txtinfo(w) ((Text *)((w)->ws))
#define biconinfo(w) ((ButtonIcon *)((w)->ws))
#define imginfo(w) ((Image *)((w)->ws))

unsigned char OnTouch(const Widget ws[], TPoint *press);
unsigned char DrawInit(const Widget ws[]);
unsigned char DrawInitWGdef(const Widget ws[],char Numwg);
unsigned char DrawOn(Widget *w);
unsigned char DrawOff(Widget *w);
unsigned char DrawDelete(Widget *w);
unsigned char WPrint(Widget *w, char *s);

#endif /* BUTTON_H_ */
