/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2015  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

#include "ee.h"
#include "ee_irq.h"
#include <stdio.h>
#include "stm32f4xx_conf.h"
//#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_sdio_sd.h"
#include "ff.h"
//#include "stm32f4xx_conf.h"
//#include "stm32f4_discovery_lcd.c"
//#include "stm32f4xx.h"
//#include "AudioLibConfig.h"
#include "Touch.h"
#include "lcd_add.h"
#include "fonts.h"
#include "FileManagement.h"
#include "FSMAudioPlayer.h"
#include "SD_CardController.h"
#include <string.h>

#include "STMPE811QTR.h"
#include "pictures.h"
#include "Widget.h"
#include "WidgetConfig.h"
#include "Touch.h"
#include "Event.h"
#include "lcd_add.h"
#include "fonts.h"
//#include "stm32f4_discovery_audio_codec.h"



List * Folder;
TCHAR Indextotest[13]; //to delate
TCHAR Indextotest1[13];
FSM MyFSM;
FSM AudioPlayer;
int imageCounter=0;
char SW=0;
/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* counconsole_init()t the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/**
 * @brief  This function handles SDIO global interrupt request.
 * @param  None
 * @retval None
 */
ISR1(SDIO_IRQHandler) {
	/* Process All SDIO Interrupt Sources */
	SD_ProcessIRQSrc();
}

/**
 * @brief  This function handles DMA2 Stream3 or DMA2 Stream6 global interrupts
 *         requests.
 * @param  None
 * @retval None
 */
ISR1(SD_SDIO_DMA_IRQHANDLER) {
	/* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
	SD_ProcessDMAIRQ();
}
/* Private function prototypes -----------------------------------------------*/
/**
 * @brief   FatFs err dispose
 * @param  None
 * @retval None
*/
char SetupImagePlay(){

	if(imageCounter<=50){
		imageCounter++;
	}
	else{
		imageCounter=0;
		return 1;
	}
	return 0;



}

//ISR1(DAC_DMA_IRQHandler) {
///* Process DMA1 Stream5 Interrupt Sources */
//	void DMA1_Channel5_IRQHandler();
//
//}

void StartSDCard(){
		DrawInit(MyWatchScr);
		LCD_SetBackColor(Black);
		LCD_SetTextColor(White);
		LCD_SetFont(&Font8x12);
		mount_SDCard();
		Folder =(List*) OpenFolder("/");//Set up the list
		ListFolderSDCard(Folder);//
		char CurrentIndex=PrintFolder(Folder,Ctail->indextail);
		MarkFolder(Folder, 0);
		//Folder =(List*) SDCardNextFolder ("/Floder10");
		//DrawInit(MyWatchScr);
		FolderFSMInit(&MyFSM, FOLDERMODE_TOP);
		//OpenWavFile("Hola");

}
TASK(TaskLCD)
{
	unsigned int px, py;
	TPoint p;
	if (GetTouch_SC_Async(&px, &py)) {
		p.x = px;
		p.y = py;
		OnTouch(MyWatchScr, &p);
	}
}

TASK(TaskPlayBack)
{
	CancelAlarm(AlarmTaskLCD);
	CancelAlarm(AlarmTaskTest);
	while(1){
		  			     volatile ITStatus it_st;
		  			  	 it_st = RESET;
		  			  	//SetupImagePlay();
		  			  	 while(it_st != SET) {
		  			  	 it_st = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_HTIF5);
		  			  	 }
		  			  	 f_read (&fileR,&BufferDMA[0],256,&BytesRead);
		  			  	 DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_HTIF5);
		  			       if(BytesRead<256)break;//break;}
		  			     if(SetupImagePlay()){
		  			    	 if (SW){
		  			    		DrawOn(&PlayScr[BDISK]);
		  			    	 	 SW=!SW;
		  			    	 }else{
		  			    		DrawOff(&PlayScr[BDISK]);
		  			    		SW=!SW;
		  			    	 }

		  			     }

		  			       it_st = RESET;
		  			       while(it_st != SET) {
		  			       it_st = DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5);
		  			       }
		  			       f_read (&fileR,&BufferDMA[256],256,&BytesRead);
		  			       DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);
		  			       if(BytesRead<256)break;
		  		}
	AudioPlayStart=0;
	TIM_Cmd(TIM6, DISABLE);
	f_close(&fileR);
	StartSDCard();
	SetRelAlarm(AlarmTaskLCD, 10, 50);
	SetRelAlarm(AlarmTaskTest, 1, 10);
}


TASK(TaskTestOk)
{
	//CancelTask(TaskPlayBack);
	if (IsEvent(UP)||IsEvent(DOWN)||IsEvent(LEFT)||IsEvent(RIGHT)){
		STM_EVAL_LEDOn(LED4);
		FSMFolder(&MyFSM,&AudioPlayer, Folder, Ctail->indextail);
				//SWatchFSMDispatch(&MyFSM,&MyWatchScr,&mywatch);
				ClearEvents();
			}
	//ActivateTask(TaskPlayBack);
	STM_EVAL_LEDOff(LED4);
	if(AudioPlayStart==1){
		ActivateTask(TaskPlayBack);
	}

}




int main(void)
{


	//GPIO_InitTypeDef GPIO_InitStructure;

	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */

	SystemInit();

	/*Initialize Erika related stuffs*/
	EE_system_init();



	/*Initialize systick */

	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();
	//RCC_GetClocksFreq(&RCC_Clocks);
	//SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);


	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED6);
	STM_EVAL_LEDOn(LED4);





	/* Initializes LCD and touchscreen */
		IOE_Config();
		/* Initialize the LCD */
		STM32f4_Discovery_LCD_Init();
	//	Lcd_Touch_Calibration();
		InitTouch(-0.102, 0.0656, -335, 10);
		//Initialize uart.

		//uart_init();//Not necessary ?
		//Start Program :)
	StartSDCard();
	//EVAL_AUDIO_SetAudioInterface(AUDIO_INTERFACE_I2S);
	SetRelAlarm(AlarmTaskLCD, 10, 50);
	//ActivateTask(TaskTestOk);
	SetRelAlarm(AlarmTaskTest, 1, 10);
	//SetRelAlarm(AlarmTaskTestOk, 10, 100);

	//EVAL_AUDIO_SetAudioInterface(AUDIO_INTERFACE_I2S);
	//EVAL_AUDIO_Init(OUTPUT_DEVICE_HEADPHONE, 100, 48000 );

	/* Forever loop: background activities (if any) should go here */
	for (;;) {
		}
}
