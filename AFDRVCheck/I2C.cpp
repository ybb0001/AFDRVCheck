#include "StdAfx.h"
#include "I2C.h"
//#include "ImageSensor.h"
#include "Common.h"
#include "dclibdef.h"
#include "dglib.h"

//card_info g_cardinfo; 
frameinfo g_frameinfo;

#define AFI2C 0
#define SonyMaker 1
#define SLSIMaker 3

CI2C::CI2C(void)
{
	m_dwIicPinOut = ETC_DCSCL | ETC_DCRST & ~ETC_DCSDA_OE;
	m_IicDcHandle = 0;
}

CI2C::~CI2C(void)
{
}

//----------------------------------------------------------------------------------------------------//
// Frame Grabber
//----------------------------------------------------------------------------------------------------//


//20180827
int CI2C::SensorDataCheckFunction() // 20180827 ()option
{

	// 20180828 test 50(NG) -> 100(OK)
	unsigned char LinecheckDelay = 100;//50;

	DWORD dwHsync, dwVsync, dwPclk; 	

	DG_CheckCamSignal(m_hCapture, LinecheckDelay);

	IIC_Delay(100);

    DG_GetCamSignalCount(m_hCapture, 10, &dwHsync); return dwHsync; 

	return 99;

}




int CI2C::Card_Init(int BD_ID)
{
	int ret;
	// const int channel	= 0;

//20180813 syz

#if PCI_C_PHY_ENABLE == 1

	//20180817
	g_cardinfo.nCardnum = 0;
	g_cardinfo.nChannel = 0;
	//1. Initialize & getting card info
	ret = DG_Init();//DC_Init();
	if(ret != 0){ return ret; }

	ret = DG_OpenHandleByCardNum(g_cardinfo.nCardnum, g_cardinfo.nChannel, &m_hCapture, NULL, NULL);
	if(ret != 0){ return ret; }

	DG_GetVersion(m_hCapture, &g_cardinfo.DllVer, &g_cardinfo.DrvVer, &g_cardinfo.ChipVer, &g_cardinfo.BoardVer);
	//DG_GetPcieInfo(m_hCapture, &g_cardinfo.Lanes, &g_cardinfo.Gen, &g_cardinfo.MaxPayLoad, &g_cardinfo.MaxReadReq); // 20180828

	//char buf[256];
	TCHAR buf[256];
	wsprintf(buf, LPWSTR("[Version : DllVer = 0x%04x, DrvVer = 0x%04x, ChipVer = 0x%04x]\n"),	g_cardinfo.DllVer, g_cardinfo.DrvVer, g_cardinfo.ChipVer);
	TRACE(buf);

	return 0;	//No error

#else

	//1. Initialize & getting card info
	ret = DC_Init();
	if(ret != 0){ return ret; }

	g_cardinfo.nBoardInstalled = DC_GetMaxCards();
	g_cardinfo.nCardnum = 0;
	g_cardinfo.nChannel = 0;
	DC_GetVersion(g_cardinfo.nCardnum, &g_cardinfo.DllVer, &g_cardinfo.DrvVer, &g_cardinfo.ChipVer);

	char buf[256];
	wsprintf(buf, "[Version : DllVer = 0x%04x, DrvVer = 0x%04x, ChipVer = 0x%04x]\n",
		g_cardinfo.DllVer, g_cardinfo.DrvVer, g_cardinfo.ChipVer);
	TRACE(buf);
	//2. power Up & set clock

	PowerUp_BufferBD();	//including init GPIO

	//3. IIC setting 

#ifdef HW_IIC
	DC_SetSpiI2cMode(g_cardinfo.nCardnum, 1);
	DC_SetHwI2cFreq(g_cardinfo.nCardnum, 200.0f);
	TRACE("_HW_IIC_MODE_%d \n", DC_GetSpiI2cMode(g_cardinfo.nCardnum));
#else
	DC_SetSpiI2cMode(g_cardinfo.nCardnum, 0);
	DC_I2cInit(g_cardinfo.nCardnum, g_cardinfo.nChannel,I2C_DLY_CNT, RST_ACTIVE_POL);

	// 20170726
	m_dwIicPinOut &= ~ETC_DCRST;                                     
	DC_WriteReg(m_IicDcHandle, 0x8b0, m_dwIicPinOut);
#endif

	return 0;	//No error

#endif

}

int CI2C::Card_End(void)
{ 
//20180813 syz
#if PCI_C_PHY_ENABLE == 1
	return DG_End();
#else
	return DC_End();
#endif
}

int CI2C::Set_Mclk_Sensor(int targetFreq_MHz)
{
	return DC_SetClkOutFreq1(g_cardinfo.nCardnum, targetFreq_MHz*5, 200, 0);
}

int CI2C::GetFrame(BYTE **pData, DWORD *Length)
{
//20180813 syz
#if PCI_C_PHY_ENABLE == 1
	int rawcnt = 0;
	return DG_GetFrame(m_hCapture, 2000, (unsigned char **)pData, &rawcnt, Length);
#else
	int ret = DC_GetFrame(g_cardinfo.nCardnum, g_cardinfo.nChannel, 1, (BYTE **)pData, NULL, pLength);
	TRACE("_DC_GETFRAME_: %d \n", ret);
	return 0;	
#endif
}

//20170417
int CI2C::FrameGrabberGetMaxCards()
{
	return DC_GetMaxCards();
}



int CI2C::FrameGrabberGetVersion(int card_num,DWORD *DllVer,DWORD *DrvVer,DWORD *ChipVer)
{
	return DC_GetVersion( card_num, DllVer, DrvVer, ChipVer);

}
//20180828
int CI2C::FrameGrabberGetVersion_2CH(HDG hDG, DWORD *pDllVer, DWORD *pDrvVer, DWORD *pChipVer, DWORD *pBrdVer)
{
	return DG_GetVersion(hDG, pDllVer, pDrvVer, pChipVer, pBrdVer);

}


int CI2C::MIPIBoardVersion_2CH(HDG hDG, DWORD *pChipVer, DWORD *pBrdVer)
{
	return DG_GetMipiVersion(hDG, pChipVer, pBrdVer);

}



