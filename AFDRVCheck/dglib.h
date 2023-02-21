
#ifndef __DG_LIB_H_____
#define __DG_LIB_H_____


#ifdef __DGLIB_EXPORT__
	#define	DGLIB_API	__declspec(dllexport)
#else
	#define	DGLIB_API	__declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------------------------------------------------------------
// Type definition

typedef unsigned int	HDG;

//------------------------------------------------------------------------------------------
// Error Code Definition

#define		DG_ERR_START						0x0000
#define		DG_ERR_COMMON_START					0x0100
#define		DG_ERR_LIB_START					0x0200
#define		DG_ERR_BASE_START					0x0300
#define		DG_ERR_CARD_START					0x0400
#define		DG_ERR_CHANNEL_START				0x0500
#define		DG_ERR_WINBOND_START				0x0600
#define		DG_ERR_CAMIOCFG_START				0x0700
#define		DG_ERR_CAMIOMIPI_START				0x0800
#define		DG_ERR_I2C_START					0x0900
#define		DG_ERR_SPI_START					0x0A00
#define		DG_ERR_CHANNEL_USB_START			0x0B00
#define		DG_ERR_USBBASE_START				0x0C00
#define		DG_ERR_BULKREGISTER_START			0x0D00
#define		DG_ERR_SERIALBASE_START				0x0E00
#define		DG_ERR_FRMGR_START					0x0F00
#define		DG_ERR_FRAME_START					0x1000
#define		DG_ERR_I2C_USB_START				0x1100
#define		DG_ERR_SPI_USB_START				0x1200
#define		DG_ERR_WINBOND_USB_START			0x1300
#define		DG_ERR_CARD_PCIE1_START				0x1400
#define		DG_ERR_CHANNEL_PCIE1_START			0x1500


//<< 자동 생성

