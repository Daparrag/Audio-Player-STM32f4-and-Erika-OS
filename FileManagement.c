#include "FileManagement.h"
//#include "rtwtypes.h"


void SetUpCurrentHeadTail(struct headdef* new_head,struct  taildef * new_tail){
	Chead=new_head;
	Ctail=new_tail;
}

void CreateListHeadTail(char _index,struct headdef *_head,struct taildef *_tail){
	struct HeadTail_List * new_listHead= (struct HeadTail_List*)malloc(sizeof(struct HeadTail_List));
	new_listHead->indexheadTail=_index;
	new_listHead->PHead=_head;
	new_listHead->PTail=_tail;
	ListHeadTail=new_listHead;
	CList=ListHeadTail;

}

void AddListHeadTail(char _index,struct headdef *_head,struct taildef *_tail){

	if (ListHeadTail==NULL)
	{
		CreateListHeadTail(_index,_head,_tail);
	}else
	{
		struct HeadTail_List * new_listHead= (struct HeadTail_List*)malloc(sizeof(struct HeadTail_List));
		new_listHead->PHead=_head;
		new_listHead->PTail=_tail;
		ListHeadTail->NextHeadTail=new_listHead;
		CList=new_listHead;
	}


}

struct Listdef * create_list(char Index, char isdir,char IndexHT,FILINFO *infofile){

	struct headdef *nhead = (struct headdef*)malloc(sizeof(struct headdef));
	struct taildef *ntail = (struct taildef*)malloc(sizeof(struct taildef));
	struct Listdef *ptr = (struct Listdef*)malloc(sizeof(struct Listdef));
	ptr->index=Index;
	ptr->isfile=isdir;
	memcpy(ptr->fname, infofile->fname, sizeof infofile->fname);
	f_getcwd(&(*(ptr)->buff),sizeof ptr->buff);
	//ptr->fname=infofile->fname;
	//ptr->Filedata=fno;
	//ptr->InfoDIR=dir;
	//ptr->infofile=fileinfo;
	ptr->SubFolder=NULL;
	ptr->nextElement=NULL;
	AddListHeadTail(IndexHT,nhead,ntail);
	nhead->ValueHead=ptr;
	nhead->indexhead=0;
	ntail->Valuetail=ptr;
	SetUpCurrentHeadTail(nhead,ntail);
	//ListHeadTail->sizeList=Index;
	return ptr;
}

void DeleteList(){
	struct taildef *temtail = (struct taildef*)malloc(sizeof(struct taildef));
	do{


				temtail->indextail=(Ctail->indextail)-1;
				temtail->Valuetail=Ctail->Valuetail->prevElement;

				LCD_DisplayStringXY(0, 0,"Asigned");
				LCD_DisplayStringXY(0,10,temtail->Valuetail->fname);
				DelaySD();
				LCD_ClearLine(LINE(1));
				free(Ctail->Valuetail);
				Ctail->indextail=temtail->indextail;
				Ctail->Valuetail=temtail->Valuetail;;


				//LCD_ClearLineWhitoutFont(LINE(5));
	}while(temtail->indextail>Chead->indexhead);
	free(temtail);
	free(Chead);
	free(Ctail);
}

struct Listdef * create_Slist(char Index, char isdir,char IndexHT){//,DIR dir,FIL fno, FILINFO fileinfo

	struct headdef *nhead = (struct headdef*)malloc(sizeof(struct headdef));
	struct taildef *ntail = (struct taildef*)malloc(sizeof(struct taildef));
	struct Listdef *ptr = (struct Listdef*)malloc(sizeof(struct Listdef));
	ptr->index=Index;
	ptr->isfile=isdir;
	//ptr->Filedata=fno;
	//ptr->InfoDIR=dir;
	//ptr->infofile=fileinfo;
	//ptr->SubFolder=NULL;
	//ptr->nextElement=NULL;
	AddListHeadTail(IndexHT,nhead,ntail);
	nhead->ValueHead=ptr;
	ntail->Valuetail=ptr;
	//SetUpCurrentHeadTail(nhead,ntail);
	return ptr;
}


void add_to_list (List * _list,uint8_T Index, char isdir, char add_to_end,char IndexTailHeadList,FILINFO *infofile)
{
	struct Listdef * newptr;
	//headdef *Newhead;
	//taildef *Newtail;


	if(Chead==NULL)
    {
    newptr  = create_list(Index,isdir,IndexTailHeadList,infofile);
    f_getcwd(&(*(newptr)->buff),sizeof newptr->buff);
    }

	else {

    		newptr  = (struct Listdef*)malloc(sizeof(struct Listdef));
    		newptr->index=Index;
    		newptr->isfile=isdir;
    		memcpy(newptr->fname, infofile->fname, sizeof infofile->fname);
    		//newptr->Filedata=fileinfo;
    		//newptr->InfoDIR=dir;
    		//newptr->infofile=fno;
    		newptr->SubFolder=NULL;
    		newptr->nextElement=NULL;
    		newptr->prevElement=Ctail->Valuetail;
    		f_getcwd(&(*(newptr)->buff),sizeof newptr->buff);

		}


		if(add_to_end)
		{
			Ctail->Valuetail->nextElement=newptr;
			Ctail->Valuetail=newptr;
			Ctail->next_tail=NULL;
			Ctail->indextail=Index;
			//ListHeadTail->sizeList=Index;
		}
		else
		{
			//Chead=NULL;
			newptr->nextElement=_list;
			Chead->ValueHead=newptr;
			_list=newptr;
		}

}

