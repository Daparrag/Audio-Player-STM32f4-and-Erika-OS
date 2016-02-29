/*
 * This File Include All the functions Necessaries for management the SDCard
 *
 * */
#include "SD_CardController.h"
#include<stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "ff.h"

/*PRIVATE VARIABLES----------------------------------------------------------- */
SD_Error Status = SD_OK;
FATFS filesystem;		/* volume lable */
FRESULT ret;			  /* Result code */
FIL file;				    /* File object */
DIR dir;				    /* Directory object */
FILINFO fno;			  /* File information object */
UINT bw, br;
const TCHAR* path;
//uint16_t buffer1[512];
//uint16_t buffer2[512];
uint16_t buffer[512];
//uint8_t test_ok = 0;
struct List * Mylist;
//extern EmptyFolder;
//extern Operator op;

//,uint16_t * buffer1,uint16_t * buffer2,UINT * BytesRead,

uint8_T graphloop=1;
TCHAR Cpath[13];
TCHAR Back[13]="..";
char EmptyFolder;

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief   FatFs err dispose
 * @param  None
 * @retval None

*/



void DelaySD (){
	 int c = 1, d = 1;

	   for ( c = 1 ; c <= 5000 ; c++ )
	       for ( d = 1 ; d <= 1000 ; d++ )
	       {}

}

void ReadingLoop(){

	while(graphloop<=6){
			LCD_DisplayStringXY(0, 0,"           reading*");
			DelaySD();
			LCD_ClearLine(LINE(0));
			LCD_DisplayStringXY(0, 0,"           reading *");
			DelaySD();
			LCD_ClearLine(LINE(0));
			LCD_DisplayStringXY(0, 0,"           reading  *");
			//LCD_DisplayStringLine(LINE(9),"           reading  *");
			DelaySD();
			LCD_ClearLine(LINE(0));
			LCD_DisplayStringXY(0, 0,"           reading   *");
			//LCD_DisplayStringLine(LINE(9),"           reading   *");
			//LCD_DisplayStringLine(LINE(10), &graphloop);
			graphloop++;
			DelaySD();
			LCD_ClearLine(LINE(0));

			}
}



TCHAR * GetPath(){
	//LCD_DisplayStringXY(0, 0,Cpath);
	return Cpath;

}

char FolderEmpty(){
	return EmptyFolder;
}

static void fault_err (FRESULT rc)
{
	const char *str =
			"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
			"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
			"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
			"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0";
	FRESULT i;

	for (i = (FRESULT)0; i != rc && *str; i++) {
		while (*str++) ;
	}
	STM_EVAL_LEDOn(LED6);
	while(1);
}

void mount_SDCard(){
	if (f_mount(&filesystem, "", 0) != FR_OK) {
			LCD_DisplayStringLine(LINE(9),"could not open the file system");
		}
}

void *  OpenFolder(const TCHAR* _path){

	ret = f_opendir(&dir,_path);
		if (ret!=FR_OK) {
			LCD_SetTextColor(Black);
			LCD_DisplayStringLine(LINE(9),"Open directory error");
			LCD_SetTextColor(White);
			return 0;
		}		ReadingLoop();
		f_chdir(_path);
		f_getcwd ((Cpath),sizeof(Cpath));
				return (void*)create_list (0, 1,0, &fno);
}



void  ListFolderSDCard(void * _Folder){
//	ListFolderSDCardID (void * _Folder,const TCHAR* _path);

	uint8_T list=1;
	EmptyFolder=1;
		do{
		ret = f_readdir(&dir, &fno) ;
		if (ret != FR_OK  || fno.fname[0]==0){
			if(list>1){
				EmptyFolder=0;
			}

			break;// Error or end of dir //
		}
		if(fno.fname[0]=='.')continue;
		if(fno.fattrib & AM_DIR) add_to_list(_Folder,list,1,1,0,&fno); //List * _list,uint8_T Index, char isdir, char add_to_end,char IndexTailHeadList
		else  add_to_list(_Folder,list,0,1,0,&fno);
		LCD_DisplayStringXY(0, 0,fno.fname);
		DelaySD();
		LCD_ClearLine(LINE(0));
		list=list+1;


		}while(ret==FR_OK);

}