enum DG 
{
    DG_ERR_SUCCESS								= DG_ERR_START,				// 0x00000000
    DG_ERR_COMMON_NO_DEVICE,                                                // 0x00000001
    DG_ERR_COMMON_NOT_INITIALIZED,                                          // 0x00000002
    DG_ERR_COMMON_ALREADY_INIT,                                             // 0x00000003
    DG_ERR_COMMON_INVALID_PARAMETER,                                        // 0x00000004
    DG_ERR_COMMON_UNSUCCESSFUL,                                             // 0x00000005
    DG_ERR_COMMON_INSUFFICIENT_RESOURCE,                                    // 0x00000006
    DG_ERR_COMMON_INVALID_HANDLE,                                           // 0x00000007
    DG_ERR_COMMON_NOT_SUPPORTED,                                            // 0x00000008
    DG_ERR_COMMON_MEMORY_PARAMETER_INVALID,                                 // 0x00000009
    DG_ERR_COMMON_MEMORY_PARAMETER_NULL,                                    // 0x0000000A
    DG_ERR_LIB_CARD_NUMBER_INVALID              = DG_ERR_LIB_START,         // 0x00000200
    DG_ERR_LIB_CHANNEL_INVALID,                                             // 0x00000201
    DG_ERR_LIB_NOT_FOUND_DEVICE,                                            // 0x00000202
    DG_ERR_BASE_DEVICE_OPEN_ERROR               = DG_ERR_BASE_START,        // 0x00000400
    DG_ERR_BASE_NO_HANDLE,                                                  // 0x00000401
    DG_ERR_BASE_DEVICE_NOT_OPENED,                                          // 0x00000402
    DG_ERR_BASE_DEVICE_CANT_CLOSE,                                          // 0x00000403
    DG_ERR_BASE_MUTEX_CANT_CREATE,                                          // 0x00000404
    DG_ERR_BASE_MUTEX_WAIT_ERROR,                                           // 0x00000405
    DG_ERR_BASE_MUTEX_RELEASE_ERROR,                                        // 0x00000406
    DG_ERR_BASE_BURST_LENGTH_INVALID,                                       // 0x00000407
    DG_ERR_BASE_FLASH_NULL,                                                 // 0x00000408
    DG_ERR_BASE_FILE_NAME_NULL,                                             // 0x00000409
    DG_ERR_BASE_CHIP_VERSION_INCORECT,                                      // 0x0000040A
    DG_ERR_CHANNEL_OPEN_BITS_PER_CLK_INVALID    = DG_ERR_CHANNEL_START,     // 0x00000500
    DG_ERR_CHANNEL_ALREADY_OPENED,                                          // 0x00000501
    DG_ERR_CHANNEL_FRAMES_INVALID,                                          // 0x00000502
    DG_ERR_CHANNEL_FRAME_SIZE_INVALID,                                      // 0x00000503
    DG_ERR_CHANNEL_FRAME_BUFFER_ALLOC_FAILS,                                // 0x00000504
    DG_ERR_CHANNEL_NOT_OPENED,                                              // 0x00000505
    DG_ERR_CHANNEL_ALREADY_PENDING,                                         // 0x00000506
    DG_ERR_CHANNEL_BUFFER_OVERFLOW,                                         // 0x00000507
    DG_ERR_CHANNEL_FRAME_OVER_RUN,                                          // 0x00000508
    DG_ERR_CHANNEL_DMA_TRANSFER_FAILS,                                      // 0x00000509
    DG_ERR_CHANNEL_NOT_PENDING,                                             // 0x0000050A
    DG_ERR_CHANNEL_START_FAILS,                                             // 0x0000050B
    DG_ERR_CHANNEL_ALREADY_STARTED,                                         // 0x0000050C
    DG_ERR_CHANNEL_NOT_STARTED,                                             // 0x0000050D
    DG_ERR_CHANNEL_GET_FRAME_TIMEOUT,                                       // 0x0000050E
    DG_ERR_CHANNEL_CHECK_MIPI_BOARD,                                        // 0x0000050F
    DG_ERR_CHANNEL_TRIGGER_PENDING,                                         // 0x00000510
    DG_ERR_CHANNEL_FRAME_ECC_ERROR,                                         // 0x00000511
    DG_ERR_CHANNEL_FRAME_CRC_ERROR,                                         // 0x00000512
    DG_ERR_WINBOND_WAIT_TIMEOUT                 = DG_ERR_WINBOND_START,     // 0x00000600
    DG_ERR_WINBOND_WRITE_RETRY_TIMEOUT,                                     // 0x00000601
    DG_ERR_WINBOND_UNSUPPORT_TYPE,                                          // 0x00000602
    DG_ERR_WINBOND_MISMATCH_DEVICE_ID,                                      // 0x00000603
    DG_ERR_WINBOND_CANT_OPEN_FILE,                                          // 0x00000604
    DG_ERR_WINBOND_VERIFY_ERROR,                                            // 0x00000605
    DG_ERR_WINBOND_SECURE_ERROR,                                            // 0x00000606
    DG_ERR_CAMIOMIPI_INVALID_INDEX              = DG_ERR_CAMIOMIPI_START,   // 0x00000800
    DG_ERR_I2C_LENGTH_ZERO                      = DG_ERR_I2C_START,         // 0x00000900
    DG_ERR_I2C_LENGTH_OVER,                                                 // 0x00000901
    DG_ERR_I2C_CLR_RX_BUFFER_TIMEOUT,                                       // 0x00000902
    DG_ERR_I2C_CLR_TX_BUFFER_TIMEOUT,                                       // 0x00000903
    DG_ERR_I2C_I2C_ACK,                                                     // 0x00000904
    DG_ERR_I2C_I2C_TIMEOUT,                                                 // 0x00000905
    DG_ERR_I2C_RD_TIMEOUT,                                                  // 0x00000906
    DG_ERR_I2C_VERIFY_ERROR_HIGH,                                           // 0x00000907
    DG_ERR_I2C_VERIFY_ERROR_LOW,                                            // 0x00000908
    DG_ERR_SPI_LENGTH_ZERO                      = DG_ERR_SPI_START,         // 0x00000A00
    DG_ERR_SPI_LENGTH_OVER,                                                 // 0x00000A01
    DG_ERR_SPI_CLR_RX_BUFFER_TIMEOUT,                                       // 0x00000A02
    DG_ERR_SPI_CLR_TX_BUFFER_TIMEOUT,                                       // 0x00000A03
    DG_ERR_SPI_RD_TIMEOUT,                                                  // 0x00000A04
    DG_ERR_CHANNEL_USB_CANT_OPEN                = DG_ERR_CHANNEL_USB_START, // 0x00000B00
    DG_ERR_CHANNEL_USB_INVALID,                                             // 0x00000B01
    DG_ERR_CHANNEL_USB_CANT_THREAD,                                         // 0x00000B02
    DG_ERR_CHANNEL_USB_INVALID_FRAME_BUFFER,                                // 0x00000B03
    DG_ERR_CHANNEL_USB_FRAME_NOT_READY,                                     // 0x00000B04
    DG_ERR_CHANNEL_USB_NOT_CAP_INFO,                                        // 0x00000B05
    DG_ERR_CHANNEL_USB_CANT_CREATE_EVENT,                                   // 0x00000B06
    DG_ERR_CHANNEL_USB_GET_FRAME_TIMEOUT,                                   // 0x00000B07
    DG_ERR_CHANNEL_USB_FRAME_EMPTY,                                         // 0x00000B08
    DG_ERR_CHANNEL_USB_XFERING,                                             // 0x00000B09
    DG_ERR_CHANNEL_USB_INVALID_GPIO_KIND,                                   // 0x00000B0A
    DG_ERR_CHANNEL_USB_NOT_EXIST_KEY,                                       // 0x00000B0B
    DG_ERR_CHANNEL_USB_INVALID_SPI_TARGET,                                  // 0x00000B0C
    DG_ERR_CHANNEL_USB_BUFFER_OVERRUN,                                      // 0x00000B0D
    DG_ERR_CHANNEL_USB_BUFFER_UNDERRUN,                                     // 0x00000B0E
    DG_ERR_USBBASE_WRITE_BEGIN_XFER_FAIL        = DG_ERR_USBBASE_START,     // 0x00000C00
    DG_ERR_USBBASE_WRITE_WAIT_XFER_FAIL,                                    // 0x00000C01
    DG_ERR_USBBASE_WRITE_FINISH_XFER_FAIL,                                  // 0x00000C02
    DG_ERR_USBBASE_READ_BEGIN_XFER_FAIL,                                    // 0x00000C03
    DG_ERR_USBBASE_READ_WAIT_XFER_FAIL,                                     // 0x00000C04
    DG_ERR_USBBASE_READ_FINISH_XFER_FAIL,                                   // 0x00000C05
    DG_ERR_USBBASE_WRITE_XFER_FAIL,											// 0x00000C06
    DG_ERR_USBBASE_READ_XFER_FAIL,                                          // 0x00000C07
    DG_ERR_USBBASE_OPEN_NO_ENDOINT,                                         // 0x00000C08
    DG_ERR_USBBASE_WRITE_FAIL,                                              // 0x00000C09
    DG_ERR_USBBASE_READ_FAIL,                                               // 0x00000C0A
    DG_ERR_USBBASE_READ_PACKET_END,                                         // 0x00000C0B
    DG_ERR_USBBASE_CANT_ALLOCATE_BUF,                                       // 0x00000C0C
    DG_ERR_BULKREGISTER_WRITE_ACK_FAIL          = DG_ERR_BULKREGISTER_START,// 0x00000D00
    DG_ERR_BULKREGISTER_READ_ACK_FAIL,                                      // 0x00000D01
    DG_ERR_BULKREGISTER_READ_ERROR,                                         // 0x00000D02
    DG_ERR_BULKREGISTER_INVALID_READ,                                       // 0x00000D03
    DG_ERR_BULKREGISTER_MUTEX_ERROR,                                        // 0x00000D04
    DG_ERR_BULKREGISTER_SURPRISE_REMOVAL,                                   // 0x00000D05
    DG_ERR_SERIALBASE_EMPTY_FIFO                = DG_ERR_SERIALBASE_START,  // 0x00000E00
    DG_ERR_SERIALBASE_NOT_REGISTER,                                         // 0x00000E01
    DG_ERR_SERIALBASE_WAIT_TIME_OUT,                                        // 0x00000E02
};

