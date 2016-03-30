#include "WidgetConfig.h"
#include "Event.h"
#include "ffconf.h"
#include "ff.h"
#include "stm32f4_discovery_lcd.h"
#include "FileManagement.h"
#include "SD_CardController.h"
#include "waveplayer2.h"


typedef enum State_ {
	FOLDERMODE_TOP,
	FOLDERMODE_NEXT,
	FOLDERMODE_LAST,
/*========From here for audio player===============*/
	PLAYSTARMODE,PLAYMODE,PAUSEMODE,VOLUMEMODE
}State;


typedef enum Signal_ {
	UPSIG,
	DOWNSIG,
	LEFTSIG,
	RIGHTSIG,
	MODE, SUBMODE, NOEVENT
} Signal;


typedef struct FSMFolder_ {
	State     curState;
	State	  SubState;
} FSM;
Signal DecodeEvents(FSM * _FSM);
void FolderFSMInit(FSM * FolderFSM, State _initialState);
void FSMTran(FSM * _FSM, State nextstate);
void FSMSubTran(FSM * _FSM, State Sstate);
void FSMFolder(FSM * _folderState,FSM * _PlayerFSM ,List * _list, char Maxindex);//dispatch SDCard
void FSMPlayer(FSM * _PlayerFSM, FSM * _FolderFSM);//dispatch PlayBack
void PlayerFSMInit(FSM * _PlayerFSM, State _initialState);

