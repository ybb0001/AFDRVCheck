// @@ 1/28, 2014


#include "stdafx.h"

#include "afxmt.h"
#include "Common.h"
#include "ActuatorDrvIC.h"
#include "AutoFocusing.h"

extern short hvca_InfPos;
extern short hvca_MacPos;

int AKSeries;  // 20170403 

CWinThread *pAFThread = NULL;
CEvent g_NewFrame(FALSE, FALSE);
AF_STATUS g_AFStatus = AF_STATUS_END;
AF_MODE  g_AFMode = AF_MODE_NORMAL;

short g_CurLensPos	= AF_STARTPOS_NORMAL;
short g_MaxLensPos	= AF_STARTPOS_NORMAL;
short g_StartLensPos = AF_STARTPOS_NORMAL;
short g_EndLensPos	= AF_ENDPOS_NORMAL;
short g_nStep = AF_NSTEP_NORMAL;
short g_nCurStep = 0;
short g_nMaxStep = 0;

int g_nSelectAFWindow; // 20170330
int g_LensMovingDelay; // 20170330
int g_AFWindowSize;    // 20170405 


DWORD g_nThreshFocalVaule = 10000;
double g_fThreshFocalRatio = 0.7;

int g_nMaxFocalValue = 0;
UINT g_nMinus = 0;
int g_nCurFocalValue = 0;

int g_nFocalValue_1st[AF_NSTEP_1ST];
short g_LensPos_1st[AF_NSTEP_1ST];
int g_nFocalValue_2nd[AF_NSTEP_2ND];
short g_LensPos_2nd[AF_NSTEP_2ND];

short g_nFrameSkip = 0;

int g_nChkAfStatus = 1;

Parameter Af_Macro;
Parameter Af_Infinity;

void SetAFModeNormal(void)
{
	g_AFMode = AF_MODE_NORMAL;
}

void ClearFrameSkip(void)
{
	g_nFrameSkip--;
}

short GetFrameSkipInfo(void)
{
	return g_nFrameSkip;
}


void SetAFModeMacro(void)
{
	g_AFMode = AF_MODE_MACRO;
}


int GetSelectAFWindow(void) // 20170330
{

	return g_nSelectAFWindow;
}

int GetSelectAFWindowSize(void) // 20170405
{

	return g_AFWindowSize;
}


void InitAF(void)
{
	SetFileRead();

#if 1
	if(g_AFMode == AF_MODE_NORMAL){
		g_CurLensPos = Af_Infinity.StartPos;//AF_STARTPOS_NORMAL;
		g_MaxLensPos = Af_Infinity.StartPos;//AF_STARTPOS_NORMAL;
		g_StartLensPos = Af_Infinity.StartPos;//AF_STARTPOS_NORMAL;
		g_EndLensPos = Af_Infinity.EndPos;//AF_ENDPOS_NORMAL;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = Af_Infinity.ScanSteps[0];//AF_NSTEP_NORMAL;
		g_nThreshFocalVaule = Af_Infinity.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Infinity.ThreshFocalRatio;

		g_nSelectAFWindow   = Af_Infinity.SelectAFRegion; // 20170330
		g_LensMovingDelay   = Af_Infinity.LensMoveDelay;  // 20170330
		g_AFWindowSize      = Af_Infinity.AFWindowSize;   // 20170405


	} 
	else if(g_AFMode == AF_MODE_MACRO) {
		g_CurLensPos = Af_Macro.StartPos;//AF_STARTPOS_MACRO;
		g_MaxLensPos = Af_Macro.StartPos;//AF_STARTPOS_MACRO;
		g_StartLensPos = Af_Macro.StartPos;//AF_STARTPOS_MACRO;
		g_EndLensPos = Af_Macro.EndPos;//AF_ENDPOS_MACRO;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = Af_Macro.ScanSteps[0];//AF_NSTEP_MACRO;
		g_nThreshFocalVaule = Af_Macro.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Macro.ThreshFocalRatio;
	}
#else
	if(g_AFMode == AF_MODE_NORMAL){
		g_CurLensPos = hvca_InfPos;
		g_MaxLensPos = hvca_MacPos;
		g_StartLensPos = hvca_InfPos;
		g_EndLensPos = hvca_MacPos;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = AF_NSTEP_NORMAL;
		g_nThreshFocalVaule = Af_Infinity.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Infinity.ThreshFocalRatio;
	} 
	else if(g_AFMode == AF_MODE_MACRO) {
		g_CurLensPos = hvca_MacPos;
		g_MaxLensPos = hvca_InfPos;
		g_StartLensPos = hvca_MacPos;
		g_EndLensPos = hvca_InfPos;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = AF_NSTEP_MACRO;
		g_nThreshFocalVaule = Af_Macro.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Macro.ThreshFocalRatio;
	}
#endif
	g_nCurStep = 0;
	g_nChkAfStatus = 0;

	memset(g_nFocalValue_1st, 0, sizeof(int)*AF_NSTEP_NORMAL);
	memset(g_LensPos_1st, 0, sizeof(short)*AF_NSTEP_NORMAL);
	memset(g_nFocalValue_2nd, 0, sizeof(int)*AF_NSTEP_2ND);
	memset(g_LensPos_2nd, 0, sizeof(short)*AF_NSTEP_2ND);

	Make1stScanPosArray(g_StartLensPos, g_EndLensPos, g_nStep);

	LensMove_Vca(g_CurLensPos);

	g_nFrameSkip = 3; 

	g_AFStatus = AF_STATUS_1ST_SCAN;

	return;
}


