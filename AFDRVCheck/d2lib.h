
#ifndef __D2_LIB_H_____
#define __D2_LIB_H_____


#ifdef __DCLIB_EXPORT__
	#define	DCLIB_API	__declspec(dllexport)
#else
	#define	DCLIB_API	__declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------------------
// Error Code Definition

#define		D2_ERR_START						0x0000
#define		D2_ERR_COMMON_START					0x0100
#define		D2_ERR_LIB_START					0x0200
#define		D2_ERR_BASE_START					0x0300
#define		D2_ERR_CARD_START					0x0400
#define		D2_ERR_CHANNEL_START				0x0500
#define		D2_ERR_WINBOND_START				0x0600
#define		D2_ERR_CAMIOCFG_START				0x0700
#define		D2_ERR_CAMIOMIPI_START				0x0800
#define		D2_ERR_I2C_START					0x0900
#define		D2_ERR_SPI_START					0x0A00


//<< 자동 생성

enum D2 
{
    D2_ERR_SUCCESS								= D2_ERR_START,				// 0x00000000
    D2_ERR_COMMON_NO_DEVICE,                                                // 0x00000001
    D2_ERR_COMMON_NOT_INITIALIZED,                                          // 0x00000002
    D2_ERR_COMMON_ALREADY_INIT,                                             // 0x00000003
    D2_ERR_COMMON_INVALID_PARAMETER,                                        // 0x00000004
    D2_ERR_COMMON_UNSUCCESSFUL,                                             // 0x00000005
    D2_ERR_COMMON_INSUFFICIENT_RESOURCE,                                    // 0x00000006
    D2_ERR_COMMON_INVALID_HANDLE,                                           // 0x00000007
    D2_ERR_COMMON_NOT_SUPPORTED,                                            // 0x00000008
    D2_ERR_LIB_CARD_NUMBER_INVALID              = D2_ERR_LIB_START,         // 0x00000200
    D2_ERR_LIB_CHANNEL_INVALID,                                             // 0x00000201
    D2_ERR_BASE_DEVICE_OPEN_ERROR               = D2_ERR_BASE_START,        // 0x00000300
    D2_ERR_BASE_NO_HANDLE,                                                  // 0x00000301
    D2_ERR_BASE_DEVICE_NOT_OPENED,                                          // 0x00000302
    D2_ERR_BASE_DEVICE_CANT_CLOSE,                                          // 0x00000303
    D2_ERR_BASE_MUTEX_CANT_CREATE,                                          // 0x00000304
    D2_ERR_BASE_MUTEX_WAIT_ERROR,                                           // 0x00000305
    D2_ERR_BASE_MUTEX_RELEASE_ERROR,                                        // 0x00000306
    D2_ERR_BASE_BURST_LENGTH_INVALID,                                       // 0x00000307
    D2_ERR_CARD_FLASH_NULL                      = D2_ERR_CARD_START,        // 0x00000400
    D2_ERR_CARD_FILE_NAME_NULL,                                             // 0x00000401
    D2_ERR_CARD_CHIP_VERSION_INCORECT,                                      // 0x00000402
    D2_ERR_CHANNEL_OPEN_BITS_PER_CLK_INVALID    = D2_ERR_CHANNEL_START,     // 0x00000500
    D2_ERR_CHANNEL_ALREADY_OPENED,                                          // 0x00000501
    D2_ERR_CHANNEL_FRAMES_INVALID,                                          // 0x00000502
    D2_ERR_CHANNEL_FRAME_SIZE_INVALID,                                      // 0x00000503
    D2_ERR_CHANNEL_FRAME_BUFFER_ALLOC_FAILS,                                // 0x00000504
    D2_ERR_CHANNEL_NOT_OPENED,                                              // 0x00000505
    D2_ERR_CHANNEL_ALREADY_PENDING,                                         // 0x00000506
    D2_ERR_CHANNEL_BUFFER_OVERFLOW,                                         // 0x00000507
    D2_ERR_CHANNEL_FRAME_OVER_RUN,                                          // 0x00000508
    D2_ERR_CHANNEL_DMA_TRANSFER_FAILS,                                      // 0x00000509
    D2_ERR_CHANNEL_NOT_PENDING,                                             // 0x0000050A
    D2_ERR_CHANNEL_START_FAILS,                                             // 0x0000050B
    D2_ERR_CHANNEL_ALREADY_STARTED,                                         // 0x0000050C
    D2_ERR_CHANNEL_NOT_STARTED,                                             // 0x0000050D
    D2_ERR_CHANNEL_MIPI_NOT_LINKED,                                         // 0x0000050E
    D2_ERR_WINBOND_WAIT_TIMEOUT                 = D2_ERR_WINBOND_START,     // 0x00000600
    D2_ERR_WINBOND_WRITE_RETRY_TIMEOUT,                                     // 0x00000601
    D2_ERR_WINBOND_UNSUPPORT_TYPE,                                          // 0x00000602
    D2_ERR_WINBOND_MISMATCH_DEVICE_ID,                                      // 0x00000603
    D2_ERR_WINBOND_CANT_OPEN_FILE,                                          // 0x00000604
    D2_ERR_WINBOND_VERIFY_ERROR,                                            // 0x00000605
    D2_ERR_WINBOND_SECURE_ERROR,                                            // 0x00000606
    D2_ERR_CAMIOCFG_INVALID_INDEX               = D2_ERR_CAMIOCFG_START,    // 0x00000700
    D2_ERR_CAMIOMIPI_INVALID_INDEX              = D2_ERR_CAMIOMIPI_START,   // 0x00000800
    D2_ERR_I2C_LENGTH_ZERO                      = D2_ERR_I2C_START,         // 0x00000900
    D2_ERR_I2C_LENGTH_OVER,                                                 // 0x00000901
    D2_ERR_I2C_CLR_RX_BUFFER_TIMEOUT,                                       // 0x00000902
    D2_ERR_I2C_CLR_TX_BUFFER_TIMEOUT,                                       // 0x00000903
    D2_ERR_I2C_I2C_ACK,                                                     // 0x00000904
    D2_ERR_I2C_I2C_TIMEOUT,                                                 // 0x00000905
    D2_ERR_I2C_RD_TIMEOUT,                                                  // 0x00000906
    D2_ERR_SPI_LENGTH_ZERO                      = D2_ERR_SPI_START,         // 0x00000A00
    D2_ERR_SPI_LENGTH_OVER,                                                 // 0x00000A01
    D2_ERR_SPI_CLR_RX_BUFFER_TIMEOUT,                                       // 0x00000A02
    D2_ERR_SPI_CLR_TX_BUFFER_TIMEOUT,                                       // 0x00000A03
    D2_ERR_SPI_RD_TIMEOUT,                                                  // 0x00000A04
};

