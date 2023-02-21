
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


//<< �ڵ� ����

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

//>> �ڵ� ����


// ����̽� ���¸� ����
// ����̽��� ���°� ���Ҷ� DCUSB_DEVICE_CALLBACK_FUNCTION �ݹ� �Լ��� API�ʿ��� ȣ��Ǹ鼭 �μ��� �Ѱ����� ��
enum DGE_DEVICE_STATUS
{
	DGE_DEVICE_PLUGOUT = 0,					// ��ġ�� �ý��ۿ��� ���ŵǴ� ��� �� �μ��� �Բ� ȣ���
	DGE_DEVICE_PLUGIN,						// ��ġ�� �ý��ۿ� �����Ǵ� ��� �� �μ��� �Բ� ȣ���
	DGE_DEVICE_CHANGED						// �� �� ��ġ ���¿� ��ȭ�� ���� ��� �� �μ��� �Բ� ȣ���
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

// DEVICE CALLBACK �Լ� ������ ����
typedef void (*DG_CALLBACK_FUNCTION)(HDG handle, LPVOID pCallbackContext, DGE_DEVICE_STATUS nDeviceStatus);

//-------------------------------------------------------------------------------------------------------------------------------
// Functions

//
// Framer Function
//

/*! 
 *	\fn		DG_Init
 *	\brief	�ý����� FrameGrabber�� �˻��ؼ� ��ü���� �����ϰ� �ʱ�ȭ �Ѵ�.
 *	\return	��ü�� �Ҵ��ϴµ� �����Ѵٸ� DG_ERR_INSUFFICIENT_RESOURCE�� ����.
 *	\return	�ý��ۿ� ��ġ�� Card�� ���ٸ� DG_ERR_NO_DEVICE�� ����.
 */
DGLIB_API int _stdcall DG_Init();

/*! 
 *	\fn		DG_End
 *	\brief	������ ��ü���� ��� �����Ѵ�.
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_End();

/*! 
 *	\fn		DG_SetCallback
 *	\brief	USB Frame Grabber�� ���� �ý��� �̺�Ʈ ������ ���� �� �ִ� Callback �Լ��� ����Ѵ�.
 *	\param	pCbCtx					pCbFunction�� ȣ��� �� ���޵� context ����
 *	\param	pCbFunction				��ġ �̺�Ʈ�� ���� callback �Լ�
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_SetCallback(LPVOID pCbCtx, DG_CALLBACK_FUNCTION pCbFunction);

/*! 
 *	\fn		DG_GetDeviceList
 *	\brief	�ý��ۿ��� �˻��� Frame Grabber ���� ����Ʈ�� ���´�.
 *	\param	pMaxDevice				Frame Grabber �ִ� ������ ���� ������ ����
 *	\return	�ý��ۿ� ��ġ�� Card�� ������ ����
 */
DGLIB_API int _stdcall DG_GetDeviceList(int *pDeviceInfoCount, PDGS_DEVICE_INFO *ppDeviceInfoList);

//
// Device Create/Close
//

/*! 
 *	\fn		DG_OpenHandle
 *	\brief	GetChannelList���� ���� ä�� �ε����� �̿��Ͽ� ä���� �����ϰ� �ڵ��� ��´�.
 *	\param	iDeviceInfoIndex		DG_GetDeviceList���� ���� ä�� �ε���
 *	\param	pHdg					ä�� �ڵ��� ���� ������ ����
 *	\param	pCbCtx					pCbFunction�� ȣ��� �� ���޵� context ����
 *	\param	pCbFunction				��ġ �̺�Ʈ�� ���� callback �Լ�
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_OpenHandle(int iChannelIndex, HDG *pHdg, 
									LPVOID pCbCtx = NULL, DG_CALLBACK_FUNCTION pCbFunction = NULL);

/*! 
 *	\fn		DG_OpenHandleByCardNum
 *	\brief	Card Number�� Channel Number�� �̿��Ͽ� ä���� �����ϰ� �ڵ��� ��´�.
 *	\param	iCard					PCIe Type ī�带 ��Ÿ���� ��ȣ
 *	\param	iChannel				iCard ī���� ä�� ��ȣ
 *	\param	pHdg					ä�� �ڵ��� ���� ������ ����
 *	\param	pCbCtx					pCbFunction�� ȣ��� �� ���޵� context ����
 *	\param	pCbFunction				��ġ �̺�Ʈ�� ���� callback �Լ�
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_OpenHandleByCardNum(int iCard, int iChannel, HDG *pHdg, 
									LPVOID pCbCtx = NULL, DG_CALLBACK_FUNCTION pCbFunction = NULL);


/*! 
 *	\fn		DG_OpenHandleByMipiBrdId
 *	\brief	MIPI Board�� DIP Switch ID�� �̿��Ͽ� ä���� �����ϰ� �ڵ��� ��´�.
 *	\param	iMipiBrdId				MIPI Board�� DIP Switch�� ������ ID��
 *	\param	iChannel				iCard ī���� ä�� ��ȣ
 *	\param	pHdg					ä�� �ڵ��� ���� ������ ����
 *	\param	pCbCtx					pCbFunction�� ȣ��� �� ���޵� context ����
 *	\param	pCbFunction				��ġ �̺�Ʈ�� ���� callback �Լ�
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_OpenHandleByMipiBrdId(int iBrdId, int iChannel, HDG *pHdg, 
									LPVOID pCbCtx = NULL, DG_CALLBACK_FUNCTION pCbFunction = NULL);

/*! 
 *	\fn		DG_CloseHandle
 *	\brief	DG_OpenHandle ���� ä�� ��ü�� �ݰ� �ڵ��� ������ �Ѵ�.
 *	\param	hDG						ä�� �ڵ�
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_CloseHandle(HDG hDG);




//
// Device Information
//

/*! 
 *	\fn		DG_GetVersion
 *	\brief	������ Card�� ���� �������� ��´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pDllVer					API ������ ���� ������ ����
 *	\param	pDrvVer					Driver ������ ���� ������ ����
 *	\param	pChipVer				FrameGrabber ������ ���� ������ ����
 *	\param	pBrdVer					FrameGrabber ���� ������
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetVersion(HDG hDG, DWORD *pDllVer, DWORD *pDrvVer, DWORD *pChipVer, DWORD *pBrdVer);

/*! 
 *	\fn		DG_GetPcieInfo
 *	\brief	Card�� Main Board ���� ���� ������ ��´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pLanes					PCI-Express Lanes ��
 *	\param	pSpeed					PCI-Express Generation ��
 *	\param	pMaxPayload				Max Payload Size
 *	\param	pMaxReadReq				Max Read Request Size
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetPcieInfo(HDG hDG, int *pLanes, int *pGen, int *pMaxPayload, int *pMaxReadReq);

/*! 
 *	\fn		DG_GetTemperature
 *	\brief	FPGA �µ� ������ ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pTemp					�µ��� ���� double �� ������
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetTemperature(HDG hDG, double *pTemp);

/*! 
 *	\fn		DG_SetFanControl
 *	\brief	FAN ������ �����Ѵ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dwFanControl			Frame Control Code
 *									PCIe NOT WORK
 *									USB3
 *										0		= ON
 *										0xA		= AUTO
 *										other	= OFF
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_SetFanControl(HDG hDG, DWORD dwFanControl);

/*! 
 *	\fn		DG_GetMipiBoardInfo
 *	\brief	MIPI Board�� ���� ������ ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iMipiBoardInfoIndex		MIPI Board ������ ��Ÿ���� index ��
 *	\param	pMipiBoardInfo			MIPI Board ������ ���� int ������
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetMipiBoardInfo(HDG hDG, int iMipiBoardInfoIndex, int *pMipiBoardInfo);

/*! 
 *	\fn		DG_SetMipiBoardInfo
 *	\brief	MIPI Board�� ���� ������ ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iMipiBoardInfoIndex		MIPI Board ������ ��Ÿ���� index ��
 *	\param	iMipiBoardInfo			MIPI Board ����
 *	\return	������ ��ü�� ���ٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_SetMipiBoardInfo(HDG hDG, int iMipiBoardInfoIndex, int iMipiBoardInfo);

//
// Link Status
//

/*! 
 *	\fn		DG_LinkStatus
 *	\brief	Frame Grabber�� MIPI Board ������ line ���¸� ����.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pLinked					���� ���¸� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_LinkStatus(HDG hDG, int *pLinked);

/*! 
 *	\fn		DG_LinkReset
 *	\brief	Frame Grabber�� MIPI Board ������ Line Sync�� Reset �Ѵ�
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iReset					1: Reset
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_LinkReset(HDG hDG);


//
// Frame Grab
//

/*! 
 *	\fn		DG_Open
 *	\brief	������ Frame ������ ��Ʈ�ϰ� Frame ���۸� �Ҵ��Ѵ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iHeight					Frame�� ����
 *	\param	iWidthBytes				���ٿ� �ʿ��� Byte ��
 *	\param	iFrameNum				�Ҵ��� Frame ����
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_Open(HDG hDG, int iHeight, int iWidthBytes, int iFrames);

/*! 
 *	\fn		DG_Close
 *	\brief	Frame ���۸� �����Ѵ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 *	\return	BitsPerClk�� ������ ���� �ٸ��ٸ� DG_ERR_OPEN_BITS_PER_CLK_INVALID�� ����;
 *	\return	�̹� Open�Ǿ� �ִٸ� DG_ERR_ALREADY_OPENED�� ����
 *	\return	Frame ���� ���� �ʹ� ���ų� ���ٸ� DG_ERR_FRAMES_INVALID ����
 *	\return	Frame Frame Size�� 0�̰ų� 4�� ����� �ƴ϶�� DG_ERR_FRAME_SIZE_INVALID ����
  */
DGLIB_API int _stdcall DG_Close(HDG hDG);

/*! 
 *	\fn		DG_Start
 *	\brief	Frame Capture�� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_Start(HDG hDG);
/*! 
 *	\fn		DG_Stop
 *	\brief	Frame Capture�� �ߴ�
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_Stop(HDG hDG);

/*! 
 *	\fn		DG_GetFrame
 *	\brief	Frame Grabber�� ���� �� Frame�� �̹��� �����͸� ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iTimeoutMs				Ÿ�� �ƿ� �ð�
 *										> 0 �ð�Frame�� ��ٸ��� �ð��� ������ Timeout ����
 *										= 0 ���� ���� ���¸� �״�� ����
 *										< 0 Frame�� ���ö����� ������ ��ٸ�
 *	\param	buf						���� �̹��� ������ ������
 *	\param	pLeftFrame				�о���� ���� ���� Frame ��
 *	\param	pFrameLength			Frame ũ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetFrame(HDG hDG, int iTimeoutMs, BYTE **buf, int *pLeftFrame, DWORD *pFrameLength);

/*! 
 *	\fn		DG_GetFrameEx
 *	\brief	Frame Grabber�� ���� �� Frame�� �̹��� �����͸� ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iTimeoutMs				Ÿ�� �ƿ� �ð�
 *										> 0 �ð�Frame�� ��ٸ��� �ð��� ������ Timeout ����
 *										= 0 ���� ���� ���¸� �״�� ����
 *										< 0 Frame�� ���ö����� ������ ��ٸ�
 *	\param	buf						���� �̹��� ������ ������
 *	\param	pFrameInfo				�о���� ���� ���� Frame ��
 *										dwLeftFrame			DMA ���ۿ� ���� �ִ� Frame ��(���ϵǴ� Frame ����)
 *										dwXferSize			���۵� ũ��(Byte Unit)
 *										dwEccError			�� �������� ECC Error Count
 *										dwCrcError			�� �������� CRC Error Count
 *										dwFrmNumber			Frame Number
 *										dwFrmTrigger		Frame Trigged
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetFrameEx(HDG hDG, int iTimeoutMs, BYTE **buf, PDGS_FRAME_INFO pFrameInfo);

/*! 
 *	\fn		DG_GetFrameTrg
 *	\brief	Frame Grabber�� ���� �� Frame�� �̹��� �����͸� ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iTimeoutMs				Ÿ�� �ƿ� �ð�
 *	\param	buf						���� �̹��� ������ ������
 *	\param	pFrameInfo				Get Frame ������ ����ִ� ����ü
 *										dwLeftFrame			DMA ���ۿ� ���� �ִ� Frame ��(���ϵǴ� Frame ����)
 *										dwXferSize			���۵� ũ��(Byte Unit)
 *										dwEccError			�� �������� ECC Error Count
 *										dwCrcError			�� �������� CRC Error Count
 *										dwFrmNumber			Frame Number
 *										dwFrmTrigger		Frame Trigged
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetFrameTrg(HDG hDG, int iTimeoutMs, BYTE **ppBuf, PDGS_FRAME_INFO pFrameInfo);

/*! 
 *	\fn		DG_GetFrame
 *	\brief	DG_GetFrame�� block �Ǿ� ���� ��� block�� �����ϰ� �ٷ� ���� ��Ų��.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_CancelGetFrame(HDG hDG);

//
// Init Framer
//

/*! 
 *	\fn		DG_SetMipiDefault
 *	\brief	MIPI DataType�� ������ ������ ����Ʈ �����Ѵ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iDt						MIPI Data Type
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API int _stdcall DG_SetMipiDefault(HDG hDG, int iDt);

/*! 
 *	\fn		DG_SetMipiInput
 *	\brief	MIPI ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iLanes					MIPI Lanes
 *	\param	iDec8b9b				MIPI 8b9b decode
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_SetMipiInput(HDG hDG, int iLanes, int iDec8b9b);

/*! 
 *	\fn		DG_SetMipiInfo
 *	\brief	MIPI ����. DT�� 4������, VC�� 1�� ������ ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	VirtualChannel			MIPI packet���� ���ϴ� ���� ä���� �����Ѵ�. ���� 0�� ����Ѵ�. 
 *	\param	iDt						MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�.
 *	\param	iDt1					MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�
 *	\param	iDt2					MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�
 *	\param	iDt3					MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_SetMipiInfo(HDG hDG, int iVc, int iDt, int iDt1, int iDt2, int iDt3);

/*! 
 *	\fn		DG_SetMipiDsiMode
 *	\brief	DSI MIPI Capture�� ���� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iDsiEnable				DSI MIPI Capture�� Enable. 
 *	\param	iDsiVideoCommand		DSI MIPI Caputre Option.
 *	\param	iDsiHsyncGen			DSI MIPI Caputre Option.
 *	\param	iDsiVsyncGen			DSI MIPI Caputre Option.
 *	\param	iLanes					DSI MIPI Lane ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_SetMipiDsiMode(HDG hDG, int iDsiEnable, int iDsiVideoCommand, int iDsiHsyncGen, int iDsiVsyncGen);

//
// Device Error & Manage Functions
//

/*! 
 *	\fn		DG_GetMipiError
 *	\brief	Framer ���� �߻��� MIPI Capture ���� ���� ������ �о� �´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pEcc1					ECC1 ������ ���� ������ ����
 *	\param	pEcc2					ECC2 ������ ���� ������ ����
 *	\param	pCrc					CRC ������ ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API int _stdcall DG_GetMipiError(HDG hDG, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		DG_ClrCapMipiError
 *	\brief	Framer ���� �߻��� ���� ������ clear �Ѵ�
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_ClrMipiError(HDG hDG);

/*! 
 *	\fn		DG_GetIsmMipiError
 *	\brief	MIPI ���� �߻��� MIPI Capture ���� ���� ������ �о� �´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pEcc1					ECC1 ������ ���� ������ ����
 *	\param	pEcc2					ECC2 ������ ���� ������ ����
 *	\param	pCrc					CRC ������ ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API int _stdcall DG_GetIsmMipiError(HDG hDG, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		DG_ClrIsmMipiError
 *	\brief	MIPI ���� �߻��� ���� ������ clear �Ѵ�
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_ClrIsmMipiError(HDG hDG);

/*! 
 *	\fn		DG_GetMipiStatus
 *	\brief	MIPI Lane Status�� ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pStatus					Lanes ���¸� ���� DWORD ������ ����
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_GetMipiStatus(HDG hDG, DWORD *pStatus);

/*! 
 *	\fn		DG_ClrMipiStatus
 *	\brief	MIPI Lane Status�� �ʱ�ȭ �Ѵ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_ClrMipiStatus(HDG hDG);

/*! 
 *	\fn		DG_CheckCamSignal
 *	\brief	�־��� �ð� ���� ��� ������ ��� Ƚ���� ���ÿ� �����Ѵ�. 
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	width_ms				������ ms ���� �ð� ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_CheckCamSignal(HDG hDG, DWORD dwWidthMs);

/*! 
 *	\fn		DG_GetCamSignalCount
 *	\brief	������ �� ī�޶��� ��� Ƚ���� ���´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	index					���� Camera Line Index
 *										[11]: Vertical Input line
 *										[10]: Horizontal Input line
 *										[9~0]: Camera Data[9:0] lines
 *	\param	val						��� Ƚ���� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API int _stdcall DG_GetCamSignalCount(HDG hDG, int index, DWORD *val);

//
// Init Sensor
//

/*! 
 *	\fn		DG_SetIsmDefault
 *	\brief	ISM I/O Default �����ϰ� ISM�� Reset �Ѵ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_SetIsmDefault(HDG hDG);

/*! 
 *	\fn		DG_SetIoVolt
 *	\brief	Vio ���� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dVio					Vio ����(0 ~ 3.3v)
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_SetIsmIoVolt(HDG hDG, double dVio);

/*! 
 *	\fn		DG_SetFreq
 *	\brief	Mipi Board�� MCLK ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iFreqMode				Clock Pin ���� ����
 *										FREQ_MODE_FREQ: ������ ���ļ� ���		
 *										FREQ_MODE_FLOAT: ���ļ� �� ���¸� float ���·� ����
 *										FREQ_MODE_HIGH: ������ ���ļ� ���� HIGH ���·� ����
 *										FREQ_MODE_LOW: ������ ���ļ� ���� LOW ���·� ����
 *	\param	dFreq					Mipi Board ���ļ�
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_SetIsmFreq(HDG hDG, int iFreqMode, double dFreq, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_SetCamReset
 *	\brief	Camera Reset �� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iReset					1: Reset, 0: Normal
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_SetIsmReset(HDG hDG, int iReset);

/*! 
 *	\fn		DG_SetIo
 *	\brief	Camera�� ����� 2bit IO Write
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	bGpio					GPIO Signal Write
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_SetIsmIo(HDG hDG, int iIoBit, int iOe, int iIo);

/*! 
 *	\fn		DG_GetIo
 *	\brief	Camera�� ����� 2bit IO Read
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pGpio					GPIO Signal Read
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API   int _stdcall DG_GetIsmIo(HDG hDG, int iIoBit, int *pIo);

//
// Serial I/O functions
//

/*! 
 *	\fn		DG_SetSpiFreq
 *	\brief	SPI ���ļ� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	freq_mhz				SPI Freq(MHz Unit)
 *	\return	������ ���ļ��� ����
 */
DGLIB_API 	int _stdcall DG_SetSpiFreq(HDG hDG, double dFreqMhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_SpiWrite
 *	\brief	SPI Write
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	length					������ ������ ����
 *	\param	last					1�̸� ������ ������ CS�� High�� �ø���.
 *	\param	buf						������ ������
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_SpiWrite(HDG hDG, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SpiRead
 *	\brief	SPI Read. �Լ� ȣ��� CS�� Low�� ����߸���.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	length					�о�帱 ������ ����
 *	\param	last					1�̸� �� �о� �帰 �� CS�� High�� �ø���.
 *	\param	buf						�Ͼ�帱 ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_SpiRead(HDG hDG, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SetI2cFreq
 *	\brief	I2C ���ļ� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	freq_khz				I2C Freq(kHz Unit)
 *	\return	������ ���ļ��� ����
 */
DGLIB_API 	int _stdcall DG_SetI2cFreq(HDG hDG, double dFreqKhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_I2cWrite
 *	\brief	I2C Write
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	length					������ ������ ����
 *	\param	start					���� ������ I2C START issue.
 *	\param	last					���� �� I2C STOP issue.
 *	\param	buf						������ ������
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_I2cWrite(HDG hDG, int iStart, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_I2cRead
 *	\brief	I2C Read.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	length					�о�帱 ������ ����.
 *	\param	last					�� �о� �帰�� I2C STOP issue.
 *	\param	buf						�Ͼ�帱 ������ ����.
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_I2cRead(HDG hDG, int iLast, BYTE *buf, int length);

//
// Mulit Serial Functions
//

/*! 
 *	\fn		DG_SetSpisFreq
 *	\brief	���� ���� SPI�� �� Ư�� SPI�� ���ļ� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iIndex					SPI Index
 *	\param	freq_mhz				SPI Freq(MHz Unit)
 *	\return	������ ���ļ��� ����
 */
DGLIB_API 	int _stdcall DG_SetSpisFreq(HDG hDG, int iIndex, double dFreqMhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_SpisWrite
 *	\brief	���� ���� SPI�� �� Ư�� SPI�� ���� SPI ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iIndex					SPI Index
 *	\param	length					������ ������ ����
 *	\param	last					1�̸� ������ ������ CS�� High�� �ø���.
 *	\param	buf						������ ������
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_SpisWrite(HDG hDG, int iIndex, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SpisRead
 *	\brief	���� ���� SPI�� �� Ư�� SPI�� ���� SPI Read
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iIndex					SPI Index
 *	\param	length					�о�帱 ������ ����
 *	\param	last					1�̸� �� �о� �帰 �� CS�� High�� �ø���.
 *	\param	buf						�Ͼ�帱 ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_SpisRead(HDG hDG, int iIndex, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_SetI2csFreq
 *	\brief	���� ���� I2c�� �� Ư�� I2c�� ���ļ��� ����
 *	\brief	I2C ���ļ� ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iIndex					I2C Index
 *	\param	freq_khz				I2C Freq(kHz Unit)
 *	\return	������ ���ļ��� ����
 */
DGLIB_API 	int _stdcall DG_SetI2csFreq(HDG hDG, int iIndex, double dFreqKhz, double *pSetFreq = NULL);

/*! 
 *	\fn		DG_I2csWrite
 *	\brief	���� ���� I2c�� �� Ư�� I2c�� ���� I2c ����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iIndex					I2C Index
 *	\param	length					������ ������ ����
 *	\param	start					���� ������ I2C START issue.
 *	\param	last					���� �� I2C STOP issue.
 *	\param	buf						������ ������
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_I2csWrite(HDG hDG, int iIndex, int iStart, int iLast, BYTE *buf, int length);

/*! 
 *	\fn		DG_I2csRead
 *	\brief	���� ���� I2c�� �� Ư�� I2c�� ���� I2c Read
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	iIndex					I2C Index
 *	\param	length					�о�帱 ������ ����.
 *	\param	last					�� �о� �帰�� I2C STOP issue.
 *	\param	buf						�Ͼ�帱 ������ ����.
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API 	int	_stdcall DG_I2csRead(HDG hDG, int iIndex, int iLast, BYTE *buf, int length);

//
// MIPI Board API
//

/*! 
 *	\fn		DG_GetMipiVersion
 *	\brief	Mipi Board�� ���� ������ ��´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pBrdVer					������ ���� ������ ����
 *	\param	pCmpVer					Compile Date�� ���� ������ ����
 *	\param	pNumChannel				ä�� ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_GetMipiVersion(HDG hDG, DWORD *pChipVer, DWORD *pBrdVer);

/*! 
 *	\fn		DG_GetMipiBrdId
 *	\brief	Mipi Board�� DIP Switch ID�� ��´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pBrdId					Board ID�� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_GetMipiBrdId(HDG hDG, int *pBrdId);

/*! 
 *	\fn		DG_GpioReadIn
 *	\brief	Mipi Board�� GPIO �� �о����
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pGpio					GPIO Signal�� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_GpioRead(HDG hDG, DWORD *pGpio);

/*! 
 *	\fn		DG_GpioWriteOut
 *	\brief	Mipi Board�� GPIO ���
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dwGpio					GPIO Signal ���
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_GpioWrite(HDG hDG, DWORD dwOe, DWORD dwData);

/*! 
 *	\fn		DG_GetGpio16
 *	\brief	Mipi Board�� GPIO �� �о����(ä�ο� ���� 16��Ʈ)
 *			LOW 16��Ʈ�� 0�� ä��, HIGH 16��Ʈ�� 1�� ä��
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pGpio					GPIO Signal�� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_GetGpio16(HDG hDG, DWORD *pGpio);

/*! 
 *	\fn		DG_SetGpioOe16
 *	\brief	Mipi Board�� GPIO Direction �����ϱ�(ä�ο� ���� 16��Ʈ)
 *			LOW 16��Ʈ�� 0�� ä��, HIGH 16��Ʈ�� 1�� ä��
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dwGpioOe				GPIO Direction 1:OUT, 0:IN
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_SetGpioOe16(HDG hDG, DWORD dwGpioOe);

/*! 
 *	\fn		DG_SetGpio16
 *	\brief	Mipi Board�� GPIO ���(ä�ο� ���� 16��Ʈ)
 *			LOW 16��Ʈ�� 0�� ä��, HIGH 16��Ʈ�� 1�� ä��
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dwGpio					GPIO Signal ���
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� DG_ERR_EXTERNAL_NOT_INIT�� ����
 */
DGLIB_API	int _stdcall DG_SetGpio16(HDG hDG, DWORD dwData);

//
// Test Pattern Enable Functions
//

/*! 
 *	\fn		DG_SetTestCamEn
 *	\brief	Framer���� Test Pattern�� �߻���Ű�� �̸� Capture�ϵ��� ����.
 *			Test Pattern Frame�� Open�� ������ ������ �°� �����ȴ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API int _stdcall DG_SetTestCamEn(HDG hDG, int iEnable);

/*! 
 *	\fn		DG_SetMipiCsiTestCamEn
 *	\brief	MIPI���� Test Pattern�� �߻���Ű�� �̸� Capture�ϵ��� ����.
 *			Test Pattern Frame�� Open�� ������ ������ �°� �����ȴ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
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
// pmulib�� ���� PMU Handle�� �����ϴ� �Լ�
//

/*! 
 *	\fn		DG_GetPmuHandle
 *	\brief	PMU Handle�� ����.
 *			�� PMU Handle�� pmulib�� �����ϴµ� ���ȴ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pHandle					PMU Handle�� ������� ������ ����
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_GetPmuHandle(HDG hDG, HANDLE *pHandle);


/*! 
 *	\fn		DG_ReleasePmuHandle
 *	\brief	����� ���� PMU Handle�� �ǵ��� �ش�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	hHandle					PMU Handle
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_ReleasePmuHandle(HDG hDG, HANDLE hHandle);


//
// Common Functions
//

/*! 
 *	\fn		DG_GetBeagle
 *	\brief	Device�� ����� BEAGLE ������ �о�´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dwData					������
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_GetBeagle(HDG hDG, DWORD *pBeagle);

/*! 
 *	\fn		DG_ClrBeagle
 *	\brief	Device�� ����� BEAGLE ������ �ʱ�ȭ �Ѵ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_ClrBeagle(HDG hDG);

/*! 
 *	\fn		DG_WriteReg
 *	\brief	Device�� Register�� ���� ��ִ´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dwAddr					Register Address
 *	\param	dwData					������
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_WriteReg(HDG hDG, DWORD dwAddr, DWORD dwData);

/*! 
 *	\fn		DG_ReadReg
 *	\brief	Device�� Register���� ���� �д´�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	dwAddr					Register Address
 *	\param	pData					�����͸� ���� ������ ����
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_ReadReg(HDG hDG, DWORD dwAddr, DWORD *pData);

/*! 
 *	\fn		DG_Prog
 *	\brief	Device�� Firmware Program
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	report					report ��ü
 *	\param	filename				�߿��� ���� �̸�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_Prog(HDG hDG, void *report, char *filename);

/*! 
 *	\fn		DG_MipiProg
 *	\brief	Mipi Board�� Firmware Program
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	report					report ��ü
 *	\param	filename				�߿��� ���� �̸�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_MipiProg(HDG hDG, void *report, char *filename);

/*! 
 *	\fn		DG_GetPhaseDelay
 *	\brief	MIPI Phase Delay�� ���� ���´�
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pDelay					���� Phase Delay ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_GetPhaseDelay(HDG hDG, int *pDelay);

/*! 
 *	\fn		DG_IncPhaseDelay
 *	\brief	MIPI Phase Delay�� ���� ������Ŵ
 *	\param	hDG					Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_IncPhaseDelay(HDG hDG);

/*! 
 *	\fn		DG_DecPhaseDelay
 *	\brief	MIPI Phase Delay�� ���� ���ҽ�Ŵ
 *	\param	hDG					Device�� ä���� ��Ÿ���� �ڵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DGLIB_API   int _stdcall DG_DecPhaseDelay(HDG hDG);

/*! 
 *	\fn		DG_GetErrorMsg
 *	\brief	���� �ڵ忡 �ش��ϴ� ���ڿ� ����
 *	\param	error					���� �ڵ�
 *	\return	���� �ڵ忡 �ش��ϴ� ���ڿ� ����
 */
DGLIB_API	const char* _stdcall DG_GetErrorMsg(int error);

#ifdef __cplusplus
}
#endif

#endif

