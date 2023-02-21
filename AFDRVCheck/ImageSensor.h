#pragma once

#include "Common.h"

/************************************************************************/
/* IIC MODE Change									                    */
/************************************************************************/
#define		IIC_2BY_1or2BY  0x00			// 2Byte + 1 or 2Byte
#define		IIC_1BYTE1BYTE	0x01			// 1Byte + 1Byte
#define		IIC_1BYTE2BYTE	0x02			// 1Byte + 2Byte
#define		IIC_2BYTE1BYTE	0x04			// 2Byte + 1Byte
#define		IIC_2BYTE2BYTE	0x08			// 2Byte + 2Byte

/************************************************************************/
/* Clock Info									                        */
/************************************************************************/
#define		J_CLKEDGELO		0x00
#define		J_CLKEDGEHI		0x01
#define		J_HSYEDGELO		0x00
#define		J_HSYEDGEHI		0x02
#define		J_VSYEDGELO		0x00
#define		J_VSYEDGEHI		0x04
#define		J_CCLKEDGEH		0x08
#define		J_CHSYEDGEH		0x10
#define		J_CVSYEDGEH		0x20
//#define	???????????		0x40
#define		J_USINGCLK		0x80		

// nENBStat		
#define		J_ENABLE_HI		0x01
#define		J_ENABLE_LO		0x02


// 20170802 X1_E1 Configuration 
#define PREVIEW_WIDTH		4000 
#define PREVIEW_HEIGHT		3000 
#define SNAP_WIDTH			8000 
#define SNAP_HEIGHT			6000 
#define PREVIEW_REG_FILE	"IMX586_P.dat"//"IMX363_M2_P_2016x1512.dat" 
#define SNAP_REG_FILE		"IMX586_S.dat"//"IMX363_M2_S_4032x3024.dat"
#define SADDR_SENSOR 0x34 
#define SENSOR_TYPE 1 // 1=SONY 2=LSI
//////////////////////////////////////////////////////////////////////
// 20180802 //20180822
#define AFI2C 0
#define SonyMaker 1
#define SLSIMaker 3

typedef struct _st_SensorInfo {
	WORD nWidth;	// Width
	WORD nHeight;	// Height
	WORD nDiagon;	// Diagonal
	WORD nSlaveAdd;	// Slave Address
	//DWORD dwStatus;
	BYTE nIICType;	// IIC type 
	BYTE nIICDelay;	// IIC Delay for Express
	BYTE nClkInfo;	// Sensor Clock info, clk, Hsync, Vsync
	BYTE nENBStat;	// Enable Status

	int nIICSpeed;

	//skykiss added below
	int nBlackLevel;
	int nPreviewScreenMode;
	int nImageFormat;
} SensorInfo;

class CImageSensor
{
public:
	CImageSensor(void);
	~CImageSensor(void);

	UINT32 PowerUp_Xplus(void); // 20170331int PowerUp_Xplus(void);
	int Init_Sensor_Xplus_Internal(BOOL bModeChange);
	int Init_Sensor_Xplus(int* regvalue_a, int* regvalue_b, int* regvalue_c, int* regvalue_d, int* regdelay, int regcount, int iictype, BOOL bModeChange = FALSE);
	int I2C_Read_Xplus(int index);
	int I2C_Write_Xplus(int addr, int data);
	int I2C_WORD_Read_Xplus(int index);
	int I2C_WORD_Write_Xplus(int index, int data);
	int Change_Resolution_Xplus(int mode);
	int SetInterface_Xplus(void);
	int check_FuseID_Xplus(UCHAR* pFuseID, int BufferSize);
	int PowerDown_Xplus(void);
	int PowerStat_Xplus(void);
	int GetSensorInfo_Xplus(void *pData);
	int CheckI2C_Xplus(void);
	//int GetFrame_Xplus(void **pData, DWORD *pLength); //20180813 syz
	int InitFrameInfo(void);
	int ImageDataBit(void);

};