//>> 자동 생성

#define SCANNER_CONFIG_CATEGORY_LIGHTING		0x020000
#define SCANNER_CONFIG_CATEGORY_TRIGGER			0x030000

enum e_config_index
{
	CONFIG_LIGHTING_OPERATION					= SCANNER_CONFIG_CATEGORY_LIGHTING,
	CONFIG_LIGHTING_CURRENT,
	CONFIG_LIGHTING_STROBE_DELAY,
	CONFIG_LIGHTING_STROBE_WIDTH,
	CONFIG_TRIGGER_ENABLE						= SCANNER_CONFIG_CATEGORY_TRIGGER,
	CONFIG_TRIGGER_EDGE,
	CONFIG_TRIGGER_HIRES,
	CONFIG_TRIGGER_DELAY,
	CONFIG_TRIGGER_SOFT_TRIGGER
};

// Firmware File Type
enum FIRMWARE_TYPE_INDEX
{
	FIRMWARE_TYPE_HEX,
	FIRMWARE_TYPE_BIN
};

enum CONFIG_LIGHTING_OP_INDEX
{
	LIGHTING_OFF,
	LIGHTING_ON,
	LIGHTING_STROBE
};

enum FREQ_MODE
{
	FREQ_MODE_FREQ = 0,
	FREQ_MODE_FLOAT,
	FREQ_MODE_HIGH,
	FREQ_MODE_LOW
};
//-------------------------------------------------------------------------------------------------------------------------------
// Functions



//
// Framer Function
//