int CI2C::PowerUp_BufferBD(void)
{	
	DC_GpioWriteOE(g_cardinfo.nCardnum, 0x0003ff00);			// 하위 8bit 입력, 10bit 출력 전환	enable out
	m_dcGPIO = 0;
	m_dcGPIO = (GPIO_EXPRESS_CYL_01__ON | GPIO_EXPRESS_CYL_02__ON | GPIO_EXPRESS_CYL_03__ON);	
	DC_GpioWriteOut(g_cardinfo.nCardnum, m_dcGPIO);
	return 0;
}

int CI2C::I2C_Read(int saddr, int index, int mode, int OIS_Delay)	//mode 0 // 20170330
{
	BYTE AddrH, AddrL, DataH, DataL;
	int Data;
	int ack = 0;

	ack += DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);	IIC_Delay(OIS_Delay);       // 20170223
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr & 0x000000FE));	IIC_Delay(OIS_Delay); // 20170223

	if(mode & I2CMODE_DOUBLEADDR){
		AddrH = (BYTE)((index >> 8) & 0x000000ff);
		ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrH);					IIC_Delay(OIS_Delay); // 20170223
	}

	AddrL = (BYTE)(index & 0x000000ff);
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrL);				    	IIC_Delay(OIS_Delay); // 20170223

	//DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);
	ack += DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);						     	IIC_Delay(OIS_Delay); // 20170223 //restart condition
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr | 0x00000001));	IIC_Delay(OIS_Delay); // 20170223

	if(mode & I2CMODE_DOUBLEDATA){
		DataH = DC_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, 0);						IIC_Delay(OIS_Delay); // 20170223
	}

	DataL = DC_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, I2C_HIGHLOW);					IIC_Delay(OIS_Delay); // 20170223
	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);										IIC_Delay(OIS_Delay); // 20170223

	if(mode & I2CMODE_DOUBLEDATA){
		Data = ((int)DataH << 8) | (int)DataL;
	} else {
		Data = (int)DataL;
	}

	DbgPrintf("I2C_Read saddr = 0x%02x, index = 0x%04x, Data = 0x%04x mode = %d(%d)\n", saddr, index, Data & 0x0000ffff, mode, ack);

	return Data & 0x0000ffff;
}





int CI2C::I2C_Read(int saddr, int index, int mode)	//mode 0
{
	BYTE AddrH, AddrL, DataH, DataL;
	int Data=0;
	int ack = 0;

#ifdef HW_IIC
	
	int ack = 0;
	AddrH = AddrL = DataH = DataL = 0;

	if(mode == 0)
	{
		AddrL = index & 0xff;
		ack += HW_I2cRead_1_N((BYTE)saddr, AddrL, 1, &DataL);
	}
	else
	{
		ack += HW_I2cRead_2_N((BYTE)saddr, index, 1, &DataL);
	}

	Data = (int)DataL;

	DbgPrintf("I2C_Read saddr = 0x%02x, index = 0x%04x, Data = 0x%04x, ack = %d\n", saddr, index, Data & 0x0000ffff, ack);

#else

#if PCI_C_PHY_ENABLE == 1

	int readdata=0;
	int akchk=0;

	if(mode == AFI2C)
	{
		BYTE buf[2] = {0, };
		BYTE rbuf = 0;
		buf[0] = saddr;
		//buf[1] = HIBYTE(index);
		buf[1] = LOBYTE(index);
		ack = DG_I2cWrite(m_hCapture, 1, 0, buf, 2);
		buf[0] += 1;
		ack += DG_I2cWrite(m_hCapture, 1, 0, buf, 1);
		ack += DG_I2cRead(m_hCapture, 1, &rbuf, 1);

		if(ack==0x0)     return rbuf & 0x0000ffff; // 20180827 return    0xFFFFFF00 | rbuf; if(akchk) return    0xFFFFFF00 | rbuf;

		else return ack;
	}

	if((mode == SonyMaker)/*||(mode == SLSIMaker)*/) // 20180910 
	{
		BYTE buf[3] = {0, };
		BYTE rbuf = 0;
		buf[0] = saddr;
		buf[1] = HIBYTE(index);
		buf[2] = LOBYTE(index);
		ack = DG_I2cWrite(m_hCapture, 1, 0, buf, 3);
		buf[0] += 1;
		ack += DG_I2cWrite(m_hCapture, 1, 0, buf, 1);
		ack += DG_I2cRead(m_hCapture, 1, &rbuf, 1);

		if(ack==0x0) 	return rbuf & 0x0000ffff; // 20180827 return	0xFFFFFF00 | rbuf; if(akchk) return	0xFFFFFF00 | rbuf;

		else return akchk;
	}

	if((mode == SLSIMaker)) // 20180910 
	{
		unsigned char* rbuf = new unsigned char[2];
		unsigned int RcvData = 0;

		BYTE buf[3] = {0, };
		//BYTE rbuf = 0;
		buf[0] = saddr;
		buf[1] = HIBYTE(index);
		buf[2] = LOBYTE(index);
		ack = DG_I2cWrite(m_hCapture, 1, 0, buf, 3);
		buf[0] += 1;
		ack += DG_I2cWrite(m_hCapture, 1, 0, buf, 1);
		ack += DG_I2cRead(m_hCapture, 1, rbuf, 2);

		RcvData=MAKEWORD(rbuf[1], rbuf[0]); 


		if(ack==0x0) 	return RcvData  & 0x0000ffff; //return rbuf & 0x0000ffff; // 20180827 return	0xFFFFFF00 | rbuf; if(akchk) return	0xFFFFFF00 | rbuf;

		else return akchk;
	}


#else
	ack += DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr & 0x000000FE));

	if(mode & I2CMODE_DOUBLEADDR){
		AddrH = (BYTE)((index >> 8) & 0x000000ff);
		ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrH);
	}

	AddrL = (BYTE)(index & 0x000000ff);
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrL);

	ack += DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);	//restart condition
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr | 0x00000001));

	if(mode & I2CMODE_DOUBLEDATA){
		DataH = DC_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, 0);
	}

	DataL = DC_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, I2C_HIGHLOW);
	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	if(mode & I2CMODE_DOUBLEDATA){
		Data = ((int)DataH << 8) | (int)DataL;
	} else {
	 Data = (int)DataL;
	}

	DbgPrintf("I2C_Read saddr = 0x%02x, index = 0x%04x, Data = 0x%04x mode = %d(%d)\n", saddr, index, Data & 0x0000ffff, mode, ack);
	#endif

	return Data & 0x0000ffff;

