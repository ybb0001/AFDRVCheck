#include "AFDRVCheck.h"
#include "ui_AFDRVCheck.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include<iostream>
#include<fstream>   
#include <string>
#include<sstream>
#include <dclib.h>
#include <dglib.h>
#include <d2lib.h>
#include "I2C.h"
//#include "Eeprom.h" 

CI2C I2C;

#pragma comment(lib,"winmm.lib")

using namespace std;
using namespace Ui;

char D[32768][2];
unsigned char DecData[32768];
unsigned char AF_DecData[32768];

char chk[2];
unsigned char slave, addr_H, addr_L;
unsigned char data_LSB[4];
int yy = 0x200000,OIS_range_ratio=80, m_Aging_Times=300000;
int CH = 0, test_Times=10;

int Value_init = -1;
int Value_Cards = -1;
int Value_Version = -1;
DWORD DllVer;
DWORD DrvVer;
DWORD ChipVer;
DWORD BrdVer;

int Value_GPIOread = -1;
DWORD GPIO_Data=0;
//DWORD GPIO_Data_Value;

int Value_GPIOwrite = -1;
int Value_Channels = -1;
int Value_I2cStart = -1;
int Value_I2cWrite = -1;
int Value_I2cRead = -1;
int EEP_Size = 16384;
const int PageSize = 0x10;
float m_Delay = 0;

MyThread *subThread = new MyThread;
QString uiContent;
HDG pHdg = 0, pHdg1=0;

bool Start = false;
Ui::EEPROM *ui_Out;
string s , src;
HINSTANCE hDllInst = LoadLibrary(TEXT("dclib.dll"));
ofstream fout(".\\logData.txt");
ofstream script_log;


void Delay(DWORD delayTime)
{
	Sleep(delayTime);
	//DWORD delayTimeBegin;
	//DWORD delayTimeEnd;
	//delayTimeBegin = timeGetTime();
	//do{
	//	delayTimeEnd = timeGetTime();
	//} while (delayTimeEnd - delayTimeBegin < delayTime);
	//int x = 0;
}


int hex2Dec(int x) {
	int s = 0;
	for (int i = 0; i < 2; i++) {
		s = s * 16;
		if (D[x][i] >= 'A')
			s += D[x][i] - 'A' + 10;
		else
			s += D[x][i] - '0';
	}
	return s;
}


void getHex(unsigned int tmp) {
	int a = tmp / 16;
	int b = tmp % 16;
	if (a < 10)
		chk[0] = '0' + a;
	else
		chk[0] = 'A' + a - 10;

	if (b < 10)
		chk[1] = '0' + b;
	else
		chk[1] = 'A' + b - 10;
}

unsigned char getHexValue(char x) {
	unsigned char s = 0;
	if (x >= 'a')
		s = x - 'a' + 10;
	else if (x >= 'A')
		s = x - 'A' + 10;
	else
		s = x - '0';
	return s;
}

int my_DG_I2C_Read2(UCHAR Slave, USHORT addr, int length, UCHAR *data) {

	int ack = 0;
	UCHAR buf[5] = { Slave ,addr >> 8,addr & 0xFF ,0,0 };
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	buf[0] += 1;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, data, length);

	return ack;
}

void log_out(int x) {
	for (int i = 0; i < x; i++) {
		getHex(DecData[i]);
		fout << chk[0] << chk[1] << " ";
	}
	fout << endl;
}

void AFDRVCheck::eepLockOpen() {

	read_Setting();

	if (ui->Dphy->isChecked()) {
		DC_I2cInit(0, 0, 1, 1);
		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x06);
		DC_I2cStop(0, 0);
		Sleep(10);
	}

	if (ui->Cphy->isChecked()) {
		BYTE buf[19] = { 0, };
		buf[0] = slave;
		buf[1] = 0x80;
		buf[2] = 0;
		buf[3] = 0;

		int ack = DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 1 + 3);
		IIC_Delayus(0.005f); // IIC_Delayus(0.001f); -> sometimes no write
		
	}
}

void  AFDRVCheck::eepLockClose() {
	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x0E);
	DC_I2cStop(0, 0);
	Sleep(10);
}

unsigned char getUchar() {
	if (src.length() < 2)
		return 0;
	unsigned char s = getHexValue(src[0])*16+ getHexValue(src[1]);
	return s;
}

void AFDRVCheck::displayText(QString s) {

	//ui->AF_Times->setText(uiContent);
	ui->AF_Times->setText(s);

}

void  AFDRVCheck::displayNum(int n) {
	ui->AF_Times->setText(QString::number(n));
}


void  AFDRVCheck::load_Setting() {

	slave = GetPrivateProfileInt(TEXT("TEST_OPTION"), TEXT("Slave"), 0xA0, TEXT(".\\Setting\\Setting.ini"));

	QString str = "00";
	int a1 = slave / 16;
	int b1 = slave % 16;
	if (a1 > 9)str[0] = 'A' + a1 - 10;
	else str[0] = '0' + a1;
	if (b1 > 9)str[1] = 'A' + b1 - 10;
	else str[1] = '0' + b1;

	ui->slave->setText(str);
	test_Times = GetPrivateProfileInt(TEXT("TEST_OPTION"), TEXT("Test_Times"), 10, TEXT(".\\Setting\\Setting.ini"));
	ui->AF_Times->setText(to_string(test_Times).c_str());

}

void  AFDRVCheck::read_Setting() {
	
	//memset(DecData, 0, sizeof(DecData));
	EEP_Size = ui->eep_size->document()->toPlainText().toInt();

	src = ui->slave->document()->toPlainText().toLocal8Bit();
	slave = getUchar();
	src = ui->addH->document()->toPlainText().toLocal8Bit();
	addr_H = getUchar();
	src = ui->addL->document()->toPlainText().toLocal8Bit();
	addr_L = getUchar();

	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();

}

void  AFDRVCheck::on_pushButton_save_clicked() {

	//memset(DecData, 0, sizeof(DecData));

}

void AFDRVCheck::GPIO_display() {

	if ((GPIO_Data & 0x1) > 0) {
		ui->checkBox->setChecked(true);
	}
	else
		ui->checkBox->setChecked(false);

	if ((GPIO_Data & 0x2) > 0) {
		ui->checkBox_1->setChecked(true);
	}
	else
		ui->checkBox_1->setChecked(false);

	if ((GPIO_Data & 0x4) > 0) {
		ui->checkBox_2->setChecked(true);
	}
	else
		ui->checkBox_2->setChecked(false);

	if ((GPIO_Data & 0x8) > 0) {
		ui->checkBox_3->setChecked(true);
	}
	else
		ui->checkBox_3->setChecked(false);

	if ((GPIO_Data & 0x10)> 0) {
		ui->checkBox_4->setChecked(true);
	}
	else
		ui->checkBox_4->setChecked(false);

	if ((GPIO_Data & 0x20) > 0) {
		ui->checkBox_5->setChecked(true);
	}
	else
		ui->checkBox_5->setChecked(false);

	if ((GPIO_Data & 0x40) > 0) {
		ui->checkBox_6->setChecked(true);
	}
	else
		ui->checkBox_6->setChecked(false);

	if ((GPIO_Data & 0x80) > 0) {
		ui->checkBox_7->setChecked(true);
	}
	else
		ui->checkBox_7->setChecked(false);

	if ((GPIO_Data & 0x100) > 0) {
		ui->checkBox_8->setChecked(true);
	}
	else
		ui->checkBox_8->setChecked(false);

	if ((GPIO_Data & 0x200) > 0) {
		ui->checkBox_9->setChecked(true);
	}
	else
		ui->checkBox_9->setChecked(false);

	if ((GPIO_Data & 0x400) > 0) {
		ui->checkBox_10->setChecked(true);
	}
	else
		ui->checkBox_10->setChecked(false);

	if ((GPIO_Data & 0x800) > 0) {
		ui->checkBox_11->setChecked(true);
	}
	else
		ui->checkBox_11->setChecked(false);

	if ((GPIO_Data & 0x1000) > 0) {
		ui->checkBox_12->setChecked(true);
	}
	else
		ui->checkBox_12->setChecked(false);

	if ((GPIO_Data & 0x2000) > 0) {
		ui->checkBox_13->setChecked(true);
	}
	else
		ui->checkBox_13->setChecked(false);

	if ((GPIO_Data & 0x4000) > 0) {
		ui->checkBox_14->setChecked(true);
	}
	else
		ui->checkBox_14->setChecked(false);

	if ((GPIO_Data & 0x8000) > 0) {
		ui->checkBox_15->setChecked(true);
	}
	else
		ui->checkBox_15->setChecked(false);

	if ((GPIO_Data & 0x10000) > 0) {
		ui->checkBox_16->setChecked(true);
	}
	else
		ui->checkBox_16->setChecked(false);

	if ((GPIO_Data & 0x20000) > 0) {
		ui->checkBox_17->setChecked(true);
	}
	else
		ui->checkBox_17->setChecked(false);

	if ((GPIO_Data & 0x40000) > 0) {
		ui->checkBox_18->setChecked(true);
	}
	else
		ui->checkBox_18->setChecked(false);

	if ((GPIO_Data & 0x80000) > 0) {
		ui->checkBox_19->setChecked(true);
	}
	else
		ui->checkBox_19->setChecked(false);

	if ((GPIO_Data & 0x100000) > 0) {
		ui->checkBox_20->setChecked(true);
	}
	else
		ui->checkBox_20->setChecked(false);

	if ((GPIO_Data & 0x200000) > 0) {
		ui->checkBox_21->setChecked(true);
	}
	else
		ui->checkBox_21->setChecked(false);

	if ((GPIO_Data & 0x400000) > 0) {
		ui->checkBox_22->setChecked(true);
	}
	else
		ui->checkBox_22->setChecked(false);

	if ((GPIO_Data & 0x800000) > 0) {
		ui->checkBox_23->setChecked(true);
	}
	else
		ui->checkBox_23->setChecked(false);

	if ((GPIO_Data & 0x1000000) > 0) {
		ui->checkBox_24->setChecked(true);
	}
	else
		ui->checkBox_24->setChecked(false);

	if ((GPIO_Data & 0x2000000) > 0) {
		ui->checkBox_25->setChecked(true);
	}
	else
		ui->checkBox_25->setChecked(false);

	if ((GPIO_Data & 0x4000000) > 0) {
		ui->checkBox_26->setChecked(true);
	}
	else
		ui->checkBox_26->setChecked(false);

	if ((GPIO_Data & 0x8000000) > 0) {
		ui->checkBox_27->setChecked(true);
	}
	else
		ui->checkBox_27->setChecked(false);

	if ((GPIO_Data & 0x10000000) > 0) {
		ui->checkBox_28->setChecked(true);
	}
	else
		ui->checkBox_28->setChecked(false);

	if ((GPIO_Data & 0x20000000) > 0) {
		ui->checkBox_29->setChecked(true);
	}
	else
		ui->checkBox_29->setChecked(false);

	if ((GPIO_Data & 0x40000000) > 0) {
		ui->checkBox_30->setChecked(true);
	}
	else
		ui->checkBox_30->setChecked(false);

	if ((GPIO_Data & 0x80000000) > 0) {
		ui->checkBox_31->setChecked(true);
	}
	else
		ui->checkBox_31->setChecked(false);

	ui->GPIO_Value->setText(QString::number(GPIO_Data, 10));
}


