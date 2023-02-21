#ifndef __DC_LIB_DEF_H_____
#define __DC_LIB_DEF_H_____

#ifdef __cplusplus
extern "C" {
#endif



#define		CAP_BASE_ERROR_START	0x0100
#define		CAP_CHAN_ERROR_START	0x0200
#define		CAP_CARD_ERROR_START	0x0300
#define		CAP_LIB_ERROR_START		0x0400
#define		DCLIB_ERROR_START		0x0500
#define		DDRAW_ERROR_START		0x0800
#define		HSIO_ERROR_START		0x0900


// error code

enum DC{
	DC_ERR_SUCCESS				= 0,

	CAP_BASE_DEVICE_OPEN_ERROR	= CAP_BASE_ERROR_START,	// NO
	CAP_BASE_NO_HANDLE,									// CBase
	CAP_BASE_DEVICE_NOT_OPENED,
	CAP_BASE_DEVICE_CANT_CLOSE,
	CAP_BASE_MUTEX_CANT_CREATE,
	CAP_BASE_MUTEX_WAIT_ERROR,
	CAP_BASE_MUTEX_RELEASE_ERROR,

	CAP_CARD_CHANNEL_OVERFLOW	= CAP_CARD_ERROR_START,	// NO
	DC_ERR_I2C_RUNNING,									// NO i2c is already running
	DC_ERR_CHIP_VERSION_INCORECT,						// capCard
	DC_ERR_FLASH_NULL,									// capCard
	DC_ERR_EEP_NULL,									// capCard

	DC_ERR_CHANNEL_INVALID		= CAP_LIB_ERROR_START,	// capLib
	DC_ERR_ALREADY_OPENED,								// capChan
	DC_ERR_OPEN_BITS_PER_CLK_INVALID,					// capChan
	DC_ERR_POSITION_INVALID,							// NO
	DC_ERR_FRAMES_INVALID,								// capChan
	DC_ERR_FRAME_SIZE_INVALID,							// capChan
	DC_ERR_FRAME_BUFFER_ALLOC_FAILS,					// capChan
	DC_ERR_START_FAILS,									// capChan

	DC_ERR_ALREADY_PENDING,								// capChan
	DC_ERR_NOT_PENDING,									// capChan
	DC_ERR_CARD_NUMBER_INVALID,							// capLib
	DC_ERR_CHANNEL_NOT_OPENED,							// capChan
	DC_ERR_ALREADY_STARTED,								// capChan
	DC_ERR_NOT_STARTED,									// capChan
	DC_ERR_BUFFER_OVERFLOW,								// capChan
	DC_ERR_FRAME_OVER_RUN,								// capChan

	DC_ERR_DMA_TRANSFER_FAILS,							// capChan
	DC_ERR_NO_GET_FRAME_PENDING,						// NO
	DC_ERR_LUT_INDEX_RANGE_INVALID,						// capChan


	DC_ERR_ALREADY_INITIALIZED	 = DCLIB_ERROR_START,	// NO
	DC_ERR_NOT_INITIALIZED,								// dclib
	DC_ERR_NO_HANDLE,									// NO
	DC_ERR_NO_DEVICE,									// dclib
	DC_ERR_INVALID_PARAMETER,							// dclib

	// display open errors
	DC_ERR_DISPLAY_OPEN_FAILS	= DDRAW_ERROR_START,	// NO
	DISP_OPEN_ALREADY_OPENED,							// CSurface
	DISP_OPEN_CREATE_EX_FAIL,							// CSurface
	DISP_OPEN_SET_COOPERATIVELEVEL_FAIL,				// CSurface
	DISP_OPEN_CREATE_SURFACE_FAIL,						// CSurface
	DISP_OPEN_CREATE_OVERLAY_FAIL,						// CSurface
	DISP_OPEN_CREATE_CLIPPER_FAIL,						// CSurface
	DISP_OPEN_CLIPPER_SET_HANDLE_FAIL,					// CSurface
	DISP_OPEN_SET_CLIPPER_FAIL,							// CSurface
	DISP_NOT_OPENED,

	// HSIO error
	DC_ERR_HSIO_READ_TIMEOUT							= HSIO_ERROR_START,
	DC_ERR_HSIO_STA_LINK_NOK,
	DC_ERR_HSIO_STA_TGT_LOOP

};

#define	BYTE	unsigned char
#define WORD	unsigned short
#define DWORD	unsigned long

__declspec(dllexport ) int _stdcall DC_Init();
__declspec(dllexport ) int _stdcall DC_End();

__declspec(dllexport ) int _stdcall DC_GetMaxCards();
__declspec(dllexport ) int _stdcall DC_GetVersion(int card_num,DWORD *DllVer,DWORD *DrvVer,DWORD *ChipVer);

__declspec(dllexport ) int _stdcall DC_GetMaxChannels(int card_num);
__declspec(dllexport ) int _stdcall DC_WriteReg(int card_num,DWORD offset,DWORD data);
__declspec(dllexport ) int _stdcall DC_ReadReg(int card_num,DWORD offset,DWORD *data);

__declspec(dllexport ) int _stdcall DC_GpioReadIn(int card_num,DWORD *data);
__declspec(dllexport ) int _stdcall DC_GpioWriteOut(int card_num,DWORD data);
__declspec(dllexport ) int _stdcall DC_GpioWriteOE(int card_num,DWORD data);

__declspec(dllexport ) int _stdcall DC_Open(int card_num,int channel,int Height,int Width,int Frames,int BitsPerClk);
__declspec(dllexport ) int _stdcall DC_Close(int card_num,int channel);

__declspec(dllexport ) int _stdcall DC_Start(int card_num,int channel);
__declspec(dllexport ) int _stdcall DC_Stop(int card_num,int channel);

__declspec(dllexport ) int _stdcall DC_GetFrame(int card_num,int channel, int blocked,BYTE **buf,WORD *length,DWORD *eof_length);
__declspec(dllexport ) int _stdcall DC_CancelGetFrame(int card_num,int channel);

__declspec(dllexport ) int _stdcall DC_SetCapInfo(int card_num,int channel,int HBP, int VBP, int ClkEdgeHigh, int HSyncEdgeHigh, int VSyncEdgeHigh, int LineArea, int Input10Bits,int SyncValidEn);
__declspec(dllexport ) int _stdcall DC_SetMipiInfo(int card_num, int channel, int VirtualChannel,int DataType);
__declspec(dllexport ) int _stdcall DC_SetLookupTable(int card_num,int channel,int index, WORD value);


// PLL control functions
__declspec(dllexport ) int _stdcall DC_SetClkOutFreq(int card_num,int clk_o_number, int ref_number);
__declspec(dllexport ) int _stdcall DC_SetClkOutFreq1(int card_num,int clk_o_number, int ref_number,int mode);


__declspec(dllexport ) int _stdcall DC_CheckCamLines(int card_num,int channel,DWORD width_ms);
__declspec(dllexport ) int _stdcall DC_GetCamLineToggleTimes(int card_num,int channel,int index,DWORD *val);

// I2C control functions
__declspec(dllexport ) void _stdcall DC_I2cInit(int card_num,int channel,int DelayCnt,int rst_active_pol);
__declspec(dllexport ) void _stdcall DC_I2cRst(int card_num,int channel);
__declspec(dllexport ) void _stdcall DC_I2cRst1(int card_num,int channel,int delay_ms);
__declspec(dllexport ) int	_stdcall DC_I2cWrite(int card_num,int channel,BYTE data);
__declspec(dllexport ) int	_stdcall DC_I2cRead(int card_num,int channel,int hilo);
__declspec(dllexport ) int	_stdcall DC_I2cStart(int card_num,int channel);
__declspec(dllexport ) void _stdcall DC_I2cStop(int card_num,int channel);

// new I2C functions
__declspec(dllexport ) int _stdcall DC_I2cClkStretchEn(int card_num,int channel,int en);
__declspec(dllexport ) 	int	_stdcall DC_SoftI2cWrite(int card_num, int channel,int length, BYTE start,BYTE last, BYTE *buf);
__declspec(dllexport ) 	int	_stdcall DC_SoftI2cRead(int card_num, int channel,int length, BYTE last, BYTE *buf);


// EEPROM program
__declspec(dllexport ) int _stdcall DC_Prog(int card_num,void *report, char *filename);
__declspec(dllexport ) int _stdcall DC_MipiProg(int card_num,void *report, char *filename);

#ifdef __DDRAW_DISABLE__
#else

// overlay display functions
__declspec(dllexport ) int	_stdcall DC_DispOpen(HWND hWnd,int width,int height,int pixelBytes);
__declspec(dllexport ) int	_stdcall DC_DispClose();
__declspec(dllexport ) void _stdcall DC_SetKeyColor(DWORD keycolor);
__declspec(dllexport ) DWORD _stdcall DC_GetKeyColor();
__declspec(dllexport ) void _stdcall DC_SetFourCC(DWORD dwFourCC);
__declspec(dllexport ) DWORD _stdcall DC_GetFourCC();
__declspec(dllexport ) void _stdcall DC_SetShowRect(RECT *sr,RECT *dr);
__declspec(dllexport ) int _stdcall DC_Update(BYTE *buf,int width,int height,int pixelbytes,int flip);	// source parameters

#endif

// I2C, SPI ÇÔ¼ö
//

//
// external I/O functions
//

__declspec(dllexport ) 	float _stdcall DC_SetSpiFreq(int card_num, float freq_mhz);
__declspec(dllexport ) 	int _stdcall DC_SetSpiLatency(int card_num, int lat);	// 0 - 7

__declspec(dllexport ) 	int	_stdcall DC_SpiWrite(int card_num, int length, BYTE last, BYTE *buf);
__declspec(dllexport ) 	int	_stdcall DC_SpiRead(int card_num, int length, BYTE last, BYTE *buf);


__declspec(dllexport ) 	float _stdcall DC_SetHwI2cFreq(int card_num, float freq_khz);
__declspec(dllexport ) 	int	_stdcall DC_HwI2cWrite(int card_num, int length, BYTE start,BYTE last, BYTE *buf);
__declspec(dllexport ) 	int	_stdcall DC_HwI2cRead(int card_num, int length, BYTE last, BYTE *buf);

__declspec(dllexport ) 	float _stdcall DC_SetClkFreq(int card_num, float freq);

__declspec(dllexport ) 	int	_stdcall DC_SetSpiI2cMode(int card_num, int si);
__declspec(dllexport ) 	int	_stdcall DC_GetSpiI2cMode(int card_num);


//
// MIPI board update functions
//
//__declspec(dllexport ) int _stdcall DC_ProgIoBoard(int card_num,void *report, char *filename);

__declspec(dllexport )	int	_stdcall DC_CheckMipiFlash(int card_num);
__declspec(dllexport )	int	_stdcall DC_DbgRead(int card_num,int target, int length, BYTE *buf);
__declspec(dllexport )	char* _stdcall DC_GetErrorMsg(int error);




//
//unused functions
//

__declspec(dllexport ) 	int	_stdcall DC_PmWrite(int card_num,int channel,DWORD offset,DWORD data);
__declspec(dllexport ) 	int	_stdcall DC_PmRead(int card_num,int channel,DWORD offset,DWORD *data);

__declspec(dllexport ) 	int	_stdcall DC_PmOsEnable(int card_num,int channel,int en);

__declspec(dllexport ) 	int	_stdcall DC_PmInit(int card_num,int channel);
__declspec(dllexport ) 	int	_stdcall DC_PmCalibration(int card_num,int channel);	

__declspec(dllexport ) 	int	_stdcall DC_PmSetPowerSwitch(int card_num,int channel,int onoff);

__declspec(dllexport ) 	int	_stdcall DC_PmSetI2cTerm(int card_num,int channel,int mode);
__declspec(dllexport ) 	int	_stdcall DC_PmSetCapEdge(int card_num,int channel,int hl);
__declspec(dllexport ) 	int	_stdcall DC_PmSetTestPatternEn(int card_num,int channel,int onoff);
__declspec(dllexport ) 	int	_stdcall DC_PmSetIoPower(int card_num,int channel,float volt);
__declspec(dllexport ) 	int	_stdcall DC_PmSetSigClk(int card_num,int channel,int sig_en,int clk_en);

__declspec(dllexport ) 	int	_stdcall DC_PmSetOe(int card_num,int channel,int bit_start,DWORD val);
__declspec(dllexport ) 	int	_stdcall DC_PmSetOut(int card_num,int channel,int bit_start,DWORD val);
__declspec(dllexport ) 	int	_stdcall DC_PmGetInput(int card_num,int channel,int bit_start,DWORD *val);

__declspec(dllexport ) 	int	_stdcall DC_PmSetOsPower(int card_num,int channel,float volt);

__declspec(dllexport ) 	int	_stdcall DC_PmGetOsLG(int card_num,int channel,int line, int delay,int cur_hl ,float *data1,float *data2);
__declspec(dllexport ) 	int	_stdcall DC_PmGetOsLP(int card_num,int channel,int line, int delay,int cur_hl ,float *data1,float *data2);
__declspec(dllexport ) 	int	_stdcall DC_PmGetOsLL(int card_num,int channel,int line0,int line1,int cur_hl,float *volt);

__declspec(dllexport ) 	int	_stdcall DC_PmSetPower(int card_num,int channel,int line,float volt,float cur);
__declspec(dllexport ) 	int	_stdcall DC_PmGetPower(int card_num,int channel,int line,float *volt,float *cur_h,float *cur_l);

__declspec(dllexport ) 	int	_stdcall DC_PmSetPowerShortCur(int card_num,int channel,int line,float cur);
__declspec(dllexport ) 	int	_stdcall DC_PmGetPowerShortStatus(int card_num,int channel,DWORD *status);
__declspec(dllexport ) 	int	_stdcall DC_PmGetVersion(int card_num,int channel,DWORD *ver);






#ifdef __cplusplus
}
#endif

#endif