/*! 
 *	\fn		D2_Init
 *	\brief	시스템의 FrameGrabber를 검색해서 객체들을 생성하고 초기화 한다.
 *	\return	객체를 할당하는데 실패한다면 D2_ERR_INSUFFICIENT_RESOURCE를 리턴.
 *	\return	시스템에 설치된 Card가 없다면 D2_ERR_NO_DEVICE를 리턴.
 */
DCLIB_API int _stdcall D2_Init();

/*! 
 *	\fn		D2_End
 *	\brief	생성된 객체들을 모두 해제한다.
 *	\return	생성된 객체가 없다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_End();

/*! 
 *	\fn		D2_GetVersion
 *	\brief	지정한 Card의 버전 정보들을 얻는다.
 *	\param	iCard				Frame Grabber 번호
 *	\param	pDllVer				API 버전을 얻어올 포인터 변수
 *	\param	pDrvVer				Driver 버전을 얻어올 포인터 변수
 *	\param	pChipVer			FrameGrabber 버전을 얻어올 포인터 변수
 *	\return	생성된 객체가 없다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_GetVersion(int iCard, DWORD *pDllVer, DWORD *pDrvVer, DWORD *pChipVer);

/*! 
 *	\fn		D2_GetSysInfo
 *	\brief	Card와 Main Board 간의 연결 정보를 얻는다.
 *	\param	iCard				Frame Grabber 번호
 *	\param	pLanes				PCI-Express Lanes 수
 *	\param	pSpeed				PCI-Express Generation 수
 *	\param	pMaxPayload			Max Payload Size
 *	\param	pMaxReadReq			Max Read Request Size
 *	\return	생성된 객체가 없다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_GetSysInfo(int iCard, int *pLanes, int *pSpeed, int *pMaxPayload, int *pMaxReadReq);

/*! 
 *	\fn		D2_GetMaxCards
 *	\brief	시스템에서 검색된 Frame Grabber 갯수를 리턴한다.
 *	\return	시스템에 설치된 Card의 갯수를 리턴
 */
DCLIB_API int _stdcall D2_GetMaxCards();
/*! 
 *	\fn		D2_GetMaxChannels
 *	\brief	지정한 Device의 Channel 갯수를 리턴한다.
 *	\param	card_num				Frame Grabber 번호
 *	\return	지정된 카드의 채널 갯수
 */
DCLIB_API int _stdcall D2_GetMaxChannels(int iCard);

/*! 
 *	\fn		D2_Open
 *	\brief	지정한 Frame 정보를 세트하고 Frame 버퍼를 할당한다.
 *	\param	card_num				Card 번호
 *	\param	channel					channel 번호
 *	\param	iHeight					Frame의 높이
 *	\param	iWidthBytes				한줄에 필요한 Byte 수
 *	\param	iFrameNum				할당할 Frame 갯수
 *	\param	iBitPerPixel			클럭당 비트수
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_Open(int iCard,int channel, int Height, int iWidthBytes, int Frames, int BitsPerClk);
/*! 
 *	\fn		D2_Close
 *	\brief	Frame 버퍼를 해제한다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 *	\return	BitsPerClk가 지정된 값과 다르다면 D2_ERR_OPEN_BITS_PER_CLK_INVALID를 리턴;
 *	\return	이미 Open되어 있다면 D2_ERR_ALREADY_OPENED를 리턴
 *	\return	Frame 버퍼 수가 너무 많거나 적다면 D2_ERR_FRAMES_INVALID 리턴
 *	\return	Frame Frame Size가 0이거나 4의 배수가 아니라면 D2_ERR_FRAME_SIZE_INVALID 리턴
  */
DCLIB_API int _stdcall D2_Close(int iCard, int channel);