void AFDRVCheck::on_checkBox_clicked() {
	GPIO_Data ^= 0x1;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_1_clicked() {
	GPIO_Data ^= 0x2;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_2_clicked() {
	GPIO_Data ^= 0x4;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_3_clicked() {
	GPIO_Data ^= 0x8;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_4_clicked() {
	GPIO_Data ^= 0x10;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_5_clicked() {
	GPIO_Data ^= 0x20;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_6_clicked() {
	GPIO_Data ^= 0x40;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_7_clicked() {
	GPIO_Data ^= 0x80;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_8_clicked() {
	GPIO_Data ^= 0x100;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_9_clicked() {
	GPIO_Data ^= 0x200;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_10_clicked() {
	GPIO_Data ^= 0x400;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_11_clicked() {
	GPIO_Data ^= 0x800;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_12_clicked() {
	GPIO_Data ^= 0x1000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_13_clicked() {
	GPIO_Data ^= 0x2000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_14_clicked() {
	GPIO_Data ^= 0x4000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_15_clicked() {
	GPIO_Data ^= 0x8000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_16_clicked() {
	GPIO_Data ^= 0x10000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_17_clicked() {
	GPIO_Data ^= 0x20000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_18_clicked() {
	GPIO_Data ^= 0x40000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_19_clicked() {
	GPIO_Data ^= 0x80000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_20_clicked() {
	GPIO_Data ^= 0x100000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_21_clicked() {
	GPIO_Data ^= 0x200000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_22_clicked() {
	GPIO_Data ^= 0x400000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_23_clicked() {
	GPIO_Data ^= 0x800000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_24_clicked() {
	GPIO_Data ^= 0x1000000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_25_clicked() {
	GPIO_Data ^= 0x2000000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_26_clicked() {
	GPIO_Data ^= 0x4000000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_27_clicked() {
	GPIO_Data ^= 0x8000000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_28_clicked() {
	GPIO_Data ^= 0x10000000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_29_clicked() {
	GPIO_Data ^= 0x20000000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_30_clicked() {
	GPIO_Data ^= 0x40000000;
	GPIO_display();
}
void AFDRVCheck::on_checkBox_31_clicked() {
	GPIO_Data ^= 0x80000000;
	GPIO_display();
}


DWORD WINAPI myThread(LPVOID argv) {

	char buff[10] = { 0 };
	memcpy(buff, argv, 10);

	script_log.open(".\\test_log.txt");
	int ack = 0;
	unsigned char Read_Data[5] = { 0 }, AF_slave_Read = 0x19;
	unsigned char OIS_Data[5] = { 0x7C,0x60,0x20,0x01,0 }, OIS_slave_Read = 0x7D;
	unsigned char OIS_Data1[5] = { 0x7C,0x61,0xDC,0x03,0 };
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.01f);
	unsigned char OIS_Data3[5] = { 0x7C,0x60,0x60,0,0 };
	int start = 1020, end = -1024;
	
	start *= OIS_range_ratio / 100.0;
	end *= OIS_range_ratio / 100.0;
	for (int x = 0; x < m_Aging_Times; x++) {

		if (Start == false) {
			break;
		}
		int pos = start;
		if (x % 2 == 1)pos = end;
		OIS_Data3[1] = 0x61;
		OIS_Data3[2] = 0xDE;  //X:0xDE   Y:0xE0
		OIS_Data3[3] = (pos >> 8) & 0xFF;
		OIS_Data3[4] = pos & 0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		OIS_Data3[2] = 0xE0;  //X:0xDE   Y:0xE0
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
		IIC_Delayus(m_Delay);
		int cnt = 0;
		OIS_Data3[2] = 0x9B;
		OIS_Data3[3] = 3;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		my_DG_I2C_Read2(0x7C, 0x619C, 2, Read_Data);
		script_log << x << "	" << Read_Data[0] * 256 + Read_Data[1] << "	";
		OIS_Data3[3] = 5;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		my_DG_I2C_Read2(0x7C, 0x619C, 2, Read_Data);
		script_log << Read_Data[0] * 256 + Read_Data[1] << endl;
	}

	script_log.close();
	return NULL;
}


void AFDRVCheck::display_EEP() {

	ui->input->clear();
	ui->input->setFontPointSize(9);
	for (int i = 0; i < EEP_Size; i++) {

		if (i % 16 == 0) {
			unsigned char a = i / 256;
			getHex(a);
			string s = chk;
			s[2] = '\0';
			ui->input->insertPlainText(s.c_str());
			unsigned char b = i % 256;
			getHex(b);
			char st[5] = { 0 };
			st[0] = chk[0]; st[1] = chk[1]; st[2] = ':'; st[3] = ' ';
			ui->input->insertPlainText(st);
		}

		getHex(DecData[i]);
		char st[4] = { 0 };
		st[0] = chk[0]; st[1] = chk[1]; st[2] = ' '; st[3] = '\0';
		ui->input->insertPlainText(st);

		if (i % 16 == 15)
			ui->input->insertPlainText("\n");
	}

}


int awI2CRead(BYTE DevId, BYTE AddrSize, BYTE* pAddr, BYTE RdSize, BYTE* pRdBuf) {

	int ack = 0;
	vector<BYTE> buf; BYTE slave = (DevId << 1) + 1;
	if (AddrSize > 0) {
		buf.push_back(DevId << 1);
		for (int x = 0; x < AddrSize; x++)
			buf.push_back(pAddr[x]);

		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf.data(), buf.size());
	}

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, RdSize);

	return ack;
}


int awI2CWrite(BYTE DevId, BYTE WrSize, BYTE* WrData) {

	int ack = 0;
	if (WrSize > 0) {
		vector<BYTE> buf;
		buf.push_back(DevId << 1);
		for (int x = 0; x < WrSize; x++)
			buf.push_back(WrData[x]);

		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf.data(), buf.size());
		//IIC_Delayus(0.01f);
	}
	return ack;
}


int awOutputLog(const char* str) {

	int ret = 0;
	fout << str << endl;
	return ret;

}


AFDRVCheck::AFDRVCheck(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::EEPROM) {

	ui->setupUi(this);
	connect(ui->Cphy, SIGNAL(clicked()), this, SLOT(on_pushButton_Cphy_clicked()));
	connect(ui->CH0, SIGNAL(clicked()), this, SLOT(on_pushButton_CH0_clicked()));
	connect(ui->CH1, SIGNAL(clicked()), this, SLOT(on_pushButton_CH1_clicked()));
	
	ui_Out = ui;

	MyThread *subThread = new MyThread;

	int id = qRegisterMetaType<QString>("");
//	connect(subThread, SIGNAL(changeText(QString)), this, SLOT(labelSetText(QString)), Qt::QueuedConnection);
//	connect(subThread, SIGNAL(changeText(QString)), this, SLOT(labelSetText(QString)));
//	connect(subThread, SIGNAL(changeNum(int)), this, SLOT(displayNum(int)));

	subThread->start();


	Value_init = DC_Init();
	Value_Cards = DC_GetMaxCards();
	Value_Version = DC_GetVersion(0, &DllVer, &DrvVer, &ChipVer);
	Value_Channels = DC_GetMaxChannels(0);
	ui->log->insertPlainText("D-Phy Hardware Version: \n");

	getHex(DllVer / 256);
	string temp = "DllVer: ";
	temp = temp +chk[0] + chk[1];
	getHex(DllVer % 256);
	temp =temp + chk[0] + chk[1];
	ui->log->insertPlainText(temp.c_str());

	getHex(DrvVer / 256);
	temp = ",  DrvVer: ";
	temp = temp +chk[0] + chk[1];
	getHex(DrvVer % 256);
	temp = temp + chk[0] + chk[1];
	ui->log->insertPlainText(temp.c_str());

	getHex(ChipVer / 256);
	temp = ",  ChipVer: ";
	temp = temp +chk[0] + chk[1];
	getHex(ChipVer % 256);
	temp = temp + chk[0] + chk[1] + '\n';
	ui->log->insertPlainText(temp.c_str());

	DC_GpioWriteOE(0, 0xFFF00);

	on_pushButton_GPIO_read_clicked();
	DC_I2cInit(0, 0, 1, 1);

	pExtFuncList->pFunc_I2C_Read = awI2CRead;
	pExtFuncList->pFunc_I2C_Write = awI2CWrite;
	pExtFuncList->pFunc_OutputLog = awOutputLog;
	AW86006.OIS_ExtFuncInit(pExtFuncList);
	load_Setting();
}

int pDeviceInfoCount = 0;
PDGS_DEVICE_INFO device_Info;
LPVOID pCbCtx = NULL;
DG_CALLBACK_FUNCTION pCbFunction = NULL;


void AFDRVCheck::on_pushButton_Cphy_clicked() {
	
	Value_init = DG_End();
	Sleep(500);
	Value_init = DG_Init();
	Sleep(500);
	Value_Cards = -1;
	Value_Cards = DG_GetDeviceList(&pDeviceInfoCount, &device_Info);

	int success = DG_OpenHandleByCardNum(0, 0, &pHdg, pCbCtx, pCbFunction);
	int success1 = DG_OpenHandleByCardNum(0, 1, &pHdg1, pCbCtx, pCbFunction);

	I2C.m_hCapture = pHdg;


	Value_Version = DG_GetVersion(pHdg, &DllVer, &DrvVer, &ChipVer, &BrdVer);
//	Value_Channels = DC_GetMaxChannels(0);
	ui->log->clear();
	ui->log->insertPlainText("C-Phy Hardware Version: \n");

	getHex(DllVer / 256);
	string temp = "DllVer: ";
	temp = temp + chk[0] + chk[1];
	getHex(DllVer % 256);
	temp = temp + chk[0] + chk[1];
	ui->log->insertPlainText(temp.c_str());

	getHex(DrvVer / 256);
	temp = ",  DrvVer: ";
	temp = temp + chk[0] + chk[1];
	getHex(DrvVer % 256);
	temp = temp + chk[0] + chk[1];
	ui->log->insertPlainText(temp.c_str());

	getHex(ChipVer / 256);
	temp = ",  ChipVer: ";
	temp = temp + chk[0] + chk[1];
	getHex(ChipVer % 256);
	temp = temp + chk[0] + chk[1];
	ui->log->insertPlainText(temp.c_str());

	getHex(BrdVer / 256);
	temp = ",  BrdVer: ";
	temp = temp + chk[0] + chk[1];
	getHex(BrdVer % 256);
	temp = temp + chk[0] + chk[1] + '\n';
	ui->log->insertPlainText(temp.c_str());
	int ret = 0;

	ret+=DG_SetI2csFreq(pHdg, 0, 400.0, NULL);

	on_pushButton_GPIO_read_clicked();
}

AFDRVCheck::~AFDRVCheck()
{
	delete ui;
}


void AFDRVCheck::on_pushButton_Read_MIPI_clicked()
{
	DWORD MIPI_Data = 0;
	if (ui->Dphy->isChecked()) {
		
		for (int i = 0; i < 1024; i++){
			DC_ReadReg(0, i, &MIPI_Data);
			fout << MIPI_Data<<endl;
		}
	}
	else if (ui->Cphy->isChecked()){

		
	}

}


void AFDRVCheck::on_pushButton_Write_MIPI_clicked()
{
	DWORD MIPI_Data = 0,ack=0;
	ifstream fin(".//MIPI_REG.txt");
	if (ui->Dphy->isChecked()) {
	
		for (int i = 0; i < 1024; i++) {
			fin >> MIPI_Data;
			ack=DC_WriteReg(0, i, MIPI_Data);
			fout << ack << endl;
		
		}
	}
	else if (ui->Cphy->isChecked()) {


	}

}


void AFDRVCheck::on_pushButton_GPIO_read_clicked()
{
	GPIO_Data = 0;
	if (ui->Dphy->isChecked())
		Value_GPIOread = DC_GpioReadIn(0, &GPIO_Data);

	else if (ui->Cphy->isChecked()){
		if (ui->CH0->isChecked())
			Value_GPIOread = DG_GpioRead(pHdg, &GPIO_Data);
		else if (ui->CH1->isChecked())
			Value_GPIOread = DG_GpioRead(pHdg1, &GPIO_Data);
	}
//	GPIO_Data %= 0x40000;
	
	ui->GPIO_Value->setText(QString::number(GPIO_Data, 10));
	
	GPIO_display();

}


void AFDRVCheck::on_pushButton_GPIO_write_clicked()
{

	GPIO_Data = ui->GPIO_Value->document()->toPlainText().toInt();

	//	GPIO_Data %= 0x40000;

	if (ui->Dphy->isChecked())
		Value_GPIOwrite = DC_GpioWriteOut(0, GPIO_Data);
	else if (ui->Cphy->isChecked()){
		if(ui->CH0->isChecked())
			Value_GPIOwrite = DG_GpioWrite(pHdg, 0xFFFFFFFF, GPIO_Data);
		else if (ui->CH1->isChecked())
			Value_GPIOwrite = DG_GpioWrite(pHdg1, 0xFFFFFFFF, GPIO_Data);
	}
	Sleep(50);

	on_pushButton_GPIO_read_clicked();
	GPIO_display();
	
}


void AFDRVCheck:: Err_display(int code) {

	QMessageBox msgBox;
	string temp = "Status_Value Error:" + to_string(code);
	msgBox.setText(tr(temp.c_str()));
	msgBox.exec();

}


void AFDRVCheck::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Enter) {
		//	on_pushButton_read_AF_clicked();
		on_pushButton_AF_SNA_Lin_clicked();
	}
	if (event->key() == Qt::Key_Enter - 1) {
		//	on_pushButton_read_AF_clicked();
		on_pushButton_AF_SNA_Lin_clicked();
	}
}


unsigned char AFDRVCheck::my_DC_I2cRead(unsigned char s, int hi, int lo, int len) {

	int ack = 0;
	ack = DC_I2cStart(0, 0);
	ack = DC_I2cWrite(0, 0, s);

	getHex(s);
	fout << chk[0] << chk[1] << "	:";
	fout << ack << "	;";

	if (hi < 255) {
		Value_I2cWrite = DC_I2cWrite(0, 0, hi);
		getHex(hi);
		fout << chk[0] << chk[1] << "	:";
		fout << ack << "	;";
	}
	ack = DC_I2cWrite(0, 0, lo);
	getHex(lo);
	fout << chk[0] << chk[1] << "	:";
	fout << ack << "	;";
	DC_I2cStop(0, 0);

	ack = DC_I2cStart(0, 0);
	ack = DC_I2cWrite(0, 0, s + 1);
	getHex(s + 1);
	fout << chk[0] << chk[1] << "	:";
	fout << ack << "	;";

	unsigned char tmp[4] = { 0 };
	if (len == 1){
		tmp[0] = DC_I2cRead(0, 0, 1);
		getHex(tmp[0]);
		fout << chk[0] << chk[1] << endl;
	}
	else {

		DC_SoftI2cRead(0, 0, len,  0xFF, tmp);
		for (int i = 0; i < len; i++){
			getHex(tmp[i]);
			fout << chk[0] << chk[1] << " ";
		}
		fout << endl;
	}
	

	DC_I2cStop(0, 0);
	Sleep(10);
	return tmp[0];
}


int AFDRVCheck::my_DC_I2cWrite(unsigned char slave, unsigned char addr_H, unsigned char addr_L, unsigned char data) {

	getHex(slave);
	fout << chk[0]<<chk[1] << "	:";
	int ack = 0;
	DC_I2cInit(0, 0, 1, 1);
	ack += DC_I2cStart(0, 0);
	ack += DC_I2cWrite(0, 0, slave);
	fout << ack << "	;";
	if (addr_H < 255) {
		ack = DC_I2cWrite(0, 0, addr_H);
		getHex(addr_H);
		fout << chk[0] << chk[1] << "	:";
		fout << ack << "	;";
	}
	ack += DC_I2cWrite(0, 0, addr_L);
	getHex(addr_L);
	fout << chk[0] << chk[1] << "	:";
	fout << ack << "	;";
	ack += DC_I2cWrite(0, 0, data);
	getHex(data);
	fout << chk[0] << chk[1] << "	:";
	DC_I2cStop(0, 0);
	fout << ack << endl;

	return ack;
}




void AFDRVCheck::on_pushButton_read_all_clicked()
{
	read_Setting();

	if (ui->Dphy->isChecked()) {

		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave);

		// 从 0x00地址开始读取
		Value_I2cWrite = DC_I2cWrite(0, 0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0);
		DC_I2cStop(0, 0);

		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave + 1);

		Value_I2cRead = DC_SoftI2cRead(0, 0, EEP_Size, 0xFF, DecData);

		DC_I2cStop(0, 0);
	}

	if (ui->Cphy->isChecked()){

		/*
		for (int i = 0; i < EEP_Size; i += PageSize) {

			BYTE buf[3] = { 0, };
			buf[0] = slave;
			buf[1] = 0;
			buf[2] = 1;

			ack = DG_I2cWrite(pHdg, 1, 0, buf, 3);
			buf[0] += 1;
			ack+= DG_I2cWrite(pHdg, 1, 0, buf, 1);

			ack += DG_I2cRead(pHdg, 1, DecData + i, PageSize);
		}
		*/
		if (ui->CH1->isChecked())
			I2C.m_hCapture = pHdg1;

		int saddr = slave;
		int index = 0x0;
		int ack = 0;
		const int PageSize = 0x10;
		int length = 0;

		for (int i = 0; i<EEP_Size; i += PageSize)
		{
			BYTE buf[3] = { 0, };
			buf[0] = saddr;
			buf[1] = HIBYTE(i);
			buf[2] = LOBYTE(i);
			ack = DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 3);
			buf[0] += 1;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData + i, PageSize);	 // 20180905
			IIC_Delayus(0.005f); // 20180905 1->5
		}
	}

	display_EEP();
	 
}


void AFDRVCheck::on_pushButton_write_all_clicked()
{
	EEP_Size = ui->eep_size->document()->toPlainText().toInt();
	src = ui->input->document()->toPlainText().toLocal8Bit();
	int now = 0, e = 0, len = src.length() - 1, TCSum = 0;

	while (now < len && e < EEP_Size) {
		if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
			((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
				|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	'))) {

			for (int i = 0; i < 16; i++) {
				D[e][0] = src[now++];
				D[e][1] = src[now++];
				DecData[e] = hex2Dec(e);
				e++;
				now++;
			}
		}
		else now++;
	}

	src = ui->slave->document()->toPlainText().toLocal8Bit();
	slave = getUchar();


	if (ui->CH1->isChecked())
		I2C.m_hCapture = pHdg1;

	eepLockOpen();

	if (ui->Dphy->isChecked()) {
		////////////////
		for (int i = 0; i < EEP_Size; i += 64) {

			if (ui->Dphy->isChecked()) {
				Value_I2cStart = DC_I2cStart(0, 0);
				Value_I2cWrite = DC_I2cWrite(0, 0, slave);
				Value_I2cWrite = DC_I2cWrite(0, 0, i / 256);
				Value_I2cWrite = DC_I2cWrite(0, 0, i % 256);
				Value_I2cWrite = DC_SoftI2cWrite(0, 0, 64, 0x00, 0x00, DecData + i);
				DC_I2cStop(0, 0);
			}

			if (ui->Dphy->isChecked()) {

				//DG_I2csWrite(HDG hDG, int iIndex, int iStart, int iLast, BYTE *buf, int length);
				Value_I2cWrite = DG_I2csWrite(pHdg, i, 0x00, 0x00, DecData + i, 64);
			}

			Sleep(10);
		}
		///////////////////
	}
	int ack = 0;
	if (ui->Cphy->isChecked()) {

		const int pageSize = 0x10;

		int k = 0;

		for (int i = 0; i < EEP_Size; i += pageSize){

			BYTE buf[19] = { 0, };
			buf[0] = slave;
			buf[1] = HIBYTE(i);
			buf[2] = LOBYTE(i);

			for (int i = 0; i < pageSize; i++)	{
				buf[i + 3] = DecData[k++];
			}
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, pageSize + 3);
			IIC_Delayus(0.005f); // IIC_Delayus(0.001f); -> sometimes no write
		}
	}

	eepLockClose();

	string str = "ack Cnt: "+to_string(ack/128) +"/" + to_string(EEP_Size ) + "\n";
	ui->log->insertPlainText(str.c_str());
	ui->log->insertPlainText("EEPROM save finished \n");


}


void AFDRVCheck::on_pushButton_read_clicked()
{
	read_Setting();
	if (ui->CH1->isChecked())
		I2C.m_hCapture = pHdg1;

	if (ui->Dphy->isChecked()){

		DC_I2cInit(0, 0, 1, 1);
		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave);

		if (ui->addH_use->isChecked())
			Value_I2cWrite = DC_I2cWrite(0, 0, addr_H);

		Value_I2cWrite = DC_I2cWrite(0, 0, addr_L);
		DC_I2cStop(0, 0);

		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave + 1);

		data_LSB[0] = 0;
		data_LSB[0] = DC_I2cRead(0, 0, 1);
		DC_I2cStop(0, 0);

	}
	
	// DG_SetI2cFreq(HDG hDG, double dFreqKhz, double *pSetFreq = NULL);                                            
	double pSetFreq = 0;

	if (ui->Cphy->isChecked()) {

		int saddr = slave;
		int index = 0x0;
		int ack = 0;
		const int PageSize = 0x10;
		int length = 0;

		BYTE buf[3] = { 0, };
		buf[0] = saddr;

		buf[1] = addr_H;
		buf[2] = addr_L;
		ack = DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 3);

		buf[0] += 1;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 1);

		ack += DG_I2cRead(I2C.m_hCapture, 1, data_LSB, 4);	 // 20180905
		IIC_Delayus(0.005f); // 20180905 1->5

	}

	getHex(data_LSB[0]);
	string s = chk;
	s[2] = ' ';
	s[3] = '\0';
	ui->readData->setText(QString::fromStdString(s.c_str()));

}


void AFDRVCheck::on_pushButton_write_clicked()
{
	src = ui->slave->document()->toPlainText().toLocal8Bit();
	slave = getUchar();
	src = ui->addH->document()->toPlainText().toLocal8Bit();
	addr_H = getUchar();
	src = ui->addL->document()->toPlainText().toLocal8Bit();
	addr_L = getUchar();

	src = ui->writeData->document()->toPlainText().toLocal8Bit();
	data_LSB[0] = getUchar();
	///////////////////////

	if (ui->CH1->isChecked())
		I2C.m_hCapture = pHdg1;

	if (ui->Dphy->isChecked()) {
		DC_I2cInit(0, 0, 1, 1);
		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave);

		if (ui->addH_use->isChecked())
			Value_I2cWrite = DC_I2cWrite(0, 0, addr_H);
		Value_I2cWrite = DC_I2cWrite(0, 0, addr_L);
		Value_I2cWrite = DC_I2cWrite(0, 0, data_LSB[0]);

		DC_I2cStop(0, 0);
	}

	if (ui->Cphy->isChecked()) {

		/*
		BYTE s[5] = { 0 };
		s[0] = slave;
		s[1] = addr_H;
		s[2] = addr_L;
		s[3] = data_LSB;
		s[4] = 0x00;

		BYTE d[5] = { 0 };
		d[0] = slave;
		d[1] = addr_H;
		d[2] = addr_L;

		d[0] = addr_H;
		d[1] = addr_L;
		d[2] = data_LSB;

		Value_I2cWrite = DG_I2cWrite(pHdg, 0xFF, 0x01, s, 4);

		Sleep(10);
		*/
		BYTE buf[19] = { 0, };
		buf[0] = slave;
		buf[1] = addr_H;
		buf[2] = addr_L;
		buf[3] = data_LSB[0];
		buf[4] = 0;
		buf[5] = 0;
		buf[6] = 2;
		
		int ack = DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 1 + 3);
		IIC_Delayus(0.005f); // IIC_Delayus(0.001f); -> sometimes no write

	}

}


void AFDRVCheck::on_pushButton_LC89812X_clicked()
{
		BYTE buf[19] = { 0, };
		buf[0] = 0x48;
		buf[1] = 0xF0;
		buf[2] = 0x15;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = 0;
		buf[6] = 2;

		int ack = DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 1 + 6);
		IIC_Delayus(0.005f); // IIC_Delayus(0.001f); -> sometimes no write

}


void AFDRVCheck::on_pushButton_SEM1215_Ver_clicked()
{
	
	my_DC_I2cRead(0x68, 0x10, 0x04,4);
	my_DC_I2cRead(0x68, 0x10, 0x08,4);

}


void AFDRVCheck::on_pushButton_Dphy_Init_clicked()
{
	
	my_DC_I2cWrite(0xCA, 0xFF, 0x01, 0xFF);
	my_DC_I2cWrite(0xCA, 0xFF, 0x00, 0xFF);
	my_DC_I2cWrite(0xCA, 0xFF, 0x16, 0x01);
	my_DC_I2cWrite(0xCA, 0xFF, 0x01, 0xFF);
	my_DC_I2cWrite(0xCA, 0xFF, 0x00, 0xFF);
	my_DC_I2cWrite(0xCA, 0xFF, 0x21, 0x01);
	my_DC_I2cWrite(0xCA, 0xFF, 0x23, 0x2B);
	my_DC_I2cWrite(0xCA, 0xFF, 0x20, 0x01);
	my_DC_I2cWrite(0xCA, 0xFF, 0x21, 0x00);
	my_DC_I2cWrite(0xCA, 0xFF, 0x10, 0x01);

	my_DC_I2cRead(0xCA, 0xFF, 0xFE,1);
	my_DC_I2cRead(0xCA, 0xFF, 0xFF,1);
	my_DC_I2cRead(0xCA, 0xFF, 0x10,1);
	Sleep(5);

	Sleep(5);
	my_DC_I2cWrite(0x6C, 0x01, 0x03, 0x01);

}


void AFDRVCheck::on_pushButton_GPIO_All_clicked()
{
	GPIO_Data = 0xFFFFFFFF;
	GPIO_display();
	Sleep(5);
	Value_GPIOwrite = DG_GpioWrite(pHdg, 0xFFFFFFFF, GPIO_Data);
	Value_GPIOwrite = DG_GpioWrite(pHdg1, 0xFFFFFFFF, GPIO_Data);
}


void AFDRVCheck::on_pushButton_read_AF_OnSemi_clicked() {

	GPIO_Data = 262143;
	Value_GPIOwrite = DC_GpioWriteOut(0, GPIO_Data);
	Sleep(50);
	on_pushButton_GPIO_read_clicked();

	memset(DecData, 0, sizeof(DecData));

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xE4);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA1);
	DC_I2cStop(0, 0);

	slave = 0xE4;

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	// 从 0x00地址开始读取
	//	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	DC_I2cStop(0, 0);

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave + 1);

	Value_I2cRead = DC_SoftI2cRead(0, 0, 128, 0xFF, DecData);

	DC_I2cStop(0, 0);

	ui->log->clear();

	for (int i = 0; i < 128; i++) {
		getHex(DecData[i]);
		string s = chk;
		s[2] = ' ';
		s[3] = '\0';
		ui->log->insertPlainText(QString::fromStdString(s.c_str()));

		if (i % 16 == 15)
			ui->log->insertPlainText("\n");
	}


	if ((DecData[127] == 0 && DecData[126] == 0) || (DecData[127] == 0xFF && DecData[126] == 0xFF)) {
		ui->input->clear();
		ui->input->setTextColor(QColor(255, 0, 0, 255));
		ui->input->setFontPointSize(18);
		ui->input->insertPlainText("AF_Drv Read Error! \n");

	}
	else {

		bool OK = true;

		if (DecData[0xF0] == 0)
			OK = false;

		if (OK) {
			ui->input->clear();
			ui->input->setTextColor(QColor(0, 0, 255, 255));
			ui->input->setFontPointSize(36);
			ui->input->insertPlainText("AF Drv Read OK! \n");

		}
		else {
			ui->input->clear();
			ui->input->setTextColor(QColor(255, 0, 0, 255));
			ui->input->setFontPointSize(36);
			ui->input->insertPlainText("AF Drv Read NG! \n");

		}

	}

	//	Value_GPIOwrite = DC_GpioWriteOut(0, 0xFF);

}


void AFDRVCheck::on_pushButton_AF_Aging_Stop_clicked() {

	Start = false;
	ui->input->insertPlainText("Aging test Stop\n");

}


void AFDRVCheck::on_pushButton_AF_Aging_clicked() {

	Start = true;
	m_Delay = ui->Delay->document()->toPlainText().toInt() / 1000.0;
	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();
	m_Aging_Times = ui->AF_Times->document()->toPlainText().toInt();

	connect(subThread, SIGNAL(changeText(QString)), this, SLOT(displayText(QString)));

	HANDLE myHandle = CreateThread(NULL, 0, myThread, (LPVOID)s.c_str(), 0, NULL);

}


void AFDRVCheck::on_pushButton_AF_Aging_OnSemi_clicked() {

	Start = true;
	GPIO_Data = 262143;
	Value_GPIOwrite = DC_GpioWriteOut(0, GPIO_Data);
	Sleep(50);
	on_pushButton_GPIO_read_clicked();

	slave = 0xE4;

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x80);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA0);
	DC_I2cStop(0, 0);

	Sleep(10);

	s = ui->AF_Times->document()->toPlainText().toLocal8Bit();
	connect(subThread, SIGNAL(changeText(QString)), this, SLOT(displayText(QString)));

	HANDLE myHandle = CreateThread(NULL, 0, myThread, (LPVOID)s.c_str(), 0, NULL);

}


void AFDRVCheck::on_pushButton_read_AF_SNA_clicked() {

	GPIO_Data = 262143;
	memset(AF_DecData, 0, sizeof(AF_DecData));
	slave = 0x18;

	if (ui->Dphy->isChecked()) {

		Value_GPIOwrite = DC_GpioWriteOut(0, GPIO_Data);
		Sleep(50);
		on_pushButton_GPIO_read_clicked();
		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
		DC_I2cStop(0, 0);

		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, slave + 1);

		Value_I2cRead = DC_SoftI2cRead(0, 0, 128, 0x3FFFF, AF_DecData);

		DC_I2cStop(0, 0);

		ui->log->clear();

		for (int i = 0; i < 128; i++) {
			getHex(AF_DecData[i]);
			string s = chk;
			s[2] = ' ';
			s[3] = '\0';
			ui->log->insertPlainText(QString::fromStdString(s.c_str()));

			if (i % 16 == 15)
				ui->log->insertPlainText("\n");
		}
	}


	if (ui->Cphy->isChecked()) {

		Value_GPIOwrite = DG_GpioWrite(0, 0xFFFFF, GPIO_Data);
		Sleep(50);
		//		on_pushButton_GPIO_read_clicked();
		//		Value_I2cStart = DC_I2cStart(0, 0);
		BYTE *s = &slave;
		Value_I2cWrite = DG_I2cWrite(0, 0, 0, s, 1);
		Value_I2cWrite = DG_I2cWrite(0, 0, 0, 0, 1);
		//		DC_I2cStop(0, 0);

		//Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DG_I2cWrite(0, 0, 0, s + 1, 1);
		Value_I2cRead = DG_I2csRead(0, 0, 0xFF, AF_DecData, 128);

		//		DC_I2cStop(0, 0);

		ui->log->clear();

		for (int i = 0; i < 128; i++) {
			getHex(AF_DecData[i]);
			string s = chk;
			s[2] = ' ';
			s[3] = '\0';
			ui->log->insertPlainText(QString::fromStdString(s.c_str()));

			if (i % 16 == 15)
				ui->log->insertPlainText("\n");
		}
	}

}


void AFDRVCheck::on_pushButton_AF_SNA_Lin_clicked() {

	on_pushButton_read_AF_SNA_clicked();

	//	int adcMax = (int)AF_DecData[0x57] * 16 + (AF_DecData[0x58] >> 4);
	//  int adcMin = (int)(AF_DecData[0x58] & 0xF) * 256 + AF_DecData[0x59];
	int linMax = (int)AF_DecData[0x5A] * 16 + (AF_DecData[0x5B] >> 4);
	int linMin = (int)(AF_DecData[0x5B] & 0xF) * 256 + AF_DecData[0x5C];

	if (linMax*linMin == 0) {

		ui->input->setTextColor(QColor(255, 0, 0, 255));
		ui->input->setFontPointSize(18);
		ui->input->insertPlainText("AF Drv Read Error! \n");
		return;
	}

	on_pushButton_read_all_clicked();

	eepLockOpen();

	unsigned char Lin[4] = { (BYTE)(linMin / 256),(BYTE)(linMin % 256),(BYTE)(linMax / 256),(BYTE)(linMax % 256) };

	for (int i = 0; i < 4; i++) {
		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0xC3 + i);
		Value_I2cWrite = DC_I2cWrite(0, 0, Lin[i]);
		DC_I2cStop(0, 0);
		DecData[0xC3 + i] = Lin[i];
		Sleep(10);
	}

	if (Value_I2cWrite != 0) {
		ui->input->clear();
		ui->input->setTextColor(QColor(255, 0, 0, 255));
		ui->input->setFontPointSize(18);
		ui->input->insertPlainText("EEPROM Write Error! \n");
		return;
	}

	int afStart = 0x00C0, afEnd = 0x00D6;

	int tmp = 0;
	for (int i = afStart + 1; i < afEnd; i++)
		tmp += DecData[i];

	tmp %= 255;
	tmp++;
	DecData[afEnd] = tmp;

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xD6);
	Value_I2cWrite = DC_I2cWrite(0, 0, DecData[afEnd]);
	DC_I2cStop(0, 0);
	Sleep(10);

	if (DecData[0x0009] > 0 && DecData[0x0009] != 9) {
		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x09);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x09);
		DC_I2cStop(0, 0);
		DecData[0x09] = 0x09;
		Sleep(10);

		int afStart = 0, infoEnd = 0x1F;

		int tmp = 0;
		for (int i = afStart + 1; i < infoEnd; i++)
			tmp += DecData[i];

		tmp %= 255;
		tmp++;
		DecData[infoEnd] = tmp;

		Value_I2cStart = DC_I2cStart(0, 0);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
		Value_I2cWrite = DC_I2cWrite(0, 0, 0x1F);
		Value_I2cWrite = DC_I2cWrite(0, 0, DecData[infoEnd]);
		DC_I2cStop(0, 0);
		Sleep(10);

	}

	int totalCheckSum = 0x0BD7;
	tmp = 0;
	for (int i = 0; i < totalCheckSum; i++)
		tmp += DecData[i];

	tmp %= 255;
	tmp++;
	DecData[totalCheckSum] = tmp;

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x0B);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xD7);
	Value_I2cWrite = DC_I2cWrite(0, 0, DecData[totalCheckSum]);
	DC_I2cStop(0, 0);
	Sleep(10);


	eepLockClose();
	//read and check
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x0B);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xD7);
	DC_I2cStop(0, 0);

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0xA2 + 1);

	data_LSB[0] = 0;
	data_LSB[0] = DC_I2cRead(0, 0, 1);
	DC_I2cStop(0, 0);

	if (data_LSB[0] != DecData[totalCheckSum]) {
		ui->input->clear();
		ui->input->setTextColor(QColor(255, 0, 0, 255));
		ui->input->setFontPointSize(18);
		ui->input->insertPlainText("EEPROM Write Error! \n");
		return;
	}

	ui->input->clear();
	ui->input->insertPlainText(" linMax = ");
	ui->input->insertPlainText(to_string(linMax).c_str());
	ui->input->insertPlainText("\n linMin = ");
	ui->input->insertPlainText(to_string(linMin).c_str());

}