int InitAF_DCC(short DCC_AF_START, short DCC_AF_END)
{
	int bresult=0;

	SetFileRead();

#if 1
	if(g_AFMode == AF_MODE_NORMAL){
		g_CurLensPos = DCC_AF_START;//AF_STARTPOS_NORMAL;
		g_MaxLensPos = DCC_AF_START;//AF_STARTPOS_NORMAL;
		g_StartLensPos = DCC_AF_START;//AF_STARTPOS_NORMAL;
		g_EndLensPos = DCC_AF_END;//AF_ENDPOS_NORMAL;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = Af_Infinity.ScanSteps[0];//AF_NSTEP_NORMAL;
		g_nThreshFocalVaule = Af_Infinity.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Infinity.ThreshFocalRatio;
	} 
	else if(g_AFMode == AF_MODE_MACRO) {
		g_CurLensPos = DCC_AF_START;//AF_STARTPOS_MACRO;
		g_MaxLensPos = DCC_AF_START;//AF_STARTPOS_MACRO;
		g_StartLensPos = DCC_AF_START;//AF_STARTPOS_MACRO;
		g_EndLensPos = DCC_AF_END;//AF_ENDPOS_MACRO;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = Af_Macro.ScanSteps[0];//AF_NSTEP_MACRO;
		g_nThreshFocalVaule = Af_Macro.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Macro.ThreshFocalRatio;
	}
#else
	if(g_AFMode == AF_MODE_NORMAL){
		g_CurLensPos = hvca_InfPos;
		g_MaxLensPos = hvca_MacPos;
		g_StartLensPos = hvca_InfPos;
		g_EndLensPos = hvca_MacPos;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = AF_NSTEP_NORMAL;
		g_nThreshFocalVaule = Af_Infinity.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Infinity.ThreshFocalRatio;
	} 
	else if(g_AFMode == AF_MODE_MACRO) {
		g_CurLensPos = hvca_MacPos;
		g_MaxLensPos = hvca_InfPos;
		g_StartLensPos = hvca_MacPos;
		g_EndLensPos = hvca_InfPos;
		g_nMaxFocalValue = 0;
		g_nMinus = 0;
		g_nStep = AF_NSTEP_MACRO;
		g_nThreshFocalVaule = Af_Macro.ThreshFocalValue;
		g_fThreshFocalRatio = Af_Macro.ThreshFocalRatio;
	}
#endif
	g_nCurStep = 0;
	g_nChkAfStatus = 0;

	memset(g_nFocalValue_1st, 0, sizeof(int)*AF_NSTEP_NORMAL);
	memset(g_LensPos_1st, 0, sizeof(short)*AF_NSTEP_NORMAL);
	memset(g_nFocalValue_2nd, 0, sizeof(int)*AF_NSTEP_2ND);
	memset(g_LensPos_2nd, 0, sizeof(short)*AF_NSTEP_2ND);

	Make1stScanPosArray(g_StartLensPos, g_EndLensPos, g_nStep);

	bresult = LensMove_Vca(g_CurLensPos);

	g_nFrameSkip = 3; 

	g_AFStatus = AF_STATUS_1ST_SCAN;

	return bresult;
}


