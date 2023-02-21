#ifndef __ActuatorDrvIC_H_____
#define __ActuatorDrvIC_H_____

// 20170403
#define AK7345 0
#define AK7371 1
#define AK7372 2
#define LC898217 3 // 20180807 

// Init
BOOL InitActuator_WV560();
BOOL InitActuator_DW9714();
int  InitVCA_AK7345(); // 20170403 AK7345, AK7371, AK7372 공용 사용 가능
int  InitVCA_LC898217();     //20180807


BOOL LensMove_WV560(short targetPos);
BOOL LensMove_DW9714(short targetPos);
BOOL LensMove_AK7345(short target_pos);
BOOL  LensMove_AKSeries(short target_pos, int AKSeries);  // 20170403 LensMove_AK7345(targetPos);
BOOL LensMove_LC898217(short target_pos);                // 20180807

SHORT GetCurrentLensPos_WV560();
SHORT GetMechanicalLimitPos_WV560(bool isMacPos = false);


void  ReadAllRegisters_AK7345(BYTE* buf);

SHORT GetCurrentLensPos_AK7345();
SHORT GetCurMagnetFieldVal_AK7345();
SHORT GetCurrentLensPos_AK7371_AK7372(int AKSeries);     // 20170403 



//


int HallCal_lc898217();
bool StampCalib(void);
bool isCalibrated(void);
unsigned char CheckCver( void );
void	IniCmd( void );
unsigned char	IniSet( unsigned char UcAutoDownload );
void E2pWriteBytes( unsigned short addr, unsigned char *dt, int len );
void E2pWriteBytes( unsigned short addr, char *dt, int len );
void	EEPROM_Set( void );
unsigned char	EEPROM_Verify( void );
void RamWriteA(unsigned char ucAddr, unsigned short usData);
void RamReadA(unsigned char ucAddr, unsigned short *pReadVal);
void E2pReadBytes( unsigned short addr, unsigned char *dt, int len );
unsigned char	EEPROM_Update( void );
void	CalibDrvOffIni( unsigned char UcIniSel );
unsigned char	CalibDrvOff( unsigned char	UcAdjSel );
void	WriteDrvOff( unsigned char UcWriteSel );
unsigned char	CalibDrv( void );
void	WitTim( unsigned short	UsWitTim );
unsigned char	WakeUpCheck(unsigned char UcRescailMode);
unsigned char	CalibHall( unsigned char	UcData );
void	CalDataWrite( void );
unsigned char	TneRunAf( void );
void RescailEn( void );
unsigned char Stmv217( unsigned char DH, unsigned char DL );


void ReadAllRegisters_AK7345(BYTE* buf);

// 20170817 BU63169 
int UpdateFW(int option);
int reois2(void);
int GetFWVersion();
int MemAreaRead(BYTE addr, BYTE* pData, int size);
void DisplayErrorMsg(int status);
BOOL IsOisStatusIdle();
UINT32 BU636169GetVersion(void);
void ServoOnOFF(int mode); 
signed short GetHallPosition_BC63163(int index, int OIS_Delay);

///////////////////////////////////////////////////////////////////////////////////////
#endif //__ActuatorDrvIC_H_____