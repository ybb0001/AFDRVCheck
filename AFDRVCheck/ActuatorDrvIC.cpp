#include "stdafx.h"
#include "ActuatorDrvIC.h"
#include "Af.h"
#include "Af_EEPROM_MEM.h"
#include "AfDef.h"
#include "I2C.h"
#include "dclibdef.h"
#include "dglib.h"     // 20180827 

/////////////////////////////For C1///////////////////////////////////////
#include "Eeprom.h"

extern CEeprom eeprom;
///////////////////////////////////////////////////////////////////////////////
extern card_info g_cardinfo;

#ifdef	MODULE_CALIBRATION

#define		FOR_RAMREG				0x00
#define		FOR_EEPROM				0x01

#define		EEPROM_WRITE_LENGTH		0x10
#define		EEPROM_WRITE_TERMINAL	0x7C

#define		OFFSET1					0x00
#define		OFFSET2					0x01
//Hall Adjustment
#define		PEAK_MAXMIN				0x7F80
#define		TARGET_MAXMIN			0x6A96
#define		WAITTIME_COUNT			0x6420

#endif	//MODULE_CALIBRATION

#define MAKEWORD(low, high) \
	((WORD)((((WORD)(high)) << 8) | ((BYTE)(low))))

#if !defined(LOBYTE)
#define LOBYTE(w)           ((unsigned char)(w))
#endif
#if !defined(HIBYTE)
#define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))
#endif

//**************************
//	Global Variable
//**************************
// 20180806 LC898211, LC898212
#define _I2C_WRITE_ADDRESS	0xE4	
#define _I2C_READ_ADDRESS	0xE5	

unsigned char I2cSlvAddrWr	= _I2C_WRITE_ADDRESS ;
unsigned char I2cSlvAddrRd	= _I2C_READ_ADDRESS ;
//extern unsigned char I2cSlvAddrWr ;
//extern unsigned char I2cSlvAddrRd ;

STADJPAR StAdjPar;

// 0406 3L8 1st SPL Main(0x18), Sub(0x1E) --> Driver IC fix
// 0520 3L8+4H8 AF Driver IC 0x18 common 
//#define SADDR_DRVIC 0x18 //0xE0 


#if 1 // LC898217XC 20180725 0 → 1
	unsigned char SADDR_DRVIC = 0xE4; 
#else // AK7372

	unsigned char SADDR_DRVIC = 0x18; 

#endif

#ifdef	MODULE_CALIBRATION

#define		FOR_RAMREG				0x00
#define		FOR_EEPROM				0x01

#define		EEPROM_WRITE_LENGTH		0x10
#define		EEPROM_WRITE_TERMINAL	0x7C

#define		OFFSET1					0x00
#define		OFFSET2					0x01
//Hall Adjustment
#define		PEAK_MAXMIN				0x7F80
#define		TARGET_MAXMIN			0x6A96
#define		WAITTIME_COUNT			0x6420

#endif	//MODULE_CALIBRATION

#define MAKEWORD(low, high) \
((WORD)((((WORD)(high)) << 8) | ((BYTE)(low))))

#if !defined(LOBYTE)
#define LOBYTE(w)           ((unsigned char)(w))
#endif
#if !defined(HIBYTE)
#define HIBYTE(w)           ((unsigned char)(((unsigned short)(w) >> 8) & 0xFF))
#endif



extern CI2C iic;

short torg_PreGain = 0x0;
short hvca_InfPos = 0x3FF;
short hvca_MacPos = 0x000;

//WV560
BOOL InitActuator_WV560()
{
	int ack = 0;
	int readData = 0x0;

	ack += iic.I2C_Write(SADDR_DRVIC, 0x00, 0x08);
	IIC_Delay(5);

	ack += iic.I2C_Write(SADDR_DRVIC, 0x03, 0x00); 
	ack += iic.I2C_Write(SADDR_DRVIC, 0x00, 0x06);

	torg_PreGain = iic.I2C_Read(SADDR_DRVIC, 0x2A, 0);
	ack += iic.I2C_Write(SADDR_DRVIC, 0x0A, (torg_PreGain & 0x0F) | 0x00);

	readData = GetCurrentLensPos_WV560();
	if(LensMove_WV560(readData) == false)
	{
		ack += 1;
	}

	ack += iic.I2C_Write(SADDR_DRVIC, 0x00, 0x07);
	IIC_Delay(10);

	ack += iic.I2C_Write(SADDR_DRVIC, 0x0A, (torg_PreGain & 0x0F) | 0x20);
	hvca_InfPos = GetMechanicalLimitPos_WV560();
	hvca_MacPos = GetMechanicalLimitPos_WV560(true);

	TRACE("vcm_driver_ic_init_%x_%x \n", torg_PreGain, readData);
	TRACE("af inf___%d mac___%d \n", hvca_InfPos, hvca_MacPos);

	//char szBuf[256] = {0,};
	//sprintf_s(szBuf, "af inf___%d mac___%d \n", hvca_InfPos, hvca_MacPos);
	//AfxMessageBox(szBuf);

	if(ack != 0) return false;

	return true;
}

BOOL LensMove_WV560(short targetPos)
{
	int ack = 0;
	int readData = 0x0;

	BYTE buf[2];

	//ack += iic.I2C_Write(SADDR_DRVIC, 0x0A, (torg_PreGain & 0x0F) | 0x00);
	ack += iic.I2C_Write(SADDR_DRVIC, 0x0A, torg_PreGain);

	buf[0] = (BYTE)( targetPos & 0xFF);			
	buf[1] = (BYTE)( (targetPos >> 8) & 0x03);	

	
 	ack += iic.I2C_Write(SADDR_DRVIC, 0x01, buf[0]);
 	ack += iic.I2C_Write(SADDR_DRVIC, 0x02, (readData | buf[1]));

#if 0
	buf[0] = iic.I2C_Read(SADDR_DRVIC, 0x01, 0);
	buf[1] = iic.I2C_Read(SADDR_DRVIC, 0x02, 0);
	TRACE("lens_move______%x_%x\n", buf[1], buf[0]);
#endif

	//IIC_Delay(50);

	int count = 0;
	while( ((0x10 & (iic.I2C_Read(SADDR_DRVIC, 0x05, 0))) != false) && (count < 10) )
	{
		IIC_Delay(5);
		count++; 
	}

	TRACE("lens_move______%x_\n", iic.I2C_Read(SADDR_DRVIC, 0x05, 0));

	if( ack != 0 )
		return false;
	else
		return true;
}

SHORT GetCurrentLensPos_WV560()
{
	DbgPrintf("%s\n", __FUNCTION__);

	UCHAR buf[2];
	USHORT temp;
	int ack = 0;
	SHORT pos;

	buf[0] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x04, 0);
	buf[1] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x05, 0);

	temp = MAKEWORD(buf[0], buf[1]);

	pos = (SHORT)(temp & 0x3ff);

	DbgPrintf("Current_position = 0x%x \n", pos);

	return pos;
}

SHORT GetMechanicalLimitPos_WV560(bool isMacPos)
{
	UCHAR buf[2];
	USHORT temp;
	int ack = 0;
	SHORT pos;
	int addr;

	if(isMacPos == false)
	{
		addr = 0x10;
	}
	else
	{
		addr = 0x12;
	}

	buf[0] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, addr + 0, 0);
	buf[1] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, addr + 1, 0);

	temp = MAKEWORD(buf[0], buf[1]);

	pos = (SHORT)(temp & 0x3ff);

	return pos;
}

BOOL InitActuator_DW9714()
{

	return true;
}

BOOL LensMove_DW9714(short targetPos)
{
	int ack = 0;
	BYTE buf[2];

	if(targetPos < 0 || targetPos > 1023) return false;
				
	buf[0] = (BYTE)( (targetPos >> 4) & 0x3F);
	buf[1] = (BYTE)( (targetPos << 4) & 0xF0);
	
	ack += iic.I2C_Write(SADDR_DRVIC, buf[0], buf[1]);

	if( ack != 0 )
		return false;
	else
		return true;
}