void Make1stScanPosArray(short startpos, short endpos, short nstep)
{
	int index;
	double fStepSize, fBasePos;

	fBasePos = startpos;
	fStepSize = ((double)endpos - startpos)/nstep;

	g_LensPos_1st[0] = startpos;
	for(index = 1;index <= nstep; index++){  // 20170405 
		fBasePos += fStepSize;
		g_LensPos_1st[index] = PosRound(fBasePos);		

		TRACE("af 1st step___%d\n", g_LensPos_1st[index]);
	}

	return;
}

void Make2ndScanPosArray(short startpos, short endpos, short nstep)
{
	int index;
	double fStepSize, fBasePos;

	fBasePos = startpos;
	fStepSize = ((double)endpos - startpos)/nstep;

	g_LensPos_2nd[0] = startpos;
	for(index = 1;index < nstep; index++){
		fBasePos += fStepSize;
		g_LensPos_2nd[index] = PosRound(fBasePos);	

		TRACE("af 2nd step___%d\n", g_LensPos_2nd[index]);
	}

	return;
}

short PosRound(double fPos)
{
	fPos += 0.5;
	return (short)fPos;
}

// 20180806 
int LensMove_Vca(short target, BOOL SrcMode)
{
	// 20180725 AFDrv.IC Select
	// #define AK7345   0
	// #define AK7371   1
	// #define AK7372   2 
	// #define LC898217 3

	// 20180727 AKSeries = LC898217; // 20180725
	unsigned char AFDrvICType=0;
	AFDrvICType = LC898217;//AK7372; // LC898217;

	int bresult = 0;

	// 20170405 Output Range selsect
	switch(AFDrvICType) // 20180727 AKSeries ¢®©¡ AFDrvICType
	{
		case AK7345:	if(target < 0 || target >  511) return -1;		break;
		case AK7371:
		case AK7372:
		case LC898217:	if(target < 0 || target > 1023) return -1;		break;
	}
	// 

	// 20180725
	switch(AFDrvICType) // 20180727 AKSeries ¢®©¡ AFDrvICType
	{

		case AK7345:
		case AK7371:
		case AK7372:	if(LensMove_AKSeries(target, AFDrvICType) == FALSE) {	bresult = 1;	}	break; // 20180727 AKSeries ¢®©¡ AFDrvICType

		case LC898217:	if(LensMove_LC898217(target) == FALSE)			    {	bresult = 1;	}	break;

	}



	TRACE("LENS_MOVE ; TARGET = %d (0x%X) ; RETRUN = %d \n",target, target, bresult);

	g_CurLensPos = target;
	g_nFrameSkip = 1; 

	return bresult;
}

void SetCurFocalValue(int fvalue)
{
	if(g_nCurStep < 3)
		g_nCurFocalValue = 0;
	else
		g_nCurFocalValue = fvalue;	

	return;
}

int GetFocalValue(void)
{
	return g_nCurFocalValue;
}

UINT GetCurPos(void){	
	return g_CurLensPos;
}

void SetNewFrameEvent(void){	
	g_NewFrame.SetEvent();
}

void StartAF(void)
{

	if(pAFThread != NULL) {
		return;	
	}

	pAFThread = AfxBeginThread(AFThread, NULL);
}


void KillThread()
{
	if(pAFThread != NULL) 
	{
		DWORD dwExitCode;

		Sleep(0);

		if( ::WaitForSingleObject(pAFThread->m_hThread, 2000) == WAIT_TIMEOUT )
		{
			::GetExitCodeThread(pAFThread->m_hThread, &dwExitCode);
			if( dwExitCode == STILL_ACTIVE )
			 {
				 if( TerminateThread(pAFThread->m_hThread, 0) )
				 {
					 pAFThread = NULL;
				 }
			 }
			pAFThread = NULL;
		}
		else
			pAFThread = NULL;

	}

	g_nChkAfStatus = 1;

	return;
}