/*! 
 *	\fn		D2_Start
 *	\brief	Frame Capture를 시작
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_Start(int iCard, int channel);
/*! 
 *	\fn		D2_Stop
 *	\brief	Frame Capture를 중단
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_Stop(int iCard,int channel);

/*! 
 *	\fn		D2_GetFrame
 *	\brief	Frame Grabber로 부터 한 Frame의 이미지 데이터를 얻어온다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	blocked					1이면 이미지 데이터를 얻어올 때 까지 block되어 기다린다.
 *	\param	buf						얻어온 이미지 데이터 포인터
 *	\param	length					얻어온 이미지의 크기.
 *	\param	eof_length				eof 이벤트가 발생한 이미지의 크기
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_GetFrame(int iCard,int channel, int blocked, BYTE **buf, WORD *length, DWORD *eof_length);

/*! 
 *	\fn		D2_GetFrameWait
 *	\brief	Frame Grabber로 부터 최신 Frame 데이터를 얻어온다.
 *			Frame Data가 들어올 때까지 이 함수는 Block되고 D2_CancelGetFrame()을 호출하면 리턴된다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_GetFrameWait(int iCard, int channel, BYTE **buf);

/*! 
 *	\fn		D2_GetFrame
 *	\brief	D2_GetFrame이 block 되어 있을 경우 block을 해제하고 바로 리턴 시킨다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_CancelGetFrame(int iCard,int channel);

//
// Framer Information
//

/*! 
 *	\fn		D2_SetCapInfo
 *	\brief	Capture하는데 필요한 옵션을 설정.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	iStartH					수평 동기 신호를 검출한 검출한 시점의 클락 인덱스를 0으로 하고, 
 *									이후에 클락이 진행 함에 따라서 증가하게 된다. 이때에 수평의 라인을 시작하는 인덱스 값이다 .
 *	\param	iStartV					수직 동기 신호가 검출된 최초의 라인 인덱스를 0이라 하면 이후에 매 수평 동기 신호가 
 *									검출 될 때마다 라인 인덱스가 증가 하게 된다. 이 때에 화면의 수평라인 시작 인덱스를 정하는 파라미터이다.
 *	\param	ClkEdgeHigh				Camera에서 나오는 클락의 어떠한 에지에서 픽셀 데이터를 잡을 것인가를 정한다. 1 : 상승 에지, 0 : 하강 에지.
 *	\param	HSyncEdgeHigh			수평동기신호에서 어떠한 에지에 기준을 두는가를 정한다. 1 : 상승 에지, 0 : 하강 에지.
 *	\param	VSyncEdgeHigh			수직동기신호에서 어떠한 에지에 기준을 두는가를 정한다. 1 : 상승 에지, 0 : 하강 에지.
 *	\param	SyncValidEn				수평동기 신호를 동기 신호로 사용하는 것이 아니라 Active구간에서 
 *									전송을 해야 할 Valid신호로 사용 여부를 결정하는 입력이다. 
 *									1이면 Valid신호로 사용하고 0이면 동기 신호로 사용한다
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_SetCapInfo(int iCard,int channel, int iStartH, int iStartV, int ClkEdgeHigh, int HSyncEdgeHigh, int VSyncEdgeHigh, int SyncValidEn);

/*! 
 *	\fn		D2_SetMipiInfo
 *	\brief	MIPI 설정. DT는 4개까지, VC는 1개 설정이 가능
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	VirtualChannel			MIPI packet에서 원하는 가상 채널을 지정한다. 보통 0을 사용한다. 
 *	\param	DataType				MIPI packet에서 받기를 원하는 데이타 타입을 지정한다.
 *	\param	DataType1				MIPI packet에서 받기를 원하는 데이타 타입을 지정한다
 *	\param	DataType1				MIPI packet에서 받기를 원하는 데이타 타입을 지정한다
 *	\param	DataType1				MIPI packet에서 받기를 원하는 데이타 타입을 지정한다
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_SetMipiInfo(int iCard, int channel, int iVirtualChannel, int iDataType, int iDataType1, int iDataType2,int iDataType3);

/*! 
 *	\fn		D2_SetMipiDsiInfo
 *	\brief	DSI MIPI Capture를 위한 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	dsi_enable				DSI MIPI Capture를 Enable. 
 *	\param	dsi_video_or_command	DSI MIPI Caputre Option.
 *	\param	dsi_hsync_gen			DSI MIPI Caputre Option.
 *	\param	dsi_vsync_gen			DSI MIPI Caputre Option.
 *	\param	lanes					DSI MIPI Lane 수
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_SetMipiDsiInfo(int iCard, int channel, int dsi_enable,int dsi_video_or_command,int dsi_hsync_gen,int dsi_vsync_gen,int lanes);

/*! 
 *	\fn		D2_GetCapMipiError
 *	\brief	Framer 에서 발생한 MIPI Capture 에러 누적 갯수를 읽어 온다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	pEcc1					ECC1 에러를 얻을 포인터 변수
 *	\param	pEcc2					ECC2 에러를 얻을 포인터 변수
 *	\param	pCrc					CRC 에러를 얻을 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API int _stdcall D2_GetCapMipiError(int iCard, int iChannel, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		D2_ClrCapMipiError
 *	\brief	Framer 에서 발생한 누적 에러를 clear 한다
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_ClrCapMipiError(int iCard, int iChannel);

/*! 
 *	\fn		D2_SetCapCsiTestCamEn
 *	\brief	Framer에서 Test Pattern을 발생시키고 이를 Capture하도록 설정.
 *			Test Pattern Frame은 Open시 설정된 정보에 맞게 설정된다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_SetCapCsiTestCamEn(int iCard, int channel, int enable);

/*! 
 *	\fn		D2_CheckCamLines
 *	\brief	주어진 시간 동안 모든 라인의 토글 횟수를 동시에 측정한다. 
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	width_ms				측정할 ms 단위 시간 값
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_CheckCamLines(int iCard,int channel, DWORD width_ms);
/*! 
 *	\fn		D2_GetCamLineToggleTimes
 *	\brief	측정이 된 카메라의 토글 횟수를 얻어온다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	index					얻어올 Camera Line Index
 *										[11]: Vertical Input line
 *										[10]: Horizontal Input line
 *										[9:0]: Camera Data[9:0] lines
 *	\param	val						토글 횟수를 얻어올 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API int _stdcall D2_GetCamLineToggleTimes(int iCard,int channel, int index, DWORD *val);

//
// Link API
//

/*! 
 *	\fn		D2_GetLinkStatus
 *	\brief	Frame Grabber와 MIPI Board 사이의 line 상태를 얻어옴.
 *	\param	card_num				Frame Grabber 번호
 *	\param	pClkLocked				Clock Locked 상태를 얻어올 포인터 변수
 *	\param	pPhaseLocked			Phase Locked 상태를 얻어올 포인터 변수
 *	\param	pLinked					연결 상태를 얻어올 포인터 변수
 *	\param	pSynced					Line이 싱크된 상태를 얻어올 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_GetLinkStatus(int iCard, int *pClkLocked, int *pPhaseLocked, int *pLinked, int *pSynced);

/*! 
 *	\fn		D2_SetLinkReset
 *	\brief	Frame Grabber와 MIPI Board 사이의 Line Sync를 Reset 한다
 *	\param	card_num				Frame Grabber 번호
 *	\param	iReset					1: Reset
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_SetLinkReset(int iCard, int iReset);

//
// Serial I/O functions
//

/*! 
 *	\fn		D2_SetSpiFreq
 *	\brief	SPI 주파수 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	freq_mhz				SPI Freq(MHz Unit)
 *	\return	설정된 주파수를 리턴
 */
