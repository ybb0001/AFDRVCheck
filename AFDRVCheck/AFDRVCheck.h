#ifndef AFDRVCheck_H
#define AFDRVCheck_H

#include <QWidget>
#include <algorithm>
#include <QKeyEvent>
#include <Windows.h>
#include <QThread>
#include <QString>
#include "mythread.h" 
#include "CAW86006_OIS_API.h" 

namespace Ui {
class EEPROM;
}

class AFDRVCheck : public QWidget
{
    Q_OBJECT

public:
    explicit AFDRVCheck(QWidget *parent = 0);
    ~AFDRVCheck();

public slots:
    void on_pushButton_read_clicked();
	void on_pushButton_write_clicked();
	void on_pushButton_read_all_clicked();
	void on_pushButton_write_all_clicked();
	void Err_display(int code);

	void on_pushButton_GPIO_read_clicked();
	void on_pushButton_GPIO_write_clicked();
	void on_pushButton_af_add_clicked();
	void on_pushButton_af_sub_clicked();
	void on_pushButton_read_AF_OnSemi_clicked();
	void on_pushButton_read_AF_SNA_clicked();
	void on_pushButton_AF_SNA_Lin_clicked();
	void on_pushButton_AF_Aging_clicked();
	void on_pushButton_AF_Aging_OnSemi_clicked();

	void on_pushButton_Cphy_clicked();
	void on_pushButton_CH0_clicked();
	void on_pushButton_CH1_clicked();

	void on_pushButton_GPIO_All_clicked();
	void on_pushButton_Dphy_Init_clicked();
	void on_pushButton_Read_MIPI_clicked();
	void on_pushButton_Write_MIPI_clicked();
	void on_pushButton_SEM1215_Ver_clicked();

	void on_pushButton_LC89812X_clicked();
	void on_pushButton_LC89812X_read_clicked();
	void on_pushButton_LC89812X_write_clicked();
	void on_pushButton_Load_clicked();
	void on_pushButton_MC_AF_clicked();
	void on_pushButton_script_clicked();
	void on_pushButton_puya_clicked();
	void on_pushButton_SEM1215_Current_clicked();
	void on_pushButton_BU24721_Read_clicked();
	void on_pushButton_BU24532_Read_clicked();
	void on_pushButton_BU24532_Drive_clicked(); 
	void on_pushButton_BU24532_Sine_clicked();

	void on_pushButton_BU24532_Test_clicked();
	void on_pushButton_BU24532_Iris_on_clicked();
	void on_pushButton_BU24532_Iris_off_clicked();

	void on_pushButton_DW1_clicked();
	void on_pushButton_BU24721_clicked();
	void on_pushButton_DW2_clicked();
	void on_pushButton_7323_clicked();
	void on_pushButton_AW86006_init_clicked();
	void on_pushButton_AW86006_FW_clicked();
	void on_pushButton_AW86006_HallCal_clicked();
	void on_pushButton_AW86006_Square_clicked();
	void on_pushButton_AW86006_Cross_Talk_clicked();

	
	void on_pushButton_AF_Aging_Stop_clicked();
	void display_EEP();
	void read_Setting();
	int BU24532_hall_read();
	int BU24532_OIS_move(int x, int y);

	void on_pushButton_read_OIS_clicked();
	void keyPressEvent(QKeyEvent *event);

	void GPIO_display();
	int  my_DC_I2cWrite(unsigned char s, unsigned char hi, unsigned char lo, unsigned char data);
	unsigned char my_DC_I2cRead(unsigned char s, int hi, int lo, int len);
	int read_Current();
	int INA219_Init();

	void displayText(QString s);
	void displayNum(int n);

	void eepLockOpen();
	void eepLockClose();


	void on_pushButton_clear_clicked();
	void on_checkBox_clicked();
	void on_checkBox_1_clicked();
	void on_checkBox_2_clicked();
	void on_checkBox_3_clicked();
	void on_checkBox_4_clicked();
	void on_checkBox_5_clicked();
	void on_checkBox_6_clicked();
	void on_checkBox_7_clicked();
	void on_checkBox_8_clicked();
	void on_checkBox_9_clicked();
	void on_checkBox_10_clicked();
	void on_checkBox_11_clicked();
	void on_checkBox_12_clicked();
	void on_checkBox_13_clicked();
	void on_checkBox_14_clicked();
	void on_checkBox_15_clicked();
	void on_checkBox_16_clicked();
	void on_checkBox_17_clicked();
	void on_checkBox_18_clicked();
	void on_checkBox_19_clicked();
	void on_checkBox_20_clicked();
	void on_checkBox_21_clicked();
	void on_checkBox_22_clicked();
	void on_checkBox_23_clicked();
	void on_checkBox_24_clicked();
	void on_checkBox_25_clicked();
	void on_checkBox_26_clicked();
	void on_checkBox_27_clicked();
	void on_checkBox_28_clicked();
	void on_checkBox_29_clicked();
	void on_checkBox_30_clicked();
	void on_checkBox_31_clicked();

public:
    Ui::EEPROM *ui;
    QImage img;
    QImage imgScaled;
	std::string name;
	CAW86006_OIS_API AW86006;
	DLL_ExtFuncList *pExtFuncList;

};


#endif // AFDRVCheck_H
