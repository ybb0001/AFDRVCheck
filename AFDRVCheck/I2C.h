#pragma once
#include "Common.h"
//#pragma comment(lib,"atlsd.lib")

//#define HW_IIC

#define I2C_DLY_CNT		1
#define I2C_HIGHLOW		1	//I2C master ack polarity

#define RST_ACTIVE_POL	0	//sensor reset active polarity
#define MCLK_SENSOR		24

//20180808 syz check
#define PCI_C_PHY_ENABLE			1

//g_dcGPIO -> GPIO out
// #define	GPIO_EXPRESS_CYL_01__ON	0x00000100L 		// GP_C8	Cylinder 01		1.2V
// #define	GPIO_EXPRESS_CYL_02__ON	0x00000200L			// GP_C9	Cylinder 02		D2.8V
// #define	GPIO_EXPRESS_CYL_03__ON	0x00000400L			// GP_C10	Cylinder 03		D1.8V
#define	GPIO_EXPRESS_CYL_01__ON	0x00000200L 		// GP_C8	Cylinder 01		1.2V
#define	GPIO_EXPRESS_CYL_02__ON	0x00000400L			// GP_C9	Cylinder 02		D2.8V
#define	GPIO_EXPRESS_CYL_03__ON	0x00001000L			// GP_C10	Cylinder 03		D1.8V

#define	GPIO_EXPRESS_LEDPOWERON	0x00000800L			// GP_C11	LED+
#define	GPIO_EXPRESS_AFPOWER_ON	0x00001000L			// GP_C12	DVDD_AF
#define	GPIO_EXPRESS_AVDD_28_ON	0x00002000L			// GP_C13	MT9V113_		A2.8V
#define	GPIO_EXPRESS_LINECK_ON_	0x00004000L			// GP_C14	Eclair			Line Check/Spare
#define	GPIO_EXPRESS_VGA__ENABL	0x00008000L			// GP_C15	NE_ENB			VGA_ENB
#define	GPIO_EXPRESS_MEGA_RESET	0x00010000L			// GP_C16	MT9V113_		VGA/Mega Reset
#define	GPIO_EXPRESS_MEGA_ENABL	0x00020000L			// GP_C17	MV9317 Reset	Mega Enable
#define	GPIO_EXPRESS_GPIO_ALL	0x0003ff00L			// GP_C8~GP_C17

#define	GPIO_EXPRESS_GPIO_C08	0x00000100L			//	GP_C08
#define	GPIO_EXPRESS_GPIO_C09	0x00000200L			//	GP_C09
#define	GPIO_EXPRESS_GPIO_C10	0x00000400L			//	GP_C10
#define	GPIO_EXPRESS_GPIO_C11	0x00000800L			//	GP_C11
#define	GPIO_EXPRESS_GPIO_C12	0x00001000L			//	GP_C12
#define	GPIO_EXPRESS_GPIO_C13	0x00002000L			//	GP_C13
#define	GPIO_EXPRESS_GPIO_C14	0x00004000L			//	GP_C14
#define	GPIO_EXPRESS_GPIO_C15	0x00008000L			//	GP_C15
#define	GPIO_EXPRESS_GPIO_C16	0x00010000L			//	GP_C16
#define	GPIO_EXPRESS_GPIO_C17	0x00020000L			//	GP_C17

//IIC & RESET signal generation
#define	ETC_DCRST		0x00000004
#define	ETC_DCSCL		0x00000002
#define	ETC_DCSDA_OE	0x00000001
#define	ETC_DCSDA		0x00000001

// Error codes
//typedef enum E_BOARD_ERROR {
//	BOARD_SUCCESS = 0,
//	INVALID_DEVICE_NUM,
//	INVALID_CAPTURE_VER,
//	INVALID_MIPI_VER,
//	BOARD_INIT_ERROR,
//	BOARD_IIC_ERROR
//};

#define MAKEDWORD(a, b)		((DWORD)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))

#define	DCRST		0x00000004
#define	DCSCL		0x00000002
#define	DCSDA_OE	0x00000001
#define	DCSDA		0x00000001
#define	DCWR(d)		DC_WriteReg(cur_card, 0x8b0, d)
#define	DCRD(d)		DC_ReadReg(cur_card, 0x8b0, &d)
#define	DCWR_0(d)	DC_WriteReg(0, 0x8b0, d)
#define	DCRD_0(d)	DC_ReadReg(0, 0x8b0, &d)




enum E_BOARD_ERROR {
	BOARD_SUCCESS = 0,
	INVALID_DEVICE_NUM,
	INVALID_CAPTURE_VER,
	INVALID_MIPI_VER,
	BOARD_INIT_ERROR,
	BOARD_IIC_ERROR
};