#endif
}

int CI2C::I2C_Read_Burst(int saddr, int index, int ByteNumIndex, char *pDataBuf, int ByteNumData)	
{
	BYTE AddrH, AddrL;
	int nDataCnt;

	if(ByteNumIndex == 0) goto INDEX_WRITESKIP_IN_READBURST;

	DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr & 0x000000FE));

	if(ByteNumIndex == 2){
		AddrH = (BYTE)((index >> 8) & 0x000000ff);
		DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrH);
	}

	AddrL = (BYTE)(index & 0x000000ff);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrL);
	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

INDEX_WRITESKIP_IN_READBURST:

	DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);	//restart condition
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr | 0x00000001));

	for(nDataCnt = 0; nDataCnt < ByteNumData; nDataCnt++){
		*(pDataBuf+nDataCnt) = DC_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, I2C_HIGHLOW);
	}

	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	return 0;
}

int CI2C::I2C_Read_Burst_uc(int saddr, int index, int ByteNumIndex, unsigned char *pDataBuf, int ByteNumData)	
{
	BYTE AddrH, AddrL;
	int nDataCnt;

	if(ByteNumIndex == 0) goto INDEX_WRITESKIP_IN_READBURST;

	DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr & 0x000000FE));


	if(ByteNumIndex == 2){
		AddrH = (BYTE)((index >> 8) & 0x000000ff);
		DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrH);
	}

	AddrL = (BYTE)(index & 0x000000ff);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrL);
	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

INDEX_WRITESKIP_IN_READBURST:

	DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);	//restart condition
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr | 0x00000001));

	for(nDataCnt = 0; nDataCnt < ByteNumData; nDataCnt++){
		*(pDataBuf+nDataCnt) = DC_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, I2C_HIGHLOW);
	}

	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	return 0;
}

int CI2C::I2C_Write(int saddr, int index, int data, int mode) // 0407 check
{
	BYTE AddrH, AddrL, DataH, DataL;
	int ack = 0;

//20180816 syz check
//#ifdef HW_IIC
//	
//	int ack = 0;
//	AddrH = AddrL = DataH = DataL = 0;
//
//	if(mode == 0)
//	{
//		AddrL = index & 0xff;
//		DataL = data & 0xff;
//		ack = HW_I2cWrite_N_N((BYTE)saddr, AddrL, DataL);
//	}
//	else
//	{
//		AddrH = (index >> 8) & 0xff;
//		AddrL = index & 0xff;
//		DataL = data & 0xff;
//		ack = HW_I2cWrite_N_N((BYTE)saddr, AddrH, AddrL, DataL);
//	}
//
//	DbgPrintf("I2C_Write saddr = 0x%02x, index = 0x%04x, Data = 0x%04x, ack = %d\n", saddr, index, data & 0x0000ffff, ack);
//
//	return ack;

//20180816 syz check
#if PCI_C_PHY_ENABLE == 1


	if(mode == AFI2C)
	{
		BYTE buf[4] = {0, };
		buf[0] = (BYTE)saddr;
		buf[1] = (BYTE)index;
		buf[2] = (BYTE)data;
		ack = DG_I2cWrite(m_hCapture, 1, 1, buf, 3);

	}

	if(mode == SonyMaker)
	{
		BYTE buf[4] = {0, };
		buf[0] = (BYTE)saddr;
		buf[1] = HIBYTE(index);
		buf[2] = LOBYTE(index);
		buf[3] = (BYTE)data;
		ack = DG_I2cWrite(m_hCapture, 1, 1, buf, 4);
	
	}

	if(mode == SLSIMaker)
	{

		BYTE buf[5] = {0, };
		buf[0] = (BYTE)saddr;
		buf[1] = HIBYTE(index);
		buf[2] = LOBYTE(index);
		buf[3] = HIBYTE(data);
		buf[4] = LOBYTE(data);
		ack = DG_I2cWrite(m_hCapture, 1, 1, buf, 5);

	}

return ack;
#else

	ack += DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr & 0x000000FE));
	if(saddr==0x1C) IIC_Delayus(0.010f);

	if(mode & I2CMODE_DOUBLEADDR){
		AddrH = (BYTE)((index >> 8) & 0x000000ff);
		ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrH);
		if(saddr==0x1C) IIC_Delayus(0.010f);
	}

	AddrL = (BYTE)(index & 0x000000ff);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrL);
	if(saddr==0x1C) IIC_Delayus(0.010f);

// 0407 check
	if(mode & I2CMODE_DOUBLEDATA){
		DataH = (BYTE)((data >> 8) & 0x000000ff);
		ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, DataH);
		if(saddr==0x1C) IIC_Delayus(0.010f);
	}

	DataL = (BYTE)(data & 0x000000ff);
	ack += DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, DataL);
	if(saddr==0x1C) IIC_Delayus(0.010f);

	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	// decho
	//DbgPrintf("I2C_Write saddr = 0x%02x, index = 0x%04x, Data = 0x%04x mode = %d(%d)\n", saddr, index, data & 0x0000ffff, mode, ack); 
	DbgPrintf("I2C_Write saddr = 0x%02x, index = 0x%04x, Data = 0x%04x mode = %d(%d)\n", saddr, index, data & 0xffff, mode, ack); // 0407 

	return ack;
#endif

}

int CI2C::I2C_Write_Burst(int saddr, int index, int ByteNumIndex, char *pDataBuf, int ByteNumData)
{
	BYTE AddrH, AddrL;
	int nDataCnt;

	DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr & 0x000000FE));

	if(ByteNumIndex == 0) goto INDEX_WRITESKIP_IN_WRITEBURST;

	if(ByteNumIndex == 2){
		AddrH = (BYTE)((index >> 8) & 0x000000ff);
		DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrH);
	}

	AddrL = (BYTE)(index & 0x000000ff);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrL);