void AFDRVCheck::on_pushButton_read_OIS_clicked() {

	//	GPIO_Data = 262143;
	//	Value_GPIOwrite = DC_GpioWriteOut(0, GPIO_Data);
	Sleep(50);
	on_pushButton_GPIO_read_clicked();

	memset(DecData, 0, sizeof(DecData));

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x48);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x39);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x01);
	DC_I2cStop(0, 0);

	slave = 0x48;

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	// 从 0x00地址开始读取
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	Value_I2cWrite = DC_I2cWrite(0, 0, 0x00);
	DC_I2cStop(0, 0);

	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave + 1);

	Value_I2cRead = DC_SoftI2cRead(0, 0, 128, 0xFF, DecData);

	DC_I2cStop(0, 0);

	ui->log->clear();

	for (int i = 0; i < 128; i++) {
		getHex(DecData[i]);
		string s = chk;
		s[2] = ' ';
		s[3] = '\0';
		ui->log->insertPlainText(QString::fromStdString(s.c_str()));

		if (i % 16 == 15)
			ui->log->insertPlainText("\n");
	}
}


void AFDRVCheck::on_pushButton_af_add_clicked() {

	src = ui->slave_af->document()->toPlainText().toLocal8Bit();
	slave = getUchar();
	src = ui->addr_af->document()->toPlainText().toLocal8Bit();
	unsigned char addr_af = getUchar();
	src = ui->afH->document()->toPlainText().toLocal8Bit();
	unsigned char afH = getUchar();
	src = ui->afL->document()->toPlainText().toLocal8Bit();
	unsigned char afL = getUchar();

	DC_I2cInit(0, 0, 1, 1);
	Value_I2cStart = DC_I2cStart(0, 0);
	Value_I2cWrite = DC_I2cWrite(0, 0, slave);
	Value_I2cWrite = DC_I2cWrite(0, 0, addr_af);
	Value_I2cWrite = DC_I2cWrite(0, 0, afH);
	Value_I2cWrite = DC_I2cWrite(0, 0, afL);

	DC_I2cStop(0, 0);

	Sleep(10);

}


