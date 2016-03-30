#include "FSMAudioPlayer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char Index;
TCHAR Root[13]="/";
TCHAR FolderPath[13];
TCHAR  CurrentPath[13];

#define MinIndex 0
//FSM.Folder_Index declaration
Signal DecodeEvents(FSM * _FSM)
{
	if(IsEvent(UP))	   return UPSIG;
	if(IsEvent(DOWN))  return DOWNSIG;
	if(IsEvent(LEFT))  return LEFTSIG;
	if(IsEvent(RIGHT)) return RIGHTSIG;
	return NOEVENT;
}

void PlayerFSMInit(FSM * _PlayerFSM, State _initialState)
{
	/*
	 * Here for Start the FSM of AudioPlayer
	 * */
	DrawInitWGdef(PlayScr,6);
	//DrawInitWGdef(PlayScr);
	_PlayerFSM->curState=_initialState;
}

void FolderFSMInit(FSM * FolderFSM, State _initialState)
{
	(*FolderFSM).curState=_initialState;
	Index=0;
//	(*ClockFSM).curState = _initialState;
//	(*ClockFSM).PAlarm=1;
//	(*ClockFSM).AlarmSetup=0;
//	(*ClockFSM).ChronoStart=0;
//	((*ClockFSM).Setwatch) = &StartSetScreen;
//	((*ClockFSM).Stopwatch) = &StartChronoscreen;
//	((*ClockFSM).Setalarmwatch) = &StartAlarmScreen;
}
//static_cast<new_type>(expression)
char IsRoot(TCHAR (* _Path)[]){
	int i;
	for (i = 0;i<= 13; i++){
		if((*_Path)[i]!=Root[i]){
			return 0;
		}
	}
	return 1;
}



void FSMTran(FSM * _FSM, State nextstate)
{
	(*_FSM).curState = nextstate;
}

void FSMSubTran(FSM * _FSM, State Sstate)
{
	(*_FSM).SubState = Sstate;
}