int InitVCA_AK7345()
{
    // 20180806 AK7345 & 7371 DataSheet Guide ¹Y¿μ
	// It is available to use I2C more than 10msec later for power on reset of VDD.
	// Address : 02h -> Data [6~5] : 0-0(Active), 1-0(Stand-by), X-1(Sleep)

	int ack = 0;
	BYTE buf;
	WORD count = 0;

	while( count < 100 )
	{
		ack += iic.I2C_Write(SADDR_DRVIC, 0x02, 0x00);

		buf = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x02, 0);

		IIC_Delay(1); // 20180801 IIC_Delay(30); 

		if( buf & 0x40 )			count++;
		else						break;
	}

	if( ack != 0 || buf & 0x40 )	return FALSE;
	else							return TRUE;
		

	// return 2;   // 20180627 return 2¿¡ ´eCN A³¸® ¹IAu¿e	
	


}

BOOL LensMove_AKSeries(short target_pos, int AKSeries) // 20170403 LensMove_AK7345(short target_pos)
{
	int ack = 0;
	int count = 0;
	SHORT LensPosition = 9999;
	unsigned char SendData[2], RcvData[2];

	switch (AKSeries)
	{   // 20170405 AK7345 ½C¹° ¹I°EAo
		case AK7345:	SendData[0] = (BYTE)( (target_pos >> 1) & 0x00ff); // Position1(H): PCTFS 8,7,6,5,4,3,2,1
						SendData[1] = (BYTE)( (target_pos << 7) & 0x0080); // Position2(L): PCTFS 0,-,-,-,-,-,-,-
						break;

		case AK7371:
		case AK7372:	SendData[0] = HIBYTE(target_pos << 6); // Position1(H): PCTFS 9,8,7,6,5,4,3,2
						SendData[1] = LOBYTE(target_pos << 6); // Position2(L): PCTFS 1,0,-,-,-,-,-,-
						break;
	}

	ack += iic.I2C_Write(SADDR_DRVIC, 0x00, SendData[0]);
	ack += iic.I2C_Write(SADDR_DRVIC, 0x01, SendData[1]);

	if( ack != 0 )	return FALSE;

	// 20170403
	// AK7371 0x86, 0x087
	// AK7372 0x84, 0x085
	switch (AKSeries)
	{
		case AK7345:    
						while( !(LensPosition == target_pos) ) 						
						{
							IIC_Delay(1);

							count++;

							RcvData[0] = iic.I2C_Read(SADDR_DRVIC, 0x04, 0);
							RcvData[1] = iic.I2C_Read(SADDR_DRVIC, 0x05, 0);
							LensPosition = MAKEWORD(RcvData[1], RcvData[0]) >> 7;

							TRACE("LensPosition diff(Target - Position) : (%4d - %4d) - Count : %d \n", target_pos, LensPosition, count);

							if( (LensPosition >= target_pos-2) && LensPosition <= target_pos+2 )	break;

							if( count > 50 )	break;

						}
			
						break; // 20170403 AK7345도 실제 기존 방법대로 구현되면 안됨

		case AK7371:	while( !(LensPosition == target_pos) ) 	// Lens Real Hall Position Read 편차 범위 지정: +/- 2						
						{
							IIC_Delay(1);

							count++;
							
							RcvData[0] = iic.I2C_Read(SADDR_DRVIC, 0x86, 0);
							RcvData[1] = iic.I2C_Read(SADDR_DRVIC, 0x87, 0);
							LensPosition = MAKEWORD(RcvData[1], RcvData[0]) >> 6;

							TRACE("LensPosition diff(Target - Position) : (%4d - %4d) - Count : %d \n", target_pos, LensPosition, count);

							if( (LensPosition >= target_pos-2) && LensPosition <= target_pos+2 )	break;

							if( count > 50 )	break;

						}

						break;

		case AK7372:	while( !(LensPosition == target_pos) ) 	// Lens Real Hall Position Read 편차 범위 지정: +/- 2
						{
							IIC_Delay(1);

							count++;

							RcvData[0] = iic.I2C_Read(SADDR_DRVIC, 0x84, 0);
							RcvData[1] = iic.I2C_Read(SADDR_DRVIC, 0x85, 0);
							LensPosition = MAKEWORD(RcvData[1], RcvData[0]) >> 6;

							TRACE("LensPosition diff(Target - Position) : (%4d - %4d) - Count : %d \n", target_pos, LensPosition, count);

							if( (LensPosition >= target_pos-2) && LensPosition <= target_pos+2 )	break;

							if( count > 50 )	break;

						}

						break;


	}

	return TRUE; 

}

// 20180806 LC898217 Init & LensMove

int InitVCA_LC898217() // 20180725 No operation
{
	unsigned short i = 0;
	unsigned char LC898217_Version = 0;

	// 1. Slave address check. 
	LC898217_Version = CheckCver();	// 0xF0==0x72

	WitTim(1);

	// 2. WakeUp
	unsigned short RcvData = 999;
	RcvData = iic.I2C_Read(SADDR_DRVIC, FUNCRSLT1, 0); // 0xB3 == 0x00

	for(i=0 ; i<3000; i++)
	{
		if(RcvData==0x00)	break;
		WitTim(5);
	}

	return LC898217_Version;
}

BOOL LensMove_LC898217(short target_pos)
{
	int ack = 0;
	unsigned char buf[2];

	buf[0] = (BYTE)(target_pos & 0xFF);	// Low		
	buf[1] = (BYTE)(target_pos >> 8);   // High	

	ack = Stmv217(buf[1], buf[0]);

	if(ack != 0)		return FALSE;
	else	     		return TRUE;

}
//

unsigned char CheckCver( void )
{
	unsigned char UcLsiVer;

	UcLsiVer = (UCHAR)iic.I2C_Read(SADDR_DRVIC, CVER, 0);
	return UcLsiVer;

	// 20180806 return( (UcLsiVer == 0x71) || (UcLsiVer == 0x72) ) ? SUCCESS : FAILURE ;
}
void	MemClr( unsigned char	*NcTgtPtr, unsigned short	UsClrSiz )
{
	unsigned short	UsClrIdx ;

	for ( UsClrIdx = 0 ; UsClrIdx < UsClrSiz ; UsClrIdx++ )
	{
		*NcTgtPtr	= 0 ;
		NcTgtPtr++ ;
	}
}

void	IniCmd( void )
{

	MemClr( ( unsigned char * )&StAdjPar, sizeof( stAdjPar ) ) ;	// Adjust Parameter Clear
}

unsigned char	IniSet( unsigned char UcAutoDownload )
{

	int ack = 0;

	unsigned char	UcStatus, UcReadDat ;
	unsigned short	i ;

	UcStatus	= CheckCver() ;

	if( UcStatus != FAILURE ) {
		IniCmd() ;

		if( UcAutoDownload != WITHOUT_DOWNLOAD ) {
			ack += iic.I2C_Write(SADDR_DRVIC,  ADWLCTL, 0x01 );

			for( i = 0 ; i < 3000 ; i++  ) {
				UcReadDat = (UCHAR)iic.I2C_Read( SADDR_DRVIC, FUNCRSLT1,  0) ;
				if( !UcReadDat ) {
					break ;
				}
			}

			if( i == 3000 ) {
				UcStatus	= DOWNLOAD_ERROR ;
			}
		}

		ack += iic.I2C_Write(SADDR_DRVIC,  PINC, 0x02 );
		ack += iic.I2C_Write(SADDR_DRVIC, TESTC, 0x20 );
	}

	return( UcStatus ) ;
}


void E2pWriteBytes( unsigned short addr, unsigned char *dt, int len )
{
	unsigned char	data[ 16 ], i ;
	unsigned char address = 0x00;
	
	address	= ( unsigned char )( addr & 0x00FF ) ;

	for( i = 0 ; i < len ; i++ ) {
		
		data[ i ]	= *dt++ ;
	
	}
	iic.I2C_Write_Burst_uc(SADDR_DRVIC, address, 1, data, len);
	WitTim( 20 ) ;
}


void E2pWriteBytes( unsigned short addr, char *dt, int len )
{
	char	data[ 16 ], i ;
	unsigned char address = 0x00;

	address	= ( unsigned char )( addr & 0x00FF ) ;

	for( i = 0 ; i < len ; i++ ) {

		data[ i ]	= *dt++ ;

	}
	iic.I2C_Write_Burst(SADDR_DRVIC, address, 1, data, len);
	WitTim( 20 ) ;
}