void AFDRVCheck::on_pushButton_af_sub_clicked() {



}


void AFDRVCheck::on_pushButton_clear_clicked() {

	ui->input->clear();
	ui->log->clear();

}


void AFDRVCheck::on_pushButton_puya_clicked() {

	int ack = 0;
	if (ui->CH1->isChecked())
		I2C.m_hCapture = pHdg1;

	unsigned char SWP_On[4] = { 0xA2,0x00,0x00,0x0E };
	unsigned char SWP_Off[4] = { 0xA2,0x00,0x00,0 };
	unsigned char r_Slave[4] = { 0xA3,0,0,0};
	unsigned char Temp[256] = { 0 };

	for (unsigned char i = 0xA0; i < 0xDF; i+=2) {
		SWP_On[0] = i;
		r_Slave[0] = i + 1;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, SWP_On, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, r_Slave, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, Temp, 4);
		if (Temp[0] == 1) {
			int xxx = 1;
			SWP_On[1] = 0xA0;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, SWP_On, 3);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, r_Slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, Temp, 1);
			SWP_On[1] = 0x00;
		}
	}

}


void AFDRVCheck::on_pushButton_script_clicked() {

	ofstream script_log(".\\script_log.txt");
	name = "script.txt";
	ifstream in(name); 

	if (!in.is_open())
	{
		QString strDisplay = "File open Failed";  
		strDisplay += '\n';
		ui->log->insertPlainText(strDisplay);
	}

	int now = 0, e = 0;
	BYTE buf[7] = { 0 };
	int cnt = 0;
	if (ui->CH1->isChecked())
		I2C.m_hCapture = pHdg1;

	while (getline(in, src))
	{
		now = 0; e = 0; cnt++;
		int len = src.length() - 1;
		if (len > 0) {
			while (now < len) {
				D[e][0] = src[now++];
				D[e][1] = src[now++];
				DecData[e] = hex2Dec(e);
				e++;
				now++;
			}

		}
		int ack = 0; unsigned char Temp[256] = { 0 };
		if (len > 0){
			if (D[0][0] == 'R' || D[0][1] == 'R') {
				if (ui->Cphy->isChecked()) {
					ack += DG_I2cRead(I2C.m_hCapture, 1, Temp, DecData[1]);
				}
				else {
					ack += DC_I2cStart(0, 0);
					ack += DC_SoftI2cRead(0, 0, DecData[1], 0xFF, DecData);
					DC_I2cStop(0, 0);
				}
				if (ack == 0)
					for (int i = 0; i < DecData[1]; i++) {
						getHex(Temp[i]);
						script_log << chk[0] << chk[1] << "	";
					}
				script_log << endl;
			}
			else if (D[0][0] == 'D' && D[0][1] == 'D') {
				unsigned int d = DecData[1];
				if(e>2) d= d*256+ DecData[2];
				Delay(d);
			}
			else if (D[0][0] == 'G' && D[0][1] == 'P') {
				unsigned int sum = 0;
				for (int k = 1; k < e && k< 5; k++) {
					sum = sum * 256 + DecData[k];
				}
				if (ui->Dphy->isChecked())
					Value_GPIOwrite = DC_GpioWriteOut(0, sum);
				else if (ui->Cphy->isChecked()) {
					Value_GPIOwrite = DG_GpioWrite(pHdg, 0xFFFFFFFF, sum);
				}
				on_pushButton_GPIO_read_clicked();
			}
			else {
				DecData[e + 1] = 0;
				if (ui->Cphy->isChecked()) {
					if (src.length() < 4) {
						ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, DecData, e);
					}
					else {
						ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DecData, e);
					}
				}
				else {
					//for (int a = 0; a < e; a++){
					//	ack += DC_I2cStart(0, 0);
					//	ack += DC_I2cWrite(0, 0, DecData[a]);
					//	DC_I2cStop(0, 0);
					//}
					if (src.length() < 4) {
						DC_SoftI2cWrite(0, 0, e, 0, 0, DecData);
					}
					else {
						DC_SoftI2cWrite(0, 0, e, 0, 1, DecData);
					}
				}
			}
			if (ack > 0) {
				script_log << "sercipt Line" << to_string(cnt) << " error: " << ack << endl;
			}
			else {
				script_log << "sercipt Line" << to_string(cnt) << " OK " << endl;
			}
		}
	}
	ui->log->insertPlainText("Script run finished \n");
	script_log.close();

}

void AFDRVCheck::on_pushButton_DW1_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N=2;
	N = ui->AF_Times->document()->toPlainText().toInt();

	unsigned char DW_Data[5] = { slave,0x70,0x15,0,2}, Read_slave= slave+1;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);
	Sleep(10);
	DW_Data[2] = 0x20;
	DW_Data[3] = 0;
	DW_Data[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);
	DW_Data[2] = 0x21;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);
	Sleep(500);

	for (int x = 0; x < N; x++) {

		for (int a = 0; a < 200; a++) {
			ack = 0;
			float d = sin(3.1415926*a / 100);
			short m = d *920;
			if (m < 0)
				m += 65536;

			unsigned char DW_Data1[5] = { slave,0x70,0x20,(unsigned char)(m / 256),(unsigned char)(m % 256) };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data1, 5);
			unsigned char DW_Data2[5] = { slave,0x70,0x21,(unsigned char)(m / 256),(unsigned char)(m % 256) };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data2, 5);
			Sleep(1);

			unsigned char DW_Data3[3] = { slave,0x70,0x46};
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 3);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

			int hall = DecData[0] * 256 + DecData[1];
			if (hall > 10000)
				hall = hall - 65536;
			
			script_log << hall << "	";

			unsigned char DW_Data4[3] = { 0xE4,0x70,0x47 };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data4, 3);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

			hall = DecData[0] * 256 + DecData[1];
			if (hall > 10000)
				hall = hall - 65536;

			script_log << hall << endl;

		}
	}

	
	ui->log->insertPlainText("DW9781 run finished \n");
	script_log.close();

}

void AFDRVCheck::on_pushButton_DW2_clicked() {
	read_Setting();
	script_log.open(".\\test_log.txt");
	ofstream test_log(".\\test_log1.txt");
	int ack = 0, e = 0, N = 10, hall = 0, X_center = -1, Y_center = -1;
	N = ui->AF_Times->document()->toPlainText().toInt();

	unsigned char DW_Data[5] = { slave,0x70,0x15,0,1 }, Read_slave = slave + 1;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);
	Sleep(300);

	DW_Data[2] = 0x46;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

	hall = (DecData[0] * 256 + DecData[1]);
	if (hall > 10000)
		hall = hall - 65536;
	X_center = hall;
	test_log << X_center << "	";
	DW_Data[2] = 0x47;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

	hall = (DecData[0] * 256 + DecData[1]);
	if (hall > 10000)
		hall = hall - 65536;
	Y_center = hall;
	test_log << Y_center << endl;
	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();
	int hall_range = 2048 * OIS_range_ratio / 100;

	for (int x = 0; x < N; x++) {

		for (int a = 0; a < 200; a++) {
			ack = 0;
			float d = sin(3.1415926*a / 100);
			short m = d * hall_range - X_center;
			//			short m = d * hall_range ;
			test_log << m << "	";

			if (m < 0)
				m += 65536;

			unsigned char DW_Data1[5] = { slave,0x70,0x25,(unsigned char)(m / 256),(unsigned char)(m % 256) };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data1, 5);

			d = sin(3.1415926*a / 100.0);
			//		d = sin(3.1415926*(2 - (a / 100.0)));
			short m1 = d * hall_range - Y_center;
			//			short m1 = d * hall_range ;
			test_log << m1 << endl;

			if (m1 < 0)
				m1 += 65536;

			unsigned char DW_Data2[5] = { slave,0x70,0x26,(unsigned char)(m1 / 256),(unsigned char)(m1 % 256) };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data2, 5);
			Sleep(1);
			if (x == 0 && a == 0)
				Sleep(200);
			else
				Sleep(1);
			unsigned char DW_Data3[3] = { slave,0x70,0x46 };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 3);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

			hall = DecData[0] * 256 + DecData[1];
			if (hall > 10000)
				hall = hall - 65536;

			script_log << hall << "	";

			unsigned char DW_Data4[3] = { slave,0x70,0x47 };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data4, 3);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

			hall = DecData[0] * 256 + DecData[1];
			if (hall > 10000)
				hall = hall - 65536;

			script_log << hall << endl;

		}
	}

	ui->log->insertPlainText("DW9781 run finished \n");
	script_log.close();
	test_log.close();
}

void AFDRVCheck::on_pushButton_DW9828C_Read_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 2;

	unsigned char DW_Data[5] = { 0x1C,0x08,0x15,0,2 }, Read_slave = 0x1D;
	unsigned char DW_Data2[5] = { 0x9C,0x08,0x15,0,2 }, Read_slave2 = 0x9D;

		for (int a = 0; a < 1000; a++) {

			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 2);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

			int hall = DecData[0] * 256 + DecData[1];
			if (hall > 32768)
				hall = hall - 65536;

			script_log << hall << "	";

			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data2,2);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave2, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

			hall = DecData[0] * 256 + DecData[1];
			if (hall > 32768)
				hall = hall - 65536;

			script_log << hall << endl;
			IIC_Delay(2);
		}
	
	ui->log->insertPlainText("DW9828C read finished \n");
	script_log.close();

}


int AFDRVCheck::bu24721_Status_check() {

	int tmo = 0,ack=0;
	unsigned char DW_Data[5] = { 0x7C,0xF0,0x20,1,0 }, Read_slave = 0x7D;

	while (DecData[0] != 1) {
		IIC_Delay(20);
		DW_Data[2] = 0x24;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 1);
		tmo++;
		if (tmo > 500)return 1;
	}
	return 0;
}

