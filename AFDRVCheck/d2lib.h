
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


//<< �ڵ� ����

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

//>> �ڵ� ����

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
 *	\brief	�ý����� FrameGrabber�� �˻��ؼ� ��ü���� �����ϰ� �ʱ�ȭ �Ѵ�.
 *	\return	��ü�� �Ҵ��ϴµ� �����Ѵٸ� D2_ERR_INSUFFICIENT_RESOURCE�� ����.
 *	\return	�ý��ۿ� ��ġ�� Card�� ���ٸ� D2_ERR_NO_DEVICE�� ����.
 */
DCLIB_API int _stdcall D2_Init();

/*! 
 *	\fn		D2_End
 *	\brief	������ ��ü���� ��� �����Ѵ�.
 *	\return	������ ��ü�� ���ٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_End();

/*! 
 *	\fn		D2_GetVersion
 *	\brief	������ Card�� ���� �������� ��´�.
 *	\param	iCard				Frame Grabber ��ȣ
 *	\param	pDllVer				API ������ ���� ������ ����
 *	\param	pDrvVer				Driver ������ ���� ������ ����
 *	\param	pChipVer			FrameGrabber ������ ���� ������ ����
 *	\return	������ ��ü�� ���ٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_GetVersion(int iCard, DWORD *pDllVer, DWORD *pDrvVer, DWORD *pChipVer);

/*! 
 *	\fn		D2_GetSysInfo
 *	\brief	Card�� Main Board ���� ���� ������ ��´�.
 *	\param	iCard				Frame Grabber ��ȣ
 *	\param	pLanes				PCI-Express Lanes ��
 *	\param	pSpeed				PCI-Express Generation ��
 *	\param	pMaxPayload			Max Payload Size
 *	\param	pMaxReadReq			Max Read Request Size
 *	\return	������ ��ü�� ���ٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_GetSysInfo(int iCard, int *pLanes, int *pSpeed, int *pMaxPayload, int *pMaxReadReq);

/*! 
 *	\fn		D2_GetMaxCards
 *	\brief	�ý��ۿ��� �˻��� Frame Grabber ������ �����Ѵ�.
 *	\return	�ý��ۿ� ��ġ�� Card�� ������ ����
 */
DCLIB_API int _stdcall D2_GetMaxCards();
/*! 
 *	\fn		D2_GetMaxChannels
 *	\brief	������ Device�� Channel ������ �����Ѵ�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\return	������ ī���� ä�� ����
 */
DCLIB_API int _stdcall D2_GetMaxChannels(int iCard);

/*! 
 *	\fn		D2_Open
 *	\brief	������ Frame ������ ��Ʈ�ϰ� Frame ���۸� �Ҵ��Ѵ�.
 *	\param	card_num				Card ��ȣ
 *	\param	channel					channel ��ȣ
 *	\param	iHeight					Frame�� ����
 *	\param	iWidthBytes				���ٿ� �ʿ��� Byte ��
 *	\param	iFrameNum				�Ҵ��� Frame ����
 *	\param	iBitPerPixel			Ŭ���� ��Ʈ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_Open(int iCard,int channel, int Height, int iWidthBytes, int Frames, int BitsPerClk);
/*! 
 *	\fn		D2_Close
 *	\brief	Frame ���۸� �����Ѵ�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 *	\return	BitsPerClk�� ������ ���� �ٸ��ٸ� D2_ERR_OPEN_BITS_PER_CLK_INVALID�� ����;
 *	\return	�̹� Open�Ǿ� �ִٸ� D2_ERR_ALREADY_OPENED�� ����
 *	\return	Frame ���� ���� �ʹ� ���ų� ���ٸ� D2_ERR_FRAMES_INVALID ����
 *	\return	Frame Frame Size�� 0�̰ų� 4�� ����� �ƴ϶�� D2_ERR_FRAME_SIZE_INVALID ����
  */
DCLIB_API int _stdcall D2_Close(int iCard, int channel);

