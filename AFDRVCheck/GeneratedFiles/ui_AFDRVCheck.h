/********************************************************************************
** Form generated from reading UI file 'AFDRVCheck.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AFDRVCHECK_H
#define UI_AFDRVCHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EEPROM
{
public:
    QPushButton *pushButton_read;
    QTextEdit *input;
    QLabel *label;
    QPushButton *pushButton_write;
    QLabel *label_5;
    QTextEdit *slave;
    QLabel *label_6;
    QTextEdit *addH;
    QTextEdit *addL;
    QLabel *label_8;
    QTextEdit *readData;
    QTextEdit *writeData;
    QTextEdit *GPIO_Value;
    QPushButton *pushButton_GPIO_write;
    QPushButton *pushButton_GPIO_read;
    QCheckBox *checkBox;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_6;
    QGroupBox *groupBox;
    QCheckBox *checkBox_17;
    QCheckBox *checkBox_16;
    QCheckBox *checkBox_20;
    QCheckBox *checkBox_27;
    QCheckBox *checkBox_30;
    QCheckBox *checkBox_19;
    QCheckBox *checkBox_23;
    QCheckBox *checkBox_25;
    QCheckBox *checkBox_29;
    QCheckBox *checkBox_21;
    QCheckBox *checkBox_22;
    QCheckBox *checkBox_18;
    QCheckBox *checkBox_31;
    QCheckBox *checkBox_26;
    QCheckBox *checkBox_28;
    QCheckBox *checkBox_24;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_read_all;
    QPushButton *pushButton_write_all;
    QGroupBox *groupBox_2;
    QLabel *label_9;
    QTextEdit *eep_size;
    QLabel *label_11;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_15;
    QPushButton *pushButton_clear;
    QTextEdit *afL;
    QLabel *label_10;
    QPushButton *pushButton_af_add;
    QTextEdit *afH;
    QTextEdit *slave_af;
    QTextEdit *addr_af;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_af_sub;
    QTextEdit *log;
    QCheckBox *addH_use;
    QRadioButton *Dphy;
    QRadioButton *Cphy;
    QRadioButton *CH0;
    QRadioButton *CH1;
    QCheckBox *R_Main;
    QPushButton *pushButton_GPIO_All;
    QPushButton *pushButton_Load;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_Read_MIPI;
    QPushButton *pushButton_Write_MIPI;
    QPushButton *pushButton_Dphy_Init;
    QPushButton *pushButton_puya;
    QWidget *tab_3;
    QPushButton *pushButton_BU24721_Read;
    QGroupBox *groupBox_6;
    QPushButton *pushButton_BU24721;
    QTextEdit *decenter_BU24721X;
    QTextEdit *decenter_BU24721Y;
    QLabel *label_4;
    QPushButton *pushButton_BU24532_Read;
    QPushButton *pushButton_BU24532_Drive;
    QPushButton *pushButton_BU24532_Iris_on;
    QPushButton *pushButton_BU24532_Iris_off;
    QPushButton *pushButton_BU24532_Test;
    QPushButton *pushButton_BU24532_Sine;
    QPushButton *pushButton_BU24721_DC;
    QPushButton *pushButton_BU24721_Drive;
    QPushButton *pushButton_BU24532_Life;
    QPushButton *pushButton_BU24631_Sine;
    QWidget *tab_4;
    QPushButton *pushButton_DW2;
    QPushButton *pushButton_DW1;
    QPushButton *pushButton_DW9828C_Read;
    QWidget *tab_5;
    QPushButton *pushButton_read_AF_OnSemi;
    QPushButton *pushButton_LC89812X;
    QPushButton *pushButton_LC89812X_read;
    QPushButton *pushButton_LC89812X_write;
    QWidget *tab_6;
    QPushButton *pushButton_MC_AF;
    QPushButton *pushButton_7323;
    QWidget *tab_7;
    QPushButton *pushButton_SEM1215_Current;
    QPushButton *pushButton_SEM1215_Ver;
    QPushButton *pushButton_SEM1217_Read;
    QWidget *tab_8;
    QPushButton *pushButton_AW86006_init;
    QPushButton *pushButton_AW86006_FW;
    QPushButton *pushButton_AW86006_HallCal;
    QPushButton *pushButton_AW86006_Square;
    QPushButton *pushButton_AW86006_Read;
    QPushButton *pushButton_AW86006_Slave_Change;
    QPushButton *pushButton_AW86006_Sine;
    QPushButton *pushButton_AW86006_Vsync;
    QPushButton *pushButton_AW86006_Gain_Write;
    QWidget *tab_2;
    QGroupBox *groupBox_4;
    QPushButton *pushButton_AF_Aging_OnSemi;
    QPushButton *pushButton_read_AF_SNA;
    QPushButton *pushButton_read_OIS;
    QPushButton *pushButton_AF_SNA_Lin;
    QPushButton *pushButton_Slave_Scan;
    QPushButton *pushButton_script;
    QGroupBox *groupBox_5;
    QLabel *label_15;
    QTextEdit *OIS_range;
    QRadioButton *radioButton_FWD;
    QRadioButton *radioButton_BWD;
    QLabel *label_16;
    QLabel *label_17;
    QRadioButton *radioButton_Axis_Y;
    QRadioButton *radioButton_Axis_X;
    QTextEdit *AF_Times;
    QTextEdit *Delay;
    QLabel *label_19;
    QPushButton *pushButton_AF_Aging_Stop;
    QPushButton *pushButton_AF_Aging;
    QPushButton *pushButton_save;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;
    QButtonGroup *buttonGroup_4;

    void setupUi(QWidget *EEPROM)
    {
        if (EEPROM->objectName().isEmpty())
            EEPROM->setObjectName(QStringLiteral("EEPROM"));
        EEPROM->resize(850, 470);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EEPROM->sizePolicy().hasHeightForWidth());
        EEPROM->setSizePolicy(sizePolicy);
        EEPROM->setMaximumSize(QSize(1440, 1200));
        EEPROM->setAcceptDrops(true);
        pushButton_read = new QPushButton(EEPROM);
        pushButton_read->setObjectName(QStringLiteral("pushButton_read"));
        pushButton_read->setGeometry(QRect(290, 250, 61, 30));
        pushButton_read->setCheckable(false);
        input = new QTextEdit(EEPROM);
        input->setObjectName(QStringLiteral("input"));
        input->setGeometry(QRect(10, 20, 420, 151));
        label = new QLabel(EEPROM);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 0, 161, 16));
        pushButton_write = new QPushButton(EEPROM);
        pushButton_write->setObjectName(QStringLiteral("pushButton_write"));
        pushButton_write->setGeometry(QRect(290, 290, 61, 30));
        pushButton_write->setCheckable(false);
        label_5 = new QLabel(EEPROM);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(90, 230, 51, 16));
        slave = new QTextEdit(EEPROM);
        slave->setObjectName(QStringLiteral("slave"));
        slave->setGeometry(QRect(90, 250, 41, 30));
        label_6 = new QLabel(EEPROM);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(150, 230, 71, 16));
        addH = new QTextEdit(EEPROM);
        addH->setObjectName(QStringLiteral("addH"));
        addH->setGeometry(QRect(140, 250, 41, 30));
        addL = new QTextEdit(EEPROM);
        addL->setObjectName(QStringLiteral("addL"));
        addL->setGeometry(QRect(190, 250, 41, 30));
        label_8 = new QLabel(EEPROM);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(250, 230, 41, 16));
        readData = new QTextEdit(EEPROM);
        readData->setObjectName(QStringLiteral("readData"));
        readData->setGeometry(QRect(240, 250, 41, 31));
        writeData = new QTextEdit(EEPROM);
        writeData->setObjectName(QStringLiteral("writeData"));
        writeData->setGeometry(QRect(240, 290, 41, 30));
        GPIO_Value = new QTextEdit(EEPROM);
        GPIO_Value->setObjectName(QStringLiteral("GPIO_Value"));
        GPIO_Value->setGeometry(QRect(470, 250, 81, 30));
        pushButton_GPIO_write = new QPushButton(EEPROM);
        pushButton_GPIO_write->setObjectName(QStringLiteral("pushButton_GPIO_write"));
        pushButton_GPIO_write->setGeometry(QRect(750, 250, 91, 30));
        pushButton_GPIO_write->setCheckable(false);
        pushButton_GPIO_read = new QPushButton(EEPROM);
        pushButton_GPIO_read->setObjectName(QStringLiteral("pushButton_GPIO_read"));
        pushButton_GPIO_read->setGeometry(QRect(650, 250, 91, 30));
        pushButton_GPIO_read->setCheckable(false);
        checkBox = new QCheckBox(EEPROM);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(820, 305, 16, 16));
        checkBox_1 = new QCheckBox(EEPROM);
        checkBox_1->setObjectName(QStringLiteral("checkBox_1"));
        checkBox_1->setGeometry(QRect(800, 305, 16, 16));
        checkBox_2 = new QCheckBox(EEPROM);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(780, 305, 16, 16));
        checkBox_3 = new QCheckBox(EEPROM);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(760, 305, 16, 16));
        checkBox_4 = new QCheckBox(EEPROM);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setGeometry(QRect(730, 305, 16, 16));
        checkBox_5 = new QCheckBox(EEPROM);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setGeometry(QRect(710, 305, 16, 16));
        checkBox_7 = new QCheckBox(EEPROM);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        checkBox_7->setGeometry(QRect(670, 305, 16, 16));
        checkBox_10 = new QCheckBox(EEPROM);
        checkBox_10->setObjectName(QStringLiteral("checkBox_10"));
        checkBox_10->setGeometry(QRect(600, 305, 16, 16));
        checkBox_9 = new QCheckBox(EEPROM);
        checkBox_9->setObjectName(QStringLiteral("checkBox_9"));
        checkBox_9->setGeometry(QRect(620, 305, 16, 16));
        checkBox_8 = new QCheckBox(EEPROM);
        checkBox_8->setObjectName(QStringLiteral("checkBox_8"));
        checkBox_8->setGeometry(QRect(640, 305, 16, 16));
        checkBox_6 = new QCheckBox(EEPROM);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        checkBox_6->setGeometry(QRect(690, 305, 16, 16));
        groupBox = new QGroupBox(EEPROM);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(440, 230, 410, 100));
        checkBox_17 = new QCheckBox(groupBox);
        checkBox_17->setObjectName(QStringLiteral("checkBox_17"));
        checkBox_17->setGeometry(QRect(360, 55, 16, 16));
        checkBox_16 = new QCheckBox(groupBox);
        checkBox_16->setObjectName(QStringLiteral("checkBox_16"));
        checkBox_16->setGeometry(QRect(380, 55, 16, 16));
        checkBox_20 = new QCheckBox(groupBox);
        checkBox_20->setObjectName(QStringLiteral("checkBox_20"));
        checkBox_20->setGeometry(QRect(290, 55, 16, 16));
        checkBox_27 = new QCheckBox(groupBox);
        checkBox_27->setObjectName(QStringLiteral("checkBox_27"));
        checkBox_27->setGeometry(QRect(140, 55, 16, 16));
        checkBox_30 = new QCheckBox(groupBox);
        checkBox_30->setObjectName(QStringLiteral("checkBox_30"));
        checkBox_30->setGeometry(QRect(70, 55, 16, 16));
        checkBox_19 = new QCheckBox(groupBox);
        checkBox_19->setObjectName(QStringLiteral("checkBox_19"));
        checkBox_19->setGeometry(QRect(320, 55, 16, 16));
        checkBox_23 = new QCheckBox(groupBox);
        checkBox_23->setObjectName(QStringLiteral("checkBox_23"));
        checkBox_23->setGeometry(QRect(230, 55, 16, 16));
        checkBox_25 = new QCheckBox(groupBox);
        checkBox_25->setObjectName(QStringLiteral("checkBox_25"));
        checkBox_25->setGeometry(QRect(180, 55, 16, 16));
        checkBox_29 = new QCheckBox(groupBox);
        checkBox_29->setObjectName(QStringLiteral("checkBox_29"));
        checkBox_29->setGeometry(QRect(90, 55, 16, 16));
        checkBox_21 = new QCheckBox(groupBox);
        checkBox_21->setObjectName(QStringLiteral("checkBox_21"));
        checkBox_21->setGeometry(QRect(270, 55, 16, 16));
        checkBox_22 = new QCheckBox(groupBox);
        checkBox_22->setObjectName(QStringLiteral("checkBox_22"));
        checkBox_22->setGeometry(QRect(250, 55, 16, 16));
        checkBox_18 = new QCheckBox(groupBox);
        checkBox_18->setObjectName(QStringLiteral("checkBox_18"));
        checkBox_18->setGeometry(QRect(340, 55, 16, 16));
        checkBox_31 = new QCheckBox(groupBox);
        checkBox_31->setObjectName(QStringLiteral("checkBox_31"));
        checkBox_31->setGeometry(QRect(50, 55, 16, 16));
        checkBox_26 = new QCheckBox(groupBox);
        checkBox_26->setObjectName(QStringLiteral("checkBox_26"));
        checkBox_26->setGeometry(QRect(160, 55, 16, 16));
        checkBox_28 = new QCheckBox(groupBox);
        checkBox_28->setObjectName(QStringLiteral("checkBox_28"));
        checkBox_28->setGeometry(QRect(110, 55, 16, 16));
        checkBox_24 = new QCheckBox(groupBox);
        checkBox_24->setObjectName(QStringLiteral("checkBox_24"));
        checkBox_24->setGeometry(QRect(200, 55, 16, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(15, 55, 20, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(15, 75, 20, 16));
        pushButton_read_all = new QPushButton(EEPROM);
        pushButton_read_all->setObjectName(QStringLiteral("pushButton_read_all"));
        pushButton_read_all->setGeometry(QRect(360, 250, 61, 30));
        pushButton_read_all->setCheckable(false);
        pushButton_write_all = new QPushButton(EEPROM);
        pushButton_write_all->setObjectName(QStringLiteral("pushButton_write_all"));
        pushButton_write_all->setGeometry(QRect(360, 290, 61, 30));
        pushButton_write_all->setCheckable(false);
        groupBox_2 = new QGroupBox(EEPROM);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 230, 420, 95));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 65, 71, 20));
        eep_size = new QTextEdit(groupBox_2);
        eep_size->setObjectName(QStringLiteral("eep_size"));
        eep_size->setGeometry(QRect(70, 60, 51, 30));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(160, 65, 31, 16));
        checkBox_11 = new QCheckBox(EEPROM);
        checkBox_11->setObjectName(QStringLiteral("checkBox_11"));
        checkBox_11->setGeometry(QRect(580, 305, 16, 16));
        checkBox_12 = new QCheckBox(EEPROM);
        checkBox_12->setObjectName(QStringLiteral("checkBox_12"));
        checkBox_12->setGeometry(QRect(550, 305, 16, 16));
        checkBox_13 = new QCheckBox(EEPROM);
        checkBox_13->setObjectName(QStringLiteral("checkBox_13"));
        checkBox_13->setGeometry(QRect(530, 305, 16, 16));
        checkBox_14 = new QCheckBox(EEPROM);
        checkBox_14->setObjectName(QStringLiteral("checkBox_14"));
        checkBox_14->setGeometry(QRect(510, 305, 16, 16));
        checkBox_15 = new QCheckBox(EEPROM);
        checkBox_15->setObjectName(QStringLiteral("checkBox_15"));
        checkBox_15->setGeometry(QRect(490, 305, 16, 16));
        pushButton_clear = new QPushButton(EEPROM);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(360, 440, 71, 30));
        pushButton_clear->setCheckable(false);
        afL = new QTextEdit(EEPROM);
        afL->setObjectName(QStringLiteral("afL"));
        afL->setGeometry(QRect(710, 360, 51, 31));
        label_10 = new QLabel(EEPROM);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(540, 340, 51, 16));
        pushButton_af_add = new QPushButton(EEPROM);
        pushButton_af_add->setObjectName(QStringLiteral("pushButton_af_add"));
        pushButton_af_add->setGeometry(QRect(770, 360, 61, 30));
        pushButton_af_add->setCheckable(false);
        afH = new QTextEdit(EEPROM);
        afH->setObjectName(QStringLiteral("afH"));
        afH->setGeometry(QRect(650, 360, 51, 30));
        slave_af = new QTextEdit(EEPROM);
        slave_af->setObjectName(QStringLiteral("slave_af"));
        slave_af->setGeometry(QRect(530, 360, 51, 30));
        addr_af = new QTextEdit(EEPROM);
        addr_af->setObjectName(QStringLiteral("addr_af"));
        addr_af->setGeometry(QRect(590, 360, 51, 30));
        label_12 = new QLabel(EEPROM);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(660, 340, 41, 16));
        label_13 = new QLabel(EEPROM);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(600, 340, 50, 16));
        label_14 = new QLabel(EEPROM);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(720, 340, 41, 16));
        groupBox_3 = new QGroupBox(EEPROM);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(440, 330, 410, 61));
        pushButton_af_sub = new QPushButton(EEPROM);
        pushButton_af_sub->setObjectName(QStringLiteral("pushButton_af_sub"));
        pushButton_af_sub->setGeometry(QRect(460, 360, 61, 30));
        pushButton_af_sub->setCheckable(false);
        log = new QTextEdit(EEPROM);
        log->setObjectName(QStringLiteral("log"));
        log->setGeometry(QRect(10, 329, 420, 141));
        addH_use = new QCheckBox(EEPROM);
        addH_use->setObjectName(QStringLiteral("addH_use"));
        addH_use->setGeometry(QRect(150, 295, 16, 16));
        addH_use->setChecked(true);
        Dphy = new QRadioButton(EEPROM);
        buttonGroup = new QButtonGroup(EEPROM);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(Dphy);
        Dphy->setObjectName(QStringLiteral("Dphy"));
        Dphy->setGeometry(QRect(20, 180, 61, 16));
        Dphy->setChecked(true);
        Cphy = new QRadioButton(EEPROM);
        buttonGroup->addButton(Cphy);
        Cphy->setObjectName(QStringLiteral("Cphy"));
        Cphy->setGeometry(QRect(20, 200, 81, 16));
        CH0 = new QRadioButton(EEPROM);
        buttonGroup_2 = new QButtonGroup(EEPROM);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(CH0);
        CH0->setObjectName(QStringLiteral("CH0"));
        CH0->setGeometry(QRect(80, 180, 41, 16));
        CH0->setChecked(true);
        CH1 = new QRadioButton(EEPROM);
        buttonGroup_2->addButton(CH1);
        CH1->setObjectName(QStringLiteral("CH1"));
        CH1->setGeometry(QRect(80, 200, 41, 16));
        R_Main = new QCheckBox(EEPROM);
        R_Main->setObjectName(QStringLiteral("R_Main"));
        R_Main->setGeometry(QRect(130, 180, 61, 16));
        R_Main->setChecked(true);
        pushButton_GPIO_All = new QPushButton(EEPROM);
        pushButton_GPIO_All->setObjectName(QStringLiteral("pushButton_GPIO_All"));
        pushButton_GPIO_All->setGeometry(QRect(570, 250, 61, 30));
        pushButton_GPIO_All->setCheckable(false);
        pushButton_Load = new QPushButton(EEPROM);
        pushButton_Load->setObjectName(QStringLiteral("pushButton_Load"));
        pushButton_Load->setGeometry(QRect(360, 170, 71, 30));
        pushButton_Load->setCheckable(false);
        tabWidget = new QTabWidget(EEPROM);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(435, 0, 411, 231));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_Read_MIPI = new QPushButton(tab);
        pushButton_Read_MIPI->setObjectName(QStringLiteral("pushButton_Read_MIPI"));
        pushButton_Read_MIPI->setGeometry(QRect(0, 30, 100, 30));
        pushButton_Read_MIPI->setCheckable(false);
        pushButton_Write_MIPI = new QPushButton(tab);
        pushButton_Write_MIPI->setObjectName(QStringLiteral("pushButton_Write_MIPI"));
        pushButton_Write_MIPI->setGeometry(QRect(0, 60, 100, 30));
        pushButton_Write_MIPI->setCheckable(false);
        pushButton_Dphy_Init = new QPushButton(tab);
        pushButton_Dphy_Init->setObjectName(QStringLiteral("pushButton_Dphy_Init"));
        pushButton_Dphy_Init->setGeometry(QRect(0, 0, 100, 30));
        pushButton_Dphy_Init->setCheckable(false);
        pushButton_puya = new QPushButton(tab);
        pushButton_puya->setObjectName(QStringLiteral("pushButton_puya"));
        pushButton_puya->setGeometry(QRect(100, 0, 100, 30));
        pushButton_puya->setCheckable(false);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButton_BU24721_Read = new QPushButton(tab_3);
        pushButton_BU24721_Read->setObjectName(QStringLiteral("pushButton_BU24721_Read"));
        pushButton_BU24721_Read->setGeometry(QRect(5, 175, 100, 30));
        pushButton_BU24721_Read->setCheckable(false);
        groupBox_6 = new QGroupBox(tab_3);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, -1, 108, 91));
        pushButton_BU24721 = new QPushButton(groupBox_6);
        pushButton_BU24721->setObjectName(QStringLiteral("pushButton_BU24721"));
        pushButton_BU24721->setGeometry(QRect(5, 55, 100, 30));
        pushButton_BU24721->setCheckable(false);
        decenter_BU24721X = new QTextEdit(groupBox_6);
        decenter_BU24721X->setObjectName(QStringLiteral("decenter_BU24721X"));
        decenter_BU24721X->setGeometry(QRect(5, 30, 50, 25));
        decenter_BU24721Y = new QTextEdit(groupBox_6);
        decenter_BU24721Y->setObjectName(QStringLiteral("decenter_BU24721Y"));
        decenter_BU24721Y->setGeometry(QRect(55, 30, 50, 25));
        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(5, 13, 105, 16));
        pushButton_BU24532_Read = new QPushButton(tab_3);
        pushButton_BU24532_Read->setObjectName(QStringLiteral("pushButton_BU24532_Read"));
        pushButton_BU24532_Read->setGeometry(QRect(105, 115, 100, 30));
        pushButton_BU24532_Read->setCheckable(false);
        pushButton_BU24532_Drive = new QPushButton(tab_3);
        pushButton_BU24532_Drive->setObjectName(QStringLiteral("pushButton_BU24532_Drive"));
        pushButton_BU24532_Drive->setGeometry(QRect(105, 85, 100, 30));
        pushButton_BU24532_Drive->setCheckable(false);
        pushButton_BU24532_Iris_on = new QPushButton(tab_3);
        pushButton_BU24532_Iris_on->setObjectName(QStringLiteral("pushButton_BU24532_Iris_on"));
        pushButton_BU24532_Iris_on->setGeometry(QRect(319, 146, 81, 30));
        pushButton_BU24532_Iris_on->setCheckable(false);
        pushButton_BU24532_Iris_off = new QPushButton(tab_3);
        pushButton_BU24532_Iris_off->setObjectName(QStringLiteral("pushButton_BU24532_Iris_off"));
        pushButton_BU24532_Iris_off->setGeometry(QRect(320, 176, 81, 30));
        pushButton_BU24532_Iris_off->setCheckable(false);
        pushButton_BU24532_Test = new QPushButton(tab_3);
        pushButton_BU24532_Test->setObjectName(QStringLiteral("pushButton_BU24532_Test"));
        pushButton_BU24532_Test->setGeometry(QRect(105, 175, 100, 30));
        pushButton_BU24532_Test->setCheckable(false);
        pushButton_BU24532_Sine = new QPushButton(tab_3);
        pushButton_BU24532_Sine->setObjectName(QStringLiteral("pushButton_BU24532_Sine"));
        pushButton_BU24532_Sine->setGeometry(QRect(105, 55, 100, 30));
        pushButton_BU24532_Sine->setCheckable(false);
        pushButton_BU24721_DC = new QPushButton(tab_3);
        pushButton_BU24721_DC->setObjectName(QStringLiteral("pushButton_BU24721_DC"));
        pushButton_BU24721_DC->setGeometry(QRect(4, 145, 100, 30));
        pushButton_BU24721_DC->setCheckable(false);
        pushButton_BU24721_Drive = new QPushButton(tab_3);
        pushButton_BU24721_Drive->setObjectName(QStringLiteral("pushButton_BU24721_Drive"));
        pushButton_BU24721_Drive->setGeometry(QRect(6, 83, 100, 30));
        pushButton_BU24721_Drive->setCheckable(false);
        pushButton_BU24532_Life = new QPushButton(tab_3);
        pushButton_BU24532_Life->setObjectName(QStringLiteral("pushButton_BU24532_Life"));
        pushButton_BU24532_Life->setGeometry(QRect(105, 145, 100, 30));
        pushButton_BU24532_Life->setCheckable(false);
        pushButton_BU24631_Sine = new QPushButton(tab_3);
        pushButton_BU24631_Sine->setObjectName(QStringLiteral("pushButton_BU24631_Sine"));
        pushButton_BU24631_Sine->setGeometry(QRect(204, 55, 100, 30));
        pushButton_BU24631_Sine->setCheckable(false);
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        pushButton_DW2 = new QPushButton(tab_4);
        pushButton_DW2->setObjectName(QStringLiteral("pushButton_DW2"));
        pushButton_DW2->setGeometry(QRect(0, 30, 100, 30));
        pushButton_DW2->setCheckable(false);
        pushButton_DW1 = new QPushButton(tab_4);
        pushButton_DW1->setObjectName(QStringLiteral("pushButton_DW1"));
        pushButton_DW1->setGeometry(QRect(0, 0, 100, 30));
        pushButton_DW1->setCheckable(false);
        pushButton_DW9828C_Read = new QPushButton(tab_4);
        pushButton_DW9828C_Read->setObjectName(QStringLiteral("pushButton_DW9828C_Read"));
        pushButton_DW9828C_Read->setGeometry(QRect(0, 60, 100, 30));
        pushButton_DW9828C_Read->setCheckable(false);
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        pushButton_read_AF_OnSemi = new QPushButton(tab_5);
        pushButton_read_AF_OnSemi->setObjectName(QStringLiteral("pushButton_read_AF_OnSemi"));
        pushButton_read_AF_OnSemi->setGeometry(QRect(300, 0, 100, 30));
        pushButton_read_AF_OnSemi->setCheckable(false);
        pushButton_LC89812X = new QPushButton(tab_5);
        pushButton_LC89812X->setObjectName(QStringLiteral("pushButton_LC89812X"));
        pushButton_LC89812X->setGeometry(QRect(0, 0, 100, 30));
        pushButton_LC89812X->setCheckable(false);
        pushButton_LC89812X_read = new QPushButton(tab_5);
        pushButton_LC89812X_read->setObjectName(QStringLiteral("pushButton_LC89812X_read"));
        pushButton_LC89812X_read->setGeometry(QRect(0, 30, 100, 30));
        pushButton_LC89812X_read->setCheckable(false);
        pushButton_LC89812X_write = new QPushButton(tab_5);
        pushButton_LC89812X_write->setObjectName(QStringLiteral("pushButton_LC89812X_write"));
        pushButton_LC89812X_write->setGeometry(QRect(0, 60, 100, 30));
        pushButton_LC89812X_write->setCheckable(false);
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        pushButton_MC_AF = new QPushButton(tab_6);
        pushButton_MC_AF->setObjectName(QStringLiteral("pushButton_MC_AF"));
        pushButton_MC_AF->setGeometry(QRect(0, 0, 100, 30));
        pushButton_MC_AF->setCheckable(false);
        pushButton_7323 = new QPushButton(tab_6);
        pushButton_7323->setObjectName(QStringLiteral("pushButton_7323"));
        pushButton_7323->setGeometry(QRect(0, 30, 100, 30));
        pushButton_7323->setCheckable(false);
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        pushButton_SEM1215_Current = new QPushButton(tab_7);
        pushButton_SEM1215_Current->setObjectName(QStringLiteral("pushButton_SEM1215_Current"));
        pushButton_SEM1215_Current->setGeometry(QRect(0, 30, 100, 30));
        pushButton_SEM1215_Current->setCheckable(false);
        pushButton_SEM1215_Ver = new QPushButton(tab_7);
        pushButton_SEM1215_Ver->setObjectName(QStringLiteral("pushButton_SEM1215_Ver"));
        pushButton_SEM1215_Ver->setGeometry(QRect(0, 0, 100, 30));
        pushButton_SEM1215_Ver->setCheckable(false);
        pushButton_SEM1217_Read = new QPushButton(tab_7);
        pushButton_SEM1217_Read->setObjectName(QStringLiteral("pushButton_SEM1217_Read"));
        pushButton_SEM1217_Read->setGeometry(QRect(100, 0, 100, 30));
        pushButton_SEM1217_Read->setCheckable(false);
        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        pushButton_AW86006_init = new QPushButton(tab_8);
        pushButton_AW86006_init->setObjectName(QStringLiteral("pushButton_AW86006_init"));
        pushButton_AW86006_init->setGeometry(QRect(0, 0, 100, 30));
        pushButton_AW86006_init->setCheckable(false);
        pushButton_AW86006_FW = new QPushButton(tab_8);
        pushButton_AW86006_FW->setObjectName(QStringLiteral("pushButton_AW86006_FW"));
        pushButton_AW86006_FW->setGeometry(QRect(0, 30, 100, 30));
        pushButton_AW86006_FW->setCheckable(false);
        pushButton_AW86006_HallCal = new QPushButton(tab_8);
        pushButton_AW86006_HallCal->setObjectName(QStringLiteral("pushButton_AW86006_HallCal"));
        pushButton_AW86006_HallCal->setGeometry(QRect(0, 60, 100, 30));
        pushButton_AW86006_HallCal->setCheckable(false);
        pushButton_AW86006_Square = new QPushButton(tab_8);
        pushButton_AW86006_Square->setObjectName(QStringLiteral("pushButton_AW86006_Square"));
        pushButton_AW86006_Square->setGeometry(QRect(100, 0, 100, 30));
        pushButton_AW86006_Square->setCheckable(false);
        pushButton_AW86006_Read = new QPushButton(tab_8);
        pushButton_AW86006_Read->setObjectName(QStringLiteral("pushButton_AW86006_Read"));
        pushButton_AW86006_Read->setGeometry(QRect(0, 120, 100, 30));
        pushButton_AW86006_Read->setCheckable(false);
        pushButton_AW86006_Slave_Change = new QPushButton(tab_8);
        pushButton_AW86006_Slave_Change->setObjectName(QStringLiteral("pushButton_AW86006_Slave_Change"));
        pushButton_AW86006_Slave_Change->setGeometry(QRect(0, 150, 100, 30));
        pushButton_AW86006_Slave_Change->setCheckable(false);
        pushButton_AW86006_Sine = new QPushButton(tab_8);
        pushButton_AW86006_Sine->setObjectName(QStringLiteral("pushButton_AW86006_Sine"));
        pushButton_AW86006_Sine->setGeometry(QRect(100, 30, 100, 30));
        pushButton_AW86006_Sine->setCheckable(false);
        pushButton_AW86006_Vsync = new QPushButton(tab_8);
        pushButton_AW86006_Vsync->setObjectName(QStringLiteral("pushButton_AW86006_Vsync"));
        pushButton_AW86006_Vsync->setGeometry(QRect(100, 150, 100, 30));
        pushButton_AW86006_Vsync->setCheckable(false);
        pushButton_AW86006_Gain_Write = new QPushButton(tab_8);
        pushButton_AW86006_Gain_Write->setObjectName(QStringLiteral("pushButton_AW86006_Gain_Write"));
        pushButton_AW86006_Gain_Write->setGeometry(QRect(100, 180, 100, 30));
        pushButton_AW86006_Gain_Write->setCheckable(false);
        tabWidget->addTab(tab_8, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(270, 0, 141, 41));
        pushButton_AF_Aging_OnSemi = new QPushButton(groupBox_4);
        pushButton_AF_Aging_OnSemi->setObjectName(QStringLiteral("pushButton_AF_Aging_OnSemi"));
        pushButton_AF_Aging_OnSemi->setGeometry(QRect(10, 10, 121, 30));
        pushButton_AF_Aging_OnSemi->setCheckable(false);
        pushButton_read_AF_SNA = new QPushButton(tab_2);
        pushButton_read_AF_SNA->setObjectName(QStringLiteral("pushButton_read_AF_SNA"));
        pushButton_read_AF_SNA->setGeometry(QRect(0, 0, 100, 30));
        pushButton_read_AF_SNA->setCheckable(false);
        pushButton_read_OIS = new QPushButton(tab_2);
        pushButton_read_OIS->setObjectName(QStringLiteral("pushButton_read_OIS"));
        pushButton_read_OIS->setGeometry(QRect(0, 60, 100, 30));
        pushButton_read_OIS->setCheckable(false);
        pushButton_AF_SNA_Lin = new QPushButton(tab_2);
        pushButton_AF_SNA_Lin->setObjectName(QStringLiteral("pushButton_AF_SNA_Lin"));
        pushButton_AF_SNA_Lin->setGeometry(QRect(0, 30, 100, 30));
        pushButton_AF_SNA_Lin->setCheckable(false);
        pushButton_Slave_Scan = new QPushButton(tab_2);
        pushButton_Slave_Scan->setObjectName(QStringLiteral("pushButton_Slave_Scan"));
        pushButton_Slave_Scan->setGeometry(QRect(0, 170, 100, 30));
        pushButton_Slave_Scan->setCheckable(false);
        tabWidget->addTab(tab_2, QString());
        pushButton_script = new QPushButton(EEPROM);
        pushButton_script->setObjectName(QStringLiteral("pushButton_script"));
        pushButton_script->setGeometry(QRect(280, 170, 71, 30));
        pushButton_script->setCheckable(false);
        groupBox_5 = new QGroupBox(EEPROM);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(440, 390, 410, 80));
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(20, 20, 20, 16));
        OIS_range = new QTextEdit(groupBox_5);
        OIS_range->setObjectName(QStringLiteral("OIS_range"));
        OIS_range->setGeometry(QRect(10, 40, 40, 30));
        radioButton_FWD = new QRadioButton(groupBox_5);
        buttonGroup_3 = new QButtonGroup(EEPROM);
        buttonGroup_3->setObjectName(QStringLiteral("buttonGroup_3"));
        buttonGroup_3->addButton(radioButton_FWD);
        radioButton_FWD->setObjectName(QStringLiteral("radioButton_FWD"));
        radioButton_FWD->setGeometry(QRect(70, 30, 41, 16));
        radioButton_FWD->setChecked(true);
        radioButton_BWD = new QRadioButton(groupBox_5);
        buttonGroup_3->addButton(radioButton_BWD);
        radioButton_BWD->setObjectName(QStringLiteral("radioButton_BWD"));
        radioButton_BWD->setGeometry(QRect(70, 50, 41, 16));
        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(60, 10, 61, 16));
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(120, 10, 31, 16));
        radioButton_Axis_Y = new QRadioButton(groupBox_5);
        buttonGroup_4 = new QButtonGroup(EEPROM);
        buttonGroup_4->setObjectName(QStringLiteral("buttonGroup_4"));
        buttonGroup_4->addButton(radioButton_Axis_Y);
        radioButton_Axis_Y->setObjectName(QStringLiteral("radioButton_Axis_Y"));
        radioButton_Axis_Y->setGeometry(QRect(120, 50, 31, 16));
        radioButton_Axis_X = new QRadioButton(groupBox_5);
        buttonGroup_4->addButton(radioButton_Axis_X);
        radioButton_Axis_X->setObjectName(QStringLiteral("radioButton_Axis_X"));
        radioButton_Axis_X->setGeometry(QRect(120, 30, 31, 16));
        radioButton_Axis_X->setChecked(true);
        AF_Times = new QTextEdit(groupBox_5);
        AF_Times->setObjectName(QStringLiteral("AF_Times"));
        AF_Times->setGeometry(QRect(350, 49, 50, 25));
        Delay = new QTextEdit(groupBox_5);
        Delay->setObjectName(QStringLiteral("Delay"));
        Delay->setGeometry(QRect(356, 20, 45, 25));
        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(360, 5, 41, 16));
        pushButton_AF_Aging_Stop = new QPushButton(groupBox_5);
        pushButton_AF_Aging_Stop->setObjectName(QStringLiteral("pushButton_AF_Aging_Stop"));
        pushButton_AF_Aging_Stop->setGeometry(QRect(305, 45, 41, 30));
        pushButton_AF_Aging_Stop->setCheckable(false);
        pushButton_AF_Aging = new QPushButton(groupBox_5);
        pushButton_AF_Aging->setObjectName(QStringLiteral("pushButton_AF_Aging"));
        pushButton_AF_Aging->setGeometry(QRect(305, 15, 41, 30));
        pushButton_AF_Aging->setCheckable(false);
        pushButton_save = new QPushButton(EEPROM);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(360, 205, 71, 30));
        pushButton_save->setCheckable(false);
        groupBox_5->raise();
        log->raise();
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        pushButton_read->raise();
        input->raise();
        label->raise();
        pushButton_write->raise();
        label_5->raise();
        slave->raise();
        label_6->raise();
        addH->raise();
        addL->raise();
        label_8->raise();
        readData->raise();
        writeData->raise();
        GPIO_Value->raise();
        pushButton_GPIO_write->raise();
        pushButton_GPIO_read->raise();
        checkBox->raise();
        checkBox_1->raise();
        checkBox_2->raise();
        checkBox_3->raise();
        checkBox_4->raise();
        checkBox_5->raise();
        checkBox_7->raise();
        checkBox_10->raise();
        checkBox_9->raise();
        checkBox_8->raise();
        checkBox_6->raise();
        pushButton_read_all->raise();
        pushButton_write_all->raise();
        checkBox_11->raise();
        checkBox_12->raise();
        checkBox_13->raise();
        checkBox_14->raise();
        checkBox_15->raise();
        afL->raise();
        label_10->raise();
        pushButton_af_add->raise();
        afH->raise();
        slave_af->raise();
        addr_af->raise();
        label_12->raise();
        label_13->raise();
        label_14->raise();
        pushButton_af_sub->raise();
        pushButton_clear->raise();
        addH_use->raise();
        Dphy->raise();
        Cphy->raise();
        CH0->raise();
        CH1->raise();
        R_Main->raise();
        pushButton_GPIO_All->raise();
        pushButton_Load->raise();
        tabWidget->raise();
        pushButton_script->raise();
        pushButton_save->raise();

        retranslateUi(EEPROM);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(EEPROM);
    } // setupUi

    void retranslateUi(QWidget *EEPROM)
    {
        EEPROM->setWindowTitle(QApplication::translate("EEPROM", "EnvyLogic Controller_20230714", Q_NULLPTR));
        pushButton_read->setText(QApplication::translate("EEPROM", "Read", Q_NULLPTR));
        label->setText(QApplication::translate("EEPROM", "Check Result", Q_NULLPTR));
        pushButton_write->setText(QApplication::translate("EEPROM", "Write", Q_NULLPTR));
        label_5->setText(QApplication::translate("EEPROM", "Slave", Q_NULLPTR));
        slave->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4C</p></body></html>", Q_NULLPTR));
        label_6->setText(QApplication::translate("EEPROM", "Addr_H/L", Q_NULLPTR));
        addH->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">A0</p></body></html>", Q_NULLPTR));
        addL->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">00</p></body></html>", Q_NULLPTR));
        label_8->setText(QApplication::translate("EEPROM", "Data", Q_NULLPTR));
        readData->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        writeData->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        GPIO_Value->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        pushButton_GPIO_write->setText(QApplication::translate("EEPROM", "GPIO_Write", Q_NULLPTR));
        pushButton_GPIO_read->setText(QApplication::translate("EEPROM", "GPIO_Read", Q_NULLPTR));
        checkBox->setText(QString());
        checkBox_1->setText(QString());
        checkBox_2->setText(QString());
        checkBox_3->setText(QString());
        checkBox_4->setText(QString());
        checkBox_5->setText(QString());
        checkBox_7->setText(QApplication::translate("EEPROM", "7", Q_NULLPTR));
        checkBox_10->setText(QString());
        checkBox_9->setText(QString());
        checkBox_8->setText(QString());
        checkBox_6->setText(QString());
        groupBox->setTitle(QApplication::translate("EEPROM", "GPIO", Q_NULLPTR));
        checkBox_17->setText(QString());
        checkBox_16->setText(QString());
        checkBox_20->setText(QString());
        checkBox_27->setText(QString());
        checkBox_30->setText(QString());
        checkBox_19->setText(QString());
        checkBox_23->setText(QApplication::translate("EEPROM", "7", Q_NULLPTR));
        checkBox_25->setText(QString());
        checkBox_29->setText(QString());
        checkBox_21->setText(QString());
        checkBox_22->setText(QString());
        checkBox_18->setText(QString());
        checkBox_31->setText(QString());
        checkBox_26->setText(QString());
        checkBox_28->setText(QString());
        checkBox_24->setText(QString());
        label_2->setText(QApplication::translate("EEPROM", "CH1", Q_NULLPTR));
        label_3->setText(QApplication::translate("EEPROM", "CH0", Q_NULLPTR));
        pushButton_read_all->setText(QApplication::translate("EEPROM", "R_All", Q_NULLPTR));
        pushButton_write_all->setText(QApplication::translate("EEPROM", "W_All", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("EEPROM", "I2C", Q_NULLPTR));
        label_9->setText(QApplication::translate("EEPROM", "EEP_Size", Q_NULLPTR));
        eep_size->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">16384</p></body></html>", Q_NULLPTR));
        label_11->setText(QApplication::translate("EEPROM", "H_Use", Q_NULLPTR));
        checkBox_11->setText(QString());
        checkBox_12->setText(QString());
        checkBox_13->setText(QString());
        checkBox_14->setText(QString());
        checkBox_15->setText(QString());
        pushButton_clear->setText(QApplication::translate("EEPROM", "Clear", Q_NULLPTR));
        afL->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">00</p></body></html>", Q_NULLPTR));
        label_10->setText(QApplication::translate("EEPROM", "Slave", Q_NULLPTR));
        pushButton_af_add->setText(QApplication::translate("EEPROM", "Move+", Q_NULLPTR));
        afH->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">02</p></body></html>", Q_NULLPTR));
        slave_af->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">E4</p></body></html>", Q_NULLPTR));
        addr_af->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">84</p></body></html>", Q_NULLPTR));
        label_12->setText(QApplication::translate("EEPROM", "AF_H", Q_NULLPTR));
        label_13->setText(QApplication::translate("EEPROM", "Addr", Q_NULLPTR));
        label_14->setText(QApplication::translate("EEPROM", "AF_L", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("EEPROM", "AF", Q_NULLPTR));
        pushButton_af_sub->setText(QApplication::translate("EEPROM", "Move-", Q_NULLPTR));
        addH_use->setText(QString());
        Dphy->setText(QApplication::translate("EEPROM", "D-Phy", Q_NULLPTR));
        Cphy->setText(QApplication::translate("EEPROM", "C-Phy", Q_NULLPTR));
        CH0->setText(QApplication::translate("EEPROM", "CH0", Q_NULLPTR));
        CH1->setText(QApplication::translate("EEPROM", "CH1", Q_NULLPTR));
        R_Main->setText(QApplication::translate("EEPROM", "R_Main", Q_NULLPTR));
        pushButton_GPIO_All->setText(QApplication::translate("EEPROM", "All ON", Q_NULLPTR));
        pushButton_Load->setText(QApplication::translate("EEPROM", "Data Load", Q_NULLPTR));
        pushButton_Read_MIPI->setText(QApplication::translate("EEPROM", "Read MIPI", Q_NULLPTR));
        pushButton_Write_MIPI->setText(QApplication::translate("EEPROM", "Write MIPI", Q_NULLPTR));
        pushButton_Dphy_Init->setText(QApplication::translate("EEPROM", "Dphy Init", Q_NULLPTR));
        pushButton_puya->setText(QApplication::translate("EEPROM", "PUYA EEPROM", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("EEPROM", "old", Q_NULLPTR));
        pushButton_BU24721_Read->setText(QApplication::translate("EEPROM", "BU24721 Read", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("EEPROM", "Sine Wave Test", Q_NULLPTR));
        pushButton_BU24721->setText(QApplication::translate("EEPROM", "BU24721 Sine", Q_NULLPTR));
        decenter_BU24721X->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        decenter_BU24721Y->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("EEPROM", "Center offset X/Y", Q_NULLPTR));
        pushButton_BU24532_Read->setText(QApplication::translate("EEPROM", "BU24532 Read", Q_NULLPTR));
        pushButton_BU24532_Drive->setText(QApplication::translate("EEPROM", "BU24532 Drive", Q_NULLPTR));
        pushButton_BU24532_Iris_on->setText(QApplication::translate("EEPROM", "IRIS Large", Q_NULLPTR));
        pushButton_BU24532_Iris_off->setText(QApplication::translate("EEPROM", "IRIS Small", Q_NULLPTR));
        pushButton_BU24532_Test->setText(QApplication::translate("EEPROM", "BU24532 Test", Q_NULLPTR));
        pushButton_BU24532_Sine->setText(QApplication::translate("EEPROM", "BU24532 Sine", Q_NULLPTR));
        pushButton_BU24721_DC->setText(QApplication::translate("EEPROM", "BU24721 DC_Sen", Q_NULLPTR));
        pushButton_BU24721_Drive->setText(QApplication::translate("EEPROM", "BU24721 Drive", Q_NULLPTR));
        pushButton_BU24532_Life->setText(QApplication::translate("EEPROM", "BU24532 Life", Q_NULLPTR));
        pushButton_BU24631_Sine->setText(QApplication::translate("EEPROM", "BU24631 Sine", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("EEPROM", "ROHM", Q_NULLPTR));
        pushButton_DW2->setText(QApplication::translate("EEPROM", "DW9781 Cls Sin", Q_NULLPTR));
        pushButton_DW1->setText(QApplication::translate("EEPROM", "DW9781 Open Sin", Q_NULLPTR));
        pushButton_DW9828C_Read->setText(QApplication::translate("EEPROM", "DW9828C Read", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("EEPROM", "DW", Q_NULLPTR));
        pushButton_read_AF_OnSemi->setText(QApplication::translate("EEPROM", "Onsemi AF_Read", Q_NULLPTR));
        pushButton_LC89812X->setText(QApplication::translate("EEPROM", "LC89812X On", Q_NULLPTR));
        pushButton_LC89812X_read->setText(QApplication::translate("EEPROM", "LC89812X Rd", Q_NULLPTR));
        pushButton_LC89812X_write->setText(QApplication::translate("EEPROM", "LC89812X Wt", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("EEPROM", "OnSemi", Q_NULLPTR));
        pushButton_MC_AF->setText(QApplication::translate("EEPROM", "MC AF Max", Q_NULLPTR));
        pushButton_7323->setText(QApplication::translate("EEPROM", "AK7323 Cls Sin", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("EEPROM", "AK", Q_NULLPTR));
        pushButton_SEM1215_Current->setText(QApplication::translate("EEPROM", "SEM1215_Current", Q_NULLPTR));
        pushButton_SEM1215_Ver->setText(QApplication::translate("EEPROM", "SEM1215_Ver", Q_NULLPTR));
        pushButton_SEM1217_Read->setText(QApplication::translate("EEPROM", "SEM1217_Read", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("EEPROM", "SEM", Q_NULLPTR));
        pushButton_AW86006_init->setText(QApplication::translate("EEPROM", "AW86006 Init", Q_NULLPTR));
        pushButton_AW86006_FW->setText(QApplication::translate("EEPROM", "AW86006 FW Down", Q_NULLPTR));
        pushButton_AW86006_HallCal->setText(QApplication::translate("EEPROM", "AW86006 HallCal", Q_NULLPTR));
        pushButton_AW86006_Square->setText(QApplication::translate("EEPROM", "AW86006 Square", Q_NULLPTR));
        pushButton_AW86006_Read->setText(QApplication::translate("EEPROM", "AW86006 Read", Q_NULLPTR));
        pushButton_AW86006_Slave_Change->setText(QApplication::translate("EEPROM", "AW86006 Slave", Q_NULLPTR));
        pushButton_AW86006_Sine->setText(QApplication::translate("EEPROM", "AW86006 Sine", Q_NULLPTR));
        pushButton_AW86006_Vsync->setText(QApplication::translate("EEPROM", "AW86006 Vsync", Q_NULLPTR));
        pushButton_AW86006_Gain_Write->setText(QApplication::translate("EEPROM", "AW Gain Write", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("EEPROM", "AW", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("EEPROM", "Aging", Q_NULLPTR));
        pushButton_AF_Aging_OnSemi->setText(QApplication::translate("EEPROM", "OnSemi AF_Aging", Q_NULLPTR));
        pushButton_read_AF_SNA->setText(QApplication::translate("EEPROM", "SNA AF_Read", Q_NULLPTR));
        pushButton_read_OIS->setText(QApplication::translate("EEPROM", " Rumba OIS_Drv ", Q_NULLPTR));
        pushButton_AF_SNA_Lin->setText(QApplication::translate("EEPROM", "SNA AF Lin", Q_NULLPTR));
        pushButton_Slave_Scan->setText(QApplication::translate("EEPROM", "Slave_Scan", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("EEPROM", "ETC", Q_NULLPTR));
        pushButton_script->setText(QApplication::translate("EEPROM", "Script", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("EEPROM", "setting", Q_NULLPTR));
        label_15->setText(QApplication::translate("EEPROM", "Amp.", Q_NULLPTR));
        OIS_range->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">90</p></body></html>", Q_NULLPTR));
        radioButton_FWD->setText(QApplication::translate("EEPROM", "FWD", Q_NULLPTR));
        radioButton_BWD->setText(QApplication::translate("EEPROM", "BWD", Q_NULLPTR));
        label_16->setText(QApplication::translate("EEPROM", "Direction", Q_NULLPTR));
        label_17->setText(QApplication::translate("EEPROM", "Axis", Q_NULLPTR));
        radioButton_Axis_Y->setText(QApplication::translate("EEPROM", "Y", Q_NULLPTR));
        radioButton_Axis_X->setText(QApplication::translate("EEPROM", "X", Q_NULLPTR));
        AF_Times->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">10</p></body></html>", Q_NULLPTR));
        Delay->setHtml(QApplication::translate("EEPROM", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">100</p></body></html>", Q_NULLPTR));
        label_19->setText(QApplication::translate("EEPROM", "Delay", Q_NULLPTR));
        pushButton_AF_Aging_Stop->setText(QApplication::translate("EEPROM", "Stop", Q_NULLPTR));
        pushButton_AF_Aging->setText(QApplication::translate("EEPROM", "Life", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("EEPROM", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class EEPROM: public Ui_EEPROM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AFDRVCHECK_H