void FSMFolder(FSM * _folderState,FSM * _PlayerFSM ,List * _list, char Maxindex){

	switch(_folderState->curState){
		case FOLDERMODE_TOP:
			switch (DecodeEvents(_folderState)){
				case DOWNSIG:
					Index++;
					MarkFolder(_list, Index);
					UnMarkFolder(_list, Index-1);
					if(Index < Maxindex)_folderState->curState=FOLDERMODE_NEXT;
					else _folderState->curState=FOLDERMODE_LAST;

					break;

					case LEFTSIG:
									/*
									 * Here code for for go-back within folders
									 *
									 * */
									strcpy(CurrentPath,(TCHAR *) GetPath());
									if(!IsRoot(&CurrentPath)){
										if(!FolderEmpty()) _list=(List*)SDCardBackFolder();
										else _list=(List*)SDCardBackFolderEmpty();
										DrawInit(MyWatchScr);
										ListFolderSDCard(_list);
										PrintFolder(_list,Ctail->indextail);
										MarkFolder(_list, 0);
										Index=0;
										LCD_DisplayStringXY(0,0,(TCHAR *)GetPath());
										_folderState->curState=FOLDERMODE_TOP;
									}


				break;

			default:
				_folderState->curState=FOLDERMODE_TOP;
			}
		break;
		case FOLDERMODE_NEXT:
			switch (DecodeEvents(_folderState)){
				case DOWNSIG:
					Index++;
					MarkFolder(_list, Index);
					UnMarkFolder(_list, Index-1);
					if(Index < Maxindex)_folderState->curState=FOLDERMODE_NEXT;
					else _folderState->curState=FOLDERMODE_LAST;
				break;
				case UPSIG:
					Index--;
					MarkFolder(_list, Index);
					UnMarkFolder(_list, Index+1);
					if(Index > MinIndex)_folderState->curState=FOLDERMODE_NEXT;
					else _folderState->curState=FOLDERMODE_TOP;
				break;
				case RIGHTSIG:
					if(Index>0 ){
						List * Element = search_in_list(Index);
							if(Element->isfile==1){
									strcpy(CurrentPath, (TCHAR *)GetPath());
									//LCD_DisplayStringXY(0,10,);
									if(IsRoot(&CurrentPath)){//Evaluate if the current path is a root
										strcat(CurrentPath,Element->fname); //concatenate The path with the new element
										_list =(List*) SDCardNextFolder (CurrentPath);
										DrawInit(MyWatchScr);
										ListFolderSDCard(_list);
										if(!FolderEmpty()){
										PrintFolder(_list,Ctail->indextail);
										MarkFolder(_list, 0);
										}
										else LCD_DisplayStringXY(0,10,"Folder Empty");
										Index=0;
										LCD_DisplayStringXY(0,0,(TCHAR*)GetPath());

									}else {
										//Concatenate the current path with the new folder to open
										strcpy(FolderPath,"/");
										strcat(FolderPath,Element->fname);
										strcat(CurrentPath,FolderPath);
										//LCD_DisplayStringXY(0,0,CurrentPath);
										//LCD_DisplayStringXY(0,10,CurrentPath);
										_list =(List*) SDCardNextFolder (CurrentPath);
										DrawInit(MyWatchScr);
										ListFolderSDCard(_list);
										if(!FolderEmpty()){
										PrintFolder(_list,Ctail->indextail);
										MarkFolder(_list, 0);
										}
										else LCD_DisplayStringXY(0,10,"Folder Empty");
										Index=0;
										LCD_DisplayStringXY(0,0,(TCHAR*)GetPath());
									}
							_folderState->curState=FOLDERMODE_TOP;
							}else{
								/*
								 * Here for call the methods that evaluate if the file is mp3 then reproduce
								 * */
								PlayerFSMInit(_PlayerFSM,PLAYMODE);
						    	_folderState->curState=PLAYSTARMODE;
						    	WavePlayInit(Element->fname);
						    	//FIL *file =(FIL *) OpenWavFile(Element->fname);
						    	//LCD_DisplayStringLine(LINE(19),(TCHAR*)file->fsize);
						    	//WavePlayStart(I2S_AudioFreq_48k,Element->fname);
								//StartPLayer(I2S_AudioFreq_48k,Element->fname);
							}


					}
				break;
				case LEFTSIG:
					/*
					 * Here code for for go-back within folders
					 *
					 * */
					strcpy(CurrentPath,(TCHAR*) GetPath());
					if(!IsRoot(&CurrentPath)){
						_list=(List*)SDCardBackFolder();
						DrawInit(MyWatchScr);
						ListFolderSDCard(_list);
						PrintFolder(_list,Ctail->indextail);
						MarkFolder(_list, 0);
						Index=0;
						LCD_DisplayStringXY(0,0,(TCHAR*)GetPath());
						_folderState->curState=FOLDERMODE_TOP;
					}


				break;

				default:
					_folderState->curState=FOLDERMODE_NEXT;
			}
		break;
		case FOLDERMODE_LAST:
			switch (DecodeEvents(_folderState)){
			case UPSIG:
				Index--;
				MarkFolder(_list, Index);
				UnMarkFolder(_list, Index+1);
				if(Index > MinIndex)_folderState->curState=FOLDERMODE_NEXT;
				else _folderState->curState=FOLDERMODE_TOP;
			break;
			case RIGHTSIG:
								if(Index>0 ){
									List * Element = search_in_list(Index);
										if(Element->isfile==1){
												strcpy(CurrentPath,(TCHAR *) GetPath());
												//LCD_DisplayStringXY(0,10,);
												if(IsRoot(&CurrentPath)){//Evaluate if the current path is a root
													strcat(CurrentPath,Element->fname); //concatenate The path with the new element
													_list =(List*) SDCardNextFolder (CurrentPath);
													DrawInit(MyWatchScr);
													ListFolderSDCard(_list);
													if(!FolderEmpty()){
													PrintFolder(_list,Ctail->indextail);
													MarkFolder(_list, 0);
													}
													else LCD_DisplayStringXY(0,10,"Folder Empty");
													LCD_DisplayStringXY(0,10,(char*)FolderEmpty);
													Index=0;
													LCD_DisplayStringXY(0,0,(TCHAR*)GetPath());

												}else {
													//Concatenate the current path with the new folder to open
													strcpy(FolderPath,"/");
													strcat(FolderPath,Element->fname);
													strcat(CurrentPath,FolderPath);
													_list =(List*) SDCardNextFolder (CurrentPath);
													DrawInit(MyWatchScr);
													ListFolderSDCard(_list);
													if(!FolderEmpty()){
													PrintFolder(_list,Ctail->indextail);
													MarkFolder(_list, 0);
													}
													else LCD_DisplayStringXY(0,10,"Folder Empty");
													Index=0;
													LCD_DisplayStringXY(0,0,(TCHAR*)GetPath());
												}
										_folderState->curState=FOLDERMODE_TOP;
										}else{
											/*
											 * Here for call the methods that evaluate if the file is mp3 then reproduce
											 * */
											PlayerFSMInit(_PlayerFSM,PLAYMODE);
											_folderState->curState=PLAYSTARMODE;
											WavePlayInit(Element->fname);
											//FIL *file =(FIL *) OpenWavFile(Element->fname);
											//LCD_DisplayStringLine(LINE(19),(TCHAR*)file->fsize);
											//WavePlayStart(I2S_AudioFreq_48k,Element->fname);
											//StartPLayer(I2S_AudioFreq_48k,Element->fname);

										}


								}
							break;
							case LEFTSIG:
								/*
								 * Here code for for go-back within folders
								 *
								 * */
								strcpy(CurrentPath, (TCHAR*)GetPath());
								if(!IsRoot(&CurrentPath)){
									_list=(List*)SDCardBackFolder();
									DrawInit(MyWatchScr);
									ListFolderSDCard(_list);
									PrintFolder(_list,Ctail->indextail);
									MarkFolder(_list, 0);
									Index=0;
									LCD_DisplayStringXY(0,0,(TCHAR*)GetPath());
									_folderState->curState=FOLDERMODE_TOP;
								}


							break;

			default: _folderState->curState=FOLDERMODE_LAST;
			}
		break;
		case PLAYSTARMODE:
			FSMPlayer(_PlayerFSM,_folderState);
			_folderState->curState=PLAYSTARMODE;

		break;
	}

}

void FSMPlayer(FSM * _PlayerFSM, FSM * _FolderFSM){
	List * Element = search_in_list(Index);
	/*
	 * HERE for FSM of audioplayer
	 * */

	//WAVEPLAYSTART(I2S_AudioFreq_48k,Element->fname);

}
