#ifndef __AUTOFOCUSING_H_____
#define __AUTOFOCUSING_H_____


typedef enum _AF_STATUS
{
	AF_STATUS_START		= 0,
	AF_STATUS_READY		= AF_STATUS_START,
	AF_STATUS_1ST_SCAN	= AF_STATUS_START+1,
	AF_STATUS_2ND_SCAN	= AF_STATUS_START+2,
	AF_STATUS_DONE		= AF_STATUS_START+3,
	AF_STATUS_END		= AF_STATUS_DONE,
	AF_STATUS_1ST_HOLD  = AF_STATUS_DONE+1,
	AF_STATUS_2ND_HOLD  = AF_STATUS_DONE+2
} AF_STATUS;

typedef enum _AF_MODE
{
	AF_MODE_START	= 0,
	AF_MODE_NORMAL	= AF_MODE_START,
	AF_MODE_MACRO	= AF_MODE_START+1,
	AF_MODE_END		= AF_MODE_MACRO
} AF_MODE;


typedef struct tagParameter
{
	int StartPos;
	int EndPos;
	int ScanSteps[2];
	int ThreshFocalValue;
	double ThreshFocalRatio;
	int SelectAFRegion; // 20170330
	int LensMoveDelay;  // 20170330
	int AFWindowSize;   // 20170405

}Parameter;

#define AF_STARTPOS_NORMAL	0x3FF
#define AF_STARTPOS_MACRO	0x0
#define AF_ENDPOS_NORMAL	0x0
#define AF_ENDPOS_MACRO		0x3FF

#define AF_NSTEP_NORMAL	64
#define AF_NSTEP_MACRO	64
#define AF_NSTEP_1ST	64
#define AF_NSTEP_2ND	32

void SetAFModeNormal(void);
void ClearFrameSkip(void);
short GetFrameSkipInfo(void);
void SetAFModeMacro(void);

int GetSelectAFWindow(void);      // 20170330
int GetSelectAFWindowSize(void);  // 20170405

void InitAF(void);
int InitAF_DCC(short DCC_AF_START, short DCC_AF_END);
void Make1stScanPosArray(short startpos, short endpos, short nstep);
void Make2ndScanPosArray(void);
short PosRound(double fPos);
int LensMove_Vca(short target, BOOL SrcMode = FALSE);
void SetCurFocalValue(int fvalue);
int GetFocalValue(void);
UINT GetCurPos(void);
void SetNewFrameEvent(void);
void StartAF(void);
void KillThread();
UINT AFThread(LPVOID pParam);
BOOL Check1stEndCondition(void);
BOOL Check2ndEndCondition(void);
int ChkAfStatus();
int SetVCM_SRC(unsigned int curpos, unsigned int target, unsigned int* nextpos);

UINT MaxFocusValue(void);
int SetFileRead(void);


#endif