void	EEPROM_Initial( void )
{
	unsigned char	*UcPtrHed ;
	unsigned char	i ;
#if 1
	UcPtrHed = &Clear_Mem[ 0 ][ 0 ] ;	// Start Address in EEPROM Buffer

	for( i = 0 ; i < 0x80 ; i += EEPROM_WRITE_LENGTH )
	{
		E2pWriteBytes( i , UcPtrHed, EEPROM_WRITE_LENGTH ) ;
		UcPtrHed	+= EEPROM_WRITE_LENGTH ;
	}
#else
	for( i = 0 ; i < 0x80 ; i++ )
	{
		RegWriteA( i, Clear_Mem[ i / 16 ][ i & 0x0F ] ) ;

		WitTim( 10 ) ;
	}
#endif
}

void	EEPROM_Set( void )
{
	unsigned char	*UcPtrHed ;
	unsigned char	i ;

#ifdef WITHOUT_TEST
#if 1
	UcPtrHed = &IniSet_Mem[ 0 ][ 0 ] ;	// Start Address in EEPROM Buffer
	for( i = 0 ; i < 0x80 ; i += EEPROM_WRITE_LENGTH )
	{
		E2pWriteBytes( i , UcPtrHed, EEPROM_WRITE_LENGTH ) ;
		UcPtrHed	+= EEPROM_WRITE_LENGTH ;
	}
#else
	for( i = 0 ; i < 0x80 ; i++ )
	{
		RegWriteA( i, IniSet_Mem[ i / 16 ][ i & 0x0F ] ) ;

		WitTim( 10 ) ;
	}
#endif
#else
	UcPtrHed = &IniSet_Mem[ 0 ][ 0 ] ;	// Start Address in EEPROM Buffer
	for( i = 0x09 ; i < 0x80 ; i += EEPROM_WRITE_LENGTH )
	{
		E2pWriteBytes( i , ( char * )UcPtrHed, EEPROM_WRITE_LENGTH ) ;
		UcPtrHed	+= EEPROM_WRITE_LENGTH ;

		if( EEPROM_WRITE_TERMINAL - ( i + EEPROM_WRITE_LENGTH ) < EEPROM_WRITE_LENGTH ) {
			break ;
		}
	}

	E2pWriteBytes( i + EEPROM_WRITE_LENGTH , &IniSet_Mem[ 7 ][ 9 ], 4 ) ;
#endif
}

int I2C_Read_SEQ(unsigned char* databuf, int index, int bufSize)
{
	int saddr = 0xE6;

	int ack = 0;

	ack += iic.SW_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)(saddr & 0x000000FE));
	//ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)((index >> 8) & 0x000000ff));
	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)(index & 0x000000ff));

	ack += iic.SW_I2cStart(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	ack += iic.SW_I2cWrite(g_cardinfo.nCardnum, g_cardinfo.nChannel, (unsigned char)(saddr | 0x00000001));

	for(int i = 0; i < bufSize; i++)
	{
		if(i == (bufSize - 1))
			*(databuf + i) = (unsigned char)iic.SW_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, 1);
		else
			*(databuf + i) = (unsigned char)iic.SW_I2cRead(g_cardinfo.nCardnum, g_cardinfo.nChannel, 0);
	}

	iic.SW_I2cStop(g_cardinfo.nCardnum, g_cardinfo.nChannel);

	return ack;
}

#if 1
unsigned char	EEPROM_Verify( void )
{

	unsigned char UcStatus = SUCCESS;

	/*

	unsigned char	data[ 16 ], i ;

	unsigned char address = 0x00;

	address	= ( unsigned char )( address & 0x00FF ) ;

	for( i = 0x00 ; i < 0x08 ; i++ ) {

		unsigned char index = (unsigned char) ( i*16 & 0x00FF );
		//iic.I2C_Read_Burst_uc(SADDR_DRVIC, index, 1, data, 16);
		I2C_Read_SEQ(data,index, 16);

		WitTim(10);

		for(unsigned char j = 0 ; j < 16 ; j++){

			unsigned char index2 = index+j;

			TRACE("SEMCO [%d] ReadVal : 0x%x WriteVal : 0x%x \n",index2 ,data[j], IniSet_Mem[ index2 / 16 ][ index2 & 0x0F ]);

			if( IniSet_Mem[ index2 / 16 ][ index2 & 0x0F ] != data[j] ) {
				UcStatus	= FAILURE ;
				break ;
			}

		}

	}

	*/

	unsigned char	data[ 128 ] ;

	unsigned char index = (unsigned char) ( 0x00 & 0x00FF );
	I2C_Read_SEQ(data,index, 128);

	for(unsigned char j = 0 ; j < 128 ; j++){
		
		TRACE("SEMCO [%d] ReadVal : 0x%x WriteVal : 0x%x \n",j ,data[j], IniSet_Mem[ j / 16 ][ j & 0x0F ]);

		if( IniSet_Mem[ j / 16 ][ j & 0x0F ] != data[j] ) {
			UcStatus	= FAILURE ;
			break ;
		}

	}

	
	

	return( UcStatus );

}
#else

unsigned char	EEPROM_Verify( void )
{
	unsigned char	UcRedVal ;
	unsigned char	i, UcStatus ;

	UcStatus	= SUCCESS ;

#ifdef WITHOUT_TEST
	for( i = 0 ; i < 0x80 ; i++ )
	{
		//E2pReadBytes( i, ( char *)&UcRedVal, 1 ) ;
		UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC,  i, 0);
		

		TRACE("SEMCO [%d] ReadVal : 0x%x WriteVal : 0x%x \n",i ,UcRedVal, IniSet_Mem[ i / 16 ][ i & 0x0F ]);

		if( IniSet_Mem[ i / 16 ][ i & 0x0F ] != UcRedVal ) {
			UcStatus	= FAILURE ;
			break ;
		}
	}
#else
	for( i = 0x09 ; i < 0x7C ; i++ )
	{
		E2pReadBytes( i, ( char *)&UcRedVal, 1 ) ;

		if( IniSet_Mem[ i / 16 ][ i & 0x0F ] != UcRedVal ) {
			UcStatus	= FAILURE ;
			break ;
		}
	}
#endif
	return( UcStatus ) ;

}
#endif

void RamWriteA(unsigned char ucAddr, unsigned short usData){


	iic.I2C_Write(SADDR_DRVIC, ucAddr, usData, I2CMODE_DOUBLEDATA);

	/*
	int ack = 0;
	BYTE slaveAddr = SADDR_DRVIC;

	DC_I2cStart(0,0);
	ack += DC_I2cWrite(0,0, slaveAddr);
	ack += DC_I2cWrite(0,0, LOBYTE(ucAddr));
	ack += DC_I2cWrite(0,0, HIBYTE(usData));
	ack += DC_I2cWrite(0,0, LOBYTE(usData));
	DC_I2cStop(0,0);

	if(ack != 0)
		TRACE("RamWriteA : Fail!");

	TRACE("RamWriteA : Success!");
	*/

	
}

void RamReadA(unsigned char ucAddr, unsigned short *pReadVal){

	*pReadVal = iic.I2C_Read(SADDR_DRVIC, ucAddr, I2CMODE_DOUBLEDATA);

	/*
	int ack = 0;
	BYTE pData[2] = {0,};
	BYTE slaveAddr = SADDR_DRVIC;
	
	
	DC_I2cStart(0,0);
	ack += DC_I2cWrite(0,0, slaveAddr);
	ack += DC_I2cWrite(0,0, LOBYTE(ucAddr));
	DC_I2cStop(0,0);

	DC_I2cStart(0,0);
	ack += DC_I2cWrite(0,0, slaveAddr+1);
	pData[1] += (BYTE)DC_I2cRead(0,0,0);
	pData[0] += (BYTE)DC_I2cRead(0,0,1);
	DC_I2cStop(0,0);

	*pReadVal = MAKEWORD(pData[0], pData[1]);

	if(ack != 0)
		TRACE("RamReadA : Fail!");

	TRACE("RamReadA : Success!");

	*/

}