UINT AFThread(LPVOID pParam)
{

	while(g_AFStatus != AF_STATUS_DONE)
	{

		::WaitForSingleObject((HANDLE)g_NewFrame, INFINITE);	
		
		if(GetFrameSkipInfo())
		{
			//TRACE("%d---frameskip==\n", GetFrameSkipInfo());
			ClearFrameSkip();
			IIC_Delay(g_LensMovingDelay); // 20170330

			continue;
		}
		//TRACE("%d---frameskip==\n", GetFrameSkipInfo());


		switch(g_AFStatus)
		{
		case AF_STATUS_1ST_SCAN:

			if(Check1stEndCondition() == TRUE || g_nCurStep >= (g_nStep) ){ // 20151113
				g_AFStatus = AF_STATUS_2ND_SCAN;

				if(g_nMaxStep < 2){
					g_StartLensPos = g_LensPos_1st[0];
					g_EndLensPos = g_LensPos_1st[4];
				}
				else if(g_nMaxStep >= g_nStep - 3){
					g_StartLensPos = g_LensPos_1st[g_nStep-4];
					g_EndLensPos = g_LensPos_1st[g_nStep];
				}
				else {
					g_StartLensPos = g_LensPos_1st[g_nMaxStep-1];  // 20170330
					g_EndLensPos = g_LensPos_1st[g_nMaxStep+1];
				}

				if(g_AFMode == AF_MODE_MACRO){
					g_nStep = Af_Macro.ScanSteps[1];
				} else {
					g_nStep = Af_Infinity.ScanSteps[1];
				}
				
				Make2ndScanPosArray(g_StartLensPos, g_EndLensPos, g_nStep);

				g_nMaxFocalValue = 0;
				g_nMaxStep = 0;
				g_nCurStep = 0;

				LensMove_Vca(g_LensPos_2nd[g_nCurStep]);

				break;
			}

			g_nCurStep++;


			LensMove_Vca(g_LensPos_1st[g_nCurStep]);//
			break;

		case AF_STATUS_2ND_SCAN:

			if(Check2ndEndCondition()){
				g_AFStatus = AF_STATUS_DONE;
				break;
			}

			g_nCurStep++;
			if(g_nCurStep >= g_nStep){	
				g_nCurStep = g_nMaxStep;
				LensMove_Vca(g_nMaxStep); // ??? 
				g_AFStatus = AF_STATUS_DONE;
				break;
			}
			LensMove_Vca(g_LensPos_2nd[g_nCurStep]);
			break;
		}

		//::Sleep(0);

	}


	// 20170405 check
	LensMove_Vca(g_LensPos_2nd[g_nMaxStep]);	
	TRACE("max pos = %X\n", g_LensPos_2nd[g_nMaxStep]);

	// 20170817 deleted



//AFError:
	g_nChkAfStatus = 1;

	pAFThread = NULL;

	return 0;
}

BOOL Check1stEndCondition(void)
{
	if(g_nCurStep < 3)
		return FALSE;	
	
	g_nFocalValue_1st[g_nCurStep] = g_nCurFocalValue = GetFocalValue();

	//DbgPrintf("%s : step = %d, pos = %d, FV = %ld (%ld) \n",__FUNCTION__, g_nCurStep, g_LensPos_1st[g_nCurStep], g_nFocalValue_1st[g_nCurStep], g_nMaxFocalValue);

	if(g_nCurFocalValue >= g_nMaxFocalValue)
	{
		g_nMaxFocalValue = g_nCurFocalValue;
		g_nMinus = 0;
		g_nMaxStep = g_nCurStep;	
	} 
	else 
	{
		if(g_nFocalValue_1st[g_nCurStep] > g_nFocalValue_1st[g_nCurStep-1])
		{
			g_nMaxFocalValue = 0;
			g_nMinus = 0;
		} 
		else
		{
			g_nMinus++;
			
			DbgPrintf("%s : g_nMinus = %d, th = %f, g_nMaxFocalValue = %ld \n",__FUNCTION__, g_nMinus, (float)g_nCurFocalValue/g_nMaxFocalValue, g_nMaxFocalValue);

			//if(g_nMinus >= 3) 
			if(g_nMinus >= 3 && (double)g_nCurFocalValue/g_nMaxFocalValue <= g_fThreshFocalRatio && g_nMaxFocalValue >= (int)g_nThreshFocalVaule) 
				return TRUE;	
		}
	}

	return FALSE;
}