//>> 자동 생성


// 디바이스 상태를 정의
// 디바이스의 상태가 변할때 DCUSB_DEVICE_CALLBACK_FUNCTION 콜백 함수가 API쪽에서 호출되면서 인수로 넘겨지는 값
enum DGE_DEVICE_STATUS
{
	DGE_DEVICE_PLUGOUT = 0,					// 장치가 시스템에서 제거되는 경우 이 인수와 함께 호출됨
	DGE_DEVICE_PLUGIN,						// 장치가 시스템에 장착되는 경우 이 인수와 함께 호출됨
	DGE_DEVICE_CHANGED						// 그 외 장치 상태에 변화가 있을 경우 이 인수와 함께 호출됨
};

enum DGE_DEVICE_TYPE
{
	DGE_DEVICE_TYPE_PCIE = 0,				// PCI-e Type Frame Grabber
	DGE_DEVICE_TYPE_USB,						// USB Type Frame Grabber
	DGE_DEVICE_TYPE_PCIE1,					// PCI-e Type 4 Lane 1ch Frame Grabber
};

enum DGE_FREQ_MODE
{
	DGE_FREQ_MODE_FREQ = 0,
	DGE_FREQ_MODE_FLOAT,
	DGE_FREQ_MODE_HIGH,
	DGE_FREQ_MODE_LOW
};

// Firmware File Type
enum DGE_FIRMWARE_TYPE_INDEX
{
	DGE_FIRMWARE_TYPE_HEX,
	DGE_FIRMWARE_TYPE_BIN
};

// MIPI Info
enum DGE_MIPI_BOARD_INFO_INDEX
{
	DGE_MIPI_BOARD_INFO_PHY_MODE,
	DGE_MIPI_BOARD_INFO_PHY_SEPERATED
};

#define DGE_SCANNER_CONFIG_CATEGORY_LIGHTING		0x020000
#define DGE_SCANNER_CONFIG_CATEGORY_TRIGGER			0x030000

enum DGE_CONFIG_INDEX
{
	DGE_CONFIG_LIGHTING_OPERATION				= DGE_SCANNER_CONFIG_CATEGORY_LIGHTING,
	DGE_CONFIG_LIGHTING_CURRENT,
	DGE_CONFIG_LIGHTING_STROBE_DELAY,
	DGE_CONFIG_LIGHTING_STROBE_WIDTH,
	DGE_CONFIG_TRIGGER_ENABLE					= DGE_SCANNER_CONFIG_CATEGORY_TRIGGER,
	DGE_CONFIG_TRIGGER_EDGE,
	DGE_CONFIG_TRIGGER_HIRES,
	DGE_CONFIG_TRIGGER_DELAY,
	DGE_CONFIG_TRIGGER_SOFT_TRIGGER,
	DGE_CONFIG_TRIGGER_TIMEOUT,
	DGE_CONFIG_TRIGGER_I2C_ERROR,
	DGE_CONFIG_TRIGGER_TIME_ACS,
	DGE_CONFIG_TRIGGER_COUNT,
	DGE_CONFIG_TRIGGER_I2C_ERROR_COUNT,
	DGE_CONFIG_TRIGGER_TIMEOUT_COUNT
};

enum DGE_CONFIG_LIGHTING_OP_INDEX
{
	DGE_LIGHTING_OFF,
	DGE_LIGHTING_ON,
	DGE_LIGHTING_STROBE
};

//-------------------------------------------------------------------------------------------------------------------------------
// structure

// Device Info
typedef struct _DGS_DEVICE_INFO
{
	int iType;
	int iBoardNum;
	int iChannelNum;
	int iBoardId;
	int iMipiId;
	int iReserved0;
	int iReserved1;
	int iReserved2;
} DGS_DEVICE_INFO, *PDGS_DEVICE_INFO;

// Frame Info
typedef struct _DGS_FRAME_INFO
{
	DWORD dwLeftFrame;
	DWORD dwXferSize;
	DWORD dwEccError;
	DWORD dwCrcError;
	DWORD dwFrmNumber;
	DWORD dwFrmTrigger;
} DGS_FRAME_INFO, *PDGS_FRAME_INFO;

//-------------------------------------------------------------------------------------------------------------------------------
// callback functions

// DEVICE CALLBACK 함수 포인터 정의
typedef void (*DG_CALLBACK_FUNCTION)(HDG handle, LPVOID pCallbackContext, DGE_DEVICE_STATUS nDeviceStatus);

//-------------------------------------------------------------------------------------------------------------------------------
// Functions

//
// Framer Function
//

/*! 
 *	\fn		DG_Init
 *	\brief	시스템의 FrameGrabber를 검색해서 객체들을 생성하고 초기화 한다.
 *	\return	객체를 할당하는데 실패한다면 DG_ERR_INSUFFICIENT_RESOURCE를 리턴.
 *	\return	시스템에 설치된 Card가 없다면 DG_ERR_NO_DEVICE를 리턴.
 */
DGLIB_API int _stdcall DG_Init();