void AFDRVCheck::on_pushButton_BU24721_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 5, mStatus=0;
	unsigned char DW_Data[5] = { 0x7C,0xF0,0x20,1,0 }, Read_slave = 0x7D;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	mStatus = bu24721_Status_check();

	int rng = ui->OIS_range->document()->toPlainText().toInt();
	int offsetX = ui->decenter_BU24721X->document()->toPlainText().toInt();
	if (offsetX < 0)offsetX = 65536 + offsetX;


	DW_Data[1] = 0xF1;
	DW_Data[2] = 0x78;
	DW_Data[3] = offsetX / 256;
	DW_Data[4] = offsetX % 256;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);

	int offsetY = ui->decenter_BU24721Y->document()->toPlainText().toInt();
	if (offsetY < 0)offsetY = 65536 + offsetY;
	DW_Data[1] = 0xF1;
	DW_Data[2] = 0x7A;
	DW_Data[3] = offsetY / 256;
	DW_Data[4] = offsetY % 256;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);

	DW_Data[1] = 0xF0;
	DW_Data[2] = 0x2A;
	DW_Data[3] = 4;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	DW_Data[2] = 0x23;
	DW_Data[3] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	DW_Data[2] = 0x21;
	DW_Data[3] = 3;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	IIC_Delay(20);

	DW_Data[2] = 0x20;
	DW_Data[3] = 2;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	DW_Data[1] = 0xF1;
	DW_Data[2] = 0x32;
	DW_Data[3] = 5494 / 256;
	DW_Data[4] = 5494 % 256;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);
	DW_Data[2] = 0x34;
	DW_Data[3] = (rng * 772 / 100) / 256;
	DW_Data[4] = (rng * 772 / 100) % 256;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);
	DW_Data[2] = 0x36;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);

	DW_Data[2] = 0x38;
	DW_Data[3] = 2;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	DW_Data[2] = 0x30;
	DW_Data[3] = 0x03;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	IIC_Delay(500);

	int hall_XY[10000][2] = { 0 }, k = 0;

	for (int a = 0; a < 2000; a++) {
		ack = 0;
		unsigned char DW_Data3[4] = { 0x7C,0xF0,0x60,0 };
		DW_Data3[2] = 0x24;
		DecData[0] = 0; int cnt = 0;
		while (DecData[0] == 0 && cnt < 30) {
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 3);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 1);
			IIC_Delayus(0.001);
			cnt++;
		}

		DW_Data3[2] = 0x60;
		DW_Data3[3] = 0;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 4);
		DW_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		hall_XY[k][0] = hall;

		unsigned char DW_Data4[4] = { 0x7C,0xF0,0x60,1 };
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data4, 4);
		DW_Data4[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data4, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		hall_XY[k++][1] = hall;
	}

	DW_Data[2] = 0x30;
	DW_Data[3] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	DW_Data[2] = 0x38;
	DW_Data[3] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	for (int i = 0; i < k; i++) {
		script_log << hall_XY[i][0] << "	" << hall_XY[i][1] << endl;
	}

	ui->log->insertPlainText("BU24721 Sine Wave run finished \n");
	script_log.close();
	//BYTE rData[2] = { 0, };
	////N2 int xch_adc, ych_adc;
	//short xch_adc, ych_adc;

	//if (ch == 0x00) {
	//	if (RegRead(BU24721_REG_ADDR_GYRO_DATA_OUTPUT5, rData, 2)) return ERR_OIS_IIC;
	//	xch_adc = MAKEWORD(rData[0], rData[1]);
	//	return xch_adc;
	//}
	//else if (ch == 0x01) {
	//	if (RegRead(BU24721_REG_ADDR_GYRO_DATA_OUTPUT6, rData, 2)) return ERR_OIS_IIC;
	//	ych_adc = MAKEWORD(rData[0], rData[1]);
	//	return ych_adc;
	//}
}


void AFDRVCheck::on_pushButton_BU24721_DC_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, axis = 0;
	unsigned char DW_Data[5] = { 0x7C,0xF0,0x20,1,0 }, Read_slave = 0x7D;
	if (ui->radioButton_Axis_Y->isChecked())axis = 1;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	IIC_Delayus(0.01f);
	DW_Data[3] = 4;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	IIC_Delayus(0.1f);
	DW_Data[2] = 0x8D;
	if(axis==0)	DW_Data[3] = 1;
	else DW_Data[3] = 3;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	DW_Data[2] = 0x70;
	DW_Data[3] = 0;
	DW_Data[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	DW_Data[2] = 0x72;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	IIC_Delayus(0.1f);

	int hall_XY[10000][2] = { 0 }, k = 0;
	
	for (short a = -1000; a < 1000; a+=16) {
		ack = 0;
		DW_Data[1] = 0xF0;
		if(axis==0)		DW_Data[2] = 0x70;
		else DW_Data[2] = 0x72;
		DW_Data[3] = a>>8;
		DW_Data[4] = a&0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5 );
		IIC_Delayus(0.01f);
		if(a==-1023)IIC_Delayus(0.5f);

		unsigned char DW_Data3[4] = { 0x7C,0xF0,0x60,0 };
		if (axis == 1)DW_Data3[3] = 1;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 4);
		DW_Data3[2] = 0x62;
		IIC_Delayus(0.01f);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		hall_XY[k++][0] = hall;
	}
	int DC_cnt = k;
	k--;
	for (short a = 1000; a > -1000; a -= 16) {
		ack = 0;
		DW_Data[1] = 0xF0;
		if (axis == 0)		DW_Data[2] = 0x70;
		else DW_Data[2] = 0x72;
		DW_Data[3] = a >> 8;
		DW_Data[4] = a & 0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 5);
		IIC_Delayus(0.01f);
		if (a == -1023)IIC_Delayus(0.5f);

		unsigned char DW_Data3[4] = { 0x7C,0xF0,0x60,0 };
		if (axis == 1)DW_Data3[3] = 1;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 4);
		DW_Data3[2] = 0x62;
		IIC_Delayus(0.01f);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		hall_XY[k--][1] = hall;
	}

	DW_Data[2] = 0x70;
	DW_Data[3] = 0;
	DW_Data[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);
	DW_Data[2] = 0x72;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data, 4);

	IIC_Delayus(0.1f);

	script_log << "DC_Up	DC_Down:" << endl;
	for (int i = 0; i < DC_cnt; i++) {
		script_log << hall_XY[i][0] << "	" << hall_XY[i][1] << endl;
	}

	ui->log->insertPlainText("BU24721 DC Test finished \n");
	script_log.close();

}


void AFDRVCheck::on_pushButton_BU24721_Drive_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 100000;
	unsigned char Iris_Data[5] = { 0x18,0xF0,0x20,1,0 }, AF_slave_Read = 0x19;
	unsigned char OIS_Data[5] = { 0x7C,0xF0,0x20,0x01,0 }, OIS_slave_Read = 0x7D;
	unsigned char OIS_Data1[5] = { 0x7C,0x8D,0xC0,0x03,0 };
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.1f);
	float d = 0;
	script_log << "X drive" << endl;
	unsigned char OIS_Data3[5] = { 0x7C,0x60,0x60,0,0 };
	int hall[4096][3];

	OIS_Data3[1] = 0xF1;
	OIS_Data3[2] = 0x7C;  //X:0x70   Y:0x72
	OIS_Data3[3] = 1;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);

	OIS_Data3[1] = 0xF0;
	OIS_Data3[2] = 0x20;  //X:0x70   Y:0x72
	OIS_Data3[3] = 7;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);

	OIS_Data3[1] = 0xF1;
	OIS_Data3[2] = 0x72;  //X:0x70   Y:0x72
	OIS_Data3[3] = 0;
	OIS_Data3[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
	IIC_Delayus(0.1);

	int start = 1020, end = -1024, step = -4;
	if (ui->radioButton_FWD->isChecked()) {
		start = -1020, end = 1024, step = 4;
	}

	for (int x = start; x != end; x += step) {
		ack = 0;
		OIS_Data3[1] = 0xF1;
		OIS_Data3[2] = 0x70;  //X:0xDE   Y:0xE0
		int pos = x;
		OIS_Data3[3] = pos >> 8;
		OIS_Data3[4] = pos & 0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
		IIC_Delayus(0.005);

		if (x == start)	IIC_Delayus(0.1);
		OIS_Data3[1] = 0xF0;
		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x00;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << x << "	"<< 0<<"	";
		script_log << hall << "	";

		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x01;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	"<<endl;

	}

	OIS_Data3[1] = 0xF1;
	OIS_Data3[2] = 0x70;  //X:0xDE   Y:0xE0
	OIS_Data3[3] = 0;
	OIS_Data3[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
	IIC_Delayus(0.1);

	////Y drive
	script_log << endl << "Y drive" << endl;
	e = 0;
	for (int x = start; x != end; x += step) {
		ack = 0;
		OIS_Data3[1] = 0xF1;
		OIS_Data3[2] = 0x72;
		int pos = x;
		OIS_Data3[3] = pos >> 8;
		OIS_Data3[4] = pos & 0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
		IIC_Delayus(0.005);

		if (x == start)	IIC_Delayus(0.1);
		OIS_Data3[1] = 0xF0;
		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x00;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;

		script_log << 0 << "	" << x << "	";
		script_log << hall << "	";

		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x01;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	" << endl;

	}

	ui->log->insertPlainText("BU24721 driving Test finished \n");
	script_log.close();

}


void AFDRVCheck::on_pushButton_BU24721_Read_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 12;
	unsigned char AF_Data[5] = { 0x18,0xF0,0x20,1,0 }, AF_slave_Read = 0x19;
	unsigned char OIS_Data[5] = { 0x7C,0xF0,0x20,0x04,0 }, OIS_slave_Read = 0x7D;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.01f);

	for (int x = 0; x < N; x++) {	
			ack = 0;
			unsigned char OIS_Data3[4] = { 0x7C,0xF0,0x60,0 };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
			IIC_Delayus(0.01f);
			OIS_Data3[2] = 0x62;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
			IIC_Delayus(0.01f);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
			IIC_Delayus(0.01f);
			int hall = DecData[0] * 256 + DecData[1];
			if (hall > 0x7FFF)
				hall = hall - 65536;
			script_log <<x<<"	"<< hall << "	" ;

			OIS_Data3[2] = 0x60;
			OIS_Data3[3] = 0x01;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
			IIC_Delayus(0.01f);
			OIS_Data3[2] = 0x62;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
			IIC_Delayus(0.01f);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

			hall = DecData[0] * 256 + DecData[1];
			if (hall > 0x7FFF)
				hall = hall - 65536;
			script_log << hall << endl;
			
		   if(ack>0)
			   script_log << "I2C error!" << endl;

		   IIC_Delayus(20.0f);
	}
	ui->log->insertPlainText("BU24721 Drift run finished \n");
	script_log.close();
}


void AFDRVCheck::on_pushButton_BU24532_Sine_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 3;
	unsigned char OIS_Data[5] = { 0x7C,0x60,0x20,0x01,0 }, OIS_slave_Read = 0x7D;
	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();
	float d = 0.001;
	unsigned char OIS_Data1[5] = { 0x7C,0x61,0xDC,0x03,0 };
	unsigned char OIS_Data3[5] = { 0x7C,0x60,0x60,0,0 };

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.01f);

	for (int x = 0; x < N; x++) {
		for (int a = 0; a < 256; a++) {
			ack = 0;
			float d = sin(3.1415926*a / 128);
			int pos = d * 1023* OIS_range_ratio/100.0;

			OIS_Data3[1] = 0x61;
			OIS_Data3[2] = 0xDE;  //X:0xDE   Y:0xE0
			OIS_Data3[3] = pos >> 8;
			OIS_Data3[4] = pos & 0xFF;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);

			float d1 = cos(3.1415926*a / 128);
			pos = d1 * 1023 * OIS_range_ratio / 100.0;
			OIS_Data3[1] = 0x61;
			OIS_Data3[2] = 0xE0;  //X:0xDE   Y:0xE0
			OIS_Data3[3] = pos >> 8;
			OIS_Data3[4] = pos & 0xFF;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);

			IIC_Delayus(0.005);
			BU24532_hall_read();
		}
	}
	ui->log->insertPlainText("BU24532 Sine read \n");
	script_log.close();
}


void AFDRVCheck::on_pushButton_BU24532_Read_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 100000;
	unsigned char Iris_Data[5] = { 0x18,0xF0,0x20,1,0 }, AF_slave_Read = 0x19;
	unsigned char OIS_Data[5] = { 0x7C,0xF0,0x20,0x04,0 }, OIS_slave_Read = 0x7D;

	float d = 0.001;
	unsigned char OIS_Data3[4] = { 0x7C,0x60,0x60,0 };
	for (int x = 0; x < N; x++) {
		ack = 0;

		OIS_Data3[1] = 0x60;
		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x00;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	";

		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x01;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	";

		OIS_Data3[1] = 0x61;
		OIS_Data3[2] = 0x9B;
		OIS_Data3[3] = 0x02;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x9C;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		script_log << DecData[0] * 256 + DecData[1] << endl;

		//if (ack > 0) {
		//	script_log << "I2C error!" << endl;
		//	ui->log->insertPlainText("I2C error! \n");
		//	return;
		//}

	}
	ui->log->insertPlainText("BU24532 Hall read \n");
	script_log.close();
}