void E2pReadBytes( unsigned short addr, unsigned char *dt, int len )
{
	E2pWriteBytes(addr, dt, 0);

	//HybridVCA_ReadArray(dt, len);
}


unsigned char	EEPROM_Update( void )
{
	unsigned char	UcStatus, UcRedVal ;
	int ack=0;
	
	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC,  INPUT, 0);
	UcRedVal	|= 0x01 ;
	ack += iic.I2C_Write(SADDR_DRVIC,  INPUT, UcRedVal);// it permits to access EEPROM by user
	ack += iic.I2C_Write(SADDR_DRVIC, E2WPMS1, 0xAF );
	//ack += iic.I2C_Write(SADDR_DRVIC, E2WPMS2, 0x85 ); //write protect release
	ack += iic.I2C_Write(SADDR_DRVIC, E2WPMS2, 0xBC ); //write protect release

	SADDR_DRVIC =  0xE6 ;

#ifdef WITHOUT_TEST
	EEPROM_Initial() ;
#endif

	EEPROM_Set() ;

	UcStatus	= EEPROM_Verify() ;

	SADDR_DRVIC = 0xE4;

	ack += iic.I2C_Write(SADDR_DRVIC, E2WPMS1, 0x00);
	ack += iic.I2C_Write(SADDR_DRVIC, E2WPMS2, 0x00); //write protect release

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC,  INPUT, 0);
	UcRedVal	&= 0xFE ;
	ack += iic.I2C_Write(SADDR_DRVIC, INPUT, UcRedVal);
	
	return( UcStatus ) ;
}
void	CalibDrvOffIni( unsigned char UcIniSel )
{
	int ack = 0;

	ack += iic.I2C_Write(SADDR_DRVIC,ASW, 0x00);// OP_SW1=L, OP_SW2=L
	ack += iic.I2C_Write(SADDR_DRVIC, DRVT1, 0x28);// SEL2=L, SLF_T=010, SLF_T_CCONL=H, SLF_G=L, SELH_AFEO=L
		

	if( !UcIniSel ) {
		ack += iic.I2C_Write(SADDR_DRVIC,DRVT2, 0x20 );	// SLFTSEL=2 CW
				
	} else {
		ack += iic.I2C_Write(SADDR_DRVIC,DRVT2, 0x30);// SLFTSEL=3 OFST2(CCW)
							
	}
	ack += iic.I2C_Write(SADDR_DRVIC, TESTAL, 0x01);// SCN_MODE=L

	if( !UcIniSel ) {
		RamWriteA( PIDO, 0x0100 ) ;
		RamWriteA( PIDO, 0x0000 ) ;		
	} else {
		RamWriteA( PIDO, 0xFF00 ) ;
		RamWriteA( PIDO, 0x0000 ) ;

	}
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, 0xF0 );// E2PACC=L
	RamWriteA( Margin, 0x0020 ) ;					// Margin Setting
	ack += iic.I2C_Write(SADDR_DRVIC, STBY, 0x04 );// STBB_DRV=L, STBB_OPAMP=H

}

unsigned char	CalibDrvOff( unsigned char	UcAdjSel )
{
	int ack=0;
	unsigned char	i	= 0 ;
	unsigned char	j, UcDts, UcOfstd	= 0 ;

	do {
		if( !UcAdjSel ) {
			ack += iic.I2C_Write(SADDR_DRVIC,DRVOFST1, UcOfstd);// OFST1 CW
			
		} else {
			ack += iic.I2C_Write(SADDR_DRVIC,DRVOFST2, UcOfstd );// OFST2 CCW
					
		}
		ack += iic.I2C_Write(SADDR_DRVIC,FUNCE2PW, 0x01 );// Driver test sequence GO
				
		for( j = 0 ; j < 300 ; j++  ) {
			UcDts = (UCHAR)iic.I2C_Read(SADDR_DRVIC, FUNCE2PW, 0);
			
			if( !UcDts ) {
				break ;
			}
		}

		if( j < 300 ) {
			UcOfstd++ ;
		} else {
			return( FAILURE ) ;
		}
		i++ ;
	} while( i < 32 ) ;

	return( SUCCESS ) ;
}
void	WriteDrvOff( unsigned char UcWriteSel )
{
	unsigned char	UcRedVal ;

	int ack=0;

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	|= 0x01 ;
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, UcRedVal );// it permits to access EEPROM by user
	ack += iic.I2C_Write(SADDR_DRVIC, E2WPMS1, 0xAF);
	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS2, 0xBC); // Write Protect Release
	

	SADDR_DRVIC = 0xE6;

	if( !UcWriteSel ) {
		//E2pWriteBytes( 0x07 , ( char * )&UcRedVal, 1 ) ;
		ack += iic.I2C_Write(SADDR_DRVIC,  0x07, UcRedVal);
		
	} else {
		//E2pWriteBytes( 0x08 , ( char * )&UcRedVal, 1 ) ;
		ack += iic.I2C_Write(SADDR_DRVIC, 0x08, UcRedVal );
		
	}

	SADDR_DRVIC = 0xE4;

	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS1, 0x00 );
	ack += iic.I2C_Write(SADDR_DRVIC, E2WPMS2, 0x00);// Write Protect
	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	&= 0xFE ;

	ack += iic.I2C_Write(SADDR_DRVIC, INPUT, UcRedVal);// it permits to access EEPROM by user

}

unsigned char	CalibDrv( void )
{
	int ack=0;
	unsigned char	UcStatus ;

	CalibDrvOffIni( OFFSET1 ) ;

	UcStatus	= CalibDrvOff( OFFSET1 ) ;

	//WriteDrvOff( OFFSET1 ) ;

	ack += iic.I2C_Write(SADDR_DRVIC,FUNCRSLT2, 0x01 );// Flag Clear
	ack += iic.I2C_Write(SADDR_DRVIC, DRVT2, 0x00  );// SLFTSEL=0

	CalibDrvOffIni( OFFSET2 ) ;

	UcStatus	= CalibDrvOff( OFFSET2 ) ;

	//WriteDrvOff( OFFSET2 ) ;

	ack += iic.I2C_Write(SADDR_DRVIC,FUNCRSLT2, 0x01 );// Flag Clear
	ack += iic.I2C_Write(SADDR_DRVIC, DRVT2, 0x00  );// SLFTSEL=0


	return( UcStatus ) ;
}
void	WitTim( unsigned short	UsWitTim )
{
	/*unsigned long	UlLopIdx, UlWitCyc ;

	UlWitCyc	= ( unsigned long )( ( float )UsWitTim / NOP_TIME / ( float )12 ) ;

	for( UlLopIdx = 0 ; UlLopIdx < UlWitCyc ; UlLopIdx++ )
	{
		;
	}*/

	IIC_Delayus((float)UsWitTim*0.001);
}
unsigned char	WakeUpCheck(unsigned char UcRescailMode)
{
	unsigned char	UcStatus, UcReadDat ;
	unsigned short	i ;
	int ack=0;

	//I2C communication check if necessary	
	UcStatus	= CheckCver() ;

	if( UcStatus != FAILURE ) {
		IniCmd() ;

		for( i = 0 ; i < 3000 ; i++  ) {
			UcReadDat = (UCHAR)iic.I2C_Read(SADDR_DRVIC, FUNCRSLT1, 0);
			
			if(UcRescailMode == RESCAILING){
				if( UcReadDat == 0x01 )             //Rescailing Mode
					break ;
			}
			else
			{
				if( !UcReadDat )
					break ;			
			}
		}

		if( i%1000 == 0 && i!=3000) {
			WitTim(5);
		}

		if( i == 3000 ) {
			UcStatus	= DOWNLOAD_ERROR ;
		}
	}

	ack += iic.I2C_Write(SADDR_DRVIC,PINC, 0x02);
	ack += iic.I2C_Write(SADDR_DRVIC,TESTC, 0x20);


	return( UcStatus ) ;
}

