
#ifndef __DC_LIB_H_____
#define __DC_LIB_H_____


#ifdef __DCLIB_EXPORT__
	#define	DCLIB_API	__declspec(dllexport)
#else
	#define	DCLIB_API	__declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define	BYTE	unsigned char
#define WORD	unsigned short
#define DWORD	unsigned long

DCLIB_API int _stdcall DC_Init();
DCLIB_API int _stdcall DC_End();

DCLIB_API int _stdcall DC_GetMaxCards();
DCLIB_API int _stdcall DC_GetVersion(int card_num,DWORD *DllVer,DWORD *DrvVer,DWORD *ChipVer);

DCLIB_API int _stdcall DC_GetMaxChannels(int card_num);
DCLIB_API int _stdcall DC_WriteReg(int card_num,DWORD offset,DWORD data);
DCLIB_API int _stdcall DC_ReadReg(int card_num,DWORD offset,DWORD *data);

DCLIB_API int _stdcall DC_GpioReadIn(int card_num,DWORD *data);
DCLIB_API int _stdcall DC_GpioWriteOut(int card_num,DWORD data);
DCLIB_API int _stdcall DC_GpioWriteOE(int card_num,DWORD data);

DCLIB_API int _stdcall DC_Open(int card_num,int channel,int Height,int Width,int Frames,int BitsPerClk);
DCLIB_API int _stdcall DC_Close(int card_num,int channel);

DCLIB_API int _stdcall DC_Start(int card_num,int channel);
DCLIB_API int _stdcall DC_Stop(int card_num,int channel);

DCLIB_API int _stdcall DC_GetFrame(int card_num,int channel, int blocked,BYTE **buf,WORD *length,DWORD *eof_length);
DCLIB_API int _stdcall DC_CancelGetFrame(int card_num,int channel);

DCLIB_API int _stdcall DC_SetCapInfo(int card_num,int channel,int HBP, int VBP, int ClkEdgeHigh, int HSyncEdgeHigh, int VSyncEdgeHigh, int LineArea, int Input10Bits,int SyncValidEn);
DCLIB_API int _stdcall DC_SetBurstLength(int card_num,int len);

DCLIB_API int _stdcall DC_SetMipiInfo(int card_num, int channel, int VirtualChannel,int DataType);
DCLIB_API int _stdcall DC_SetMipiInfoMulti(int card_num, int channel, int VirtualChannel,int DataType,int DataType1,int DataType2,int DataType3);
DCLIB_API int _stdcall DC_SetLookupTable(int card_num,int channel,int index, WORD value);

// new function
DCLIB_API int _stdcall DC_GetPcieInfo(int card_num,DWORD *max_payload,DWORD *lanes,DWORD *payload);
DCLIB_API int _stdcall DC_SetPciePayLoad(int card_num,DWORD payload); // 128,256,512,1024

DCLIB_API int _stdcall DC_SetMipiDsiInfo(int card_num, int channel, int dsi_enable,int dsi_video_or_command,int dsi_hsync_gen,int dsi_vsync_gen,int lanes);
DCLIB_API int _stdcall DC_SetMipiCsiTestCamEn(int card_num, int channel, int enable);
DCLIB_API int _stdcall DC_GetMipiError(int card_num, int channel, DWORD *status);
DCLIB_API int _stdcall DC_ClrMipiError(int card_num, int channel);



// PLL control functions
DCLIB_API int _stdcall DC_SetClkOutFreq(int card_num,int clk_o_number, int ref_number);
DCLIB_API int _stdcall DC_SetClkOutFreq1(int card_num,int clk_o_number, int ref_number,int mode);


DCLIB_API int _stdcall DC_CheckCamLines(int card_num,int channel,DWORD width_ms);
DCLIB_API int _stdcall DC_GetCamLineToggleTimes(int card_num,int channel,int index,DWORD *val);

// I2C control functions
DCLIB_API void _stdcall DC_I2cInit(int card_num,int channel,int DelayCnt,int rst_active_pol);
DCLIB_API void _stdcall DC_I2cRst(int card_num,int channel);
DCLIB_API void _stdcall DC_I2cRst1(int card_num,int channel,int delay_ms);
DCLIB_API int	_stdcall DC_I2cWrite(int card_num,int channel,BYTE data);
DCLIB_API int	_stdcall DC_I2cRead(int card_num,int channel,int hilo);
DCLIB_API int	_stdcall DC_I2cStart(int card_num,int channel);
DCLIB_API void _stdcall DC_I2cStop(int card_num,int channel);

DCLIB_API int _stdcall DC_I2cClkStretchEn(int card_num,int channel,int en);

DCLIB_API 	int	_stdcall DC_SoftI2cWrite(int card_num, int channel,int length, BYTE start,BYTE last, BYTE *buf);
DCLIB_API 	int	_stdcall DC_SoftI2cRead(int card_num, int channel,int length, BYTE last, BYTE *buf);


