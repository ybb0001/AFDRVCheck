#include "StdAfx.h"
#include "I2C.h"
#include "Eeprom.h"
#include "dglib.h" // 20180904

//=================== EEPROM Type ===================//

// 1. BRCG064GWZ-3 
// 2. CAT24C64     
// 1과 2는 변경점이 없는 듯...
//===================================================//

//#define SADDR_EEPROM	0xA2 // 20181012 0xA0

extern card_info g_cardinfo; 
//extern class CI2C;

//CI2C iic;

CEeprom::CEeprom(void)
{
}

CEeprom::~CEeprom(void)
{
}

int CEeprom::I2C_Read_EEPROM(int index)
{
	int address = index & 0xffff;

	int data = iic.I2C_Read(SADDR_EEPROM, address, I2CMODE_DOUBLEADDR);

	return (data & 0x000000ff);
}

int CEeprom::I2C_Write_EEPROM(int index, int data)
{
	int saddr2 = data & 0xff;
	int address = index & 0xffff;

	iic.I2C_Write(SADDR_EEPROM, address, data, I2CMODE_DOUBLEADDR);

	return 0;
}

int CEeprom::I2C_Read_SEQ_EEPROM(unsigned char* databuf, int bufSize)
{
	int saddr = SADDR_EEPROM;
	int index = 0x0;

	int ack = 0;


#if PCI_C_PHY_ENABLE == 1 // 20180904

	// 20180905 E2P Page(0x10) Read (Max 0x400)

	const int PageSize = 0x10;
	int length = 0;

	for(int i=0; i<bufSize; i +=PageSize)
	{

		BYTE buf[3] = {0, };
		buf[0] = saddr;

		buf[1] = HIBYTE(i);
		buf[2] = LOBYTE(i);
		ack = DG_I2cWrite(iic.m_hCapture, 1, 0, buf, 3);

		buf[0] += 1;
		ack += DG_I2cWrite(iic.m_hCapture, 1, 0, buf, 1);

		ack += DG_I2cRead(iic.m_hCapture, 1, databuf+i, PageSize);	 // 20180905
		IIC_Delayus(0.005f); // 20180905 1->5


	}

	if(ack)	return  TRUE;
	else			FALSE;


#else


	ack += iic.SW_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)(saddr & 0x000000FE));
	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)((index >> 8) & 0x000000ff));
	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)(index & 0x000000ff));

	ack += iic.SW_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)(saddr | 0x00000001));

	for(int i = 0; i < bufSize; i++)
	{
		if(i == (bufSize - 1))			*(databuf + i) = (unsigned char)iic.SW_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, 1);
		else							*(databuf + i) = (unsigned char)iic.SW_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, 0);
	}

	iic.SW_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

#endif

	return ack;
}

int CEeprom::I2C_Write_SEQ_EEPROM(int index, unsigned char* databuf, int bufSize)  // 20180905 
{
	const int pageSize = 0x10;

	int ack = 0;

	for(int i = 0; i < bufSize; i += pageSize)
	{
		ack += I2C_Write_PAG_EEPROM(index + i, databuf + i);


	}

	return ack;
}

int CEeprom::I2C_Write_PAG_EEPROM(int index, unsigned char* databuf) // 20180904 
{
	const int pageSize = 0x10;

	int saddr = SADDR_EEPROM;	
	int address = index & 0xffff;

	int ack = 0;


#if PCI_C_PHY_ENABLE == 1 // 20180905

	BYTE buf[19]={0,};
	buf[0] = SADDR_EEPROM;
	buf[1] = HIBYTE(index);
	buf[2] = LOBYTE(index);


	for(int i = 0; i < pageSize; i++)
	{
		buf[i+3] = databuf[i];

	}

	ack += DG_I2cWrite(iic.m_hCapture, 1, 1, buf, pageSize+3); 
	IIC_Delayus(0.005f); // IIC_Delayus(0.001f); -> sometimes no write

#else

	ack += iic.SW_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)(saddr & 0x000000FE));

	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)((address >> 8) & 0x000000ff));

	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)((address & 0x00ff) & 0x000000ff));


	for(int i = 0; i < pageSize; i++)
	{
		ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, databuf[i]);		
	}	

	iic.SW_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

#endif

	return ack;
}