void AFDRVCheck::on_pushButton_BU24532_Drive_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 100000;
	unsigned char Iris_Data[5] = { 0x7C,0xF0,0x20,1,0 }, AF_slave_Read = 0x19;
	unsigned char OIS_Data[5] = { 0x7C,0x60,0x20,0x01,0 }, OIS_slave_Read = 0x7D;
	unsigned char OIS_Data1[5] = { 0x7C,0x61,0xDC,0x03,0 };
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.01f);
	float d = 0;
	script_log << "X drive" << endl;
	unsigned char OIS_Data3[5] = { 0x7C,0x60,0x60,0,0 };
	int hall[4096][3];


	OIS_Data3[1] = 0x61;
	OIS_Data3[2] = 0xE0;  //X:0xDE   Y:0xE0
	OIS_Data3[3] = 0;
	OIS_Data3[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
	IIC_Delayus(0.1);

	int start = 1020, end = -1024, step = -4;
	if (ui->radioButton_FWD->isChecked()) {
		start = -1020, end = 1024, step = 4;
	}


	for (int x = start; x != end; x+= step) {
		ack = 0;
		OIS_Data3[1] = 0x61;
		OIS_Data3[2] = 0xDE;  //X:0xDE   Y:0xE0
		int pos = x;
		OIS_Data3[3] = pos >>8;
		OIS_Data3[4] = pos & 0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
		IIC_Delayus(0.005);

		if (x == start)	IIC_Delayus(0.05);
		OIS_Data3[1] = 0x60;
		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x00;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	";

		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x01;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	";

		OIS_Data3[1] = 0x61;
		OIS_Data3[2] = 0x9B;
		OIS_Data3[3] = 0x02;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x9C;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		script_log << DecData[0] * 256 + DecData[1] << endl;

		//if (ack > 0) {
		//	script_log << "I2C error!" << endl;
		//	ui->log->insertPlainText("I2C error! \n");
		//	return;
		//}

	}

	OIS_Data3[1] = 0x61;
	OIS_Data3[2] = 0xDE;  //X:0xDE   Y:0xE0
	OIS_Data3[3] = 0;
	OIS_Data3[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
	IIC_Delayus(0.1);

	////Y drive
	script_log << endl << "Y drive" << endl;
	e = 0;
	for (int x = start; x != end; x += step) {
		ack = 0;
		OIS_Data3[1] = 0x61;
		OIS_Data3[2] = 0xE0;
		int pos = x;
		OIS_Data3[3] = pos >> 8;
		OIS_Data3[4] = pos & 0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
		IIC_Delayus(0.005);

		if (x == start)	IIC_Delayus(0.05);
		OIS_Data3[1] = 0x60;
		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x00;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		int hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	";

		OIS_Data3[2] = 0x60;
		OIS_Data3[3] = 0x01;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x62;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

		hall = DecData[0] * 256 + DecData[1];
		if (hall > 0x7FFF)
			hall = hall - 65536;
		script_log << hall << "	";

		OIS_Data3[1] = 0x61;
		OIS_Data3[2] = 0x9B;
		OIS_Data3[3] = 0x02;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		IIC_Delayus(d);
		OIS_Data3[2] = 0x9C;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
		IIC_Delayus(d);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		script_log << DecData[0] * 256 + DecData[1] << endl;

		//if (ack > 0) {
		//	script_log << "I2C error!" << endl;
		//	ui->log->insertPlainText("I2C error! \n");
		//	return;
		//}

	}
	
	ui->log->insertPlainText("BU24532 driving Test finished \n");
	script_log.close();
}


void AFDRVCheck::on_pushButton_BU24532_Life_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0;
	unsigned char Read_Data[5] = { 0 }, AF_slave_Read = 0x19;
	unsigned char OIS_Data[5] = { 0x7C,0x60,0x20,0x01,0 }, OIS_slave_Read = 0x7D;
	unsigned char OIS_Data1[5] = { 0x7C,0x61,0xDC,0x03,0 };
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.01f);
	float dd = ui->Delay->document()->toPlainText().toInt()/1000.0;
	unsigned char OIS_Data3[5] = { 0x7C,0x60,0x60,0,0 };
	int start = 1020, end = -1024;
	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();
	int N = ui->AF_Times->document()->toPlainText().toInt();
	start *= OIS_range_ratio / 100.0;
	end *= OIS_range_ratio / 100.0;
	for (int x = 0; x < N; x ++) {
		ack = 0;
		int pos = start;
		if(x%2==1)pos = end;
		OIS_Data3[1] = 0x61;
		OIS_Data3[2] = 0xDE;  //X:0xDE   Y:0xE0
		OIS_Data3[3] = (pos >> 8) & 0xFF;
		OIS_Data3[4] = pos & 0xFF;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		OIS_Data3[2] = 0xE0;  //X:0xDE   Y:0xE0
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);
		IIC_Delayus(dd);
		int cnt = 0;
		//do {
		//	IIC_Delayus(5); cnt++;
		//	my_DG_I2C_Read2(0x7C, 0x6024,1, Read_Data);	
		//	if (Read_Data[0] == 1) {
		//		IIC_Delayus(2);
		//		break;
		//	}
		//} while (cnt<10);

		OIS_Data3[2] = 0x9B; 
		OIS_Data3[3] = 3;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		my_DG_I2C_Read2(0x7C, 0x619C, 2, Read_Data);
		script_log << x<<"	"<<Read_Data[0] * 256 + Read_Data[1] << "	";
		OIS_Data3[3] = 5;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
		my_DG_I2C_Read2(0x7C, 0x619C, 2, Read_Data);
		script_log << Read_Data[0] * 256 + Read_Data[1] << endl;
	}

	ui->log->insertPlainText("BU24532 OIS Life Test finished \n");
	script_log.close();
}


int AFDRVCheck::BU24532_hall_read() {
	unsigned char OIS_Data3[5] = { 0x7C,0x60,0x60,0,0 }, OIS_slave_Read = 0x7D;;
	int ack = 0;	float d = 0;
	OIS_Data3[1] = 0x61;
	OIS_Data3[2] = 0x9B;
	OIS_Data3[3] = 0x03;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
	IIC_Delayus(d);
	OIS_Data3[2] = 0x9C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	IIC_Delayus(d);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	int hall = DecData[0] * 256 + DecData[1];
	if (hall > 0x7FFF)
		hall = hall - 65536;
	script_log << hall << "	";

	OIS_Data3[2] = 0x9B;
	OIS_Data3[3] = 0x04;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
	IIC_Delayus(d);
	OIS_Data3[2] = 0x9C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	IIC_Delayus(d);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

	hall = DecData[0] * 256 + DecData[1];
	if (hall > 0x7FFF)
		hall = hall - 65536;
	//script_log << hall << "	";

	//OIS_Data3[1] = 0x61;
	//OIS_Data3[2] = 0xDE;
	//ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	//IIC_Delayus(d);
	//ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	//ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	//hall = DecData[0] * 256 + DecData[1];
	//if (hall > 0x7FFF)
	//	hall = hall - 65536;
	//script_log << hall << "	";

	//OIS_Data3[1] = 0x61;
	//OIS_Data3[2] = 0xE0;
	//ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	//IIC_Delayus(d);
	//ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	//ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	//hall = DecData[0] * 256 + DecData[1];
	//if (hall > 0x7FFF)
	//	hall = hall - 65536;
	script_log << hall << "	" << endl;
	return 0;
}


int AFDRVCheck::BU24532_OIS_move(int x, int y) {

	unsigned char OIS_Data3[5] = { 0x7C,0x61,0xDE,0,0 };
	unsigned char OIS_Data1[5] = { 0x7C,0x61,0xDC,0x03,0 };
	int ack = 0;	float d = 0;
	OIS_Data3[3] = x >> 8;
	OIS_Data3[4] = x & 0xFF;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
	OIS_Data3[2] = 0xE0;
	OIS_Data3[3] = y >> 8;
	OIS_Data3[4] = y & 0xFF;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data1, 4);

	return 0;
}


void AFDRVCheck::on_pushButton_BU24532_Test_clicked() {

	script_log.open(".\\test_log.txt");
	int ack = 0;
	unsigned char OIS_Data[5] = { 0x7C,0x60,0x20,0x01,0 }, OIS_slave_Read = 0x7D;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.02f);

	BU24532_hall_read();

	BU24532_OIS_move(-200, 0);
	IIC_Delayus(0.05f);
	BU24532_hall_read();
	BU24532_OIS_move(200, 0);
	IIC_Delayus(0.05f);
	BU24532_hall_read();

	BU24532_OIS_move(0, -200);
	IIC_Delayus(0.05f);
	BU24532_hall_read();

	BU24532_OIS_move(0, 200);
	IIC_Delayus(0.05f);
	BU24532_hall_read();

	script_log.close();
	
	ui->log->insertPlainText("BU24532 Test finished \n");
	
}


void AFDRVCheck::on_pushButton_BU24532_Iris_on_clicked() {

	int ack = 0;
	unsigned char OIS_Data[5] = { 0x7C,0x60,0xD6,0x04,0x80 }, OIS_slave_Read = 0x7D;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	OIS_Data[1] = 0x61;
	OIS_Data[2] = 0xEE;
	OIS_Data[3] = 0xFD;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 5);
	IIC_Delayus(0.02);
	OIS_Data[3] = 0;
	OIS_Data[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 5);
	IIC_Delayus(0.5f);

	OIS_Data[2] = 0x9B;
	OIS_Data[3] = 0x02;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	OIS_Data[2] = 0x9C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	script_log << DecData[0] * 256 + DecData[1] << endl;
	string str = "Iris Hall=	" + to_string(DecData[0] * 256 + DecData[1]) + "\n";

	ui->log->insertPlainText("BU24532 Iris Move to Large \n");
	ui->log->insertPlainText(str.c_str());

}


void AFDRVCheck::on_pushButton_BU24532_Iris_off_clicked() {

	int ack = 0;
	unsigned char OIS_Data[5] = { 0x7C,0x60,0xD6,0x04,0x80 }, OIS_slave_Read = 0x7D;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	OIS_Data[1] = 0x61;
	OIS_Data[2] = 0xEE;
	OIS_Data[3] = 0x02;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 5);
	IIC_Delayus(0.02);
	OIS_Data[3] = 0;
	OIS_Data[4] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 5);
	IIC_Delayus(0.5f); 

	OIS_Data[2] = 0x9B;
	OIS_Data[3] = 0x02;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	OIS_Data[2] = 0x9C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	script_log << DecData[0] * 256 + DecData[1] << endl;
	string str = "Iris Hall=	" + to_string(DecData[0] * 256 + DecData[1]) + "\n";

	ui->log->insertPlainText("BU24532 Iris Move to Small \n");
	ui->log->insertPlainText(str.c_str());
}


int AFDRVCheck::BU24631_hall_read() {
	unsigned char OIS_Data3[5] = { 0x78,0x60,0x60,0,0 }, OIS_slave_Read = 0x79;;
	int ack = 0;	float d = 0;
	OIS_Data3[1] = 0x60;
	OIS_Data3[2] = 0x60;
	OIS_Data3[3] = 0x00;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
	IIC_Delayus(d);
	OIS_Data3[2] = 0x62;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	IIC_Delayus(d);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	int hall = DecData[0] * 256 + DecData[1];
	if (hall > 0x7FFF)
		hall = hall - 65536;
	script_log << hall << "	";

	OIS_Data3[2] = 0x60;
	OIS_Data3[3] = 0x01;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
	IIC_Delayus(d);
	OIS_Data3[2] = 0x62;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	IIC_Delayus(d);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);

	hall = DecData[0] * 256 + DecData[1];
	if (hall > 0x7FFF)
		hall = hall - 65536;
	script_log << hall << "	";

	OIS_Data3[1] = 0x61;
	OIS_Data3[2] = 0xDE;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	IIC_Delayus(d);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] * 256 + DecData[1];
	if (hall > 0x7FFF)
		hall = hall - 65536;
	script_log << hall << "	";

	OIS_Data3[1] = 0x61;
	OIS_Data3[2] = 0xE0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 3);
	IIC_Delayus(d);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] * 256 + DecData[1];
	if (hall > 0x7FFF)
		hall = hall - 65536;
	script_log << hall << "	" << endl;
	return 0;
}

int AFDRVCheck::Rohm_Statu_check() {

	unsigned char OIS_Data[5] = { 0x78,0x60,0x24,0,0 }, OIS_slave_Read = 0x79;;
	int ack = 0;
	int k = 0;
	while (k < 1000) {

		ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
		DecData[0] = 0;
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 1);
		if (DecData[0])
			break;
		k++;
		IIC_Delayus(0.001);
	}
	return DecData[0];
}

void AFDRVCheck::on_pushButton_BU24631_Sine_clicked() {

	int offsetX = ui->decenter_BU24721X->document()->toPlainText().toInt();
	int offsetY = ui->decenter_BU24721Y->document()->toPlainText().toInt();

	script_log.open(".\\test_log.txt");
	int ack = 0, e = 0, N = 3;
	unsigned char OIS_Data[5] = { 0x78,0x60,0x20,0x01,0 }, OIS_slave_Read = 0x79;
	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();
	float d = 0.001;
	unsigned char OIS_Data3[4] = { 0x78,0x61,0x7D,1 };
	unsigned char OIS_Data1[5] = { 0x78,0x61,0xDC,0x03,0 };

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.1);
	Rohm_Statu_check();
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 4);
	IIC_Delayus(0.01);
	Rohm_Statu_check();

	OIS_Data[3] = 7;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 4);
	IIC_Delayus(0.01);
	Rohm_Statu_check();

	for (int x = 0; x < N; x++) {
		for (int a = 0; a < 256; a++) {
			ack = 0;
			float d = sin(3.1415926*a / 128);
			short pos = d * 1023 * OIS_range_ratio / 100.0+ offsetX;

			OIS_Data3[1] = 0x60;
			OIS_Data3[2] = 0xB0;  //X:0xB0   Y:0xB2
			OIS_Data3[3] = pos >> 8;
			OIS_Data3[4] = pos & 0xFF;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);

			float d1 = cos(3.1415926*a / 128);
			pos = d1 * 1023 * OIS_range_ratio / 100.0+ offsetY;
			OIS_Data3[1] = 0x60;
			OIS_Data3[2] = 0xB2;  ///X:0xB0   Y:0xB2
			OIS_Data3[3] = pos >> 8;
			OIS_Data3[4] = pos & 0xFF;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data3, 5);

			if(x==0&&a==0)	IIC_Delayus(0.5);

			IIC_Delayus(0.005);
			int k = 0;
			if (Rohm_Statu_check());

			BU24631_hall_read();
		}
	}
	ui->log->insertPlainText("BU24631 Sine test \n");
	script_log.close();
}

void AFDRVCheck::on_pushButton_7323_clicked() {

	ofstream script_log(".\\hall_log.txt");
	ofstream test_log(".\\target_log.txt");
	int ack = 0, e = 0, N = 5, hall = 0, X_center = 0x8000, Y_center = 0x8000;

	unsigned char AKM_Data[3] = { 0x1C,0,0x80 }, Read_slave = 0x1D;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, AKM_Data,3);
	AKM_Data[1] = 0x01;
	AKM_Data[2] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, AKM_Data, 3);
	AKM_Data[0] = 0x9C;
	AKM_Data[1] = 0x00;
	AKM_Data[2] = 0x80;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, AKM_Data, 3);
	AKM_Data[1] = 0x01;
	AKM_Data[2] = 0;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, AKM_Data, 3);
	AKM_Data[1] = 0x02;
	Sleep(30);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, AKM_Data, 3);
	AKM_Data[0] = 0x1C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, AKM_Data, 3);

	Sleep(500);
	OIS_range_ratio = 80;
	int hall_range = 0x8000 * OIS_range_ratio / 100.0;

	int hall_data[25600][2] = { 0 }, target_data[25600][2] = { 0 }, n = 0;

	for (int x = 0; x < N; x++) {
		for (int a = 0; a < 256; a++) {
			ack = 0;
			float d = sin(3.1415926*a / 128);
			int m = d * hall_range + X_center;
//			test_log << m << "	"; 
			target_data[n][0] = m;

			unsigned char DW_Data1[3] = { 0x1C,0x00,(unsigned char)(m / 128) };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data1, 3);
			DW_Data1[1] = 1;
			DW_Data1[2] = m % 256;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data1, 3);

			d = sin(3.1415926*a / 128);
			int m1 = d * hall_range + Y_center;