struct Listdef * search_in_list(char Index)
{
	//char MySearch[13];
	struct Listdef *ptr = Chead->ValueHead;
	struct Listdef *tempPrt=NULL;
	//LCD_DisplayStringLine(LINE(9),"Start Search..");
	while(ptr != NULL){
		if ((ptr->index) == Index){
		//	sprintf(MySearch,"search done by %d", ptr->index);
		//	LCD_DisplayStringLine(LINE(10),&MySearch);
			DelaySD();
		//	LCD_ClearLine(LINE(10));
			return ptr;
		}
		else{
			tempPrt=ptr;
			ptr=ptr->nextElement;
		//	sprintf(MySearch,"searching by %d", Index);
		//	LCD_DisplayStringLine(LINE(10),&MySearch);
		}

	}
	//LCD_DisplayStringLine(LINE(10),"Search Fault !!");
	return NULL;

}



void  Create_Sublist(List * _list,char IndexHT){
		//is necesary add the index for search the current open folder
	List * newList = create_Slist(0,0,IndexHT);
	search_in_list(IndexHT)->SubFolder=newList;
	Ctail->Valuetail->SubFolder=newList;
	SetUpCurrentHeadTail(CList->PHead,CList->PTail);


}

char  PrintFolder(List * _list,char maxIndex){
	TCHAR Indextotest[13];
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	LCD_SetFont(&Font8x12);

	char i;
	if (maxIndex<=17){
		for(i=0;i<=maxIndex;i++){
			List * Element = search_in_list(i);
				if(Element->isfile==1){
						strcpy(Indextotest,"<Dir>  ");
						strcat(Indextotest,Element->fname);
						//strcat(Indextotest,"  ");
						//strcat(Indextotest,Element->buff);
						LCD_DisplayStringLine(LINE(2+i),Indextotest);

							}else{
								strcpy(Indextotest,"<File> ");
								strcat(Indextotest,Element->fname);
								//strcat(Indextotest,"  ");
								//strcat(Indextotest,Element->buff);
								LCD_DisplayStringLine(LINE(2+i),Indextotest);
							}

		}
	return 0;
	}else{
		for (i=0; i<17;i++){
			List * Element = search_in_list(i);
							if(Element->isfile==1){
										strcpy(Indextotest,"<Dir>  ");
										strcat(Indextotest,Element->fname);
										//strcat(Indextotest,"  ");
										//strcat(Indextotest,Element->buff);
										LCD_DisplayStringLine(LINE(2+i),Indextotest);

									}else{
											strcpy(Indextotest,"<File> ");
											strcat(Indextotest,Element->fname);
											//strcat(Indextotest,"  ");
											//strcat(Indextotest,Element->buff);
											LCD_DisplayStringLine(LINE(2+i),Indextotest);
									}
		}
		LCD_DisplayStringLine(LINE(19), "* * * @more");

	}
	return i;
}

void MarkFolder(List * _list, char i){
	TCHAR Indextotest[13];
	LCD_SetTextColor(Blue);

	List * Element = search_in_list(i%17);
					if(Element->isfile==1){
							strcpy(Indextotest,"<Dir>  ");
							strcat(Indextotest,Element->fname);
							//strcat(Indextotest,"  ");
							//strcat(Indextotest,Element->buff);
							LCD_DisplayStringLine(LINE(2+(i%17)),Indextotest);

								}else{
									strcpy(Indextotest,"<File> ");
									strcat(Indextotest,Element->fname);
									//strcat(Indextotest,"  ");
									//strcat(Indextotest,Element->buff);
									LCD_DisplayStringLine(LINE(2+(i%17)),Indextotest);
								}
					LCD_SetTextColor(White);

}


void UnMarkFolder(List * _list, char i){
	TCHAR Indextotest[13];
	LCD_SetTextColor(White);

	List * Element = search_in_list(i%17);
					if(Element->isfile==1){
							strcpy(Indextotest,"<Dir>  ");
							strcat(Indextotest,Element->fname);
							//strcat(Indextotest,"  ");
							//strcat(Indextotest,Element->buff);
							LCD_DisplayStringLine(LINE(2+(i%17)),Indextotest);

								}else{
									strcpy(Indextotest,"<File> ");
									strcat(Indextotest,Element->fname);
									//strcat(Indextotest,"  ");
									//strcat(Indextotest,Element->buff);
									LCD_DisplayStringLine(LINE(2+(i%17)),Indextotest);
								}

}