/*! 
 *	\fn		D2_Start
 *	\brief	Frame Capture�� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_Start(int iCard, int channel);
/*! 
 *	\fn		D2_Stop
 *	\brief	Frame Capture�� �ߴ�
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_Stop(int iCard,int channel);

/*! 
 *	\fn		D2_GetFrame
 *	\brief	Frame Grabber�� ���� �� Frame�� �̹��� �����͸� ���´�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	blocked					1�̸� �̹��� �����͸� ���� �� ���� block�Ǿ� ��ٸ���.
 *	\param	buf						���� �̹��� ������ ������
 *	\param	length					���� �̹����� ũ��.
 *	\param	eof_length				eof �̺�Ʈ�� �߻��� �̹����� ũ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_GetFrame(int iCard,int channel, int blocked, BYTE **buf, WORD *length, DWORD *eof_length);

/*! 
 *	\fn		D2_GetFrameWait
 *	\brief	Frame Grabber�� ���� �ֽ� Frame �����͸� ���´�.
 *			Frame Data�� ���� ������ �� �Լ��� Block�ǰ� D2_CancelGetFrame()�� ȣ���ϸ� ���ϵȴ�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_GetFrameWait(int iCard, int channel, BYTE **buf);

/*! 
 *	\fn		D2_GetFrame
 *	\brief	D2_GetFrame�� block �Ǿ� ���� ��� block�� �����ϰ� �ٷ� ���� ��Ų��.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_CancelGetFrame(int iCard,int channel);

//
// Framer Information
//

/*! 
 *	\fn		D2_SetCapInfo
 *	\brief	Capture�ϴµ� �ʿ��� �ɼ��� ����.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	iStartH					���� ���� ��ȣ�� ������ ������ ������ Ŭ�� �ε����� 0���� �ϰ�, 
 *									���Ŀ� Ŭ���� ���� �Կ� ���� �����ϰ� �ȴ�. �̶��� ������ ������ �����ϴ� �ε��� ���̴� .
 *	\param	iStartV					���� ���� ��ȣ�� ����� ������ ���� �ε����� 0�̶� �ϸ� ���Ŀ� �� ���� ���� ��ȣ�� 
 *									���� �� ������ ���� �ε����� ���� �ϰ� �ȴ�. �� ���� ȭ���� ������� ���� �ε����� ���ϴ� �Ķ�����̴�.
 *	\param	ClkEdgeHigh				Camera���� ������ Ŭ���� ��� �������� �ȼ� �����͸� ���� ���ΰ��� ���Ѵ�. 1 : ��� ����, 0 : �ϰ� ����.
 *	\param	HSyncEdgeHigh			���򵿱��ȣ���� ��� ������ ������ �δ°��� ���Ѵ�. 1 : ��� ����, 0 : �ϰ� ����.
 *	\param	VSyncEdgeHigh			���������ȣ���� ��� ������ ������ �δ°��� ���Ѵ�. 1 : ��� ����, 0 : �ϰ� ����.
 *	\param	SyncValidEn				���򵿱� ��ȣ�� ���� ��ȣ�� ����ϴ� ���� �ƴ϶� Active�������� 
 *									������ �ؾ� �� Valid��ȣ�� ��� ���θ� �����ϴ� �Է��̴�. 
 *									1�̸� Valid��ȣ�� ����ϰ� 0�̸� ���� ��ȣ�� ����Ѵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_SetCapInfo(int iCard,int channel, int iStartH, int iStartV, int ClkEdgeHigh, int HSyncEdgeHigh, int VSyncEdgeHigh, int SyncValidEn);

/*! 
 *	\fn		D2_SetMipiInfo
 *	\brief	MIPI ����. DT�� 4������, VC�� 1�� ������ ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	VirtualChannel			MIPI packet���� ���ϴ� ���� ä���� �����Ѵ�. ���� 0�� ����Ѵ�. 
 *	\param	DataType				MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�.
 *	\param	DataType1				MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�
 *	\param	DataType1				MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�
 *	\param	DataType1				MIPI packet���� �ޱ⸦ ���ϴ� ����Ÿ Ÿ���� �����Ѵ�
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_SetMipiInfo(int iCard, int channel, int iVirtualChannel, int iDataType, int iDataType1, int iDataType2,int iDataType3);

/*! 
 *	\fn		D2_SetMipiDsiInfo
 *	\brief	DSI MIPI Capture�� ���� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	dsi_enable				DSI MIPI Capture�� Enable. 
 *	\param	dsi_video_or_command	DSI MIPI Caputre Option.
 *	\param	dsi_hsync_gen			DSI MIPI Caputre Option.
 *	\param	dsi_vsync_gen			DSI MIPI Caputre Option.
 *	\param	lanes					DSI MIPI Lane ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_SetMipiDsiInfo(int iCard, int channel, int dsi_enable,int dsi_video_or_command,int dsi_hsync_gen,int dsi_vsync_gen,int lanes);

/*! 
 *	\fn		D2_GetCapMipiError
 *	\brief	Framer ���� �߻��� MIPI Capture ���� ���� ������ �о� �´�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	pEcc1					ECC1 ������ ���� ������ ����
 *	\param	pEcc2					ECC2 ������ ���� ������ ����
 *	\param	pCrc					CRC ������ ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API int _stdcall D2_GetCapMipiError(int iCard, int iChannel, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		D2_ClrCapMipiError
 *	\brief	Framer ���� �߻��� ���� ������ clear �Ѵ�
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_ClrCapMipiError(int iCard, int iChannel);

/*! 
 *	\fn		D2_SetCapCsiTestCamEn
 *	\brief	Framer���� Test Pattern�� �߻���Ű�� �̸� Capture�ϵ��� ����.
 *			Test Pattern Frame�� Open�� ������ ������ �°� �����ȴ�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_SetCapCsiTestCamEn(int iCard, int channel, int enable);

/*! 
 *	\fn		D2_CheckCamLines
 *	\brief	�־��� �ð� ���� ��� ������ ��� Ƚ���� ���ÿ� �����Ѵ�. 
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	width_ms				������ ms ���� �ð� ��
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_CheckCamLines(int iCard,int channel, DWORD width_ms);
/*! 
 *	\fn		D2_GetCamLineToggleTimes
 *	\brief	������ �� ī�޶��� ��� Ƚ���� ���´�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	index					���� Camera Line Index
 *										[11]: Vertical Input line
 *										[10]: Horizontal Input line
 *										[9:0]: Camera Data[9:0] lines
 *	\param	val						��� Ƚ���� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API int _stdcall D2_GetCamLineToggleTimes(int iCard,int channel, int index, DWORD *val);

//
// Link API
//

/*! 
 *	\fn		D2_GetLinkStatus
 *	\brief	Frame Grabber�� MIPI Board ������ line ���¸� ����.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	pClkLocked				Clock Locked ���¸� ���� ������ ����
 *	\param	pPhaseLocked			Phase Locked ���¸� ���� ������ ����
 *	\param	pLinked					���� ���¸� ���� ������ ����
 *	\param	pSynced					Line�� ��ũ�� ���¸� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_GetLinkStatus(int iCard, int *pClkLocked, int *pPhaseLocked, int *pLinked, int *pSynced);

/*! 
 *	\fn		D2_SetLinkReset
 *	\brief	Frame Grabber�� MIPI Board ������ Line Sync�� Reset �Ѵ�
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	iReset					1: Reset
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_SetLinkReset(int iCard, int iReset);

//
// Serial I/O functions
//

/*! 
 *	\fn		D2_SetSpiFreq
 *	\brief	SPI ���ļ� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	freq_mhz				SPI Freq(MHz Unit)
 *	\return	������ ���ļ��� ����
 */
