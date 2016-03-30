#ifndef __SD_CARDCONTROLER_H
#define __SD_CARDCONTROLER_H

#include "ee.h"
#include "ee_irq.h"
#include <stdio.h>
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery_sdio_sd.h"
#include "stm32f4_discovery_lcd.h"
#include "ff.h"



//#define NULL 0



/* extern variables ---------------------------------------------------------*/
//SD_Error Status = SD_OK;
///extern FATFS filesystem;		/* volume lable */
//extern FRESULT ret;			  /* Result code */
//extern FIL file;				    /* File object */
//extern DIR dir;				    /* Directory object */
//extern FILINFO fno;			  /* File information object */
//extern UINT bw, br;
//const TCHAR* path;

//uint8_t buff[128];
//uint8_t test_ok = 0;
//struct List * Mylist;
//extern EmptyFolder;



//extern mylist;
void mount_SDCard();//Important
TCHAR * GetPath();//Important
static void fault_err (FRESULT rc);
void *  OpenFolder(const TCHAR* _path);
void  ListFolderSDCard(void * _Folder);
FRESULT  ListSDCardCont (void * _Folder,const TCHAR* _path);
void * SDCardNextFolder(const TCHAR * _path);
char FolderEmpty();
void * SDCardBackFolder();
void * SDCardBackFolderEmpty();
void OpenFile(TCHAR * Filename);
void ReadFile(uint16_t * buff1,uint16_t * buff2, UINT * BytesRead, DWORD  _WaveCounter, char op);
//void PrintFolder();

#endif