INDEX_WRITESKIP_IN_WRITEBURST:

	for(nDataCnt = 0; nDataCnt < ByteNumData; nDataCnt++){
		DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, *(pDataBuf+nDataCnt));
	}	

	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	return 0;
}

int CI2C::I2C_Write_Burst_uc(int saddr, int index, int ByteNumIndex, unsigned char *pDataBuf, int ByteNumData)
{
	BYTE AddrH, AddrL;
	int nDataCnt;

	DC_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (BYTE)(saddr & 0x000000FE));

	if(ByteNumIndex == 0) goto INDEX_WRITESKIP_IN_WRITEBURST;

	if(ByteNumIndex == 2){
		AddrH = (BYTE)((index >> 8) & 0x000000ff);
		DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrH);
	}

	AddrL = (BYTE)(index & 0x000000ff);
	DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, AddrL);

INDEX_WRITESKIP_IN_WRITEBURST:

	for(nDataCnt = 0; nDataCnt < ByteNumData; nDataCnt++){
		DC_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, *(pDataBuf+nDataCnt));
	}	

	DC_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	return 0;
}

int CI2C::SetCapInfo(int channel,int HBP, int VBP, int ClkEdgeHigh, int HSyncEdgeHigh, int VSyncEdgeHigh, int LineArea, int Input10Bits,DWORD jpg_eof_sig)
{
	return DC_SetCapInfo(g_cardinfo.nCardnum, channel,HBP, VBP, ClkEdgeHigh, HSyncEdgeHigh, VSyncEdgeHigh, LineArea, Input10Bits,jpg_eof_sig);	
}

// begin getting frame
int CI2C::Channel_Open(int Height, int Width, int Frames,int BitPerClock)
{
	g_frameinfo.nHeight	= Height;
	g_frameinfo.nWidth	= Width;
	g_frameinfo.nFrames	= Frames;
	g_frameinfo.nBitperClock	= BitPerClock;
	g_frameinfo.bIsChannelOpen	= TRUE;

	//TODO:
	//DC_Open(g_cardinfo.nCardnum, g_cardinfo.nChannel, Height, Width, Frames,BitPerClock);	//raw8
	#if PCI_C_PHY_ENABLE == 1
	int err = DG_Open(m_hCapture, Height, Width*1.25f, 12);

	if(err == DG_ERR_CHANNEL_ALREADY_OPENED) {
		DG_Stop(m_hCapture);
		err = DG_ERR_SUCCESS;
		return err;
	}
	DG_Start(m_hCapture);
	#else
	DC_Open(g_cardinfo.nCardnum, g_cardinfo.nChannel, Height,(int) (Width*1.25f), Frames, BitPerClock);	//raw10

#if 0
	DC_SetCapInfo(
		g_cardinfo.nCardnum, 
		g_cardinfo.nChannel,
		0,	//HSTART
		0,	//VSTART
		1,	//clkedgehigh
		1,	//HSYNCEDGEHIGH
		1,	//vsyncedgehigh
		0,	//line area
		0,	//n10bit
		0);
#endif
	DC_SetCapInfo(
		g_cardinfo.nCardnum, 
		g_cardinfo.nChannel,
		0,	//HSTART
		0,	//VSTART
		1,	//clkedgehigh
		1,	//HSYNCEDGEHIGH
		1,	//vsyncedgehigh
		0,	//line area
		1,	//n10bit
		0);

	DC_Start(g_cardinfo.nCardnum, g_cardinfo.nChannel);
#endif
	return 0;
}

//stop getting frame
int CI2C::Channel_Close(BOOL bModeChange)
{
	if(bModeChange == FALSE)
	{
#if PCI_C_PHY_ENABLE == 1
		DG_Stop(m_hCapture);
		DG_Close(m_hCapture);
#else
		DC_Stop(g_cardinfo.nCardnum, g_cardinfo.nChannel);
		DC_Close(g_cardinfo.nCardnum, g_cardinfo.nChannel);
#endif
	}
	return 0;
}
// Set St-Mipi FPGA Control 1:PowerOn, 0:PowerDown, ;;; nPwdn	0: High, 1:High->Low, 2: Low->High
// dwData: SubBoard Type 0x20:MIPI2Lane, 0x80:MIPI4Lane
// 0x1E:YUV,	0x20~0x22:RGB,		0x2A~0x2C:RAW,	0x30~0x37:JPEG

#define _DC_MIPI4LANE_

// 20170331int CI2C::Z_Set_MIPI_FPGA(int nOn1Off0/*=0*/, int nPwdn/*=0*/, BYTE DataType/*=0x1E*/, int nLane/*=2*/, DWORD *dwData/*=NULL*/)
UINT32 CI2C::Z_Set_MIPI_FPGA(int nOn1Off0/*=0*/, int nPwdn/*=0*/, BYTE DataType/*=0x1E*/, int nLane/*=2*/, DWORD *dwData/*=NULL*/)