// EEPROM program
DCLIB_API int _stdcall DC_Prog(int card_num,void *report, char *filename);
DCLIB_API int _stdcall DC_MipiProg(int card_num,void *report, char *filename);

// overlay display functions
DCLIB_API int	_stdcall DC_DispOpen(void *hWnd,int width,int height,int pixelBytes);
DCLIB_API int	_stdcall DC_DispClose();
DCLIB_API void _stdcall DC_SetKeyColor(DWORD keycolor);
DCLIB_API DWORD _stdcall DC_GetKeyColor();
DCLIB_API void _stdcall DC_SetFourCC(DWORD dwFourCC);
DCLIB_API DWORD _stdcall DC_GetFourCC();
DCLIB_API void _stdcall DC_SetShowRect(RECT *sr,RECT *dr);
DCLIB_API int _stdcall DC_Update(BYTE *buf,int width,int height,int pixelbytes,int flip);	// source parameters

// Surface 관련 추가함수
DCLIB_API 	int	_stdcall DC_GetFourCCs(DWORD *pNumCodes, DWORD *pCodes);
DCLIB_API int	_stdcall DC_DispOpen1(void *hWnd,int width,int height);
DCLIB_API void _stdcall DC_SetFourCC1(DWORD dwFourCC,int BufWidth,int BufHeight);
DCLIB_API int _stdcall DC_Update1(BYTE *buf);	// source parameters


// I2C, SPI 함수
//

//
// external I/O functions
//
DCLIB_API 	float _stdcall DC_SetSpiFreq(int card_num, float freq_mhz);
DCLIB_API 	int _stdcall DC_SetSpiLatency(int card_num, int lat);

DCLIB_API 	int	_stdcall DC_SpiWrite(int card_num, int length, BYTE last, BYTE *buf);
DCLIB_API 	int	_stdcall DC_SpiRead(int card_num, int length, BYTE last, BYTE *buf);

DCLIB_API 	float _stdcall DC_SetHwI2cFreq(int card_num, float freq_khz);
DCLIB_API 	int	_stdcall DC_HwI2cWrite(int card_num, int length, BYTE start,BYTE last, BYTE *buf);
DCLIB_API 	int	_stdcall DC_HwI2cRead(int card_num, int length, BYTE last, BYTE *buf);

DCLIB_API 	float _stdcall DC_SetClkFreq(int card_num, float freq);

DCLIB_API 	int	_stdcall DC_SetSpiI2cMode(int card_num, int si);
DCLIB_API 	int	_stdcall DC_GetSpiI2cMode(int card_num);


//
// MIPI board update functions
//
DCLIB_API	int	_stdcall DC_CheckMipiFlash(int card_num);
DCLIB_API	int	_stdcall DC_DbgRead(int card_num,int target, int length, BYTE *buf);
DCLIB_API	char* _stdcall DC_GetErrorMsg(int error);


//
// SPI 핸들을 관리하는 함수
//

DCLIB_API   int _stdcall DC_GetPmuHandle(int card_num, HANDLE *pHandle);
DCLIB_API   int _stdcall DC_ReleasePmuHandle(int card_num, HANDLE hHandle);

//
// 기존 PMU 함수들
//