BOOL Check2ndEndCondition(void)
{

	if(g_nCurStep < 3)return FALSE;	

	g_nFocalValue_2nd[g_nCurStep] = g_nCurFocalValue = GetFocalValue();

	//DbgPrintf("%s : step = %d, pos = %d, FV = %ld (%ld) \n",__FUNCTION__, g_nCurStep, g_LensPos_2nd[g_nCurStep], g_nFocalValue_2nd[g_nCurStep], g_nMaxFocalValue);

	if(g_nCurFocalValue >= g_nMaxFocalValue)
	{
		g_nMaxFocalValue = g_nCurFocalValue;
		g_nMinus = 0;
		g_nMaxStep = g_nCurStep;
	} 
	else
	{
		g_nMinus++;

		if(g_nMinus >= 3)
			return TRUE;		
	}

	return FALSE;
}


int ChkAfStatus()
{
	return g_nChkAfStatus;
}


int SetVCM_SRC(unsigned int curpos, unsigned int target, unsigned int* nextpos)
{
	BYTE tSrc = 0;

#if 0
	unsigned int displacement = target - curpos;

	if(displacement >= 234)			{	tSrc = 0x0F;	*nextpos = curpos + 234;	}
	else if(displacement >= 232)	{	tSrc = 0x0E;	*nextpos = curpos + 232;	}
	else if(displacement >= 230)	{	tSrc = 0x0D;	*nextpos = curpos + 230;	}
	else if(displacement >= 193)	{	tSrc = 0x02;	*nextpos = curpos + 193;	}
	else if(displacement >= 189)	{	tSrc = 0x01;	*nextpos = curpos + 189;	}
	else if(displacement >= 185)	{	tSrc = 0x00;	*nextpos = curpos + 185;	}
	else if(displacement >= 180)	{	tSrc = 0x1F;	*nextpos = curpos + 180;	}
	else if(displacement >= 176)	{	tSrc = 0x1E;	*nextpos = curpos + 176;	}
	else if(displacement >= 172)	{	tSrc = 0x1D;	*nextpos = curpos + 172;	}
	else if(displacement >= 120)	{	tSrc = 0x12;	*nextpos = curpos + 120;	}
	else if(displacement >= 115)	{	tSrc = 0x11;	*nextpos = curpos + 115;	}
	else if(displacement >= 110)	{	tSrc = 0x10;	*nextpos = curpos + 110;	}
	else							{	return FALSE;	}
				
	// change ringing setting
	unsigned char addrbuf[2] = {0,};
	unsigned char databuf[2] = {0,};

	addrbuf[0] = 0xEC;
	databuf[0] = 0xA3;
	I2C_SYS_Write2_Ex_Mul(g_cardinfo.nCardnum, 0x18, 1, addrbuf, 1, databuf);

	addrbuf[0] = 0xA1;
	databuf[0] = 0x05;
	I2C_SYS_Write2_Ex_Mul(g_cardinfo.nCardnum, 0x18, 1, addrbuf, 1, databuf);

	addrbuf[0] = 0xF2;
	databuf[0] = (tSrc<<3) & 0xF8;
	I2C_SYS_Write2_Ex_Mul(g_cardinfo.nCardnum, 0x18, 1, addrbuf, 1, databuf);

	addrbuf[0] = 0xDC;
	databuf[0] = 0x51;
	I2C_SYS_Write2_Ex_Mul(g_cardinfo.nCardnum, 0x18, 1, addrbuf, 1, databuf);

#endif


	return TRUE;
}


UINT MaxFocusValue(void)
{
	return g_nMaxFocalValue;
}