unsigned char	CalibHall( unsigned char	UcData )
{
	unsigned long	UlCount ;
	unsigned char	UcRedVal, UcStatus ;
	int ack=0;

	ack += iic.I2C_Write(SADDR_DRVIC, FUNCRUN2, UcData);// Start Hall Calibration & MaxMin Mesure
						
	WitTim(50);
	for( UlCount = 0 ; UlCount < 75000 ; UlCount++  ) {
		UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, FUNCRUN2, 0);
		
		if( !UcRedVal ) {
			break ;
		}
	}

	if( UcRedVal < 75000 ) {
		UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, FUNCRUN2, 0);
		
		if( !( UcRedVal & 0xC0 ) ) {
			UcStatus	= SUCCESS ;
		} else {
			UcStatus	= FAILURE ;
		}
	} else {
		ack += iic.I2C_Write(SADDR_DRVIC,FUNCRUN2, 0x00 );// Stop Hall Calibration & MaxMin Mesure
		
		UcStatus	= FAILURE ;
	}

	return( UcStatus ) ;

}

bool StampCalib(void){

	int ack=0;

	unsigned char	UcRedVal ;

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	|= 0x01 ;
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, UcRedVal );// it permits to access EEPROM by user

	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS1, 0xAF );
	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS2, 0x85 );// Write Protect Release

	SADDR_DRVIC = 0xE6;

	ack += iic.I2C_Write(SADDR_DRVIC,0x1F, 0x07);

	WitTim( 20 ) ;

	SADDR_DRVIC = 0xE4;

	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS1, 0x00 );
	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS2, 0x00 );// Write Protect

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	&= 0xFE ;
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, UcRedVal );// it permits to access EEPROM by user

	if(ack != 0) return FAILURE;

	return SUCCESS;

}

bool isCalibrated(void){

	int ack=0;

	unsigned char	UcRedVal, result ;

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	|= 0x01 ;
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, UcRedVal );// it permits to access EEPROM by user

	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS1, 0xAF );
	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS2, 0x85 );// Write Protect Release

	SADDR_DRVIC = 0xE6;

	result = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x1F, 0);

	SADDR_DRVIC = 0xE4;

	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS1, 0x00 );
	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS2, 0x00 );// Write Protect

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	&= 0xFE ;
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, UcRedVal );// it permits to access EEPROM by user


	if (result==0x07) return SUCCESS;

	else return FAILURE;

}

void	CalDataWrite( void )
{
	unsigned char	UcRedVal ;
	unsigned char	UcData[ 4 ] ;
	int ack=0;

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	|= 0x01 ;
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, UcRedVal );// it permits to access EEPROM by user

	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS1, 0xAF );
	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS2, 0x85 );// Write Protect Release

	SADDR_DRVIC = 0xE6;

	UcData[ 0 ]	= StAdjPar.StHalAdj.UsAdaOff >> 8 ;
	UcData[ 1 ]	= StAdjPar.StHalAdj.UsAdaOff & 0x00FF ;
	UcData[ 2 ]	= StAdjPar.StHalAdj.UsHlaOff >> 8 ;
	UcData[ 3 ]	= StAdjPar.StHalAdj.UsHlaBia >> 8 ;
	E2pWriteBytes( 0x10 , ( char * )&UcData, 4 ) ;

	UcData[ 0 ]	= StAdjPar.StHalAdj.UsHlaMax >> 8 ;
	UcData[ 1 ]	= ( StAdjPar.StHalAdj.UsHlaMax & 0x00F0 ) | ( ( StAdjPar.StHalAdj.UsHlaMin & 0xF000 ) >> 12 ) ;
	UcData[ 2 ]	= ( StAdjPar.StHalAdj.UsHlaMin & 0x0FF0 ) >> 4 ;
	E2pWriteBytes( 0x67 , ( char * )&UcData, 3 ) ;

	/*
	for(int i = 0 ; i < 128 ; i++){

		TRACE("[%d] ",i+1);

		(UCHAR)iic.I2C_Read(0xE6,  i+256, 0);

	}
	*/

	SADDR_DRVIC = 0xE4;

	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS1, 0x00 );
	ack += iic.I2C_Write(SADDR_DRVIC,E2WPMS2, 0x00 );// Write Protect

	UcRedVal = (UCHAR)iic.I2C_Read(SADDR_DRVIC, INPUT, 0);
	UcRedVal	&= 0xFE ;
	ack += iic.I2C_Write(SADDR_DRVIC,INPUT, UcRedVal );// it permits to access EEPROM by user



}
#define REVERSE_POS 0 //Reverse INF/MAC Position, MAC 0x03FF, INF 0x0000
#define DEFAULT_POS 1 //Default INF/MAC Position, MAC 0x0000, INF 0x03FF
unsigned char	TneRunAf( void )
{
	unsigned char	UcHalSts, UcStatus ;
	unsigned short	UsBiasOffset ;
	unsigned char   UcPos = REVERSE_POS;
	int ack = 0 ;

	UcHalSts	= EXE_END ;
	
	ack += iic.I2C_Write(SADDR_DRVIC,FUNCRSLT2, 0xFF );// Error Flag Clear

	RamWriteA( PeakMax, PEAK_MAXMIN ) ;					// Peak+(upper 8bit) & Peak-(lower 8bit)
	RamWriteA( TgtMax, TARGET_MAXMIN ) ;				// Target Max(upper 8bit) & Min(lower 8bit)
	RamWriteA( CountThd, WAITTIME_COUNT ) ;				// 100ms(upper 8bit)& 32U®???n(lower 8bit)


	if(UcPos == DEFAULT_POS){  
		RamWriteA( AjCoef, 0x5550) ;    // Offset Coefficient:1/1.5(Original)
		ack += iic.I2C_Write(SADDR_DRVIC,FUNCOPT1, 0x0E );// Option
		
	}  else if(UcPos == REVERSE_POS){  
		RamWriteA( Margin, 0x0402) ;    //Addr.0x38 Margin Bias:0400h & Offset:0200h
		RamWriteA( AjCoef, 0xAAB0) ;    // Offset Coefficient:-1/1.5
		ack += iic.I2C_Write(SADDR_DRVIC,FUNCOPT1, 0x0F );// Option
		
	}

	UcStatus	= CalibHall( 0x01 ) ; //<- UN??? x 1

	RamReadA( MSR2CH, &StAdjPar.StHalAdj.UsHlbMax ) ;
	RamReadA( MSR2CL, &StAdjPar.StHalAdj.UsHlbMin ) ;
	RamReadA( DAHLO, &UsBiasOffset ) ;
	RamReadA( COFF, &StAdjPar.StHalAdj.UsAdbOff ) ;
	StAdjPar.StHalAdj.UsHlbCen	= ( unsigned short )( ( ( short )StAdjPar.StHalAdj.UsHlbMax + ( short )StAdjPar.StHalAdj.UsHlbMin ) / 2 ) ;
	StAdjPar.StHalAdj.UsHlbOff	= UsBiasOffset & 0xFF00 ;
	StAdjPar.StHalAdj.UsHlbBia	= UsBiasOffset << 8 ;

	UcStatus	= CalibHall( 0x81 ) ; //<- UN???UN??? x 10

	RamReadA( MSR2CH, &StAdjPar.StHalAdj.UsHlaMax ) ;
	RamReadA( MSR2CL, &StAdjPar.StHalAdj.UsHlaMin ) ;
	RamReadA( DAHLO, &UsBiasOffset ) ;
	StAdjPar.StHalAdj.UsHlaCen	= ( unsigned short )( ( ( short )StAdjPar.StHalAdj.UsHlaMax + ( short )StAdjPar.StHalAdj.UsHlaMin ) / 2 ) ;
	RamWriteA( COFF, StAdjPar.StHalAdj.UsHlaCen ) ;
	StAdjPar.StHalAdj.UsAdaOff	= StAdjPar.StHalAdj.UsHlaCen ;
	StAdjPar.StHalAdj.UsHlaOff	= UsBiasOffset & 0xFF00 ;
	StAdjPar.StHalAdj.UsHlaBia	= UsBiasOffset << 8 ;

	if( UcStatus ) {
		UcHalSts	= EXE_HADJ ;
	} else {
		CalDataWrite() ;
	}

	return( UcHalSts ) ;
}
void RescailEn( void )
{
	int ack = 0;
	ack += iic.I2C_Write(SADDR_DRVIC,FUNCRUN2, 0x02 );
	WitTim(1) ;//WAIT	1ms
}