/*! 
 *	\fn		DG_End
 *	\brief	생성된 객체들을 모두 해제한다.
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_End();

/*! 
 *	\fn		DG_SetCallback
 *	\brief	USB Frame Grabber를 위해 시스템 이벤트 정보를 받을 수 있는 Callback 함수를 등록한다.
 *	\param	pCbCtx					pCbFunction가 호출될 때 전달될 context 변수
 *	\param	pCbFunction				장치 이벤트를 받을 callback 함수
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_SetCallback(LPVOID pCbCtx, DG_CALLBACK_FUNCTION pCbFunction);

/*! 
 *	\fn		DG_GetDeviceList
 *	\brief	시스템에서 검색된 Frame Grabber 정보 리스트를 얻어온다.
 *	\param	pMaxDevice				Frame Grabber 최대 갯수를 얻어올 포인터 변수
 *	\return	시스템에 설치된 Card의 갯수를 리턴
 */
DGLIB_API int _stdcall DG_GetDeviceList(int *pDeviceInfoCount, PDGS_DEVICE_INFO *ppDeviceInfoList);

//
// Device Create/Close
//

/*! 
 *	\fn		DG_OpenHandle
 *	\brief	GetChannelList에서 얻은 채널 인덱스를 이용하여 채널을 오픈하고 핸들을 얻는다.
 *	\param	iDeviceInfoIndex		DG_GetDeviceList에서 얻은 채널 인덱스
 *	\param	pHdg					채널 핸들을 얻을 포인터 변수
 *	\param	pCbCtx					pCbFunction가 호출될 때 전달될 context 변수
 *	\param	pCbFunction				장치 이벤트를 받을 callback 함수
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_OpenHandle(int iChannelIndex, HDG *pHdg, 
									LPVOID pCbCtx = NULL, DG_CALLBACK_FUNCTION pCbFunction = NULL);

/*! 
 *	\fn		DG_OpenHandleByCardNum
 *	\brief	Card Number와 Channel Number를 이용하여 채널을 오픈하고 핸들을 얻는다.
 *	\param	iCard					PCIe Type 카드를 나타내는 번호
 *	\param	iChannel				iCard 카드의 채널 번호
 *	\param	pHdg					채널 핸들을 얻을 포인터 변수
 *	\param	pCbCtx					pCbFunction가 호출될 때 전달될 context 변수
 *	\param	pCbFunction				장치 이벤트를 받을 callback 함수
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_OpenHandleByCardNum(int iCard, int iChannel, HDG *pHdg, 
									LPVOID pCbCtx = NULL, DG_CALLBACK_FUNCTION pCbFunction = NULL);


/*! 
 *	\fn		DG_OpenHandleByMipiBrdId
 *	\brief	MIPI Board의 DIP Switch ID를 이용하여 채널을 오픈하고 핸들을 얻는다.
 *	\param	iMipiBrdId				MIPI Board의 DIP Switch에 설정된 ID값
 *	\param	iChannel				iCard 카드의 채널 번호
 *	\param	pHdg					채널 핸들을 얻을 포인터 변수
 *	\param	pCbCtx					pCbFunction가 호출될 때 전달될 context 변수
 *	\param	pCbFunction				장치 이벤트를 받을 callback 함수
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_OpenHandleByMipiBrdId(int iBrdId, int iChannel, HDG *pHdg, 
									LPVOID pCbCtx = NULL, DG_CALLBACK_FUNCTION pCbFunction = NULL);

/*! 
 *	\fn		DG_CloseHandle
 *	\brief	DG_OpenHandle 얻은 채널 객체를 닫고 핸들을 릴리즈 한다.
 *	\param	hDG						채널 핸들
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_CloseHandle(HDG hDG);




//
// Device Information
//

/*! 
 *	\fn		DG_GetVersion
 *	\brief	지정한 Card의 버전 정보들을 얻는다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pDllVer					API 버전을 얻어올 포인터 변수
 *	\param	pDrvVer					Driver 버전을 얻어올 포인터 변수
 *	\param	pChipVer				FrameGrabber 버전을 얻어올 포인터 변수
 *	\param	pBrdVer					FrameGrabber 보드 리비전
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetVersion(HDG hDG, DWORD *pDllVer, DWORD *pDrvVer, DWORD *pChipVer, DWORD *pBrdVer);

/*! 
 *	\fn		DG_GetPcieInfo
 *	\brief	Card와 Main Board 간의 연결 정보를 얻는다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pLanes					PCI-Express Lanes 수
 *	\param	pSpeed					PCI-Express Generation 수
 *	\param	pMaxPayload				Max Payload Size
 *	\param	pMaxReadReq				Max Read Request Size
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetPcieInfo(HDG hDG, int *pLanes, int *pGen, int *pMaxPayload, int *pMaxReadReq);

/*! 
 *	\fn		DG_GetTemperature
 *	\brief	FPGA 온도 정보를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pTemp					온도를 얻어올 double 형 포인터
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetTemperature(HDG hDG, double *pTemp);

/*! 
 *	\fn		DG_SetFanControl
 *	\brief	FAN 동작을 설정한다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dwFanControl			Frame Control Code
 *									PCIe NOT WORK
 *									USB3
 *										0		= ON
 *										0xA		= AUTO
 *										other	= OFF
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_SetFanControl(HDG hDG, DWORD dwFanControl);

/*! 
 *	\fn		DG_GetMipiBoardInfo
 *	\brief	MIPI Board에 대한 정보를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iMipiBoardInfoIndex		MIPI Board 정보를 나타내는 index 값
 *	\param	pMipiBoardInfo			MIPI Board 정보를 얻어올 int 포인터
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetMipiBoardInfo(HDG hDG, int iMipiBoardInfoIndex, int *pMipiBoardInfo);

/*! 
 *	\fn		DG_SetMipiBoardInfo
 *	\brief	MIPI Board에 대한 정보를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iMipiBoardInfoIndex		MIPI Board 정보를 나타내는 index 값
 *	\param	iMipiBoardInfo			MIPI Board 정보
 *	\return	생성된 객체가 없다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_SetMipiBoardInfo(HDG hDG, int iMipiBoardInfoIndex, int iMipiBoardInfo);

//
// Link Status
//

/*! 
 *	\fn		DG_LinkStatus
 *	\brief	Frame Grabber와 MIPI Board 사이의 line 상태를 얻어옴.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pLinked					연결 상태를 얻어올 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_LinkStatus(HDG hDG, int *pLinked);

/*! 
 *	\fn		DG_LinkReset
 *	\brief	Frame Grabber와 MIPI Board 사이의 Line Sync를 Reset 한다
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iReset					1: Reset
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_LinkReset(HDG hDG);


//
// Frame Grab
//

/*! 
 *	\fn		DG_Open
 *	\brief	지정한 Frame 정보를 세트하고 Frame 버퍼를 할당한다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iHeight					Frame의 높이
 *	\param	iWidthBytes				한줄에 필요한 Byte 수
 *	\param	iFrameNum				할당할 Frame 갯수
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_Open(HDG hDG, int iHeight, int iWidthBytes, int iFrames);

/*! 
 *	\fn		DG_Close
 *	\brief	Frame 버퍼를 해제한다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 *	\return	BitsPerClk가 지정된 값과 다르다면 DG_ERR_OPEN_BITS_PER_CLK_INVALID를 리턴;
 *	\return	이미 Open되어 있다면 DG_ERR_ALREADY_OPENED를 리턴
 *	\return	Frame 버퍼 수가 너무 많거나 적다면 DG_ERR_FRAMES_INVALID 리턴
 *	\return	Frame Frame Size가 0이거나 4의 배수가 아니라면 DG_ERR_FRAME_SIZE_INVALID 리턴
  */