//DCLIB_API 	int	_stdcall DC_PmuGetVersion(int card_num,DWORD *ver);
//
//DCLIB_API 	int	_stdcall DC_PmuWrite(int card_num,DWORD offset,DWORD data);
//DCLIB_API 	int	_stdcall DC_PmuRead(int card_num,DWORD offset,DWORD *data);
//
//
//DCLIB_API 	int	_stdcall DC_PmuInit(int card_num);
//
//DCLIB_API 	int	_stdcall DC_PmuSetPwr(int card_num,int p_ch,float volt,float cut_A);
//DCLIB_API 	int	_stdcall DC_PmuSetPwrSw(int card_num,int p_ch,int hl_off);
//DCLIB_API 	int	_stdcall DC_PmuSetGndSw(int card_num,int onoff);
//
//DCLIB_API 	int	_stdcall DC_PmuDoPwrMon(int card_num,int onoff,DWORD src_load_flags);	// power monitor enable
//
//DCLIB_API 	int	_stdcall DC_PmuGetVolt(int card_num,int p_ch,float *volt);
//DCLIB_API 	int	_stdcall DC_PmuGetCur(int card_num,int p_ch,float *cur_mA_uA,int *unit_hl);
//DCLIB_API 	int	_stdcall DC_PmuGetCut(int card_num,DWORD *status);
//
//DCLIB_API 	int	_stdcall DC_PmuSetLedCur(int card_num,float cur_mA);
//DCLIB_API 	int	_stdcall DC_PmuGetLedVolt(int card_num,float *volt);
//DCLIB_API 	int	_stdcall DC_PmuGetLedCur(int card_num,float *cur_mA);
//
////
//// open/short & leakage test
////
//
//DCLIB_API 	int _stdcall DC_PmuSetIoSw(int card_num,int dc_normal);
//DCLIB_API 	int _stdcall DC_PmuSetTimes(int card_num,float us_discharge,float us_charge,float us_measure);
//DCLIB_API 	int _stdcall DC_PmuSetSrc(int card_num,float volt, float cur_mA);
//DCLIB_API 	int _stdcall DC_PmuSetClrPins(int card_num);
//
//DCLIB_API 	int _stdcall DC_PmuSetEnvPins(int card_num,int pin_s, int pin_e); 
//DCLIB_API 	int _stdcall DC_PmuSetDestPins(int card_num,int pin_s, int pin_e); 
//DCLIB_API 	int _stdcall DC_PmuSetDestPinState(int card_num,int state); 
//// DC test시에 참여 하는 핀은 이 함수로 지정된 핀들이다. 
//// state : 0 : off, 1 : PMU SRC, 2 : GND, 3 : GND_SINK 
//
//DCLIB_API 	int _stdcall DC_PmuCheckCur(int card_num,int src_sink,float ref_min, float ref_max);
//DCLIB_API 	int _stdcall DC_PmuCheckVolt(int card_num,float ref_min,float ref_max);
//DCLIB_API 	int _stdcall DC_PmuCheckCap(int card_num,float us_delay,float ref_min,float ref_max,float v_diff);
//DCLIB_API 	int _stdcall DC_PmuDoTest(int card_num);
//
//// val : 측정 값 돌려 받는 변수이다. 
//// result 
//// 0 : OK, 1 : short, 1 : open, 2 : v_diff small (Cap check mode시에 시용)
//DCLIB_API 	int _stdcall DC_PmuGetResult(int card_num,int pin,float *val,int *result);
//
////works : 
//// 0 : calibrate, 1 : save cal, 2 : load cal, else undefined
//DCLIB_API 	int _stdcall DC_PmuCalibrate(int card_num,int works);
//
////
////dest : 
////0 : power LC
////1 : power NC,LED cur , 
////2 : DC leakage sink, 
////3 : DC leakage source
////
//DCLIB_API 	int _stdcall DC_PmuCalOffset(int card_num,int *numbers,int dest,int init);
//
//// set cal data 
//DCLIB_API 	int _stdcall DC_PmuSetCal(int card_num,int src,int *cal);
//
//// get cal data 
//DCLIB_API 	int _stdcall DC_PmuGetCal(int card_num,int src,int *cal);
//
//// config PMU board
//DCLIB_API 	int _stdcall DC_PmuProg(int card_num,void *report, char *filename);

//
// I2C 핸들을 관리하는 함수
//

DCLIB_API   int _stdcall DC_GetMipiHandle(int card_num, int channel, HANDLE *pHandle);
DCLIB_API   int _stdcall DC_ReleaseMipiHandle(int card_num, int channel, HANDLE hHandle);

// 
// MIPI 보드 IOMAP을 억세스 하는 API
//

//DCLIB_API   int _stdcall MIPI_Write(int card_num, int channel, BYTE bAddr, BYTE bData);
//DCLIB_API   int _stdcall MIPI_Read(int card_num, int channel, BYTE bAddr, BYTE *pData);
//
//DCLIB_API   int _stdcall MIPI_SetGpio(int card_num, int channel, BYTE bGpioOE, BYTE bGpio);
//DCLIB_API   int _stdcall MIPI_GetGpio(int card_num, int channel, BYTE bGpioOE, BYTE *pGpio);
//
//DCLIB_API   int _stdcall MIPI_ResetExternal(int card_num, int channel, int iReset);
//DCLIB_API   int _stdcall MIPI_SelVolt(int card_num, int channel, int iVioVolt, int iVrefVolt);
//DCLIB_API   int _stdcall MIPI_GetSpiEnable(int card_num, int channel, int *pSpiEnable);
//
//DCLIB_API   int _stdcall MIPI_SetParallel(int card_num, int channel, int iVC, int iDT, 
//                                          int iParEn, int iBits, int iTestEn, int iWidth, int iHeight);
//
//DCLIB_API   int _stdcall MIPI_SetReset(int card_num, int channel, int iReset);
//
//DCLIB_API   int _stdcall MIPI_SetMipiControl(int card_num, int channel, int iVc, int iDt, int i8b9b, int iLane);
//
//DCLIB_API   int _stdcall MIPI_GetError(int card_num, int channel, int *pError);
//DCLIB_API   int _stdcall MIPI_ClearError(int card_num, int channel, bool bClrStatus, bool bClrTotalErrCount);
//DCLIB_API   int _stdcall MIPI_GetTotalErrCount(int card_num, int channel, int *pEcc1, int *pEcc2, int *pCrc);
//
//DCLIB_API   int _stdcall MIPI_GetVersion(int card_num, int channel, int *pCompileVersion, int *pChipID);
//
#ifdef __cplusplus
}
#endif

#endif