DCLIB_API 	double _stdcall D2_SetSpiFreq(int iCard, int channel, double freq_mhz);

/*! 
 *	\fn		D2_SpiWrite
 *	\brief	SPI Write
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	length					전송할 데이터 길이
 *	\param	last					1이면 전송이 끝나고 CS를 High로 올린다.
 *	\param	buf						전송할 데이터
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API 	int	_stdcall D2_SpiWrite(int iCard, int channel, int length, BYTE last, BYTE *buf);

/*! 
 *	\fn		D2_SpiRead
 *	\brief	SPI Read. 함수 호출시 CS를 Low로 떨어뜨린다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	length					읽어드릴 데이터 길이
 *	\param	last					1이면 다 읽어 드린 후 CS를 High로 올린다.
 *	\param	buf						일어드릴 데이터 버퍼
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API 	int	_stdcall D2_SpiRead(int iCard, int channel, int length, BYTE last, BYTE *buf);

/*! 
 *	\fn		D2_SetI2cFreq
 *	\brief	I2C 주파수 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	freq_khz				I2C Freq(kHz Unit)
 *	\return	설정된 주파수를 리턴
 */
DCLIB_API 	double _stdcall D2_SetI2cFreq(int iCard, int channel, double freq_khz);

/*! 
 *	\fn		D2_I2cWrite
 *	\brief	I2C Write
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	length					전송할 데이터 길이
 *	\param	start					전송 시작전 I2C START issue.
 *	\param	last					전송 후 I2C STOP issue.
 *	\param	buf						전송할 데이터
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API 	int	_stdcall D2_I2cWrite(int iCard, int channel, int length, BYTE start, BYTE last, BYTE *buf);
/*! 
 *	\fn		D2_I2cRead
 *	\brief	I2C Read.
 *	\param	card_num				Frame Grabber 번호.
 *	\param	channel					연결된 channel 번호.
 *	\param	length					읽어드릴 데이터 길이.
 *	\param	last					다 읽어 드린후 I2C STOP issue.
 *	\param	buf						일어드릴 데이터 버퍼.
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API 	int	_stdcall D2_I2cRead(int iCard, int channel, int length, BYTE last, BYTE *buf);

//
// MIPI API
//

/*! 
 *	\fn		D2_SetMipiControl
 *	\brief	MIPI 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	iLanes					MIPI Lanes
 *	\param	iEnc					MIPI 8b9b encoded
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_SetMipiControl(int iCard, int iChannel, int iLanes, int iEnc);

/*! 
 *	\fn		D2_GetMipiError
 *	\brief	MIPI Board 발생한 MIPI Capture 에러 누적 갯수를 읽어 온다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	pEcc1					ECC1 에러를 얻을 포인터 변수
 *	\param	pEcc2					ECC2 에러를 얻을 포인터 변수
 *	\param	pCrc					CRC 에러를 얻을 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API int _stdcall D2_GetMipiError(int iCard, int iChannel, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		D2_ClrMipiError
 *	\brief	MIPI Board 에서 발생한 누적 에러를 clear 한다
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API int _stdcall D2_ClrMipiError(int iCard, int iChannel);


/*! 
 *	\fn		D2_SetMipiCsiTestCamEn
 *	\brief	MIPI에서 Test Pattern을 발생시키고 이를 Capture하도록 설정.
 *			Test Pattern Frame은 Open시 설정된 정보에 맞게 설정된다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	내부 객체가 생성되지 않았다면 D2_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API	int _stdcall D2_SetMipiCsiTestCamEn(int iCard, int channel, int enable);

/*! 
 *	\fn		D2_GetMipiVersion
 *	\brief	Mipi Board의 버전 정보를 얻는다.
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					Mipi Board의 채널 번호
 *	\param	pBrdVer					버전을 얻어올 포인터 변수
 *	\param	pCmpVer					Compile Date를 얻어올 포인터 변수
 *	\param	pNumChannel				채널 갯수
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API	int _stdcall D2_GetMipiVersion(int iCard, int channel, DWORD *pBrdVer, DWORD *pCmpVer, int *pNumChannel);

/*! 
 *	\fn		D2_SetMipiVref
 *	\brief	MIPI Signal 비교 전압 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	iVref					MIPI Vref Volt
 *										0: 0.5v
 *										1: 0.68v
 *										2: 0.8v
 *										3: undefined
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_SetMipiVref(int iCard, int iChannel, int iVref);

/*! 
 *	\fn		D2_SetMipiVioDac
 *	\brief	Vio 전압 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	dVio					Vio 전압(0 ~ 1.8v)
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_SetMipiVioDac(int iCard, int iChannel, double dVio);

/*! 
 *	\fn		D2_SetMipiFreq
 *	\brief	Mipi Board의 MCLK 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	iFreqMode				Clock Pin 상태 설정
 *										FREQ_MODE_FREQ: 설정된 주파수 출력		
 *										FREQ_MODE_FLOAT: 주파수 핀 상태를 float 상태로 설정
 *										FREQ_MODE_HIGH: 설정된 주파수 핀을 HIGH 상태로 설정
 *										FREQ_MODE_LOW: 설정된 주파수 핀을 LOW 상태로 설정
 *	\param	dFreq					Mipi Board 주파수
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API	int _stdcall D2_SetMipiFreq(int iCard, int iChannel, int iFreqMode, double dFreq);

/*! 
 *	\fn		D2_GpioReadIn
 *	\brief	Mipi Board의 GPIO 값 읽어오기
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	pGpio					GPIO Signal을 읽을 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API	int _stdcall D2_GpioReadIn(int iCard, int iChannel, DWORD *pGpio);

/*! 
 *	\fn		D2_GpioWriteOut
 *	\brief	Mipi Board의 GPIO 출력
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	dwGpio					GPIO Signal 출력
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API	int _stdcall D2_GpioWriteOut(int iCard, int iChannel, DWORD dwData);

/*! 
 *	\fn		D2_GpioWriteOE
 *	\brief	Mipi Board의 GPIO Output Enable을 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	dwOutEnable				bit가 1이면 Output, 0이면 Input
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API	int _stdcall D2_GpioWriteOE(int iCard, int iChannel, DWORD dwData);

//
// Smart Cam API
//

/*! 
 *	\fn		D2_SetCamConfig
 *	\brief	D2_ERR_NOT_SUPPORTED
 */
