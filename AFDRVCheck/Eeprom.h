#pragma once

#include "Common.h"
#include "I2C.h"


class CEeprom
{
public:
	CEeprom(void);
	~CEeprom(void);

	// 20180904 
	int I2C_Read_EEPROM(int index);
	int I2C_Read_SEQ_EEPROM(unsigned char* databuf, int bufSize);

	int I2C_Write_EEPROM(int index, int data);
	int I2C_Write_PAG_EEPROM(int index, unsigned char* databuf);
	int I2C_Write_SEQ_EEPROM(int index, unsigned char* databuf, int bufSize);

public:
	unsigned char SADDR_EEPROM = 0xA0;
	CI2C iic;

};