{
	// '11.12.12 added(MIPI 4Lane)
	char msg[128];

	E_BOARD_ERROR err;

	//20180808 syz check
#if PCI_C_PHY_ENABLE == 1
	if(nOn1Off0 != 0) {
		if(DG_SetTestCamEn(m_hCapture, 0) != DG_ERR_SUCCESS) {
			err = BOARD_IIC_ERROR;
			return err;
		}

		if(DG_SetMipiTestCamEn(m_hCapture, 0) != DG_ERR_SUCCESS) {
			err = BOARD_IIC_ERROR;
			return err;
		}

		if(DG_SetMipiDefault(m_hCapture, 0x2B) != DG_ERR_SUCCESS) {
			err = BOARD_IIC_ERROR;
			return err;
		}

		if(DG_SetMipiInput(m_hCapture, 3, 0) != DG_ERR_SUCCESS) {
			err = BOARD_IIC_ERROR;
			return err;
		}

		if(DG_SetIsmDefault(m_hCapture) != DG_ERR_SUCCESS) {
			err = BOARD_IIC_ERROR;
			return err;
		}

		if(DG_SetIsmFreq(m_hCapture, 0, 24) != DG_ERR_SUCCESS) {
			err = BOARD_IIC_ERROR;
			return err;
		}
		IIC_Delayus(0.010f);		
		DG_SetIsmReset(m_hCapture, 1);
		IIC_Delayus(0.00050f);
		DG_SetIsmReset(m_hCapture, 0);
		IIC_Delayus(0.010f);

		if(DG_SetI2cFreq(m_hCapture, 300.0)  != DG_ERR_SUCCESS) { // 20180827 300
			err = BOARD_IIC_ERROR;
			return err;
		}
		err = BOARD_SUCCESS;

	}
	else {
		err = BOARD_SUCCESS;
	}
	return err;

#else
	// '11.12.12 추가(MIPI 4Lane)
	BYTE vc, dt, lanes, e8b9b;
	// Parallel camera MIPI tx generator info
	if(nOn1Off0 == -888){
		if(nPwdn == 0){
			// MIPI capture info
			vc	= 0;
			dt	= 0x1E;
			lanes= 2;
			e8b9b= 0;

			I2C_Write(0xCA, 0x21, 0x01);					// mipi reset active
			I2C_Write(0xCA, 0x23, (vc<<5) | dt);			// set MIPI vc,dt
			// mipi receiver init
			I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));	// lane numbers=3, and en 8b9b=0
			I2C_Write(0xCA, 0x21, 0);						// reset release
#if defined(_DC_MIPI4LANE_)
			DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, vc, dt);		// set framegrabber MIPI VC & data type
#endif
#if 0
			data	 = iic.Read_Reg_16(0xCA, 254);		akchk	+= (int)((data >>8) & 0xff);
			data1	 = (data&0xff) << 8;
			data	 = iic.Read_Reg_16(0xCA, 255);		akchk	+= (int)((data >>8) & 0xff);
			data1	|= (data&0xff);
			data2	 = iic.Read_Reg_16(0xCA, 16);		akchk	+= (int)((data2>>8) & 0xff);
			if(dwData != NULL){		*dwData	= (((DWORD)data1<<8) | ((DWORD)data2));	}
			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] ID = 0x%04X, ADDR(0x10) = 0x%04X, (ACK)%d", data1, data2, akchk);
			if(data1 == 0x20){							iiDlg.m_ctrlLog.write(CR_STEELBLU,	"\t-> MIPI2 Lane");		}
			else if(data1 == 0x80 || data1 == 0x81){	iiDlg.m_ctrlLog.write(CR_STEELBLU,	"\t-> MIPI4 Lane");		}
#endif
		}
		else if(nPwdn == 1){
			I2C_Write(0xCA, 0x40, 0x1e);					// VC & DT of the parallel MIPI TX
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)40,1E (ACK)%d", akchk);
			I2C_Write(0xCA, 0x44, (nLane*2) & 0xff);		//
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)44,%02X (ACK)%d", (nLane*2) & 0xff, akchk);
			I2C_Write(0xCA, 0x45, (nLane*2) >> 8);			//
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)45,%02X (ACK)%d", (nLane*2) >> 8, akchk);
			I2C_Write(0xCA, 0x41, (1<<7) | 16);			// bit 7 : par_en, bit[4:0] data bit width
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)41,%02X (ACK)%d", (1<<7) | 16, akchk);

			vc	= 0;
			dt	= 0x1E;
			lanes= 2;
			e8b9b= 0;
			//vc_dt = 0x2b;	// RAW10
			//vc_dt = 0x2c;	// RAW12
			I2C_Write(0xCA, 0x21, 1);								// mipi reset active
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)21,01 (ACK)%d", akchk);
			I2C_Write(0xCA, 0x23, (vc<<5) | dt);					// set MIPI vc,dt;
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)23,%02X (ACK)%d", (vc<<5) | dt, akchk);
			// mipi receiver init
			I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));			// lane numbers=3, and en 8b9b=0
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)20,%02X (ACK)%d", (e8b9b<<4) | (lanes-1), akchk);
			I2C_Write(0xCA, 0x21, 0);								// reset release
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)21,00 (ACK)%d", akchk);

#if defined(_DC_MIPI4LANE_)
			DC_SetMipiInfo(0,0, vc, dt);		// set framegrabber MIPI VC & data type
#endif
#if 0
			data	 = iic.Read_Reg_16(0xCA, 254);		akchk	+= (int)((data >>8) & 0xff);
			data1	 = (data&0xff) << 8;
			data	 = iic.Read_Reg_16(0xCA, 255);		akchk	+= (int)((data >>8) & 0xff);
			data1	|= (data&0xff);
			data2	 = iic.Read_Reg_16(0xCA, 16);		akchk	+= (int)((data2>>8) & 0xff);
			if(dwData != NULL){		*dwData	= (((DWORD)data1<<8) | ((DWORD)data2));	}
			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] ID = 0x%04X, ADDR(0x10) = 0x%04X, (ACK)%d", data1, data2, akchk);
#endif

		}
		else if(nPwdn == 2){
			I2C_Write(0xCA, 0x01, 0xdf);
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)01,DF (ACK)%d", akchk);
			I2C_Write(0xCA, 0x00, DataType);
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)00,%02X (ACK)%d", DataType, akchk);
			//data	 = iic.Read_Reg_16(0xCA, 0);
			//if(dwData != NULL){		*dwData	= data;	}
			//iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] (SND)00 (RES)%02X (ACK)%d", data, akchk);
		}

		//theApp.gsSensor.nIICDelay	= nOldIIC;
		//theApp.gsSensor.nIICSpeed	= nOldSpd;
		//return akchk;
		return 0;
	}
	// MIPI Dataline Setting Only(MIPI4Lane Only)	****************************************
	else if(nOn1Off0 == -1){
		// YUV, 4-lane, vc=0,dt=0x1e
		vc	= 0;
		dt	= DataType;	// 0x1E;	// YUV		//vc_dt = 0x2b;	// RAW10, //vc_dt = 0x2c;	// RAW12
		lanes= nLane;	//	4;
		e8b9b= 0;

		I2C_Write(0xCA, 0x21, 0x01);					// mipi reset active
		I2C_Write(0xCA, 0x23, (vc<<5) | dt);			// set MIPI vc,dt
		// mipi receiver init
		I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));	// lane numbers=3, and en 8b9b=0
		I2C_Write(0xCA, 0x21, 0);						// reset release