typedef struct _tag_card_info {
	int nBoardInstalled;
	int nCardnum;		//for express card	
	int nChannel;		//for express card	
	DWORD DllVer;		//for express card	
	DWORD DrvVer;		//for express card	
	DWORD ChipVer;		//for express card	
	DWORD BoardVer;
	//20180828
	int Lanes;
	int Gen;
	int MaxPayLoad;
	int MaxReadReq;

}card_info;

typedef struct _tag_frame_info {
	int nHeight;
	int nWidth;
	int nFrames;		//for express card	
	int nBitperClock;	//for express card	
	int Imageformat;
	BOOL bIsChannelOpen;
	FRAME_MODE nFrameMode;
	int nBlackLevel;
	int nLane;
} frameinfo;

class CI2C
{
public:
	CI2C(void);
	~CI2C(void);

	unsigned int m_hCapture;

//----------------------------------------------------------------------------------------------------//
	// Frame Grabber
	//----------------------------------------------------------------------------------------------------//
	int Card_Init(int BD_ID);
	int Card_End(void);
	int Set_Mclk_Sensor(int targetFreq_MHz);
    int GetFrame(BYTE **pData, DWORD *pLength);
	int FrameGrabberGetMaxCards(void); //20170417
	int FrameGrabberGetVersion(int card_num,DWORD *DllVer,DWORD *DrvVer,DWORD *ChipVer); // 20170417

	int SensorDataCheckFunction(); 	// 20180827
	int FrameGrabberGetVersion_2CH(unsigned int hDG, DWORD *pDllVer, DWORD *pDrvVer, DWORD *pChipVer, DWORD *pBrdVer); // 20180828
	int MIPIBoardVersion_2CH(unsigned int hDG, DWORD *pChipVer, DWORD *pBrdVer); // 20180828


	int PowerUp_BufferBD(void);
	//int Init_BufferBD(void);
	int I2C_Read(int saddr, int index, int mode);
	int I2C_Read(int saddr, int index, int mode, int OIS_Delay); 	// 20170330

	int I2C_Read_Burst(int saddr, int index, int ByteNumIndex, char *pDataBuf, int ByteNumData);
	int I2C_Read_Burst_uc(int saddr, int index, int ByteNumIndex, unsigned char *pDataBuf, int ByteNumData)	;
	int I2C_Write(int saddr, int addr, int data, int mode = I2CMODE_SINGLEADDRDATA);
	int I2C_Write_Burst(int saddr, int index, int ByteNumIndex, char *pDataBuf, int ByteNumData);
	int I2C_Write_Burst_uc(int saddr, int index, int ByteNumIndex, unsigned char *pDataBuf, int ByteNumData);
	int SetCapInfo(int channel,int HBP, int VBP, int ClkEdgeHigh, int HSyncEdgeHigh, int VSyncEdgeHigh, int LineArea, int Input10Bits,DWORD jpg_eof_sig);
	int Channel_Open(int Height, int Width, int Frames,int BitPerClock);
	int Channel_Close(BOOL bModeChange = FALSE);

	// 20170331int Z_Set_MIPI_FPGA(int nOn1Off0=0, int nPwdn=0, BYTE DataType=0x1E, int nLane=2, DWORD *dwData=NULL);
	UINT32 Z_Set_MIPI_FPGA(int nOn1Off0=0, int nPwdn=0, BYTE DataType=0x1E, int nLane=2, DWORD *dwData=NULL);

	int Z_Set_MIPI_ST2(int nLaneClock=400, int nMipi=1, int nNoBypass=1, int n2Lane=1, WORD nDatatype=0x2B, WORD nDatatype2=0x0C, int nBit=8,int n081Rev0=0);

	//----------------------------------------------------------------------------------------------------//
	// Reset
	//----------------------------------------------------------------------------------------------------//
	void RST_High();
	void RST_Low();

	//----------------------------------------------------------------------------------------------------//
	// SW I2C
	//----------------------------------------------------------------------------------------------------//
	int SW_I2cWrite(int card_num,int channel,BYTE data);
	int SW_I2cRead(int card_num,int channel,int hilo);
	int SW_I2cStart(int card_num,int channel);
	void SW_I2cStop(int card_num,int channel);

	//----------------------------------------------------------------------------------------------------//
	// HW I2C
	//----------------------------------------------------------------------------------------------------//
	int	HW_I2cWrite_N_N(BYTE slvAddr, int numbers,...);
	int	HW_I2cRead_0_N(BYTE slvAddr, int numbers, BYTE *data);
	int HW_I2cRead_1_N(BYTE slvAddr, BYTE addr, int len, BYTE *datBuf);
	int HW_I2cRead_2_N(BYTE slvAddr, int addr, int len, BYTE *datBuf);
	

public:
	DWORD m_dcGPIO;
	//DWORD m_dwDCout;
	int cur_card;

	DWORD dwDCout;

	DWORD m_dwIicPinOut;	//scl high, sda high, reset high
	int m_IicDcHandle;
	int channel = 0;
	card_info g_cardinfo;

};

