//********************************************************************************
//
//		<< LC898217 Evaluation Soft>>
//		Program Name	: Af.h
// 		Explanation		: LC898217 Global Declaration & ProtType Declaration
//		Design			: Y.Yamada
//		History			: First edition						2015.07.03 Y.Tashita
//********************************************************************************


#define	FW_VER			0x0007

#ifdef	AFINI
	#define	AFINI__
#else
	#define	AFINI__		extern
#endif

#ifdef	AFCMD
	#define	AFCMD__
#else
	#define	AFCMD__		extern
#endif

#define		MODULE_CALIBRATION		// for module maker
#define		WITHOUT_TEST
#define		SLAVE_ADDRESS_FOR_RAMREG	0xE4
#define		SLAVE_ADDRESS_FOR_EEPROM	0xE6

// Command Status
#define		EXE_END		0x02		// Execute End (Adjust OK)
#define		EXE_HADJ	0x06		// Adjust NG : Hall NG (Gain or Offset)
#define		EXE_LADJ	0x0A		// Adjust NG : X Loop NG (Gain)
#define		EXE_OCADJ	0x42		// Adjust NG : OSC Clock NG
#define		EXE_ERR		0x99		// Execute Error End

// Common Define
#define	SUCCESS			0x00		// Success
#define	FAILURE			0x01		// Failure
#define CALIBRATED		0x02

#ifndef ON
 #define	ON				0x01		// ON
 #define	OFF				0x00		// OFF
#endif

#define	NOP_TIME		0.00004166F

#define	WITHOUT_DOWNLOAD	0
#define	AUTO_DOWNLOAD		1
#define	MANUAL_DOWNLOAD		2

#define RESCAILING 1

#define	INITIALIZATION_OK	0
#define	I2C_ERROR			1
#define	DOWNLOAD_ERROR		2

struct STCMDTBL{
	unsigned short Cmd ;
	unsigned int UiCmdStf ;
	void ( *UcCmdPtr )( void ) ;
} ;

/*** caution [little-endian] ***/

// Word Data Union
union	WRDVAL{
	unsigned short	UsWrdVal ;
	unsigned char	UcWrkVal[ 2 ] ;
	struct {
		unsigned char	UcLowVal ;
		unsigned char	UcHigVal ;
	} StWrdVal ;
} ;

typedef union WRDVAL	UnWrdVal ;

union	DWDVAL {
	unsigned long	UlDwdVal ;
	unsigned short	UsDwdVal[ 2 ] ;
	struct {
		unsigned short	UsLowVal ;
		unsigned short	UsHigVal ;
	} StDwdVal ;
	struct {
		unsigned char	UcRamVa0 ;
		unsigned char	UcRamVa1 ;
		unsigned char	UcRamVa2 ;
		unsigned char	UcRamVa3 ;
	} StCdwVal ;
} ;

typedef union DWDVAL	UnDwdVal;

// Float Data Union
union	FLTVAL {
	float			SfFltVal ;
	unsigned long	UlLngVal ;
	unsigned short	UsDwdVal[ 2 ] ;
	struct {
		unsigned short	UsLowVal ;
		unsigned short	UsHigVal ;
	} StFltVal ;
} ;

typedef union FLTVAL	UnFltVal ;

union	SNDWDVAL {
	signed long	SlDwdVal ;
	signed short	SsDwdVal[ 2 ] ;
	struct {
		signed short	SsLowVal ;
		signed short	SsHigVal ;
	} StDwdVal ;
	struct {
		signed char	ScRamVa0 ;
		signed char	ScRamVa1 ;
		signed char	ScRamVa2 ;
		signed char	ScRamVa3 ;
	} StCdwVal ;
} ;

typedef union SNDWDVAL	SnDwdVal;


typedef struct STADJPAR {
	struct {
		//Before
		unsigned short	UsHlbCen ;				// Hall Center Value after Hall Adjust
		unsigned short	UsHlbMax ;				// Hall Max Value
		unsigned short	UsHlbMin ;				// Hall Min Value
		unsigned short	UsHlbOff ;				// Hall Offset Value
		unsigned short	UsHlbBia ;				// Hall Gain Value
		unsigned short	UsAdbOff ;				// Hall A/D Offset Value
		
		//After
		unsigned short	UsHlaCen ;				// Hall Center Value after Hall Adjust
		unsigned short	UsHlaMax ;				// Hall Max Value
		unsigned short	UsHlaMin ;				// Hall Min Value
		unsigned short	UsHlaOff ;				// Hall Offset Value
		unsigned short	UsHlaBia ;				// Hall Gain Value
		unsigned short	UsAdaOff ;				// Hall A/D Offset Value
	} StHalAdj ;
	
	struct {
		unsigned short	UsLgbVal ;				// Loop Gain befre
		unsigned short	UsLgaVal ;				// Loop Gain after
	} StLopGan ;
} stAdjPar ;

AFCMD__	stAdjPar	StAdjPar ;				// Execute Command Parameter

// Prottype Declation
AFINI__ unsigned char	IniSet( unsigned char ) ;											// Initial Top Function
AFINI__ void			WitTim( unsigned short ) ;											// Wait
AFINI__ void			MemClr( unsigned char *, unsigned short ) ;							// Memory Clear Function

AFCMD__ unsigned char	EEPROM_Update( void ) ;
#ifdef WITHOUT_TEST
AFCMD__ unsigned char	CalibDrv( void ) ;
#endif
AFCMD__ unsigned char	TneRunAf( void ) ;