#if defined(_DC_MIPI4LANE_)
		DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, vc, dt);		// set framegrabber MIPI VC & data type
#endif
		//theApp.gsSensor.nIICDelay	= nOldIIC;
		//theApp.gsSensor.nIICSpeed	= nOldSpd;
		//return akchk;
		return 0;
	}
	// Power On
	else if(nOn1Off0 == 1){
		//iiDlg.m_ctrlLog.write(CR_GREEN_,	"// Start FPGA Init");	// Set ST-MIPI
		I2C_Write(0xCA, 0x01, 0xFF);	// OE enable
		I2C_Write(0xCA, 0x00, 0xFF);	// power on
		if(nPwdn == 1){
			IIC_Delayus(0.010f);
			I2C_Write(0xCA, 0x00, 0x7F);	// power on & pwdn low
#if defined(_DC_MIPI4LANE_)
			DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, 0, 0);		// set framegrabber MIPI VC & data type
#endif
		}else if(nPwdn == 2){
			IIC_Delayus(0.010f);
			I2C_Write(0xCA, 0x16, 0x01);	//
			I2C_Write(0xCA, 0x01, 0xFF);	//
			I2C_Write(0xCA, 0x00, 0xFF);	//
#if defined(_DC_MIPI4LANE_)
			DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, 0, 0);		// set framegrabber MIPI VC & data type
#endif
			IIC_Delayus(0.010f);
		}
		// '11.12.12 추가(MIPI 4Lane)	****************************************
		else if(nPwdn == 402){		// -> Power on -> Mipi설정
			// 20151103 IIC_Delayus(0.010f);
			//IIC_Delay(1000); // DECHO : Remove When Board is changed
			I2C_Write(0xCA, 0x16, 0x01);	//
			I2C_Write(0xCA, 0x01, 0xFF);	//
			I2C_Write(0xCA, 0x00, 0xFF);	//
			IIC_Delayus(0.010f);
			// YUV, 4-lane, vc=0,dt=0x1e
			vc	= 0;
			dt	= DataType;	// 0x1E;	// YUV		//vc_dt = 0x2b;	// RAW10, //vc_dt = 0x2c;	// RAW12
			lanes= nLane;	//4;	// 
			e8b9b= 0;

			I2C_Write(0xCA, 0x21, 0x01);					// mipi reset active
			I2C_Write(0xCA, 0x23, (vc<<5) | dt);			// set MIPI vc,dt
			// mipi receiver init
			I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));	// lane numbers=3, and en 8b9b=0
			I2C_Write(0xCA, 0x21, 0);						// reset release
#if defined(_DC_MIPI4LANE_)
 #if (_DC_DLL__VER_ >= 0x31D)
			if(DataType == 0x30+0x31){		DC_SetMipiInfoMulti(PCIEX_CARD_NUM, 0, vc, 0x30,0x31,0,0);		}
			else{							iic.SDC_SetMipiInfo(0, vc, dt);									}	// set framegrabber MIPI VC & data type
 #else
			//IIC_Delay(1000); // 20151103  // DECHO : Remove When Board is changed
			DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, vc, dt);		// set framegrabber MIPI VC & data type
 #endif
#endif
		}
		// '12.02.24 추가(MIPI 4Lane)	****************************************
		else if(nPwdn == 403){		// -> Mipi만 설정
			IIC_Delayus(0.010f);
			I2C_Write(0xCA, 0x00, 0xFF);	//
			IIC_Delayus(0.010f);
			// YUV, 4-lane, vc=0,dt=0x1e
			vc	= 0;
			dt	= DataType;	// 0x1E;	// YUV		//vc_dt = 0x2b;	// RAW10, //vc_dt = 0x2c;	// RAW12
			lanes= nLane;//	4;
			e8b9b= 0;

			I2C_Write(0xCA, 0x21, 0x01);					// mipi reset active
			I2C_Write(0xCA, 0x23, (vc<<5) | dt);			// set MIPI vc,dt
			// mipi receiver init
			I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));	// lane numbers=3, and en 8b9b=0
			I2C_Write(0xCA, 0x21, 0);						// reset release
#if defined(_DC_MIPI4LANE_)
			DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, vc, dt);		// set framegrabber MIPI VC & data type
#endif
		}
		// '13.03.11 추가(MIPI4DSI)		****************************************
		else if(nPwdn == 442){		// 
			IIC_Delayus(0.010f);
			I2C_Write(0xCA, 0x00, 0xFF);	//
			IIC_Delayus(0.010f);
			// YUV, 4-lane, vc=0,dt=0x1e
			vc	= 0;
			dt	= DataType;	// 0x1E;	// YUV		//vc_dt = 0x2b;	// RAW10, //vc_dt = 0x2c;	// RAW12
			lanes= nLane;	//	4;
			e8b9b= 0;

			I2C_Write(0xCA, 0x21, 0x01);					// mipi reset active
			I2C_Write(0xCA, 0x22, 0x01);					// mipi dsi enable

			I2C_Write(0xCA, 0x23, (vc<<5) | dt);			// set MIPI vc,dt
			// mipi receiver init
			I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));	// lane numbers=3, and en 8b9b=0
			I2C_Write(0xCA, 0x21, 0);						// reset release
#if defined(_DC_MIPI4LANE_)
			DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, vc, dt);		// set framegrabber MIPI VC & data type
#endif
			// dsi enable bit 2,
			//iic.SDC_WriteReg(0x4008, (1<<2) | (lanes-1) );
			DC_WriteReg(0, 0x4008, (0<<5) | (0<<4) | (1<<3) | (1<<2) | (lanes-1) );	// 2013.04.03	- Melius
#if 0
			DWORD d1;
			iic.SDC_ReadReg(0x4008, &d1);
			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] 0x4008Reg = 0x%08X", d1);
			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] DSI enabled = 0x%02X"	, iic.Read_Reg_16(0xCA, 0x22));
			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] DIS lanes = 0x%2X"		, iic.Read_Reg_16(0xCA, 0x20));
			WLog->write(_T("[FPGA] 0x4008Reg = 0x%08X"), d1);