DCLIB_API   int _stdcall D2_SetCamConfig(int iCard, int iChannel, int iIndex, int iValue);

/*! 
 *	\fn		D2_GetCamConfig
 *	\brief	D2_ERR_NOT_SUPPORTED
 */
DCLIB_API   int _stdcall D2_GetCamConfig(int iCard, int iChannel, int iIndex, int *pValue);

/*! 
 *	\fn		D2_SetCamPower
 *	\brief	D2_ERR_NOT_SUPPORTED
 */
DCLIB_API   int _stdcall D2_SetCamPower(int iCard, int iChannel, int iOnOff);

/*! 
 *	\fn		D2_SetCamReset
 *	\brief	Camera Reset 핀 설정
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	iReset					1: Reset, 0: Normal
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_SetCamReset(int iCard, int iChannel, int iReset);

/*! 
 *	\fn		D2_SetCamGpio
 *	\brief	Camera에 연결된 2bit GPIO Write
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	bGpio					GPIO Signal Write
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_SetCamGpio(int iCard, int iChannel, BYTE bGpio);

/*! 
 *	\fn		D2_GetCamGpio
 *	\brief	Camera에 연결된 2bit GPIO Read
 *	\param	card_num				Frame Grabber 번호
 *	\param	channel					연결된 channel 번호
 *	\param	pGpio					GPIO Signal Read
 *	\return	내부 변수가 세트되지 않았다면 D2_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DCLIB_API   int _stdcall D2_GetCamGpio(int iCard, int iChannel, BYTE *pGpio);


/*! 
 *	\fn		DG_GetPmuHandle
 *	\brief	PMU Handle을 얻어낸다.
 *			얻어낸 PMU Handle은 pmulib를 구동하는데 사용된다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pHandle					PMU Handle을 얻기위한 포인터 변수
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API   int _stdcall D2_GetPmuHandle(int iCard, HANDLE *pHandle);


/*! 
 *	\fn		DG_ReleasePmuHandle
 *	\brief	사용이 끝난 PMU Handle을 되돌려 준다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	hHandle					PMU Handle
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DCLIB_API   int _stdcall D2_ReleasePmuHandle(int iCard, HANDLE hHandle);



/*! 
 *	\fn		D2_GetErrorMsg
 *	\brief	에러 코드에 해당하는 문자열 리턴
 *	\param	error					에러 코드
 *	\return	에러 코드에 해당하는 문자열 리턴
 */
DCLIB_API	const char* _stdcall D2_GetErrorMsg(int error);

//
// Interanl Functions
//

DCLIB_API int _stdcall D2_WriteReg(int iCard, DWORD offset, DWORD data);
DCLIB_API int _stdcall D2_ReadReg(int iCard, DWORD offset, DWORD *data);


// Channel = -1 is Card
DCLIB_API int _stdcall D2_WriteFlash(int iCard, int iChannel, PBYTE pData, int iLength);
DCLIB_API int _stdcall D2_ReadFlash(int iCard, int iChannel, PBYTE pData, int iLength);

//
// Flash program
//

DCLIB_API int _stdcall D2_Prog(int iCard,void *report, char *filename);
DCLIB_API int _stdcall D2_MipiProg(int iCard, int channel, void *report, char *filename);


#ifdef __cplusplus
}
#endif

#endif