DGLIB_API int _stdcall DG_Close(HDG hDG);

/*! 
 *	\fn		DG_Start
 *	\brief	Frame Capture를 시작
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_Start(HDG hDG);
/*! 
 *	\fn		DG_Stop
 *	\brief	Frame Capture를 중단
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_Stop(HDG hDG);

/*! 
 *	\fn		DG_GetFrame
 *	\brief	Frame Grabber로 부터 한 Frame의 이미지 데이터를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iTimeoutMs				타임 아웃 시간
 *										> 0 시간Frame을 기다리고 시간이 지나면 Timeout 에러
 *										= 0 현재 버퍼 상태를 그대로 리턴
 *										< 0 Frame이 들어올때까지 무한정 기다림
 *	\param	buf						얻어온 이미지 데이터 포인터
 *	\param	pLeftFrame				읽어오지 않은 남은 Frame 수
 *	\param	pFrameLength			Frame 크기
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetFrame(HDG hDG, int iTimeoutMs, BYTE **buf, int *pLeftFrame, DWORD *pFrameLength);

/*! 
 *	\fn		DG_GetFrameEx
 *	\brief	Frame Grabber로 부터 한 Frame의 이미지 데이터를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iTimeoutMs				타임 아웃 시간
 *										> 0 시간Frame을 기다리고 시간이 지나면 Timeout 에러
 *										= 0 현재 버퍼 상태를 그대로 리턴
 *										< 0 Frame이 들어올때까지 무한정 기다림
 *	\param	buf						얻어온 이미지 데이터 포인터
 *	\param	pFrameInfo				읽어오지 않은 남은 Frame 수
 *										dwLeftFrame			DMA 버퍼에 남아 있는 Frame 수(리턴되는 Frame 포함)
 *										dwXferSize			전송된 크기(Byte Unit)
 *										dwEccError			이 프레임의 ECC Error Count
 *										dwCrcError			이 프레임의 CRC Error Count
 *										dwFrmNumber			Frame Number
 *										dwFrmTrigger		Frame Trigged
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetFrameEx(HDG hDG, int iTimeoutMs, BYTE **buf, PDGS_FRAME_INFO pFrameInfo);

/*! 
 *	\fn		DG_GetFrameTrg
 *	\brief	Frame Grabber로 부터 한 Frame의 이미지 데이터를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iTimeoutMs				타임 아웃 시간
 *	\param	buf						얻어온 이미지 데이터 포인터
 *	\param	pFrameInfo				Get Frame 정보가 담겨있는 구조체
 *										dwLeftFrame			DMA 버퍼에 남아 있는 Frame 수(리턴되는 Frame 포함)
 *										dwXferSize			전송된 크기(Byte Unit)
 *										dwEccError			이 프레임의 ECC Error Count
 *										dwCrcError			이 프레임의 CRC Error Count
 *										dwFrmNumber			Frame Number
 *										dwFrmTrigger		Frame Trigged
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetFrameTrg(HDG hDG, int iTimeoutMs, BYTE **ppBuf, PDGS_FRAME_INFO pFrameInfo);

/*! 
 *	\fn		DG_GetFrame
 *	\brief	DG_GetFrame이 block 되어 있을 경우 block을 해제하고 바로 리턴 시킨다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_CancelGetFrame(HDG hDG);

//
// Init Framer
//

/*! 
 *	\fn		DG_SetMipiDefault
 *	\brief	MIPI DataType과 나머지 설정을 디폴트 설정한다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iDt						MIPI Data Type
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API int _stdcall DG_SetMipiDefault(HDG hDG, int iDt);

/*! 
 *	\fn		DG_SetMipiInput
 *	\brief	MIPI 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iLanes					MIPI Lanes
 *	\param	iDec8b9b				MIPI 8b9b decode
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_SetMipiInput(HDG hDG, int iLanes, int iDec8b9b);

/*! 
 *	\fn		DG_SetMipiInfo
 *	\brief	MIPI 설정. DT는 4개까지, VC는 1개 설정이 가능
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	VirtualChannel			MIPI packet에서 원하는 가상 채널을 지정한다. 보통 0을 사용한다. 
 *	\param	iDt						MIPI packet에서 받기를 원하는 데이타 타입을 지정한다.
 *	\param	iDt1					MIPI packet에서 받기를 원하는 데이타 타입을 지정한다
 *	\param	iDt2					MIPI packet에서 받기를 원하는 데이타 타입을 지정한다
 *	\param	iDt3					MIPI packet에서 받기를 원하는 데이타 타입을 지정한다
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_SetMipiInfo(HDG hDG, int iVc, int iDt, int iDt1, int iDt2, int iDt3);

/*! 
 *	\fn		DG_SetMipiDsiMode
 *	\brief	DSI MIPI Capture를 위한 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iDsiEnable				DSI MIPI Capture를 Enable. 
 *	\param	iDsiVideoCommand		DSI MIPI Caputre Option.
 *	\param	iDsiHsyncGen			DSI MIPI Caputre Option.
 *	\param	iDsiVsyncGen			DSI MIPI Caputre Option.
 *	\param	iLanes					DSI MIPI Lane 수
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_SetMipiDsiMode(HDG hDG, int iDsiEnable, int iDsiVideoCommand, int iDsiHsyncGen, int iDsiVsyncGen);

//
// Device Error & Manage Functions
//

/*! 
 *	\fn		DG_GetMipiError
 *	\brief	Framer 에서 발생한 MIPI Capture 에러 누적 갯수를 읽어 온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pEcc1					ECC1 에러를 얻을 포인터 변수
 *	\param	pEcc2					ECC2 에러를 얻을 포인터 변수
 *	\param	pCrc					CRC 에러를 얻을 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API int _stdcall DG_GetMipiError(HDG hDG, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		DG_ClrCapMipiError
 *	\brief	Framer 에서 발생한 누적 에러를 clear 한다
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_ClrMipiError(HDG hDG);

/*! 
 *	\fn		DG_GetIsmMipiError
 *	\brief	MIPI 에서 발생한 MIPI Capture 에러 누적 갯수를 읽어 온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pEcc1					ECC1 에러를 얻을 포인터 변수
 *	\param	pEcc2					ECC2 에러를 얻을 포인터 변수
 *	\param	pCrc					CRC 에러를 얻을 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API int _stdcall DG_GetIsmMipiError(HDG hDG, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		DG_ClrIsmMipiError
 *	\brief	MIPI 에서 발생한 누적 에러를 clear 한다
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_ClrIsmMipiError(HDG hDG);

/*! 
 *	\fn		DG_GetMipiStatus
 *	\brief	MIPI Lane Status를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pStatus					Lanes 상태를 얻어올 DWORD 포인터 변수
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_GetMipiStatus(HDG hDG, DWORD *pStatus);

/*! 
 *	\fn		DG_ClrMipiStatus
 *	\brief	MIPI Lane Status를 초기화 한다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_ClrMipiStatus(HDG hDG);

/*! 
 *	\fn		DG_CheckCamSignal
 *	\brief	주어진 시간 동안 모든 라인의 토글 횟수를 동시에 측정한다. 
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	width_ms				측정할 ms 단위 시간 값
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_CheckCamSignal(HDG hDG, DWORD dwWidthMs);

/*! 
 *	\fn		DG_GetCamSignalCount
 *	\brief	측정이 된 카메라의 토글 횟수를 얻어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	index					얻어올 Camera Line Index
 *										[11]: Vertical Input line
 *										[10]: Horizontal Input line
 *										[9~0]: Camera Data[9:0] lines
 *	\param	val						토글 횟수를 얻어올 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API int _stdcall DG_GetCamSignalCount(HDG hDG, int index, DWORD *val);

//
// Init Sensor
//

/*! 
 *	\fn		DG_SetIsmDefault
 *	\brief	ISM I/O Default 설정하고 ISM을 Reset 한다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_SetIsmDefault(HDG hDG);

/*! 
 *	\fn		DG_SetIoVolt
 *	\brief	Vio 전압 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dVio					Vio 전압(0 ~ 3.3v)
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_SetIsmIoVolt(HDG hDG, double dVio);

/*! 
 *	\fn		DG_SetFreq
 *	\brief	Mipi Board의 MCLK 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iFreqMode				Clock Pin 상태 설정
 *										FREQ_MODE_FREQ: 설정된 주파수 출력		
 *										FREQ_MODE_FLOAT: 주파수 핀 상태를 float 상태로 설정
 *										FREQ_MODE_HIGH: 설정된 주파수 핀을 HIGH 상태로 설정
 *										FREQ_MODE_LOW: 설정된 주파수 핀을 LOW 상태로 설정
 *	\param	dFreq					Mipi Board 주파수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_SetIsmFreq(HDG hDG, int iFreqMode, double dFreq, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_SetCamReset
 *	\brief	Camera Reset 핀 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iReset					1: Reset, 0: Normal
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_SetIsmReset(HDG hDG, int iReset);

/*! 
 *	\fn		DG_SetIo
 *	\brief	Camera에 연결된 2bit IO Write
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	bGpio					GPIO Signal Write
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_SetIsmIo(HDG hDG, int iIoBit, int iOe, int iIo);

/*! 
 *	\fn		DG_GetIo
 *	\brief	Camera에 연결된 2bit IO Read
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pGpio					GPIO Signal Read
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API   int _stdcall DG_GetIsmIo(HDG hDG, int iIoBit, int *pIo);

//
// Serial I/O functions
//

/*! 
 *	\fn		DG_SetSpiFreq
 *	\brief	SPI 주파수 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	freq_mhz				SPI Freq(MHz Unit)
 *	\return	설정된 주파수를 리턴
 */