//			test_log << m1 << endl;
			target_data[n][1] = m1;

			unsigned char DW_Data2[3] = { 0x9C,0x00,(unsigned char)(m1 / 128) };
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data2, 3);
			DW_Data2[1] = 1;
			DW_Data2[2] = m1 % 256;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data2, 3);
			Sleep(1);

			Read_slave = 0x1D; 
			unsigned short X_hall = 0, Y_hall = 0;
			unsigned char DW_Data3[2] = { 0x1C,0x84};
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3,2);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 1);
			X_hall += DecData[0] * 256;
			DW_Data3[1] = 0x85;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 2);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 1);
			X_hall += DecData[0];
			hall_data[n][0] = X_hall;

	//		if (X_hall > 32767)
	//			X_hall = X_hall - 65536;

	//		script_log << X_hall << "	";

			Read_slave = 0x9D;
			DW_Data3[0] = 0x9C;
			DW_Data3[1] = 0x84;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 2);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 1);
			Y_hall += DecData[0] * 256;
			DW_Data3[1] = 0x85;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, DW_Data3, 2);
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &Read_slave, 1);
			ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 1);
			Y_hall += DecData[0];
			hall_data[n][1] = Y_hall;
	//		if (Y_hall > 32767)
	//			Y_hall = Y_hall - 65536;

	//		script_log << Y_hall << endl;
			n++;
		}
	}

	for (int x = 0; x < n; x++) {
		test_log << target_data[x][0] << "	" << target_data[x][1] << endl;
		script_log << hall_data[x][0] << "	"<< hall_data[x][1]<<endl;
	}

	ui->log->insertPlainText("AK7323 run finished \n");
	script_log.close();
	test_log.close();
}


int  AFDRVCheck::INA219_Init() {

	int ack = 0; unsigned char Temp[256] = { 0 }, R = 0x83;
	Temp[0] = 0x82;
	Temp[1] = 0x00;
	Temp[2] = 0x39;
	Temp[3] = 0x9F;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, Temp, 4);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, Temp, 4);
	Temp[1] = 0x05;
	Temp[2] = 0x50;
	Temp[3] = 0x00;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, Temp, 4);

	Temp[1] = 0x04;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, Temp, 2);

	return ack;
}


int  AFDRVCheck::read_Current() {

	int ack = 0; unsigned char Temp[256] = { 0 }, R = 0x83;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &R, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, Temp, 2);

	if (ack == 0) {
		int c = Temp[0] * 256 + Temp[1];
		if (c > 0x8000)
			return c - 0x10000;
		else return c;
	}
	else return -100000;

}


void AFDRVCheck::on_pushButton_SEM1215_Current_clicked() {

	ofstream Current_out(".\\Current_log.txt");

	if (ui->CH1->isChecked())
		I2C.m_hCapture = pHdg1;

	INA219_Init();

	int c = 0,ack=0; 
	unsigned char Temp[5] = { 0x68,0x2,0x04,0,0 };

	int sum = 0, sum2 = 0;
	for (int i = 0; i < 100; i++) {
		sum+= read_Current();
	}	

	for (int i = 0; i < 100; i++) {
		c = read_Current();
		sum2 += c;
		Current_out << c << endl;
		Temp[3] = (i * 50) % 256;
		Temp[4] = ((i * 50) % 1024) / 256;
		if (i % 10 == 0) {		
			int k = 0;
			if (i % 20 == 0)k = 1;
			if (i % 30 == 0)k = 2;
			Temp[3] = (500*k) % 256;
			Temp[4] = (500*k) / 256;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, Temp, 5);
		}
		Sleep(3);
		fout << i << "	" << ack << endl;
	}
	float gap = (sum2 - sum) / 100.0;
	string s = "AF Current gap=	" + to_string(gap) + "\n";
	ui->log->insertPlainText(s.c_str());   

}


void AFDRVCheck::on_pushButton_SEM1217_Read_clicked() {

	ofstream script_log("test_log.txt");
	int ack = 0, hall = 0; string s;
	unsigned char OIS_Data[5] = { 0xC2,0x04,0x28,0,0 }, OIS_slave_Read = 0xC3;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] + DecData[1] * 256;
	s = "X_Hall_Range:	" + to_string(hall) + "\n";
	ui->log->insertPlainText(s.c_str());

	OIS_Data[2] = 0x2A;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] + DecData[1] * 256;
	s = "Y_Hall_Range:	" + to_string(hall) + "\n";
	ui->log->insertPlainText(s.c_str());

	OIS_Data[1] = 0xA1;
	OIS_Data[2] = 0x22;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] + DecData[1] * 256;
	s = "EPA X Hall Min:	" + to_string(hall) + "\n";
	ui->log->insertPlainText(s.c_str());

	OIS_Data[1] = 0xA1;
	OIS_Data[2] = 0x24;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] + DecData[1] * 256;
	s = "EPA X Hall Max:	" + to_string(hall) + "\n";
	ui->log->insertPlainText(s.c_str());

	OIS_Data[1] = 0xA1;
	OIS_Data[2] = 0x42;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] + DecData[1] * 256;
	s = "EPA Y Hall Min:	" + to_string(hall) + "\n";
	ui->log->insertPlainText(s.c_str());

	OIS_Data[1] = 0xA1;
	OIS_Data[2] = 0x44;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, OIS_Data, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &OIS_slave_Read, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
	hall = DecData[0] + DecData[1] * 256;
	s = "EPA Y Hall Max:	" + to_string(hall) + "\n";
	ui->log->insertPlainText(s.c_str());

	s = "SEM1217_Read done\n";
	ui->log->insertPlainText(s.c_str());

}


void AFDRVCheck::on_pushButton_CH1_clicked() {

	I2C.m_hCapture = pHdg1;
	ui->log->insertPlainText("CH1 was selected\n");
}


void AFDRVCheck::on_pushButton_CH0_clicked() {

	I2C.m_hCapture = pHdg;
	ui->log->insertPlainText("CH0 was selected\n");
}


void AFDRVCheck::on_pushButton_Load_clicked() {

	read_Setting();

	src = ui->input->document()->toPlainText().toLocal8Bit();
	int now = 0, e = 0, len = src.length() - 1;

	while (now < len && e < EEP_Size) {
		if ((now == 0 || src[now - 1] == ' ' || src[now - 1] == '	' || src[now - 1] == '\n') &&
			((src[now + 2] == ' '&&src[now + 5] == ' '&&src[now + 8] == ' ')
				|| (src[now + 2] == '	'&&src[now + 5] == '	'&&src[now + 8] == '	'))) {

			for (int i = 0; i < 16; i++) {
				D[e][0] = src[now++];
				D[e][1] = src[now++];
				DecData[e] = hex2Dec(e);
				e++;
				now++;
			}
		}
		else now++;
	}

	display_EEP();

}


void AFDRVCheck::on_pushButton_LC89812X_read_clicked() {

	read_Setting();
	int saddr = slave;
	int index = 0x0;
	int ack = 0;
	int length = 0;

	BYTE buf[7] = { 0x76,0xE0,0,0,0,0,0 };
	BYTE buf1[7] = { 0x49,0,0,0,0,0,0 };
//	ack = DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 7);

	BYTE page[7] = { 0x48,0x50,0x02,0,0,0,0x80 };
	BYTE read_start[7] = { 0x48,0x50,0,0,0,0,0 };

	buf[0] = 0x76;
	buf[1] = 0xC0;
	buf[2] = 0x00;
	buf[3] = 0x00;
	buf[4] = 0xE0;
	buf[5] = 0x80;
	buf[6] = 0x00;
//	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 7);
	buf[1] = 0x80;
	buf[2] = 0x00;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 3);

	buf[0] = 0x77;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 1);

	unsigned char Temp[128];
	int size = 4;
	ack += DG_I2cRead(I2C.m_hCapture, 1, Temp, size);	 // 20180905

	for (int i = 0; i < size; i ++) {
		getHex(Temp[i]);
		fout << chk[0]<< chk[1] << endl;
	}
	fout << endl;

}


void AFDRVCheck::on_pushButton_LC89812X_write_clicked() {

	read_Setting();
	int saddr = slave;
	int index = 0x0;
	int ack = 0;
	int length = 0;

	BYTE buf_C[7] = { 0x48,0xC0,0,0,0xE0,0x70,0 };
	BYTE buf_D[7] = { 0x48,0xD0,0,0,0,0,0 };
	BYTE buf_R[7] = { 0x49,0xD0,0,0,0,0,0 };
	//	ack = DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 7);

	BYTE page[7] = { 0x48,0x50,0x02,0,0,0,0x80 };
	BYTE read_start[7] = { 0x48,0x50,0,0,0,0,0 };

	buf_C[6] = 0x08;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);

	buf_D[6] = 0x02;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;
	//////////////////////////
	buf_C[6] = 0x0C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);

	buf_D[4] = 0x02;
	buf_D[6] = 0x0D;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[6] = 0x1C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);

	buf_D[4] = 0x00;
	buf_D[6] = 0x00;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[6] = 0x10;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);

	buf_D[4] = 0x00;
	buf_D[6] = 0x01;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (int i = 0; i < 3; i++) {
		buf_C[6] = 0x00;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_R, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 4);
		log_out(4);
		Delay(20);
		fout << ack << endl;
	}
	//////////////////////////
	buf_C[6] = 0x10;
	buf_C[6] = 0x1C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[4] = 0x00;
	buf_D[6] = 0x02;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x75;
	buf_C[6] = 0x54;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0xAA;
	buf_D[4] = 0xAA;
	buf_D[5] = 0xAA;
	buf_D[6] = 0xAA;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;
	//////////////////////////
	buf_C[5] = 0x7A;
	buf_C[6] = 0xA8;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x55;
	buf_D[4] = 0x55;
	buf_D[5] = 0x55;
	buf_D[6] = 0x55;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x74;
	buf_C[6] = 0xCC;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0x00;
	buf_D[6] = 0x01;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x76;
	buf_C[6] = 0x64;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0x00;
	buf_D[6] = 0x10;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x7C;
	buf_C[6] = 0xCC;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0xAC;
	buf_D[6] = 0xD5;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x70;
	buf_C[6] = 0x0C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0x00;
	buf_D[6] = 0x00;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x70;
	buf_C[6] = 0x1C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x70;
	buf_C[6] = 0x10;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0x00;
	buf_D[6] = 0x04;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x70;
	buf_C[6] = 0x1C;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0x00;
	buf_D[6] = 0x02;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;

	//////////////////////////
	buf_C[5] = 0x70;
	buf_C[6] = 0x14;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0x00;
	buf_D[6] = 0x10;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 7);
	Delay(10);
	fout << ack << endl;
	//////////////////////////
	buf_C[4] = 0xD0;
	buf_C[5] = 0x00;
	buf_C[6] = 0x60;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
	buf_D[3] = 0x00;
	buf_D[4] = 0x00;
	buf_D[5] = 0x00;
	buf_D[6] = 0x01;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf_D, 7);
	Delay(30);
	fout << ack << endl;
	//////////////////////////////
	for (int i = 0; i < 3; i++){

		buf_C[4] = 0xE0;
		buf_C[5] = 0x50;
		buf_C[6] = 0xD4;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_C, 7);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_D, 3);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_R, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 4);
		log_out(4);
		Delay(30);
		fout << ack << endl;
	}
}


void AFDRVCheck::on_pushButton_MC_AF_clicked() {

	read_Setting();
	int saddr = slave;
	int index = 0x0;
	int ack = 0;
	int length = 0;

	BYTE buf_W[4] = { 0x18,0x00,0,0};
	BYTE buf_D[2] = { 0};
	BYTE buf_R[7] = { 0x19,0x84,0,0,0,0,0 };
	//	ack = DG_I2cWrite(I2C.m_hCapture, 1, 0, buf, 7);

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_W, 4);
	Delay(1000);
//	buf_W[1] = 0x01;
	buf_W[2] = 0xFF;
	buf_W[3] = 0xFF;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_W, 4);
	ack = 0;

	for (int i = 0; i < 10000; i++) {
		buf_W[1] = 0x84;
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_W, 2);
		ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_R, 1);
		ack += DG_I2cRead(I2C.m_hCapture, 1, DecData, 2);
		fout << DecData[0] * 256 + DecData[1] << endl;

		int d = 3;
		if (i % 50 == 0) {

			Delay(d);
			buf_W[1] = 0;
			buf_W[2] = 0x7F;
			buf_W[3] = 0xF0;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_W, 4);
			Delay(d);
			buf_W[1] = 0;
			buf_W[2] = 0;
			buf_W[3] = 0;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_W, 4);
			Delay(d);
			buf_W[1] = 0;
			buf_W[2] = 0x7F;
			buf_W[3] = 0xF0;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_W, 4);
			Delay(d);
			buf_W[1] = 0;
			buf_W[2] = 0xFF;
			buf_W[3] = 0xF0;
			ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, buf_W, 4);

		}
	}
}


void AFDRVCheck::on_pushButton_AW86006_init_clicked() {

	pExtFuncList->pFunc_I2C_Read = awI2CRead;
	pExtFuncList->pFunc_I2C_Write = awI2CWrite;
	pExtFuncList->pFunc_OutputLog = awOutputLog;
	AW86006.OIS_ExtFuncInit(pExtFuncList);
	int nReturnCode = 0;
	BYTE Ver = 0;
	AW86006.GetDllVersion(&Ver);
	//string str = "DLL Version:	" + to_string(Ver) + "\n";
	//ui->log->insertPlainText(str.c_str());
	////AW86006.GetVersionId(&Ver);
	////str = "FW Version:	" + to_string(Ver) + "\n";
	////ui->log->insertPlainText(str.c_str());

	AwSet7bitI2CSlaveAddr(0x48>>1);
	nReturnCode+=AwResetChip();
	nReturnCode+=AwSetChipMode(2);
	nReturnCode+= AwServeOn();

	ui->log->insertPlainText("AW86006 init & Set Slave 0x48\n");

}


void AFDRVCheck::on_pushButton_AW86006_FW_clicked() {

	int ret = 0, u32Len=0;
	QString filename = QFileDialog::getOpenFileName(this, tr("Open FW"), "", tr("BIN File(*.bin *.rom *.prog *.ntbrst)"));
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string name = code->fromUnicode(filename).data();

	ifstream fin(name, std::ios::binary);

	struct _stat info;
	_stat(name.c_str(), &info);
	u32Len = info.st_size;

	BYTE *bypBinBuf = new BYTE[u32Len];
	fin.read((char*)bypBinBuf, sizeof(char) * u32Len);
	unsigned int mSize = u32Len / 4;
	if (u32Len % 4 > 0)mSize++;

	ret = AwBootControl(20, 2);
	string str = "AwBootControl: " + to_string(ret)+"\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwMoveBinDownload(bypBinBuf, mSize);
	str = "AwMoveBinDownload: " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwResetChip();
	str = "AwResetChip: " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());
	ret = AwSetChipMode(2);
	str = "AwSetChipMode(2): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwFlashErase();
	str = "AwFlashErase(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwResetChip();
	str = "AwResetChip(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwSetChipMode(2);
	str = "AwSetChipMode(2): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwFlashUpdate();
	str = "AwFlashUpdate(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());


	ui->log->insertPlainText("AW86006 FW Download + Flash Erase done\n");
}


