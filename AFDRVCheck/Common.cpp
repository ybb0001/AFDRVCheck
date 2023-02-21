#include "stdafx.h"
#include "mmsystem.h"
#include "Common.h"


// delay function

LARGE_INTEGER g_nFreq, g_nStart, g_nStop;	// For Stopwatch
float g_fEtime;

void StopWatchms(int start0stop1)
{
	if (start0stop1==0)	{
		QueryPerformanceFrequency(&g_nFreq);
		QueryPerformanceCounter(&g_nStart);
	}
	else {
		QueryPerformanceCounter(&g_nStop);
		if (g_nFreq.LowPart==0 && g_nFreq.HighPart==0) g_fEtime = -1;
		else {
			g_fEtime = (float)(g_nStop.LowPart - g_nStart.LowPart);

			if (g_fEtime < 0) g_fEtime += 4294967296;	// (2<<32);// 2^32;

			g_fEtime /= (g_nFreq.LowPart+ (g_nFreq.HighPart * 4294967296));
		}
	}
}

float IIC_Delayus(float D_Time)
{
	StopWatchms(0);
	MSG		nMsg;
	while(1){
		while(PeekMessage(&nMsg, NULL, 0, 0, PM_REMOVE)) {		//¸Þ½ÃÁö ÆßÇÎ
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);
		}
		StopWatchms(1);
		if(g_fEtime >= D_Time)	break;
	}
	return g_fEtime;
}

int IIC_Delay(UINT D_Time)
{
	DWORD m_start, m_now, m_dtime, nCnt;
	MSG		nMsg;
	nCnt	= 0;
	timeGetTime();
	timeGetTime();
	m_start	= timeGetTime();
	do{
		m_now	= timeGetTime();
		m_dtime	= m_now - m_start;
		if(m_dtime >= D_Time)
			break;
		//Message Pump
		while(PeekMessage(&nMsg, NULL, 0, 0, PM_REMOVE)){
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);
		}
		m_now	= timeGetTime();
		m_dtime	= m_now - m_start;
	}while(m_dtime <= D_Time);
	return (int)m_dtime;
}

//Debug

void DbgPrintf(char* format,...)
{
	char outString[256];
	va_list args;
	va_start(args, format);
	vsprintf_s(outString, format, args);
	va_end(args);
	OutputDebugStringA(outString);
	return;
}


//IIC & RESET signal generation


//load sensor settings

int g_nRegSetCnt;
int g_nRegSetValue_a[REG_MAX_NUM];
int g_nRegSetValue_b[REG_MAX_NUM];
int g_nRegSetValue_c[REG_MAX_NUM];
int g_nRegSetValue_d[REG_MAX_NUM];
int g_nRegDelayValue_d[REG_MAX_NUM];
CString g_strRegFile;