#endif
		}
// 		else if(nPwdn == 443){		// 
// 			iic.IIC_Delayus(0.010f);
// 			I2C_Write(0xCA, 0x00, 0xFF);	//
// 			iic.IIC_Delayus(0.010f);
// 			// YUV, 4-lane, vc=0,dt=0x1e
// 			vc	= 0;
// 			dt	= DataType;	// 0x1E;	// YUV		//vc_dt = 0x2b;	// RAW10, //vc_dt = 0x2c;	// RAW12
// 			lanes= nLane;	//	4;
// 			e8b9b= 0;
// 
// 			I2C_Write(0xCA, 0x21, 0x01);					// mipi reset active
// 			I2C_Write(0xCA, 0x22, 0x01);					// mipi dsi enable
// 
// 			I2C_Write(0xCA, 0x23, (vc<<5) | dt);			// set MIPI vc,dt
// 			// mipi receiver init
// 			I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));	// lane numbers=3, and en 8b9b=0
// 			I2C_Write(0xCA, 0x21, 0);						// reset release
// #if defined(_DC_MIPI4LANE_)
// 			iic.SDC_SetMipiInfo(0, vc, dt);		// set framegrabber MIPI VC & data type
// #endif
// 			// dsi enable bit 2,
// 			iic.SDC_WriteReg(0x4008, (1<<2) | (lanes-1) );
// 			//iic.SDC_WriteReg(0x4008, (0<<5) | (0<<4) | (1<<3) | (1<<2) | (lanes-1) );	// 2013.04.03	- Melius
// 
// 			DWORD d1;
// 			iic.SDC_ReadReg(0x4008, &d1);
// 			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] 0x4008Reg = 0x%08X", d1);
// 			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] DSI enabled = 0x%02X"	, iic.Read_Reg_16(0xCA, 0x22));
// 			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] DIS lanes = 0x%2X"		, iic.Read_Reg_16(0xCA, 0x20));
// 		}
		else if(nPwdn == 441){		// 
			IIC_Delayus(0.010f);
			I2C_Write(0xCA, 0x00, 0xFF);	//
			IIC_Delayus(0.010f);
			// YUV, 4-lane, vc=0,dt=0x1e
			vc	= 0;
			dt	= DataType;	// 0x1E;	// YUV		//vc_dt = 0x2b;	// RAW10, //vc_dt = 0x2c;	// RAW12
			lanes= nLane;	//	4;
			e8b9b= 0;

			I2C_Write(0xCA, 0x21, 0x01);					// mipi reset active
			I2C_Write(0xCA, 0x22, 0x01);					// mipi dsi enable

			I2C_Write(0xCA, 0x23, (vc<<5) | dt);			// set MIPI vc,dt
			// mipi receiver init
			I2C_Write(0xCA, 0x20, (e8b9b<<4) | (lanes-1));	// lane numbers=3, and en 8b9b=0
			I2C_Write(0xCA, 0x21, 0);						// reset release
#if defined(_DC_MIPI4LANE_)
			DC_SetMipiInfo(g_cardinfo.nCardnum, g_cardinfo.nChannel, vc, dt);		// set framegrabber MIPI VC & data type
#endif
			// dsi enable bit 2,
			DC_WriteReg(0, 0x4008, (1<<2) | (lanes-1) );

//			DWORD d1;
//			DC_ReadReg(0x4008, &d1);
//			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] 0x4008Reg = 0x%08X", d1);
//			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] DSI enabled = 0x%02X"	, iic.Read_Reg_16(0xCA, 0x22));
//			iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] DIS lanes = 0x%2X"		, iic.Read_Reg_16(0xCA, 0x20));
//			WLog->write(_T("[FPGA] 0x4008Reg = 0x%08X"), d1);
		}
		//
		I2C_Write(0xCA, 0x10, 0x01);	// enable external i2c

#if 1
		int akchk = 0, data, data1, data2;
		// Get version of the MIPI board
		//IIC_Delay(1000); // 20151103  // DECHO : Remove When Board is changed
		data	 = I2C_Read(0xCA, 254,0);		akchk	+= (int)((data >>8) & 0xff);	
		data1	 = (data&0xff) << 8;
		data	 = I2C_Read(0xCA, 255,0);		akchk	+= (int)((data >>8) & 0xff);	
		data1	|= (data&0xff);
		data2	 = I2C_Read(0xCA, 16,0);		akchk	+= (int)((data2>>8) & 0xff);
		//IIC_Delay(1000); // 20151103  // DECHO : Remove When Board is changed
		TRACE("MIPI_SUB_VER___0x%x_\n", data1);
		TRACE("MIPI_SUB_VER___0x%x_\n", data2);

//		if(dwData != NULL){		*dwData	= (((DWORD)data1<<8) | ((DWORD)data2));	}
//		iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] ID = 0x%04X, ADDR(0x10) = 0x%04X, (ACK)%d", data1, data2, akchk);
//		WLog->write(_T("[FPGA] ID = 0x%04X, ADDR(0x10) = 0x%04X, (ACK)%d"), data1, data2, akchk);
//		if(		data1 == 0x20){						iiDlg.m_ctrlLog.write(CR_STEELBLU,	"\t-> MIPI2 Lane");		}
//		else if(data1 == 0x80 || data1 == 0x81){	iiDlg.m_ctrlLog.write(CR_STEELBLU,	"\t-> MIPI4 Lane");		}


		// 20170331
		// return 0;
		UINT32 MIPI_SUB_VER;
		MIPI_SUB_VER = MAKELONG(data2, data1);
		return MIPI_SUB_VER;
		//