DCLIB_API 	double _stdcall D2_SetSpiFreq(int iCard, int channel, double freq_mhz);

/*! 
 *	\fn		D2_SpiWrite
 *	\brief	SPI Write
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	length					������ ������ ����
 *	\param	last					1�̸� ������ ������ CS�� High�� �ø���.
 *	\param	buf						������ ������
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API 	int	_stdcall D2_SpiWrite(int iCard, int channel, int length, BYTE last, BYTE *buf);

/*! 
 *	\fn		D2_SpiRead
 *	\brief	SPI Read. �Լ� ȣ��� CS�� Low�� ����߸���.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	length					�о�帱 ������ ����
 *	\param	last					1�̸� �� �о� �帰 �� CS�� High�� �ø���.
 *	\param	buf						�Ͼ�帱 ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API 	int	_stdcall D2_SpiRead(int iCard, int channel, int length, BYTE last, BYTE *buf);

/*! 
 *	\fn		D2_SetI2cFreq
 *	\brief	I2C ���ļ� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	freq_khz				I2C Freq(kHz Unit)
 *	\return	������ ���ļ��� ����
 */
DCLIB_API 	double _stdcall D2_SetI2cFreq(int iCard, int channel, double freq_khz);

/*! 
 *	\fn		D2_I2cWrite
 *	\brief	I2C Write
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	length					������ ������ ����
 *	\param	start					���� ������ I2C START issue.
 *	\param	last					���� �� I2C STOP issue.
 *	\param	buf						������ ������
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API 	int	_stdcall D2_I2cWrite(int iCard, int channel, int length, BYTE start, BYTE last, BYTE *buf);
/*! 
 *	\fn		D2_I2cRead
 *	\brief	I2C Read.
 *	\param	card_num				Frame Grabber ��ȣ.
 *	\param	channel					����� channel ��ȣ.
 *	\param	length					�о�帱 ������ ����.
 *	\param	last					�� �о� �帰�� I2C STOP issue.
 *	\param	buf						�Ͼ�帱 ������ ����.
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API 	int	_stdcall D2_I2cRead(int iCard, int channel, int length, BYTE last, BYTE *buf);

//
// MIPI API
//

/*! 
 *	\fn		D2_SetMipiControl
 *	\brief	MIPI ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	iLanes					MIPI Lanes
 *	\param	iEnc					MIPI 8b9b encoded
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_SetMipiControl(int iCard, int iChannel, int iLanes, int iEnc);

/*! 
 *	\fn		D2_GetMipiError
 *	\brief	MIPI Board �߻��� MIPI Capture ���� ���� ������ �о� �´�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	pEcc1					ECC1 ������ ���� ������ ����
 *	\param	pEcc2					ECC2 ������ ���� ������ ����
 *	\param	pCrc					CRC ������ ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API int _stdcall D2_GetMipiError(int iCard, int iChannel, int *pEcc1, int *pEcc2, int *pCrc);

/*! 
 *	\fn		D2_ClrMipiError
 *	\brief	MIPI Board ���� �߻��� ���� ������ clear �Ѵ�
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API int _stdcall D2_ClrMipiError(int iCard, int iChannel);


/*! 
 *	\fn		D2_SetMipiCsiTestCamEn
 *	\brief	MIPI���� Test Pattern�� �߻���Ű�� �̸� Capture�ϵ��� ����.
 *			Test Pattern Frame�� Open�� ������ ������ �°� �����ȴ�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	enable					1: Test Pattern Enable, 0: Disable
 *	\return	���� ��ü�� �������� �ʾҴٸ� D2_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API	int _stdcall D2_SetMipiCsiTestCamEn(int iCard, int channel, int enable);

/*! 
 *	\fn		D2_GetMipiVersion
 *	\brief	Mipi Board�� ���� ������ ��´�.
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					Mipi Board�� ä�� ��ȣ
 *	\param	pBrdVer					������ ���� ������ ����
 *	\param	pCmpVer					Compile Date�� ���� ������ ����
 *	\param	pNumChannel				ä�� ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API	int _stdcall D2_GetMipiVersion(int iCard, int channel, DWORD *pBrdVer, DWORD *pCmpVer, int *pNumChannel);

/*! 
 *	\fn		D2_SetMipiVref
 *	\brief	MIPI Signal �� ���� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	iVref					MIPI Vref Volt
 *										0: 0.5v
 *										1: 0.68v
 *										2: 0.8v
 *										3: undefined
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_SetMipiVref(int iCard, int iChannel, int iVref);

/*! 
 *	\fn		D2_SetMipiVioDac
 *	\brief	Vio ���� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	dVio					Vio ����(0 ~ 1.8v)
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_SetMipiVioDac(int iCard, int iChannel, double dVio);

/*! 
 *	\fn		D2_SetMipiFreq
 *	\brief	Mipi Board�� MCLK ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	iFreqMode				Clock Pin ���� ����
 *										FREQ_MODE_FREQ: ������ ���ļ� ���		
 *										FREQ_MODE_FLOAT: ���ļ� �� ���¸� float ���·� ����
 *										FREQ_MODE_HIGH: ������ ���ļ� ���� HIGH ���·� ����
 *										FREQ_MODE_LOW: ������ ���ļ� ���� LOW ���·� ����
 *	\param	dFreq					Mipi Board ���ļ�
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API	int _stdcall D2_SetMipiFreq(int iCard, int iChannel, int iFreqMode, double dFreq);

/*! 
 *	\fn		D2_GpioReadIn
 *	\brief	Mipi Board�� GPIO �� �о����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	pGpio					GPIO Signal�� ���� ������ ����
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API	int _stdcall D2_GpioReadIn(int iCard, int iChannel, DWORD *pGpio);

/*! 
 *	\fn		D2_GpioWriteOut
 *	\brief	Mipi Board�� GPIO ���
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	dwGpio					GPIO Signal ���
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API	int _stdcall D2_GpioWriteOut(int iCard, int iChannel, DWORD dwData);

/*! 
 *	\fn		D2_GpioWriteOE
 *	\brief	Mipi Board�� GPIO Output Enable�� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	dwOutEnable				bit�� 1�̸� Output, 0�̸� Input
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
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
 *	\brief	Camera Reset �� ����
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	iReset					1: Reset, 0: Normal
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_SetCamReset(int iCard, int iChannel, int iReset);

/*! 
 *	\fn		D2_SetCamGpio
 *	\brief	Camera�� ����� 2bit GPIO Write
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	bGpio					GPIO Signal Write
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_SetCamGpio(int iCard, int iChannel, BYTE bGpio);

/*! 
 *	\fn		D2_GetCamGpio
 *	\brief	Camera�� ����� 2bit GPIO Read
 *	\param	card_num				Frame Grabber ��ȣ
 *	\param	channel					����� channel ��ȣ
 *	\param	pGpio					GPIO Signal Read
 *	\return	���� ������ ��Ʈ���� �ʾҴٸ� D2_ERR_EXTERNAL_NOT_INIT�� ����
 */
DCLIB_API   int _stdcall D2_GetCamGpio(int iCard, int iChannel, BYTE *pGpio);


/*! 
 *	\fn		DG_GetPmuHandle
 *	\brief	PMU Handle�� ����.
 *			�� PMU Handle�� pmulib�� �����ϴµ� ���ȴ�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	pHandle					PMU Handle�� ������� ������ ����
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API   int _stdcall D2_GetPmuHandle(int iCard, HANDLE *pHandle);


/*! 
 *	\fn		DG_ReleasePmuHandle
 *	\brief	����� ���� PMU Handle�� �ǵ��� �ش�.
 *	\param	hDG						Device�� ä���� ��Ÿ���� �ڵ�
 *	\param	hHandle					PMU Handle
 *	\return	���� ��ü�� �������� �ʾҴٸ� DG_ERR_NOT_INITIALIZED�� ����
 */
DCLIB_API   int _stdcall D2_ReleasePmuHandle(int iCard, HANDLE hHandle);



/*! 
 *	\fn		D2_GetErrorMsg
 *	\brief	���� �ڵ忡 �ش��ϴ� ���ڿ� ����
 *	\param	error					���� �ڵ�
 *	\return	���� �ڵ忡 �ش��ϴ� ���ڿ� ����
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