int WINAPI LoadSettings(LPSTR RegFileName) // 0406 i2c mode setting
{
	FILE    *stream;
	errno_t err;
	char cmd[256], buf[256];
	char ch;
	int     add,add2,data1,data2,delaytime, i;
	bool bModechk = true;
	int nI2cMode = I2CMODE_SINGLEADDRDATA;

//	char programpath[1024];
	LPWSTR programpath=_T("");

	GetModuleFileName( NULL, programpath, 1024);


	g_strRegFile = programpath;
	g_strRegFile = g_strRegFile.Mid(0, g_strRegFile.ReverseFind(TEXT('\\')));

	g_strRegFile += "\\Register\\";
	g_strRegFile += RegFileName;

	//1. init reg array
	memset(g_nRegSetValue_a, 0, sizeof(int)*REG_MAX_NUM);
	memset(g_nRegSetValue_b, 0, sizeof(int)*REG_MAX_NUM);
	memset(g_nRegSetValue_c, 0, sizeof(int)*REG_MAX_NUM);
	memset(g_nRegSetValue_d, 0, sizeof(int)*REG_MAX_NUM);
	memset(g_nRegDelayValue_d, 0, sizeof(int)*REG_MAX_NUM);

	g_nRegSetCnt = 0;

	//if ((err = fopen_s(&stream,g_strRegFile.CopyChars,"r")) != 0){		
	if ((err = fopen_s(&stream, (char *)(LPCTSTR)g_strRegFile, "r")) != 0) {
		return -1;
	}

	while(1){ 
		memset(buf,0,256);
		i	= 0;
		while(1){
			ch		= fgetc(stream);
			buf[i]	= (char)ch;
			if(ch == EOF){					i		= 0;	break;	}
			if(ch == '\n' || ch == '\r'){	buf[i]	= 0x0;	break;	}
			i++;
		}
		if(i == 0 && ch == EOF)		break;
		if(buf[0] =='#' || buf[0] ==' ' || i < 5)	continue;		

		if(g_nRegSetCnt >= REG_MAX_NUM-1)break;

		sscanf_s(buf, "%s", cmd, 256);
		if(strcmp(cmd, "setreg")==0){

////////////////// I2C mode check ////////////////////////

			if(bModechk){
				add = add2 = 0x5A5A;
				sscanf_s(buf, "%s $%02x%02x", cmd, 256, &add, &add2, sizeof(add), sizeof(add2));
				if(add2 != 0x5A5A)nI2cMode = I2CMODE_DOUBLEADDR;

				data1 = data2 = 0x5A5A;
				
				if(nI2cMode & I2CMODE_DOUBLEADDR){	//2byte addr
					sscanf_s(buf, "%s $%02x%02x $%02x%02x", cmd, 256, &add, &add2, &data1, &data2, sizeof(add), sizeof(add2), sizeof(data1), sizeof(data2));

					if(data2 != 0x5A5A){
						nI2cMode |= I2CMODE_DOUBLEDATA;
					}

				} else {	//1byte addr
					sscanf_s(buf, "%s $%02x $%02x%02x", cmd, 256, &add, &data1, &data2, sizeof(add), sizeof(data1), sizeof(data2));
					if(data2 != 0x5A5A){
						nI2cMode |= I2CMODE_DOUBLEDATA;
					}
				}	
				bModechk = false;	
			}
////////////////// end of I2C mode check ////////////////////////

			switch(nI2cMode){

				case I2CMODE_SINGLEADDRDATA:
					sscanf_s(buf, "%s $%02x $%02x", cmd, 256, &add, &data1, sizeof(add), sizeof(data1));

					g_nRegSetValue_a[g_nRegSetCnt] = add;
					g_nRegSetValue_b[g_nRegSetCnt] = data1;

					break;

				case I2CMODE_DOUBLEADDR:
					sscanf_s(buf, "%s $%02x%02x $%02x", cmd, 256, &add, &add2, &data1, sizeof(add), sizeof(add2), sizeof(data1));

					g_nRegSetValue_a[g_nRegSetCnt] = add;
					g_nRegSetValue_b[g_nRegSetCnt] = add2;
					g_nRegSetValue_c[g_nRegSetCnt] = data1;

					break;

				case I2CMODE_DOUBLEDATA:
					sscanf_s(buf, "%s $%02x $%02x%02x", cmd, 256, &add, &data1, &data2, sizeof(add), sizeof(data1), sizeof(data2));


					g_nRegSetValue_a[g_nRegSetCnt] = add;
					g_nRegSetValue_b[g_nRegSetCnt] = data1;
					g_nRegSetValue_c[g_nRegSetCnt] = data2;
					
					break;

				case I2CMODE_DOUBLEADDR | I2CMODE_DOUBLEDATA:  // 0407 I2C data order
					sscanf_s(buf, "%s $%02x%02x $%02x%02x", cmd, 256, &add, &add2, &data1, &data2, sizeof(add), sizeof(add2), sizeof(data1), sizeof(data2));

					g_nRegSetValue_a[g_nRegSetCnt] = add;
					g_nRegSetValue_b[g_nRegSetCnt] = add2;
 					g_nRegSetValue_c[g_nRegSetCnt] = data1;
 					g_nRegSetValue_d[g_nRegSetCnt] = data2;
//					g_nRegSetValue_c[g_nRegSetCnt] = data2; // 0407
//					g_nRegSetValue_c[g_nRegSetCnt] = data1;

					break;
			}	//end of switch(nI2cMode)

			g_nRegSetCnt++;

		}
		else if(strcmp(cmd, "delay") == 0){		//Read Delay Time
			sscanf_s(buf, "%s $%04d", cmd, 256, &delaytime, sizeof(delaytime));
			g_nRegDelayValue_d[g_nRegSetCnt]	= delaytime;
		}
	}	//end of while(1)


	fclose(stream);

	return 0;
}