#define TIME_OUT 1000
#define TIMEOUT_ERROR 10

unsigned char Stmv217( unsigned char DH, unsigned char DL )
{
	unsigned char	UcConvCheck;
	unsigned char	UcSetTime;
	int	UcCount;	

	int ack = 0;

	//AF Operation
	ack += iic.I2C_Write(SADDR_DRVIC,TARGETH, DH );//0x84, DH 0x0X
	ack += iic.I2C_Write(SADDR_DRVIC,TARGETL, DL ); //0x85, DL 0xXX

	WitTim(5) ;//WAIT	5ms // 20151104
	UcCount = 0;

	do
	{
		UcConvCheck = (UCHAR)iic.I2C_Read(SADDR_DRVIC, SRVSTATE1, 0);	//0xB0
		UcConvCheck = UcConvCheck & 0x80;  	//bit7 == 0 or not
		UcSetTime = (UCHAR)iic.I2C_Read(SADDR_DRVIC, TGTCNVTIM, 0);	//0xB2 Settle Time check Settle Time Calculate =
		// ( B2h Read Value x 0.171mS ) - 2.731mS Condition:
		//EEPROM 55h(THD1) = 0x20
		//82h:bit2-0( LOCCNVCNT ) = 100b
		WitTim(2) ;//WAIT 2ms 20151104 2->10
		UcCount++;
		if(UcCount == TIME_OUT)	{
			return TIMEOUT_ERROR;
		}
	}while(UcConvCheck); 	

	return SUCCESS;
}




int HallCal_lc898217(){

	unsigned char	UcEEPSts ;
	unsigned char	UcDrvCalSts ;
	unsigned char	UcIniSts ;

	unsigned char	UcAFSts ;
	unsigned char	UcHalSts ;
	unsigned char	UcSts ;
	unsigned char	UcDownloadMode = AUTO_DOWNLOAD;
	unsigned char	UcMode = RESCAILING ;

	UcIniSts = IniSet( WITHOUT_DOWNLOAD ); //Chip Version and I2C communication Checking
	if (UcIniSts != SUCCESS){
		TRACE("SEMCO IniSet Fail!!\n");
		return FAILURE;
	}

	UcEEPSts= EEPROM_Update(); 

	if (UcEEPSts != SUCCESS){
		TRACE("SEMCO EEPROM_Update Fail!!\n");
		return FAILURE;
	}

	//Drv Calibratoin just for No Test Sample
	UcDrvCalSts = CalibDrv();
	if (UcDrvCalSts != SUCCESS){
		TRACE("SEMCO CalibDrv Fail!!\n");
		return FAILURE;
	}

	//Power off and wait 100ms
	//Power Off
	
	DWORD dcGPIO;
	dcGPIO = GPIO_EXPRESS_GPIO_ALL;

	dcGPIO	&= ~GPIO_EXPRESS_GPIO_C11;	DC_GpioWriteOut(g_cardinfo.nCardnum, dcGPIO);
	
	WitTim(100); //Wait 100ms
	
	dcGPIO	|= GPIO_EXPRESS_GPIO_C11;	DC_GpioWriteOut(g_cardinfo.nCardnum, dcGPIO);
	//Power On
	WitTim(5); //Wait 5ms

	if( UcDownloadMode == AUTO_DOWNLOAD){
		UcSts = WakeUpCheck(RESCAILING);

		if (UcSts != SUCCESS){
			TRACE("SEMCO WakeUpCheck Fail!!\n");
			return FAILURE;
		}

	}
	else if( UcDownloadMode == MANUAL_DOWNLOAD){
		UcIniSts = IniSet(MANUAL_DOWNLOAD);
		if (UcIniSts != SUCCESS)
			return FAILURE;
	}


	UcHalSts =TneRunAf(); //Hall calibratoin
	if (UcHalSts != 0x02){
		TRACE("SEMCO TneRunAf Fail!!\n");
		return FAILURE;
	}

	if(UcMode ==  RESCAILING){
		RescailEn(); //A1h 02h setting
	}


	//Set Init Position
	UcAFSts = Stmv217( 0x01, 0x00 );   //Inintial position ex. 0x0100
	if (UcAFSts != SUCCESS){
		TRACE("SEMCO Stmv217 Fail!!\n");
		return FAILURE;
	}



	// below is writing sequence to determine whether success or fail.

	//iic.I2C_Write(eeprom_saddr, address, 0x4D, I2CMODE_DOUBLEADDR); //4D is 77(mean success) in decimal.

	if(StampCalib()!=SUCCESS){
		TRACE("SEMCO StampCalib Fail!!\n");
		return FAILURE;
	}

	TRACE("SEMCO HybridVCA_ControlAPI_Init Success!!\n");
	//Lens Posintion Reading need to bit shift >>4



	return SUCCESS;

}


// 20180806 

SHORT GetCurrentLensPos_AK7371_AK7372(int AKSeries) // 20170403
{
	UCHAR RcvData[2];

	SHORT Position;

	switch(AKSeries)
	{

	case AK7371:	RcvData[0] = iic.I2C_Read(SADDR_DRVIC, 0x86, 0);
					RcvData[1] = iic.I2C_Read(SADDR_DRVIC, 0x87, 0);
					Position = MAKEWORD(RcvData[1], RcvData[0]) >> 6;
					break;

	case AK7372:	RcvData[0] = iic.I2C_Read(SADDR_DRVIC, 0x84, 0);  // High
					RcvData[1] = iic.I2C_Read(SADDR_DRVIC, 0x85, 0);  // Low
					Position = MAKEWORD(RcvData[1], RcvData[0]) >> 6;
					break;
    // 20180725
	case LC898217:  RcvData[0] = iic.I2C_Read(SADDR_DRVIC, 0x0A, 0);  // 0x0A High 
					RcvData[1] = iic.I2C_Read(SADDR_DRVIC, 0x0B, 0);  // 0x0B Low
					Position = MAKEWORD(RcvData[1], RcvData[0]) >> 4;

					break;

	}




	TRACE("AK737X LensPosition : %4d", Position);

	return Position;

}



SHORT GetCurrentLensPos_AK7345()
{
	UCHAR buf[2];
	USHORT temp;
	int ack = 0;
	SHORT pos;

	buf[0] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x00, 0);
	buf[1] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x01, 0);

	temp = MAKEWORD(buf[1], buf[0]);

	pos = (SHORT)(temp >> 7);

	return pos;
}

SHORT GetCurMagnetFieldVal_AK7345()
{
	UCHAR buf[2];
	USHORT temp;
	int ack = 0;
	SHORT val;

	buf[0] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x04, 0);
	buf[1] = (UCHAR)iic.I2C_Read(SADDR_DRVIC, 0x05, 0);

	temp = MAKEWORD(buf[1], buf[0]);

	val = (SHORT)(temp >> 7);

	return val;
}

void ReadAllRegisters_AK7345(BYTE* buf)
{
	for(int i=0; i<0x10; i++)
	{
		buf[i] = (BYTE)iic.I2C_Read(SADDR_DRVIC, i, 0);
	}
}


///////////////////////////////////////////////////// BU63169 ////////////////////////////////////////////////////////
int reois2(void)
{
	 iic.I2C_Write(0x1C, 0x847F,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA);
	IIC_Delay(1000);
	// Servo on (0x0C0C)
	TRACE("> Servo on\n");
 iic.I2C_Write(0x1C, 0x847F,0x0C0C,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA);
 return 0;
}


UINT32 BU636169GetVersion(void) // 20170424 
{

	// 20170330 deleted // 
	int OIS_Delay = 10; // 20170223 

	// 20170424
	UINT32 TotalVersion;
	int FWVersion, CoeffVersion;
	TotalVersion = FWVersion = CoeffVersion = 0;

	FWVersion    = iic.I2C_Read(0x1C, 0x84F6, I2CMODE_DOUBLEADDR | I2CMODE_DOUBLEDATA, OIS_Delay); // 20170223 
	CoeffVersion = iic.I2C_Read(0x1C, 0x8476, I2CMODE_DOUBLEADDR | I2CMODE_DOUBLEDATA, OIS_Delay); // 20170223 

	TRACE("FWVersion : %4X, CoeffVersion : %4X", FWVersion, CoeffVersion); 

	TotalVersion = MAKELONG(FWVersion, CoeffVersion);

	TRACE("TotalVersion : %X", TotalVersion); 

	return TotalVersion;

}