void * SDCardNextFolder(const TCHAR * _path){
	DeleteList();
	return (void*) OpenFolder(_path);
}


void * SDCardBackFolder(){
	DeleteList();
	return (void*) OpenFolder("..");
}

void * SDCardBackFolderEmpty(){
	//DeleteList();
	return (void*) OpenFolder("..");
}

FRESULT  ListSDCardCont (void * _Folder,const TCHAR* _path){
		int i;
		char *fn;

		ret=f_opendir(&dir,_path);
			if(ret==FR_OK){
				ReadingLoop();
				 //_Folder=create_list (0, 1,0, &fno);
				i=0;
					for(;;){
						ret=f_readdir(&dir,&fno);
						if(ret != FR_OK || fno.fname[0] == 0) break;
						if(fno.fname[0]=='.')continue;
						//fn = fno.fname;
						if(fno.fattrib & AM_DIR){
							add_to_list(_Folder,i,1,1,0,&fno);
							ret=ListSDCardCont(_Folder,_path);
							i++;

						}else{

							add_to_list(_Folder,i,0,1,0,&fno);
							i++;
						}
					}
			}

			return ret;
};



void OpenFile(TCHAR * Filename){
	//ret = f_opendir(&dir,"/");
	f_close(&file);
	ret = f_open(&file,Filename,FA_READ | FA_WRITE);
		if(ret!=FR_OK){
			LCD_ClearLine(LINE(17));
			LCD_DisplayStringLine(LINE(17),"Open file error");
			}else{
				LCD_ClearLine(LINE(17));
				LCD_DisplayStringLine(LINE(17),"Open file Ok");
			}
}
void ReadFile(uint16_t * buff1,uint16_t * buff2,UINT * BytesRead,DWORD  _WaveCounter,char op){
	ret=f_sync (&file);
	if(op==0){
		ret=f_read (&file, buff1,_MAX_SS, BytesRead);
	}
	else if(op==1){

		ret=f_lseek(&file,_WaveCounter);
		ret=f_read (&file, buff1,_MAX_SS, BytesRead);
		ret=f_read (&file, buff2, _MAX_SS, BytesRead);

	}
			if(ret!=FR_OK){
				LCD_ClearLine(LINE(17));
				LCD_DisplayStringLine(LINE(17),"Error Reading The File");
			}else {
				f_sync (&file);
				LCD_ClearLine(LINE(17));
				LCD_DisplayStringLine(LINE(17),"Reading File Ok");
			}


}



FIL * OpenWavFile(TCHAR * Filename,uint16_t * buffer1,uint16_t * buffer2,UINT * BytesRead){
	FIL * PontertoFile;

	ret = f_open(&file, Filename, FA_READ);

					if(ret!=FR_OK){
						LCD_DisplayStringLine(LINE(17),"Open file error");
						return 0;
					}else{
						//f_lseek(&file, WaveCounter);

						ret = f_read(&file, buffer1,_MAX_SS , BytesRead);	/* Read a chunk of file */
						ret = f_read(&file, buffer2,_MAX_SS , BytesRead);	/* Read a chunk of file */
							if (ret || BytesRead) {
										LCD_ClearLine(LINE(17));
										LCD_DisplayStringLine(LINE(17),"Open file error");
									}else{
										LCD_DisplayStringLine(LINE(17),"Open file Ok");
										LCD_ClearLine(LINE(18));
										LCD_DisplayStringLine(LINE(18),"Ending OpenFile...");

									}

						}
					PontertoFile=&file;
					return PontertoFile;
}



