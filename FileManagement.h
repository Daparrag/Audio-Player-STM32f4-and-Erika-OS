#ifndef __SD_CARDCONTROL_H
#define __SD_CARDCONTROL_H

//#define NULL 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4_discovery_sdio_sd.h"
#include "stm32f4_discovery_lcd.h"
#include "ff.h"
#include "rtwtypes.h"
#include "ff.h"


typedef struct Listdef List;//define a likedlist for alocate the folder infromation an access to it
typedef struct headdef head;//define a likedlist for alocate the folder infromation an access to it
typedef struct taildef tail;//define a likedlist for alocate the folder infromation an access to it
typedef struct HeadTail_List HTList;

struct Listdef{

	char index; //ID
	char isfile;//indicate if the element is a file or directory
	//DIR InfoDIR; const TCHAR*	pat
	//FIL Filedata;BYTE*	dir_ptr;
	TCHAR	fname[13];//FILINFO infofile;//file or folder name
	//f_getcwd (
	 TCHAR buff[13]; /* [OUT] Buffer to return path name */
	  //UINT len     /* [IN] The length of the buffer */
	//);

	List * SubFolder;//not used
	List * nextElement;//next element of the list
	List * prevElement;//-last element of the list
};


struct headdef{
	char indexhead;
	struct Listdef * ValueHead;
	head * next_head;
};


struct taildef{
	char indextail;
	struct Listdef * Valuetail;
	tail * next_tail;
};

struct HeadTail_List{
	char  indexheadTail;
	char sizeList;
	struct headdef * PHead;
	struct taildef * PTail;
	HTList * NextHeadTail;
};

struct headdef *Chead;
struct taildef *Ctail;
struct HeadTail_List * ListHeadTail;
struct HeadTail_List * CList;






void Create_Sublist(List * _list,char IndexHT);
struct Listdef * search_in_list(char Index);//Important
void add_to_list (List * _list,uint8_T Index, char isdir, char add_to_end,char IndexTailHeadList,FILINFO *infofile);//Important
struct Listdef * create_Slist(char Index, char isdir,char IndexHT);//a modificar.
struct Listdef * create_list(char Index, char isdir,char IndexHT,FILINFO *infofile);
void AddListHeadTail(char _index,struct headdef *_head,struct taildef *_tail);
void CreateListHeadTail(char _index,struct headdef *_head,struct taildef *_tail);
void SetUpCurrentHeadTail(struct headdef* new_head,struct taildef * new_tail);
char  PrintFolder(List * _list,char maxIndex);
//                          void  ListFolderSDCard(List * _Folder);//Important
void MarkFolder(List * _list, char i);//Important
void UnMarkFolder(List * _list, char i);//Important
#endif