void AFDRVCheck::on_pushButton_AW86006_HallCal_clicked() {

	int ret = 0;
	BYTE bias[2];
	string str;

	ret = AwSetChipMode(2);
	str = "AwSetChipMode(2): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	bias[0] = 90;
	bias[1] = 160;

	ret = AwHallCal(bias[0], bias[1]);
	str = "AwHallCal(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());
	IIC_Delayus(1.0f);
	ret = AwLensOffsetCal(600,800);
	str = "AwLensOffsetCal(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	UINT16 uFre = 10;
	BYTE uAmp = 10;
	float fCaldBX = 10.48;
	float fCaldBY = 10.71;
	float fRangeDown = 0.7f;
	float fRangeUp = 2.0f;

	ret = AwLoopGainCal2(uFre, uAmp, fCaldBX, fCaldBY, fRangeDown, fRangeUp);
	str = "AwLoopGainCal2(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	AW_read_Data();
}

int mAW_hall_check( float x, float y) {
	int ret = 0;
	float hall[4] = { 0 };
	AwReadLineOut(hall);
	script_log << hall[0] << "	" << hall[1] << endl;

	if (abs(x - hall[0]) > 50)
		ret++;

	if (abs(y - hall[1]) > 50)
		ret++;

	return ret;
}

void AFDRVCheck::on_pushButton_AW86006_Square_clicked() {

	script_log.open("test_log.txt");

	int ret = 0;	
	string str;
	AwSet7bitI2CSlaveAddr(0x48>>1);
	ret = AwOisOff();
	str = "AwOisOff(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwUnLockDebugProtect();
	str = "AwUnLockDebugProtect(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());
	ret = AwWriteLoopStatus(1);
	str = "AwWriteLoopStatus(1): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());
	ret = AwOisOn();
	str = "AwOisOn(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwWriteTargetX(-1000);
	ret+= AwWriteTargetY(-1000);
	str = "AwWriteTarget: -1000,-1000; " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());
	IIC_Delayus(0.3f);
	int ok = 0; float d = 0.01;
	int range = 1000, step = 50, spec = 50;
	int x = -1 * range, y = -1 * range,f=1;

	for (int k = 0; k < 4; k++) {
		int a = k % 2, b = (k + 1) % 2;
		if (k == 2)f= -1;
		do{
			ret = AwWriteTargetX(x);
			ret = AwWriteTargetY(y);
			IIC_Delayus(d);
			ok+=mAW_hall_check(x, y);
			x += step*b*f, y += step*a*f;
		} 
		while (abs(x) < range || abs(y) < range);
	}

	str = "Draw Square test; " + to_string(ok) + "\n";
	ui->log->insertPlainText(str.c_str());
	script_log.close();
}

void AFDRVCheck::on_pushButton_AW86006_Read_clicked() {

	int ret = 0, ack=0;
	string str; INT16 hall[2];
	ret = AwServeOn();
	//ret = AwFlashUpdate();
	AW_read_Data();
	ret = AwReadAdc(hall);

	fout << "Hall X:	" << hall[0] << endl;
	fout << "Hall Y:	" << hall[1] << endl;

	BYTE pRdBuf[4] = { 0 };
	BYTE slave = 0x49;
	BYTE buf[4] = { 0x48, 0xF8, 0x9C, 0 };

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, 2);

	fout << "Lens offset X:	" << pRdBuf[0] + pRdBuf[1] * 256 << endl;

	buf[2] = 0x9E;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, 2);

	fout << "Lens offset Y:	" << pRdBuf[0] + pRdBuf[1] * 256 << endl;

	buf[1] = 0xF7;
	buf[2] = 0x04;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, 2);

	fout << "PGA offset X:	" << pRdBuf[0] + pRdBuf[1] * 256 << endl;

	buf[2] = 0x06;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, 2);

	fout << "PGA offset Y:	" << pRdBuf[0] + pRdBuf[1] * 256 << endl;

	str = "Lens offset read done\n";
	ui->log->insertPlainText(str.c_str());

}

void AFDRVCheck::AW_read_Data() {
	tCalData caldata;
	int ret;
	ret = AwGetCalData(&caldata);
	string str = "AwGetCalData(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	str = "byPgaGain_X: " + to_string(caldata.byPgaGain[0]) + "\n";
	fout << str;
	str = "byPgaGain_Y: " + to_string(caldata.byPgaGain[1]) + "\n";
	fout << str;
	str = "byHallBias_X: " + to_string(caldata.byHallBias[0]) + "\n";
	fout << str;
	str = "byHallBias_Y: " + to_string(caldata.byHallBias[1]) + "\n";
	fout << str;
	str = "u16HallOffset_X: " + to_string(caldata.u16HallOffset[0]) + "\n";
	fout << str;
	str = "u16HallOffset_Y: " + to_string(caldata.u16HallOffset[1]) + "\n";
	fout << str;
	str = "n16GyroOffset_X: " + to_string(caldata.n16GyroOffset[0]) + "\n";
	fout << str;
	str = "n16GyroOffset_Y: " + to_string(caldata.n16GyroOffset[1]) + "\n";
	fout << str;
	str = "fHallMaxX: " + to_string(caldata.fHallMaxX) + "\n";
	fout << str;
	str = "fHallMinX: " + to_string(caldata.fHallMinX) + "\n";
	fout << str;
	str = "fHallMaxY: " + to_string(caldata.fHallMaxY) + "\n";
	fout << str;
	str = "fHallMinY: " + to_string(caldata.fHallMinY) + "\n";
	fout << str;
	str = "fLoopGainX: " + to_string(caldata.fLoopGainX) + "\n";
	fout << str;
	str = "fLoopGainY: " + to_string(caldata.fLoopGainY) + "\n";
	fout << str;
	str = "fGyroGainX: " + to_string(caldata.fGyroGainX) + "\n";
	fout << str;
	str = "fGyroGainY: " + to_string(caldata.fGyroGainY) + "\n";
	fout << str;

	str = "fCrosstalkParaXA0: " + to_string(caldata.fCrosstalkParaXA0) + "\n";
	fout << str;
	str = "fCrosstalkParaYA0: " + to_string(caldata.fCrosstalkParaYA0) + "\n";
	fout << str;
	str = "fCrosstalkParaXB0: " + to_string(caldata.fCrosstalkParaXB0) + "\n";
	fout << str;
	str = "fCrosstalkParaYB0: " + to_string(caldata.fCrosstalkParaYB0) + "\n";
	fout << str;
	str = "fCrosstalkParaXC0: " + to_string(caldata.fCrosstalkParaXC0) + "\n";
	fout << str;
	str = "fCrosstalkParaYC0: " + to_string(caldata.fCrosstalkParaYC0) + "\n";
	fout << str;

	fout << "n16HallCodeX:	";
	for (int i = 0; i < 9; i++)
		fout << caldata.n16HallCodeX[i] << "	";
	fout << endl;

	fout << "n16HallCodeY:	";
	for (int i = 0; i < 9; i++)
		fout << caldata.n16HallCodeY[i] << "	";
	fout << endl;

	fout << "fLinearityXK:	";
	for (int i = 0; i < 9; i++) 
		fout << caldata.fLinearityXK[i] << "	";
	fout << endl;

	fout << "fLinearityXB:	";
	for (int i = 0; i < 9; i++)
		fout << caldata.fLinearityXB[i] << "	";
	fout << endl;

	fout << "fLinearityYK:	";
	for (int i = 0; i < 9; i++)
		fout << caldata.fLinearityYK[i] << "	";
	fout << endl;

	fout << "fLinearityYB:	";
	for (int i = 0; i < 9; i++)
		fout << caldata.fLinearityYB[i] << "	";
	fout << endl;

	str = "fGyroSin: " + to_string(caldata.fGyroSin) + "\n";
	fout << str;
	str = "fGyroCos: " + to_string(caldata.fGyroCos) + "\n";
	fout << str;
	str = "fPixelStepX: " + to_string(caldata.fPixelStepX) + "\n";
	fout << str;
	str = "fPixelStepY: " + to_string(caldata.fPixelStepY) + "\n";
	fout << str;
	str = "n16LensOffsetX: " + to_string(caldata.n16LensOffsetX) + "\n";
	fout << str;
	str = "n16LensOffsetY: " + to_string(caldata.n16LensOffsetY) + "\n";
	fout << str;

	str = "fCrosstalkK0X: " + to_string(caldata.fCrosstalkK0X) + "\n";
	fout << str;
	str = "fCrosstalkK1X: " + to_string(caldata.fCrosstalkK1X) + "\n";
	fout << str;
	str = "fCrosstalkK0Y: " + to_string(caldata.fCrosstalkK0Y) + "\n";
	fout << str;
	str = "fCrosstalkK1Y: " + to_string(caldata.fCrosstalkK1Y) + "\n";
	fout << str;

	str = "fAfDriftParaXA0: " + to_string(caldata.fAfDriftParaXA0) + "\n";
	fout << str;
	str = "fAfDriftParaYA0: " + to_string(caldata.fAfDriftParaYA0) + "\n";
	fout << str;
	str = "fAfDriftParaXB0: " + to_string(caldata.fAfDriftParaXB0) + "\n";
	fout << str;
	str = "fAfDriftParaYB0: " + to_string(caldata.fAfDriftParaYB0) + "\n";
	fout << str;
	str = "fAfDriftParaXC0: " + to_string(caldata.fAfDriftParaXC0) + "\n";
	fout << str;
	str = "fAfDriftParaYC0: " + to_string(caldata.fAfDriftParaYC0) + "\n";
	fout << str;

}

void AFDRVCheck::on_pushButton_AW86006_Slave_Change_clicked() {

	int ret = 0, ack = 0; string str;

	AwSet7bitI2CSlaveAddr(0xBA >> 1);

	ret = AwI2cAddrModify(0xD2>>1);
	str = "AwI2cAddrModify(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ret = AwResetChipAfterI2CModify();
	str = "AwResetChipAfterI2CModify(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	AwSet7bitI2CSlaveAddr(0xD2>>1);

	BYTE Ver = 0;
	ret = AwGetChipId(&Ver);
	str = "AwGetChipId(): " + to_string(Ver) + "\n";
	ui->log->insertPlainText(str.c_str());

	str = "Slave Change done\n";
	ui->log->insertPlainText(str.c_str());

}

void AFDRVCheck::on_pushButton_AW86006_Sine_clicked() {
	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();
	script_log.open("test_log.txt");
	int ret = 0;string str;
	AwSet7bitI2CSlaveAddr(0x48 >> 1);
	//ret = AwServeOff();
	//ret = AwOisOff();
	//str = "AwOisOff(): " + to_string(ret) + "\n";
	//ui->log->insertPlainText(str.c_str());
	//ret = AwUnLockDebugProtect();
	//str = "AwUnLockDebugProtect(): " + to_string(ret) + "\n";
	//ui->log->insertPlainText(str.c_str());
	//ret = AwWriteLoopStatus(1);
	//str = "AwWriteLoopStatus(1): " + to_string(ret) + "\n";
	//ui->log->insertPlainText(str.c_str());
	//ret = AwOisOn();
	//str = "AwOisOn(): " + to_string(ret) + "\n";
	//ui->log->insertPlainText(str.c_str());
	unsigned char nCircleValue = 5;
	nCircleValue += int(1200 * OIS_range_ratio / 10000.0) << 4;

	ret = AwDrawCircleOn(3, nCircleValue);
	str = "AwDrawCircleOn(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());
	float hall[1001][4];
	IIC_Delayus(0.1f);
	for (int i = 0; i < 1000; i++) {
		IIC_Delayus(0.002f);
		AwReadLineOut(hall[i]);
	}

	for (int i = 0; i < 1000; i++) {
		script_log << hall[i][0] << "	" << hall[i][1] << endl;	
	}

	ret = AwDrawCircleOff(3, nCircleValue);
	str = "AwDrawCircleOff(): " + to_string(ret) + "\n";
	ui->log->insertPlainText(str.c_str());

	ui->log->insertPlainText("OIS Sine Test done!");
	script_log.close();
}

void AFDRVCheck::on_pushButton_AW86006_Vsync_clicked() {
	OIS_range_ratio = ui->OIS_range->document()->toPlainText().toInt();
	script_log.open("test_log.txt");
	int ret = 0; string str; int ack = 0;
	AwSet7bitI2CSlaveAddr(0x48 >> 1);

	BYTE pRdBuf[4] = { 0 };
	BYTE slave = 0x49;
	BYTE buf[4] = { 0x48, 0x00, 0x03, 1 };

	AwOisOff();
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 4);
	AwOisOn();
	IIC_Delayus(0.01f);
	buf[2] = 0x00;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, 1);

	buf[2] = 0x03;

	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, 1);
	int x = pRdBuf[0];
	str = "EIS_ON=	" + to_string(x) + "\n";
	ui->log->insertPlainText(str.c_str());

	buf[2] = 0x16;
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 3);
	ack += DG_I2cWrite(I2C.m_hCapture, 1, 0, &slave, 1);
	ack += DG_I2cRead(I2C.m_hCapture, 1, pRdBuf, 1);

	if (ack != 0) {
		ui->log->insertPlainText("OIS I2C NG!");
	}
	x = pRdBuf[0];
	str = "OIS_EN=	"+ to_string(x) +"\n";
	ui->log->insertPlainText(str.c_str());
	ui->log->insertPlainText("OIS Vsync Test done!\n");
	script_log.close();
}

void AFDRVCheck::on_pushButton_Slave_Scan_clicked() {

	script_log.open("test_log.txt");
	for (int x = 1; x < 256; x++) {

		BYTE buf[4] = { x, 0, 0 ,0};
		int ack = DG_I2cWrite(I2C.m_hCapture, 1, 1, buf, 4);
		script_log << "slave: " << x << "ack  " << ack << endl;
		if (ack == 0) {
			string str = "slave has ack：" + to_string(x)+'\n';
			ui->log->insertPlainText(str.c_str());
		}
	}

	script_log.close();
}

void AFDRVCheck::on_pushButton_AW86006_Gain_Write_clicked() {

	UINT32 xGain = 0xC1138096;
	UINT32 yGain = 0xC1073C01;

	int ret = AwWriteGyroGain0Y(*(float *)&yGain);
	ret += AwWriteGyroGain0X(*(float *)&xGain);
	ret += AwFlashUpdate();

	string str = "AW write Gyro Gain：" + to_string(ret) + '\n';
	ui->log->insertPlainText(str.c_str());
}