// 20170817 
void ServoOnOFF(int mode) 
{
	if(mode==0)	{	iic.I2C_Write(0x1C, 0x847F,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA); 	IIC_Delay(100); }// Servo OFF

	else		{	iic.I2C_Write(0x1C, 0x847F,0x0C0C,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA);	IIC_Delay(100); }// Servo ON

}

signed short GetHallPosition_BC63163(int index, int OIS_Delay)
{

	signed short Position;

	Position = iic.I2C_Read(0x1C, index, I2CMODE_DOUBLEADDR | I2CMODE_DOUBLEDATA, OIS_Delay);		

	return Position;

}


int UpdateFW(int option)
{

	int result;
	_ADJ calData;
	CString log;

	int fwVer = GetFWVersion();

	char szDirve[256],szDir[256]; 
	char programpath[_MAX_PATH];
	CString fileName;

	int X1_PJT_OISFWVersion = 0; 	// 20180308 int A1_ZEUS_OISFWVersion = 0;


	GetModuleFileName( NULL, programpath, _MAX_PATH);
	_splitpath_s(programpath, szDirve, _MAX_DRIVE, szDir, _MAX_DIR, NULL, NULL, NULL, NULL);

	// 20180308
	// PGSelect - OIS FW Folder
	// D5x    : fw_01_D5x
	// New_E1 : fw_02_New_E1
	// E8     : fw_03_E8 

	CString OISINIFilePath;
	int OISFWFolder;

	CString SplInfo;
	SplInfo.Format("%s%s%s",szDirve,szDir,"\\Setting\\current.dcc"); 

	OISFWFolder = GetPrivateProfileInt("DCC_SET",	"DUAL_PJT_PG_SELECT",	    0,	SplInfo); 

	if(OISFWFolder == 0x00) 
	{
		X1_PJT_OISFWVersion = GetPrivateProfileInt("DCC_SET",	"DCC_OIS_VERSION_D5x",	    0,	SplInfo); 
		OISINIFilePath.Format("%s%s%s",szDirve,szDir,"OIS_FW_01_D5x");
	}
	else if(OISFWFolder == 0x01)
	{
		X1_PJT_OISFWVersion = GetPrivateProfileInt("DCC_SET",	"DCC_OIS_VERSION_New_E1",	0,	SplInfo); 
		OISINIFilePath.Format("%s%s%s",szDirve,szDir,"OIS_FW_02_New_E1");
	}
	else if(OISFWFolder == 0x02)
	{
		X1_PJT_OISFWVersion = GetPrivateProfileInt("DCC_SET",	"DCC_OIS_VERSION_E8",	    0,	SplInfo); 
		OISINIFilePath.Format("%s%s%s",szDirve,szDir,"OIS_FW_03_E8");	
	}


	int len = OISINIFilePath.GetLength();

	char* path = new char[len];

	strcpy(path, OISINIFilePath.GetBuffer(0));

	result = ROHMOIS_SetIniFilePath(path);

	if(result != 0)	{	DisplayErrorMsg(result);	return FALSE;	}
	//
	

	if( LOWORD(fwVer) == X1_PJT_OISFWVersion) // 20180308 if( LOWORD(fwVer) == A1_ZEUS_OISFWVersion) 
	{
		TRACE("[FINISH] firmware is downloaded already.");	return TRUE;
	}

	TRACE("[START] Downloading firmware\n");

	TRACE("> Initializing OIS adjustment dll...\n");

	result = ROHMOIS_InitFADJ();

	if(result != 0)
	{
		DisplayErrorMsg(result);	return FALSE;
	}

	int nId = 0;
	int nDelay = 1;

	result = ROHMOIS_Init_HW(nId, nDelay);

	if(result != ADJ_OK)
	{
		DisplayErrorMsg(result);	return FALSE;
	}

	TRACE(("> ROHM_OIS_ABS.dll Port: %d, Delay: %d\n"), nId, nDelay);

	TRACE("> Downloading binary file...");

	result = ROHMOIS_ProgramDownload();

	if(result != ADJ_OK)
	{
		DisplayErrorMsg(result);	return FALSE;
	}

	TRACE("> Downloading Coefficient file...\n");

	result = ROHMOIS_CoefDownload();

	if(result != ADJ_OK)
	{
		DisplayErrorMsg(result);	return FALSE;
	}

	if( IsOisStatusIdle() != TRUE )
	{
		TRACE("[ERROR] Invalid OIS status\n");	return FALSE;
	}

////////////////////////////////////////////////////////////////
	FillMemory(&calData, sizeof(_ADJ), 0xFF);	

	TRACE("[START] Centering with Adjustment Data\n");

	TRACE("> Load Data from memory...");

	{
		static const int m_nvm_offset	= 0x1666; // 20170817 0x1656(Ver1.0) ¡æ 2.0

		calData.gl_CURDAT	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 0),eeprom.I2C_Read_EEPROM(m_nvm_offset + 1));
		calData.gl_HALOFS_X	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 2), eeprom.I2C_Read_EEPROM(m_nvm_offset + 3));
		calData.gl_HALOFS_Y	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 4), eeprom.I2C_Read_EEPROM(m_nvm_offset + 5));
		calData.gl_HX_OFS	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 6), eeprom.I2C_Read_EEPROM(m_nvm_offset + 7));
		calData.gl_HY_OFS	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 8), eeprom.I2C_Read_EEPROM(m_nvm_offset + 9));
		calData.gl_PSTXOF	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 10),eeprom.I2C_Read_EEPROM(m_nvm_offset + 11));
		calData.gl_PSTYOF	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 12), eeprom.I2C_Read_EEPROM(m_nvm_offset + 13));
		calData.gl_GX_OFS	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 14), eeprom.I2C_Read_EEPROM(m_nvm_offset + 15));
		calData.gl_GY_OFS	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 16), eeprom.I2C_Read_EEPROM(m_nvm_offset + 17));
		calData.gl_KgxHG	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 18), eeprom.I2C_Read_EEPROM(m_nvm_offset + 19));
		calData.gl_KgyHG	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 20), eeprom.I2C_Read_EEPROM(m_nvm_offset + 21));
		calData.gl_KGXG		= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 22), eeprom.I2C_Read_EEPROM(m_nvm_offset + 23));
		calData.gl_KGYG		= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 24), eeprom.I2C_Read_EEPROM(m_nvm_offset + 25));
		calData.gl_SFTHAL_X	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 26), eeprom.I2C_Read_EEPROM(m_nvm_offset + 27));
		calData.gl_SFTHAL_Y	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 28), eeprom.I2C_Read_EEPROM(m_nvm_offset + 29));
		calData.gl_TMP_X_	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 30), eeprom.I2C_Read_EEPROM(m_nvm_offset + 31));
		calData.gl_TMP_Y_	= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 32), eeprom.I2C_Read_EEPROM(m_nvm_offset + 33));
		calData.gl_KgxH0		= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 34), eeprom.I2C_Read_EEPROM(m_nvm_offset + 35));
		calData.gl_KgyH0		= MAKEWORD(eeprom.I2C_Read_EEPROM(m_nvm_offset + 36), eeprom.I2C_Read_EEPROM(m_nvm_offset + 37));
	}

	const BYTE	_ADDR_GYRO_REG_GYRO_CONFIG	= 0x1B;
	const BYTE	_ADDR_GYRO_REG_ACCEL_CONFIG	= 0x1C;
	const BYTE  _ADDR_GYRO_REG_PWR_MGMT_1	= 0x6B;
	
	static const int _ERR_SUCCESS			= 0;

	// reset device // I2CMODE_DOUBLEDATA
	if( iic.I2C_Write(0x1C, 0x8218,0x0F00,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821B,0x806B,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821C,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;

	IIC_Delayus(0.100f);

	// set PWR_MGMT = 01b //_ADDR_GYRO_REG_PWR_MGMT_1
	if( iic.I2C_Write(0x1C, 0x8218,0x0F00,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821B,0x016B,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821C,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;

	IIC_Delayus(0.200f);

	// set FS_SEL = 01b: bit[4:3] of GYRO_CONFIG register (00001000b = 0x08) _ADDR_GYRO_REG_GYRO_CONFIG
	if( iic.I2C_Write(0x1C, 0x8218,0x0F00,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821B,0x081B,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821C,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;

	// set AFS_SEL = 00b _ADDR_GYRO_REG_ACCEL_CONFIG
	if( iic.I2C_Write(0x1C, 0x8218,0x0F00,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821B,0x001C,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	if( iic.I2C_Write(0x1C, 0x821C,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )			return FALSE;
	
	IIC_Delayus(0.001f);

	TRACE("> Centering...\n");

	int status = ADJ_OK;

	IIC_Delay(100);

	status = ROHMOIS_InitOIS(&calData);

	if(status != ADJ_OK)
	{
		TRACE("[ERROR] OIS init. is failed\n");		return FALSE;
	}

	TRACE("> disable gyro accelator output...");

	if( iic.I2C_Write(0x1C, 0x828B,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )		return FALSE; 	// accelation ratio X
	if( iic.I2C_Write(0x1C, 0x82CB,0x0000,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )		return FALSE;  	// accelation ratio Y
	if( iic.I2C_Write(0x1C, 0x8410,0xFF7F,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )		return FALSE;   // gyro ratio 1.0

	// Servo on (0x0C0C)
	IIC_Delay(100);

	TRACE("> Servo on\n");

	if( iic.I2C_Write(0x1C, 0x847F,0x0C0C,I2CMODE_DOUBLEADDR|I2CMODE_DOUBLEDATA) != _ERR_SUCCESS )		return FALSE;

	TRACE("[FINISH] Centering with Adjustment Data\n");

	return TRUE;
}

int GetFWVersion() // 20170330
{
	// 20170330 deleted // 
	int OIS_Delay = 1; // 20170223 20170817 10->1 

	// 20170424
	int FWVersion, CoeffVersion;
	FWVersion = CoeffVersion = 0;

	FWVersion    = iic.I2C_Read(0x1C, 0x84F6, I2CMODE_DOUBLEADDR | I2CMODE_DOUBLEDATA, OIS_Delay); // 20170223 
	CoeffVersion = iic.I2C_Read(0x1C, 0x8476, I2CMODE_DOUBLEADDR | I2CMODE_DOUBLEDATA, OIS_Delay); // 20170223 

	TRACE("FWVersion : %4X, CoeffVersion : %4X", FWVersion, CoeffVersion); 

	return FWVersion;
}

int MemAreaRead(BYTE addr, BYTE* pData, int size)
{
	int result;

	BYTE wBuf[2];
	static const BYTE _I2C_OPCODE_MEM_ACCESS	= 0x84;
	BYTE opcode	= _I2C_OPCODE_MEM_ACCESS;

	wBuf[0] = opcode;
	wBuf[1] = addr;
	int index = ((opcode | 0xFF) < 8) | (addr | 0xFF);


	static const BYTE _SLAVE_ADDR				= 0x1C;
	//result = ReadI2CDev(_SLAVE_ADDR, 2, wBuf, 2, pData);
	result = iic.I2C_Read_Burst_uc(_SLAVE_ADDR,  index, 2, pData, size);
	if(result != 0)
		return FALSE;
	else
		return TRUE;
}

void DisplayErrorMsg(int status)
{
	char log[128];

	switch(status)
	{
	case ADJ_OK:
		break;
	case PROG_DL_ERR:
		TRACE("[ERROR] FW download\n");
		break;
	case COEF_DL_ERR:
		TRACE("[ERROR] Coeff. download\n");
		break;
	case I2C_WRITE_ERR:
		TRACE("[ERROR] I2C write\n");
		break;
	case I2C_READ_ERR:
		TRACE("[ERROR] I2C read\n");
		break;
	case EEPROM_WRITE_ERR:
		TRACE("[ERROR] EEPROM write\n");
		break;
	case EEPROM_READ_ERR:
		TRACE("[ERROR] EEPROM read\n");
		break;
	case NO_INI_FILE_EXIST:
		TRACE("[ERROR] ROHM_OIS.INI file doesn't exists\n");
		break;
	case NO_FW_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: FW\n");
		break;
	case NO_FW_FILE_EXIST:
		TRACE("[ERROR] FW file doesn't exists");
		break;
	case NO_COEF_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: COEF\n");
		break;
	case NO_COEF_FILE_EXIST:
		TRACE("[ERROR] Coeff.(mem) file doesn't exists\n");
		break;
	case NO_CROP_X_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: CROP_X\n");
		break;
	case NO_CROP_Y_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: CROP_Y\n");
		break;
	case NO_CROP_WIDTH_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: CROP_WIDTH\n");
		break;
	case NO_CROP_HEIGHT_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: CROP_HEIGHT\n");
		break;
	case NO_DIR_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: DIR\n");
		break;
	case NO_IMAGE_DIR_EXIST:
		TRACE("[ERROR] Image saving path for adjustment doesn't exists\n");
		break;
	case NO_SLICELEVEL_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: SLICELEVEL\n");
		break;
	case NO_OFS_TBL_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: OFS_TBL\n");
		break;
	case NO_BETWEEN_CIRCLE_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: DISTANCE_BETWEEN_CIRCLE\n");
		break;
	case NO_TO_CIRCLE_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: DISTANCE_TO_CIRCLE\n");
		break;
	case NO_D_CF_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: D_CF\n");
		break;
	case NO_ACT_DRV_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: ACT_DRV\n");
		break;
	case NO_FOCAL_LENGTH_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: FOCAL_LENGTH\n");
		break;
	case NO_MAX_OIS_SENSE_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: MAX_OIS_SENSE\n");
		break;
	case NO_MIN_OIS_SENSE_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: MIN_OIS_SENSE\n");
		break;
	case NO_MAX_COIL_R_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: MAX_COIL_R\n");
		break;
	case NO_MIN_COIL_R_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: MIN_COIL_R\n");
		break;
	case NO_EEPROM_SLVADR_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: EEPROM_SLVADR\n");
		break;
	case NO_EEPROM_FADJ_START_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: EEPROM_FADJ_START\n");
		break;
	case NO_ENLARGE_MOVABLE_RANGE_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: ENLARGE_MOVABLE_RANGE\n");
		break;
	case NO_RANGE_CRITERIA_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: RANGE_CRITERIA\n");
		break;
	case NO_MARGIN_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: MARGIN\n");
		break;
	case NO_EXT_CLK_KEY_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: EXT_CLK\n");
		break;
	case NO_ENABLE_GYRO_DRIFT_COMP_EXIST:
		TRACE("[ERROR] Setting value in ROHM_OIS.INI: ENABLE_GYRO_DRIFT_COMP\n");
		break;
	case NO_OIS_ABS_KEY_EXIST:
		TRACE("[ERROR] ROHM_OIS_ABS.DLL path is undefined in ROHM_OIS.INI\n");
		break;
	case LIBRALY_LOAD_ERR:
		TRACE("[ERROR] ROHM_OIS_GENE.DLL load error\n");
		break;
	default:
		sprintf_s(log, "[ERROR] Undefined status: %d\n", status);
		TRACE(log);
		break;
	}
}

BOOL IsOisStatusIdle()
{
	static const BYTE _MEM_ADDR_STATUS			= 0xF7;
	static const BYTE _STATUS_IDLE		= 0x04;
	BYTE pData[2];
	USHORT count = 0;
	
	while( count < 5 )
	{
		IIC_Delay(100);
		//MemAreaRead(_MEM_ADDR_STATUS, pData,2);
		BYTE n = LOBYTE(iic.I2C_Read(0x1C, 0x84F7, I2CMODE_DOUBLEADDR | I2CMODE_DOUBLEDATA));

		if( n == _STATUS_IDLE)
			break;
		else
			count++;
	}

	if( count >= 10 )
		return FALSE;
	TRACE("Ois Status Idle!!!!\n");
	return TRUE;
}