DGLIB_API 	int _stdcall DG_SetSpiFreq(HDG hDG, double dFreqMhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_SpiWrite
 *	\brief	SPI Write
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	length					전송할 데이터 길이
 *	\param	last					1이면 전송이 끝나고 CS를 High로 올린다.
 *	\param	buf						전송할 데이터
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_SpiWrite(HDG hDG, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SpiRead
 *	\brief	SPI Read. 함수 호출시 CS를 Low로 떨어뜨린다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	length					읽어드릴 데이터 길이
 *	\param	last					1이면 다 읽어 드린 후 CS를 High로 올린다.
 *	\param	buf						일어드릴 데이터 버퍼
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_SpiRead(HDG hDG, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SetI2cFreq
 *	\brief	I2C 주파수 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	freq_khz				I2C Freq(kHz Unit)
 *	\return	설정된 주파수를 리턴
 */
DGLIB_API 	int _stdcall DG_SetI2cFreq(HDG hDG, double dFreqKhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_I2cWrite
 *	\brief	I2C Write
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	length					전송할 데이터 길이
 *	\param	start					전송 시작전 I2C START issue.
 *	\param	last					전송 후 I2C STOP issue.
 *	\param	buf						전송할 데이터
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_I2cWrite(HDG hDG, int iStart, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_I2cRead
 *	\brief	I2C Read.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	length					읽어드릴 데이터 길이.
 *	\param	last					다 읽어 드린후 I2C STOP issue.
 *	\param	buf						일어드릴 데이터 버퍼.
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_I2cRead(HDG hDG, int iLast, BYTE *buf, int length);

//
// Mulit Serial Functions
//

/*! 
 *	\fn		DG_SetSpisFreq
 *	\brief	여러 개의 SPI들 중 특정 SPI의 주파수 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iIndex					SPI Index
 *	\param	freq_mhz				SPI Freq(MHz Unit)
 *	\return	설정된 주파수를 리턴
 */
DGLIB_API 	int _stdcall DG_SetSpisFreq(HDG hDG, int iIndex, double dFreqMhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_SpisWrite
 *	\brief	여러 개의 SPI들 중 특정 SPI를 통해 SPI 전송
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iIndex					SPI Index
 *	\param	length					전송할 데이터 길이
 *	\param	last					1이면 전송이 끝나고 CS를 High로 올린다.
 *	\param	buf						전송할 데이터
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_SpisWrite(HDG hDG, int iIndex, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SpisRead
 *	\brief	여러 개의 SPI들 중 특정 SPI를 통해 SPI Read
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iIndex					SPI Index
 *	\param	length					읽어드릴 데이터 길이
 *	\param	last					1이면 다 읽어 드린 후 CS를 High로 올린다.
 *	\param	buf						일어드릴 데이터 버퍼
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_SpisRead(HDG hDG, int iIndex, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SetI2csFreq
 *	\brief	여러 개의 I2c들 중 특정 I2c의 주파수를 설정
 *	\brief	I2C 주파수 설정
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iIndex					I2C Index
 *	\param	freq_khz				I2C Freq(kHz Unit)
 *	\return	설정된 주파수를 리턴
 */
DGLIB_API 	int _stdcall DG_SetI2csFreq(HDG hDG, int iIndex, double dFreqKhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_I2csWrite
 *	\brief	여러 개의 I2c들 중 특정 I2c를 통해 I2c 전송
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iIndex					I2C Index
 *	\param	length					전송할 데이터 길이
 *	\param	start					전송 시작전 I2C START issue.
 *	\param	last					전송 후 I2C STOP issue.
 *	\param	buf						전송할 데이터
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_I2csWrite(HDG hDG, int iIndex, int iStart, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_I2csRead
 *	\brief	여러 개의 I2c들 중 특정 I2c를 통해 I2c Read
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	iIndex					I2C Index
 *	\param	length					읽어드릴 데이터 길이.
 *	\param	last					다 읽어 드린후 I2C STOP issue.
 *	\param	buf						일어드릴 데이터 버퍼.
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API 	int	_stdcall DG_I2csRead(HDG hDG, int iIndex, int iLast, BYTE *buf, int length);

//
// MIPI Board API
//

/*! 
 *	\fn		DG_GetMipiVersion
 *	\brief	Mipi Board의 버전 정보를 얻는다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pBrdVer					버전을 얻어올 포인터 변수
 *	\param	pCmpVer					Compile Date를 얻어올 포인터 변수
 *	\param	pNumChannel				채널 갯수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_GetMipiVersion(HDG hDG, DWORD *pChipVer, DWORD *pBrdVer);

/*! 
 *	\fn		DG_GetMipiBrdId
 *	\brief	Mipi Board의 DIP Switch ID를 얻는다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pBrdId					Board ID를 얻어올 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_GetMipiBrdId(HDG hDG, int *pBrdId);

/*! 
 *	\fn		DG_GpioReadIn
 *	\brief	Mipi Board의 GPIO 값 읽어오기
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pGpio					GPIO Signal을 읽을 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_GpioRead(HDG hDG, DWORD *pGpio);

/*! 
 *	\fn		DG_GpioWriteOut
 *	\brief	Mipi Board의 GPIO 출력
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dwGpio					GPIO Signal 출력
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_GpioWrite(HDG hDG, DWORD dwOe, DWORD dwData);

/*! 
 *	\fn		DG_GetGpio16
 *	\brief	Mipi Board의 GPIO 값 읽어오기(채널에 따라 16비트)
 *			LOW 16비트는 0번 채널, HIGH 16비트는 1번 채널
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pGpio					GPIO Signal을 읽을 포인터 변수
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_GetGpio16(HDG hDG, DWORD *pGpio);

/*! 
 *	\fn		DG_SetGpioOe16
 *	\brief	Mipi Board의 GPIO Direction 설정하기(채널에 따라 16비트)
 *			LOW 16비트는 0번 채널, HIGH 16비트는 1번 채널
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dwGpioOe				GPIO Direction 1:OUT, 0:IN
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_SetGpioOe16(HDG hDG, DWORD dwGpioOe);

/*! 
 *	\fn		DG_SetGpio16
 *	\brief	Mipi Board의 GPIO 출력(채널에 따라 16비트)
 *			LOW 16비트는 0번 채널, HIGH 16비트는 1번 채널
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dwGpio					GPIO Signal 출력
 *	\return	내부 변수가 세트되지 않았다면 DG_ERR_EXTERNAL_NOT_INIT를 리턴
 */
DGLIB_API	int _stdcall DG_SetGpio16(HDG hDG, DWORD dwData);

//
// Test Pattern Enable Functions
//

/*! 
 *	\fn		DG_SetTestCamEn
 *	\brief	Framer에서 Test Pattern을 발생시키고 이를 Capture하도록 설정.
 *			Test Pattern Frame은 Open시 설정된 정보에 맞게 설정된다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API int _stdcall DG_SetTestCamEn(HDG hDG, int iEnable);

/*! 
 *	\fn		DG_SetMipiCsiTestCamEn
 *	\brief	MIPI에서 Test Pattern을 발생시키고 이를 Capture하도록 설정.
 *			Test Pattern Frame은 Open시 설정된 정보에 맞게 설정된다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API	int _stdcall DG_SetMipiTestCamEn(HDG hDG, int iEnable);

//
// Trigger Control for standalone
//

/*! 
 *	\fn		DG_SetCamConfig
 *	\brief	D2_ERR_NOT_SUPPORTED
 */
DGLIB_API   int _stdcall DG_SetCamConfig(HDG hDG, int iIndex, int iValue);

/*! 
 *	\fn		DG_GetCamConfig
 *	\brief	D2_ERR_NOT_SUPPORTED
 */
DGLIB_API   int _stdcall DG_GetCamConfig(HDG hDG, int iIndex, int *pValue);

/*! 
 *	\fn		DG_SetCamPower
 *	\brief	D2_ERR_NOT_SUPPORTED
 */
DGLIB_API   int _stdcall DG_SetCamPower(HDG hDG, int iOnOff);

//
// pmulib를 위한 PMU Handle을 관리하는 함수
//

/*! 
 *	\fn		DG_GetPmuHandle
 *	\brief	PMU Handle을 얻어낸다.
 *			얻어낸 PMU Handle은 pmulib를 구동하는데 사용된다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pHandle					PMU Handle을 얻기위한 포인터 변수
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_GetPmuHandle(HDG hDG, HANDLE *pHandle);


/*! 
 *	\fn		DG_ReleasePmuHandle
 *	\brief	사용이 끝난 PMU Handle을 되돌려 준다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	hHandle					PMU Handle
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_ReleasePmuHandle(HDG hDG, HANDLE hHandle);


//
// Common Functions
//

/*! 
 *	\fn		DG_GetBeagle
 *	\brief	Device에 저장된 BEAGLE 정보를 읽어온다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dwData					데이터
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_GetBeagle(HDG hDG, DWORD *pBeagle);

/*! 
 *	\fn		DG_ClrBeagle
 *	\brief	Device에 저장된 BEAGLE 정보를 초기화 한다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_ClrBeagle(HDG hDG);

/*! 
 *	\fn		DG_WriteReg
 *	\brief	Device의 Register에 값을 써넣는다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dwAddr					Register Address
 *	\param	dwData					데이터
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_WriteReg(HDG hDG, DWORD dwAddr, DWORD dwData);

/*! 
 *	\fn		DG_ReadReg
 *	\brief	Device의 Register에서 값을 읽는다.
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	dwAddr					Register Address
 *	\param	pData					데이터를 얻어올 포인터 변수
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_ReadReg(HDG hDG, DWORD dwAddr, DWORD *pData);

/*! 
 *	\fn		DG_Prog
 *	\brief	Device의 Firmware Program
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	report					report 객체
 *	\param	filename				펌웨어 파일 이름
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_Prog(HDG hDG, void *report, char *filename);

/*! 
 *	\fn		DG_MipiProg
 *	\brief	Mipi Board의 Firmware Program
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	report					report 객체
 *	\param	filename				펌웨어 파일 이름
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_MipiProg(HDG hDG, void *report, char *filename);

/*! 
 *	\fn		DG_GetPhaseDelay
 *	\brief	MIPI Phase Delay의 값을 얻어온다
 *	\param	hDG						Device와 채널을 나타내는 핸들
 *	\param	pDelay					현재 Phase Delay 값
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_GetPhaseDelay(HDG hDG, int *pDelay);

/*! 
 *	\fn		DG_IncPhaseDelay
 *	\brief	MIPI Phase Delay의 값을 증가시킴
 *	\param	hDG					Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_IncPhaseDelay(HDG hDG);

/*! 
 *	\fn		DG_DecPhaseDelay
 *	\brief	MIPI Phase Delay의 값을 감소시킴
 *	\param	hDG					Device와 채널을 나타내는 핸들
 *	\return	내부 객체가 생성되지 않았다면 DG_ERR_NOT_INITIALIZED를 리턴
 */
DGLIB_API   int _stdcall DG_DecPhaseDelay(HDG hDG);

/*! 
 *	\fn		DG_GetErrorMsg
 *	\brief	에러 코드에 해당하는 문자열 리턴
 *	\param	error					에러 코드
 *	\return	에러 코드에 해당하는 문자열 리턴
 */
DGLIB_API	const char* _stdcall DG_GetErrorMsg(int error);

#ifdef __cplusplus
}
#endif

#endif