#endif
	}
	// Power Off						****************************************
	else if(nOn1Off0 == 0){
#if defined(_DC_MIPI4LANE_)
		DC_SetMipiInfo(0,0, 0, 0);		// set framegrabber MIPI VC & data type
#endif
		//iiDlg.m_ctrlLog.write(CR_GREEN_,	"// Stop FPGA");
		I2C_Write(0xCA, 0x10, 0x00);	// disable external i2c
		I2C_Write(0xCA, 0x00, 0x00);	//
		I2C_Write(0xCA, 0x01, 0xFF);	//

#if 0
		data	 = iic.Read_Reg_16(0xCA, 0x00);		akchk	+= (int)((data >>8) & 0xff);
		data1	 = (data&0xff) << 8;
		data	 = iic.Read_Reg_16(0xCA, 0x01);		akchk	+= (int)((data >>8) & 0xff);
		data1	|= (data&0xff);
		data2	 = iic.Read_Reg_16(0xCA, 0x02);		akchk	+= (int)((data2>>8) & 0xff);
		iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] Power off 0x%04X %04X", data1, data2);

		data	 = iic.Read_Reg_16(0xCA, 254);		akchk	+= (int)((data >>8) & 0xff);
		data1	 = (data&0xff) << 8;
		data	 = iic.Read_Reg_16(0xCA, 255);		akchk	+= (int)((data >>8) & 0xff);
		data1	|= (data&0xff);
		data2	 = iic.Read_Reg_16(0xCA, 16);		akchk	+= (int)((data2 >>8) & 0xff);
		if(dwData != NULL){		*dwData	= (((DWORD)data1<<8) | ((DWORD)data2));	}

		iic.SDC_WriteReg(0x4008, 0);	// 2013.04.16	- DSI Reset
		DWORD d1;
		iic.SDC_ReadReg(0x4008, &d1);

		iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] 0x4008Reg = 0x%08X", d1);
		iiDlg.m_ctrlLog.write(CR_DARKMAGE,	"[FPGA] ID = 0x%04X, ADDR(0x10) = 0x%04X, (ACK)%d", data1, data2, akchk);
		WLog->write(_T("[FPGA] 0x4008Reg = 0x%08X"), d1);
		WLog->write(_T("[FPGA] ID = 0x%04X, ADDR(0x10) = 0x%04X, (ACK)%d"), data1, data2, akchk);
#endif
	}
#if 0
	else{

	}	
	theApp.gsSensor.nIICDelay	= nOldIIC;
	theApp.gsSensor.nIICSpeed	= nOldSpd;
	return akchk;
#endif
	return 0;
#endif
}

//for express b'd 2-lane
int CI2C::Z_Set_MIPI_ST2(int nLaneClock/*=400*/, int nMipi/*=1*/, int nNoBypass/*=1*/, int n2Lane/*=1*/,
								   WORD nDatatype/*=0x2B*/, WORD nDatatype2/*=0x0C*/, int nBit/*=8*/,int n081Rev0/*=0*/)
{
	return 0;
}


//----------------------------------------------------------------------------------------------------//
// Reset
//----------------------------------------------------------------------------------------------------//
void CI2C::RST_High()
{
	#if PCI_C_PHY_ENABLE == 1
#else
	m_dwIicPinOut	|= ETC_DCRST;		// RST High
	DC_WriteReg(m_IicDcHandle, 0x8b0, m_dwIicPinOut);
#endif
}

void CI2C::RST_Low()
{
	#if PCI_C_PHY_ENABLE == 1
#else
	m_dwIicPinOut	&= ~ETC_DCRST;		// RST Low
	DC_WriteReg(m_IicDcHandle, 0x8b0, m_dwIicPinOut);
#endif
}

//----------------------------------------------------------------------------------------------------//
// SW I2C
//----------------------------------------------------------------------------------------------------//
int CI2C::SW_I2cWrite(int card_num,int channel, BYTE data)
{
	return DC_I2cWrite(card_num, channel, data);
}
int CI2C::SW_I2cRead(int card_num, int channel, int hilo)
{
	return DC_I2cRead(card_num, channel, hilo);
}
int CI2C::SW_I2cStart(int card_num, int channel)
{
	return DC_I2cStart(card_num, channel);
}
void CI2C::SW_I2cStop(int card_num, int channel)
{
	DC_I2cStop(card_num, channel);
	
	return;
}

//----------------------------------------------------------------------------------------------------//
// HW I2C
//----------------------------------------------------------------------------------------------------//

//<internal_function_i2c>
int	CI2C::HW_I2cWrite_N_N(BYTE slvAddr, int numbers,...)
{
	BYTE buf[256];

	buf[0] = slvAddr;

	va_list vl;
	va_start(vl, numbers);
	for (int i=0; i < numbers; i++) {
		buf[i+1] = va_arg(vl, char);
	}
	va_end(vl);

	int ack = DC_HwI2cWrite(g_cardinfo.nCardnum, numbers+1, 0, numbers, buf);

	return ack;
}

int	CI2C::HW_I2cRead_0_N(BYTE slvAddr, int numbers, BYTE *data)
{
	BYTE sa = slvAddr+1;
	int ack;
	ack = DC_HwI2cWrite(g_cardinfo.nCardnum, 1, 0, 0, &sa);
	ack += DC_HwI2cRead(g_cardinfo.nCardnum, numbers, 1, data);

	return ack;
}

int CI2C::HW_I2cRead_1_N(BYTE slvAddr, BYTE addr, int len, BYTE *datBuf)
{
	int ack;
	BYTE buf[4];

	buf[0] = slvAddr;
	buf[1] = addr;
	ack = DC_HwI2cWrite(g_cardinfo.nCardnum, 2, 0, 1, buf);

	buf[0] = slvAddr+1;
	ack += DC_HwI2cWrite(g_cardinfo.nCardnum, 1, 0, 0, buf);
	ack += DC_HwI2cRead(g_cardinfo.nCardnum, len, 1, datBuf);

	return ack;
}

int CI2C::HW_I2cRead_2_N(BYTE slvAddr, int addr, int len, BYTE *datBuf)
{
	int ack;
	BYTE buf[4];

	buf[0] = slvAddr;
	buf[1] = (addr >> 8) & 0xff;
	buf[2] = addr & 0xff;
	ack = DC_HwI2cWrite(g_cardinfo.nCardnum, 3, 0, 2, buf);

	buf[0] = slvAddr+1;
	ack += DC_HwI2cWrite(g_cardinfo.nCardnum, 1, 0, 0, buf);
	ack += DC_HwI2cRead(g_cardinfo.nCardnum, len, 1, datBuf);

	return ack;
}
//</internal_function_i2c>