int SetFileRead(void)
{
	char szDirve[256],szDir[256]; 
	char programpath[_MAX_PATH];
	CString fileName;

	GetModuleFileName( NULL, programpath, _MAX_PATH);
	_splitpath_s(programpath, szDirve, _MAX_DRIVE, szDir, _MAX_DIR, NULL, NULL, NULL, NULL);

	int temp = 0;

	CString SplInfo;
	SplInfo.Format("%s%s%s",szDirve,szDir,"\\Setting\\Xiaomi_F1.ini"); // 20180806 E1->F1

	Af_Infinity.SelectAFRegion  = GetPrivateProfileInt("AF_SETTING",	"SelectAFRegion",	0,	SplInfo); // 20170330
	Af_Infinity.LensMoveDelay   = GetPrivateProfileInt("AF_SETTING",	"LensMoveDelay",	0,	SplInfo); // 20170330
	Af_Infinity.AFWindowSize    = GetPrivateProfileInt("AF_SETTING",	"AFWindowSize",	    1,	SplInfo); // 20170405

	// Normal A/F
	Af_Infinity.StartPos = GetPrivateProfileInt("NORMAL_AF",	"StartPosition",	hvca_InfPos,	SplInfo);  
	Af_Infinity.EndPos = GetPrivateProfileInt("NORMAL_AF",	"EndPosition",	hvca_MacPos,	SplInfo);  
	//if(Af_Infinity.EndPos < Af_Infinity.StartPos)	Af_Infinity.EndPos = AF_ENDPOS_NORMAL;

	DbgPrintf("Normal AF Start : %d End : %d\n",Af_Infinity.StartPos,Af_Infinity.EndPos);
	
	Af_Infinity.ScanSteps[0] = GetPrivateProfileInt("NORMAL_AF",	"ScanSteps_1st",	AF_NSTEP_NORMAL,	SplInfo);
	//if(Af_Infinity.ScanSteps[0] <= 0) Af_Infinity.ScanSteps[0] = AF_NSTEP_NORMAL;
	Af_Infinity.ScanSteps[1] = GetPrivateProfileInt("NORMAL_AF",	"ScanSteps_2nd",	AF_NSTEP_2ND,	SplInfo);
	//if(Af_Infinity.ScanSteps[1] <= 0) Af_Infinity.ScanSteps[1] = AF_NSTEP_2ND;

	DbgPrintf("Normal AF Scan Step : %d/%d \n",Af_Infinity.ScanSteps[0], Af_Infinity.ScanSteps[1]);

	Af_Infinity.ThreshFocalValue = GetPrivateProfileInt("NORMAL_AF",	"ThreshFocalValue",	10000,	SplInfo);
	temp = GetPrivateProfileInt("NORMAL_AF",	"ThreshFocalRatio",	70,	SplInfo); 
	Af_Infinity.ThreshFocalRatio = (double)temp/100.0;

	// Macro A/F
	Af_Macro.StartPos = GetPrivateProfileInt("MACRO_AF",	"StartPosition",	hvca_InfPos - (hvca_InfPos >> 2),	SplInfo);
	Af_Macro.EndPos = GetPrivateProfileInt("MACRO_AF",	"EndPosition",	hvca_MacPos + (hvca_MacPos >> 2),	SplInfo);  
	//if(Af_Macro.EndPos < Af_Macro.StartPos)	Af_Macro.EndPos = AF_ENDPOS_NORMAL;

	DbgPrintf("Macro Start : %d End : %d\n",Af_Macro.StartPos,Af_Macro.EndPos);

	Af_Macro.ScanSteps[0] = GetPrivateProfileInt("MACRO_AF",	"ScanSteps_1st",	AF_NSTEP_MACRO,	SplInfo);
	//if(Af_Macro.ScanSteps[0] <= 0) Af_Macro.ScanSteps[0] = AF_NSTEP_MACRO;
	Af_Macro.ScanSteps[1] = GetPrivateProfileInt("MACRO_AF",	"ScanSteps_2nd",	AF_NSTEP_2ND,	SplInfo);
	//if(Af_Macro.ScanSteps[1] <= 0) Af_Macro.ScanSteps[1] = AF_NSTEP_2ND;

	DbgPrintf("Macro AF Scan Step : %d/%d \n",Af_Macro.ScanSteps[0], Af_Macro.ScanSteps[1]);

	Af_Macro.ThreshFocalValue = GetPrivateProfileInt("MACRO_AF",	"ThreshFocalValue",	10000,	SplInfo);
	temp = GetPrivateProfileInt("MACRO_AF",	"ThreshFocalRatio",	70,	SplInfo); 
	Af_Macro.ThreshFocalRatio = (double)temp/100.0;


	return 0;
}
