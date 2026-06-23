/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *contentFrame;
    QStackedWidget *stackedWidget;
    QWidget *loginIndex;
    QLineEdit *password_input;
    QLineEdit *username_input;
    QPushButton *submitBtn;
    QCheckBox *storeLoginCheckbox;
    QLabel *password_label;
    QLabel *username_label;
    QLabel *statusLabel;
    QWidget *appSelectIndex;
    QPushButton *DualToonContBtn;
    QPushButton *AutoGroupSelectBtn;
    QPushButton *DoodleBtn;
    QPushButton *InvasionBtn;
    QPushButton *LaunchTTBtn;
    QPushButton *ToonHQWebBtn;
    QWidget *toonHQToonSelect;
    QListWidget *toonListWidget;
    QWidget *toonHQConnected;
    QLabel *connectedToonLabel;
    QPushButton *disconnectToonBtn;
    QLabel *bg_label_x;
    QLabel *labelToonHQ;
    QLabel *connectedInfoLabel;
    QWidget *launchTTRPage;
    QLineEdit *unameInput1;
    QLabel *uname_label_1;
    QLineEdit *pwordInput1;
    QLabel *pword_label_1;
    QLineEdit *aliasInput1;
    QLabel *alias_label_1;
    QPushButton *addClient_btn1;
    QLabel *addClient_label1;
    QPushButton *save_btn1;
    QPushButton *edit_btn1;
    QLabel *launch_label1;
    QPushButton *remove_bt1;
    QPushButton *save_btn1_noInc;
    QPushButton *launch_btn1;
    QLineEdit *aliasInput2;
    QPushButton *addClient_btn2;
    QLineEdit *pwordInput2;
    QLabel *alias_label_2;
    QLineEdit *unameInput2;
    QLabel *pword_label_2;
    QPushButton *launch_btn2;
    QPushButton *save_btn2;
    QPushButton *edit_btn2;
    QPushButton *remove_bt2;
    QLabel *addClient_label2;
    QLabel *uname_label_2;
    QPushButton *save_btn2_noInc;
    QLabel *launch_label2;
    QPushButton *save_btn3;
    QPushButton *launch_btn3;
    QPushButton *addClient_btn3;
    QLabel *alias_label_3;
    QLabel *launch_label3;
    QLineEdit *unameInput3;
    QLineEdit *pwordInput3;
    QLabel *addClient_label3;
    QLineEdit *aliasInput3;
    QPushButton *remove_bt3;
    QLabel *uname_label_3;
    QPushButton *save_btn3_noInc;
    QPushButton *edit_btn3;
    QLabel *pword_label_3;
    QLabel *status_label_1;
    QLabel *status_label_2;
    QLabel *status_label_3;
    QPushButton *manual_loc_btnEDIT1;
    QLineEdit *fileLocation_input1;
    QLabel *installLoc_label1;
    QLabel *installLoc_label2;
    QLineEdit *fileLocation_input2;
    QPushButton *manual_loc_btnEDIT2;
    QLineEdit *fileLocation_input3;
    QPushButton *manual_loc_btnEDIT3;
    QLabel *installLoc_label3;
    QWidget *dualToonPage;
    QPushButton *start_arrowKeysBtn;
    QPushButton *stop_dualBtn;
    QPushButton *start_WASDBtn;
    QLabel *whichRunningLabel;
    QLabel *dual_headerLabel;
    QLabel *typingLabel;
    QWidget *invasionPage;
    QListWidget *invasionListWidget;
    QLabel *invasionCounterLabel;
    QWidget *doodlePage;
    QPushButton *start_trick1Btn;
    QPushButton *stop_trainingBtn;
    QPushButton *start_trick2Btn;
    QPushButton *grab_coordsBtn;
    QPushButton *start_trick3Btn;
    QPushButton *start_trick4Btn;
    QPushButton *start_trick5Btn;
    QPushButton *start_trick6Btn;
    QPushButton *start_trick7Btn;
    QLabel *current_trickLabel;
    QComboBox *labelBox;
    QComboBox *labelBox_2;
    QComboBox *labelBox_3;
    QComboBox *labelBox_4;
    QComboBox *labelBox_5;
    QComboBox *labelBox_6;
    QComboBox *labelBox_7;
    QLabel *resolutionLabel;
    QWidget *ToonHQWebsitePage;
    QPushButton *minBtn;
    QPushButton *xBtn;
    QFrame *titleBarFrame;
    QPushButton *homeBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(812, 700);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(900, 700));
        MainWindow->setWindowOpacity(1.000000000000000);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        contentFrame = new QFrame(centralwidget);
        contentFrame->setObjectName("contentFrame");
        contentFrame->setGeometry(QRect(0, 10, 801, 581));
        contentFrame->setStyleSheet(QString::fromUtf8("QFrame#contentFrame {\n"
"    background-color: #fdfdfd;\n"
"	border-radius: 12px;    \n"
"	border-width: 2px;\n"
"	background-clip: border;\n"
"    border-style: solid;\n"
"	padding: 1px;\n"
"    border-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0, stop:0 #3674f7, stop:0.878307 #2153bf);\n"
"}"));
        contentFrame->setFrameShape(QFrame::StyledPanel);
        contentFrame->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(contentFrame);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(-10, -20, 821, 701));
        loginIndex = new QWidget();
        loginIndex->setObjectName("loginIndex");
        password_input = new QLineEdit(loginIndex);
        password_input->setObjectName("password_input");
        password_input->setGeometry(QRect(140, 120, 591, 51));
        password_input->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        password_input->setEchoMode(QLineEdit::Password);
        username_input = new QLineEdit(loginIndex);
        username_input->setObjectName("username_input");
        username_input->setGeometry(QRect(140, 60, 591, 51));
        username_input->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        submitBtn = new QPushButton(loginIndex);
        submitBtn->setObjectName("submitBtn");
        submitBtn->setGeometry(QRect(320, 230, 191, 61));
        QFont font;
        font.setPointSize(16);
        submitBtn->setFont(font);
        submitBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(22, 135, 211, 255),\n"
"    		stop:1 rgba(1, 94, 158, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        storeLoginCheckbox = new QCheckBox(loginIndex);
        storeLoginCheckbox->setObjectName("storeLoginCheckbox");
        storeLoginCheckbox->setGeometry(QRect(20, 190, 391, 31));
        storeLoginCheckbox->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
"	color: #2153bf\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 25px;\n"
"    height: 25px;\n"
"	border: 2px solid;\n"
"	border-radius: 5px;\n"
"	border-color: #2c64dc;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0, stop:0 #2c64dc, stop:0.878307 #2356c4);\n"
"    image: url(config/icons/check-mark.png);\n"
"    background-position: center;\n"
"}\n"
"\n"
"QCheckBox::indicator::hover {\n"
"	background-color: #e1e8fa;\n"
"}\n"
"\n"
"QCheckBox::indicator::checked::hover\n"
"{\n"
"    background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0, stop:0 #5683e3, stop:0.878307 #4273dd);\n"
"\n"
"}"));
        password_label = new QLabel(loginIndex);
        password_label->setObjectName("password_label");
        password_label->setGeometry(QRect(20, 130, 141, 31));
        QFont font1;
        font1.setPointSize(18);
        password_label->setFont(font1);
        username_label = new QLabel(loginIndex);
        username_label->setObjectName("username_label");
        username_label->setGeometry(QRect(20, 70, 141, 31));
        username_label->setFont(font1);
        statusLabel = new QLabel(loginIndex);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(350, 290, 191, 41));
        stackedWidget->addWidget(loginIndex);
        appSelectIndex = new QWidget();
        appSelectIndex->setObjectName("appSelectIndex");
        DualToonContBtn = new QPushButton(appSelectIndex);
        DualToonContBtn->setObjectName("DualToonContBtn");
        DualToonContBtn->setGeometry(QRect(30, 260, 371, 61));
        DualToonContBtn->setFont(font);
        DualToonContBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #18de8c,\n"
"    		stop:1 #10a366\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #6defb9,\n"
"    		stop:1 #2eeb9c\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #0e8252,\n"
"    		stop:1 #07462c\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        AutoGroupSelectBtn = new QPushButton(appSelectIndex);
        AutoGroupSelectBtn->setObjectName("AutoGroupSelectBtn");
        AutoGroupSelectBtn->setGeometry(QRect(30, 180, 371, 61));
        AutoGroupSelectBtn->setFont(font);
        AutoGroupSelectBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        DoodleBtn = new QPushButton(appSelectIndex);
        DoodleBtn->setObjectName("DoodleBtn");
        DoodleBtn->setGeometry(QRect(420, 260, 371, 61));
        DoodleBtn->setFont(font);
        DoodleBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #33a5ea,\n"
"    		stop:1 #1378b5\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #8fcef4,\n"
"    		stop:1 #43aceb\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #116ea6,\n"
"    		stop:1 #43aceb\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        InvasionBtn = new QPushButton(appSelectIndex);
        InvasionBtn->setObjectName("InvasionBtn");
        InvasionBtn->setGeometry(QRect(30, 340, 761, 61));
        InvasionBtn->setFont(font);
        InvasionBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #58527d,\n"
"    		stop:1 #3e3957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #8b86af,\n"
"    		stop:1 #6a6195\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #2d2a3f,\n"
"    		stop:1 #121119\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        LaunchTTBtn = new QPushButton(appSelectIndex);
        LaunchTTBtn->setObjectName("LaunchTTBtn");
        LaunchTTBtn->setGeometry(QRect(30, 100, 761, 61));
        LaunchTTBtn->setFont(font);
        LaunchTTBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d84445,\n"
"    		stop:1 #a42223\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ea9899,\n"
"    		stop:1 #db5152\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #971f20,\n"
"    		stop:1 #501011 \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        ToonHQWebBtn = new QPushButton(appSelectIndex);
        ToonHQWebBtn->setObjectName("ToonHQWebBtn");
        ToonHQWebBtn->setGeometry(QRect(420, 180, 371, 61));
        ToonHQWebBtn->setFont(font);
        ToonHQWebBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #8c34eb,\n"
"    		stop:1 #601aab\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #c191f4,\n"
"    		stop:1 #9348e3\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #5a11a8,\n"
"    		stop:1 #2e0d52 \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        stackedWidget->addWidget(appSelectIndex);
        toonHQToonSelect = new QWidget();
        toonHQToonSelect->setObjectName("toonHQToonSelect");
        toonListWidget = new QListWidget(toonHQToonSelect);
        toonListWidget->setObjectName("toonListWidget");
        toonListWidget->setGeometry(QRect(20, 60, 781, 531));
        toonListWidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->addWidget(toonHQToonSelect);
        toonHQConnected = new QWidget();
        toonHQConnected->setObjectName("toonHQConnected");
        connectedToonLabel = new QLabel(toonHQConnected);
        connectedToonLabel->setObjectName("connectedToonLabel");
        connectedToonLabel->setGeometry(QRect(30, 150, 111, 101));
        disconnectToonBtn = new QPushButton(toonHQConnected);
        disconnectToonBtn->setObjectName("disconnectToonBtn");
        disconnectToonBtn->setGeometry(QRect(730, 170, 41, 41));
        disconnectToonBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: white;\n"
"	font-weight: bold;\n"
"    border: 1px solid #c21f02;\n"
"    border-radius: 20px;\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 #F82500, stop:1 #c21f02);\n"
"    padding: 3px;\n"
"    }\n"
"\n"
"QPushButton:hover {\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 #ff583a, stop:1 #fd3916);\n"
"	border-color: #fd3916;\n"
"    }\n"
"\n"
"QPushButton:pressed {\n"
"	background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 #ba1c00, stop:1 #911702);\n"
"	border-color: #911702;\n"
"    }\n"
""));
        bg_label_x = new QLabel(toonHQConnected);
        bg_label_x->setObjectName("bg_label_x");
        bg_label_x->setGeometry(QRect(30, 150, 771, 81));
        bg_label_x->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	border-image: url(config/icons/ttr_background.png) 0 0 0 0 repeat repeat;\n"
"	border-radius: 8px;\n"
"	qproperty-alignment: 'AlignCenter';\n"
"	color: #fdfdfd;\n"
"}"));
        labelToonHQ = new QLabel(toonHQConnected);
        labelToonHQ->setObjectName("labelToonHQ");
        labelToonHQ->setGeometry(QRect(330, 60, 191, 71));
        labelToonHQ->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-image: url(config/icons/ToonHQIcon.png) 0 0 0 0 stretch stretch;\n"
"}"));
        connectedInfoLabel = new QLabel(toonHQConnected);
        connectedInfoLabel->setObjectName("connectedInfoLabel");
        connectedInfoLabel->setGeometry(QRect(220, 150, 491, 81));
        connectedInfoLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	background-color: transparent;\n"
"	border-radius: 8px;\n"
"	text-align: center;\n"
"	color: #fdfdfd;\n"
"}"));
        stackedWidget->addWidget(toonHQConnected);
        bg_label_x->raise();
        connectedToonLabel->raise();
        labelToonHQ->raise();
        connectedInfoLabel->raise();
        disconnectToonBtn->raise();
        launchTTRPage = new QWidget();
        launchTTRPage->setObjectName("launchTTRPage");
        unameInput1 = new QLineEdit(launchTTRPage);
        unameInput1->setObjectName("unameInput1");
        unameInput1->setGeometry(QRect(260, 80, 411, 41));
        unameInput1->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        uname_label_1 = new QLabel(launchTTRPage);
        uname_label_1->setObjectName("uname_label_1");
        uname_label_1->setGeometry(QRect(60, 80, 141, 31));
        uname_label_1->setFont(font1);
        pwordInput1 = new QLineEdit(launchTTRPage);
        pwordInput1->setObjectName("pwordInput1");
        pwordInput1->setGeometry(QRect(260, 130, 411, 41));
        pwordInput1->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        pword_label_1 = new QLabel(launchTTRPage);
        pword_label_1->setObjectName("pword_label_1");
        pword_label_1->setGeometry(QRect(60, 130, 141, 31));
        pword_label_1->setFont(font1);
        aliasInput1 = new QLineEdit(launchTTRPage);
        aliasInput1->setObjectName("aliasInput1");
        aliasInput1->setGeometry(QRect(260, 180, 411, 41));
        aliasInput1->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        alias_label_1 = new QLabel(launchTTRPage);
        alias_label_1->setObjectName("alias_label_1");
        alias_label_1->setGeometry(QRect(60, 180, 191, 31));
        alias_label_1->setFont(font1);
        addClient_btn1 = new QPushButton(launchTTRPage);
        addClient_btn1->setObjectName("addClient_btn1");
        addClient_btn1->setGeometry(QRect(300, 110, 61, 61));
        addClient_btn1->setFont(font);
        addClient_btn1->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        addClient_label1 = new QLabel(launchTTRPage);
        addClient_label1->setObjectName("addClient_label1");
        addClient_label1->setGeometry(QRect(60, 120, 221, 41));
        addClient_label1->setFont(font1);
        save_btn1 = new QPushButton(launchTTRPage);
        save_btn1->setObjectName("save_btn1");
        save_btn1->setGeometry(QRect(690, 120, 61, 61));
        save_btn1->setFont(font);
        save_btn1->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        edit_btn1 = new QPushButton(launchTTRPage);
        edit_btn1->setObjectName("edit_btn1");
        edit_btn1->setGeometry(QRect(550, 60, 61, 61));
        edit_btn1->setFont(font);
        edit_btn1->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ffd900,\n"
"    		stop:1 #c4a704\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ffe866,\n"
"    		stop:1 #fbdd33\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #998200,\n"
"    		stop:1 #605202\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        launch_label1 = new QLabel(launchTTRPage);
        launch_label1->setObjectName("launch_label1");
        launch_label1->setGeometry(QRect(40, 70, 411, 41));
        launch_label1->setFont(font1);
        remove_bt1 = new QPushButton(launchTTRPage);
        remove_bt1->setObjectName("remove_bt1");
        remove_bt1->setGeometry(QRect(630, 60, 61, 61));
        remove_bt1->setFont(font);
        remove_bt1->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d84445,\n"
"    		stop:1 #a42223\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ea9899,\n"
"    		stop:1 #db5152\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #971f20,\n"
"    		stop:1 #501011\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        save_btn1_noInc = new QPushButton(launchTTRPage);
        save_btn1_noInc->setObjectName("save_btn1_noInc");
        save_btn1_noInc->setGeometry(QRect(690, 120, 61, 61));
        save_btn1_noInc->setFont(font);
        save_btn1_noInc->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        launch_btn1 = new QPushButton(launchTTRPage);
        launch_btn1->setObjectName("launch_btn1");
        launch_btn1->setGeometry(QRect(470, 60, 61, 61));
        launch_btn1->setFont(font);
        launch_btn1->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        aliasInput2 = new QLineEdit(launchTTRPage);
        aliasInput2->setObjectName("aliasInput2");
        aliasInput2->setGeometry(QRect(260, 360, 411, 41));
        aliasInput2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        addClient_btn2 = new QPushButton(launchTTRPage);
        addClient_btn2->setObjectName("addClient_btn2");
        addClient_btn2->setGeometry(QRect(300, 290, 61, 61));
        addClient_btn2->setFont(font);
        addClient_btn2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        pwordInput2 = new QLineEdit(launchTTRPage);
        pwordInput2->setObjectName("pwordInput2");
        pwordInput2->setGeometry(QRect(260, 310, 411, 41));
        pwordInput2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        alias_label_2 = new QLabel(launchTTRPage);
        alias_label_2->setObjectName("alias_label_2");
        alias_label_2->setGeometry(QRect(60, 360, 191, 31));
        alias_label_2->setFont(font1);
        unameInput2 = new QLineEdit(launchTTRPage);
        unameInput2->setObjectName("unameInput2");
        unameInput2->setGeometry(QRect(260, 260, 411, 41));
        unameInput2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        pword_label_2 = new QLabel(launchTTRPage);
        pword_label_2->setObjectName("pword_label_2");
        pword_label_2->setGeometry(QRect(60, 310, 141, 31));
        pword_label_2->setFont(font1);
        launch_btn2 = new QPushButton(launchTTRPage);
        launch_btn2->setObjectName("launch_btn2");
        launch_btn2->setGeometry(QRect(470, 240, 61, 61));
        launch_btn2->setFont(font);
        launch_btn2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        save_btn2 = new QPushButton(launchTTRPage);
        save_btn2->setObjectName("save_btn2");
        save_btn2->setGeometry(QRect(690, 300, 61, 61));
        save_btn2->setFont(font);
        save_btn2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        edit_btn2 = new QPushButton(launchTTRPage);
        edit_btn2->setObjectName("edit_btn2");
        edit_btn2->setGeometry(QRect(550, 240, 61, 61));
        edit_btn2->setFont(font);
        edit_btn2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ffd900,\n"
"    		stop:1 #c4a704\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ffe866,\n"
"    		stop:1 #fbdd33\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #998200,\n"
"    		stop:1 #605202\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        remove_bt2 = new QPushButton(launchTTRPage);
        remove_bt2->setObjectName("remove_bt2");
        remove_bt2->setGeometry(QRect(630, 240, 61, 61));
        remove_bt2->setFont(font);
        remove_bt2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d84445,\n"
"    		stop:1 #a42223\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ea9899,\n"
"    		stop:1 #db5152\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #971f20,\n"
"    		stop:1 #501011\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        addClient_label2 = new QLabel(launchTTRPage);
        addClient_label2->setObjectName("addClient_label2");
        addClient_label2->setGeometry(QRect(60, 300, 221, 41));
        addClient_label2->setFont(font1);
        uname_label_2 = new QLabel(launchTTRPage);
        uname_label_2->setObjectName("uname_label_2");
        uname_label_2->setGeometry(QRect(60, 260, 141, 31));
        uname_label_2->setFont(font1);
        save_btn2_noInc = new QPushButton(launchTTRPage);
        save_btn2_noInc->setObjectName("save_btn2_noInc");
        save_btn2_noInc->setGeometry(QRect(690, 300, 61, 61));
        save_btn2_noInc->setFont(font);
        save_btn2_noInc->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        launch_label2 = new QLabel(launchTTRPage);
        launch_label2->setObjectName("launch_label2");
        launch_label2->setGeometry(QRect(40, 250, 411, 41));
        launch_label2->setFont(font1);
        save_btn3 = new QPushButton(launchTTRPage);
        save_btn3->setObjectName("save_btn3");
        save_btn3->setGeometry(QRect(690, 480, 61, 61));
        save_btn3->setFont(font);
        save_btn3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        launch_btn3 = new QPushButton(launchTTRPage);
        launch_btn3->setObjectName("launch_btn3");
        launch_btn3->setGeometry(QRect(470, 420, 61, 61));
        launch_btn3->setFont(font);
        launch_btn3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        addClient_btn3 = new QPushButton(launchTTRPage);
        addClient_btn3->setObjectName("addClient_btn3");
        addClient_btn3->setGeometry(QRect(300, 470, 61, 61));
        addClient_btn3->setFont(font);
        addClient_btn3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        alias_label_3 = new QLabel(launchTTRPage);
        alias_label_3->setObjectName("alias_label_3");
        alias_label_3->setGeometry(QRect(60, 540, 191, 31));
        alias_label_3->setFont(font1);
        launch_label3 = new QLabel(launchTTRPage);
        launch_label3->setObjectName("launch_label3");
        launch_label3->setGeometry(QRect(40, 430, 411, 41));
        launch_label3->setFont(font1);
        unameInput3 = new QLineEdit(launchTTRPage);
        unameInput3->setObjectName("unameInput3");
        unameInput3->setGeometry(QRect(260, 440, 411, 41));
        unameInput3->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        pwordInput3 = new QLineEdit(launchTTRPage);
        pwordInput3->setObjectName("pwordInput3");
        pwordInput3->setGeometry(QRect(260, 490, 411, 41));
        pwordInput3->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        addClient_label3 = new QLabel(launchTTRPage);
        addClient_label3->setObjectName("addClient_label3");
        addClient_label3->setGeometry(QRect(60, 480, 221, 41));
        addClient_label3->setFont(font1);
        aliasInput3 = new QLineEdit(launchTTRPage);
        aliasInput3->setObjectName("aliasInput3");
        aliasInput3->setGeometry(QRect(260, 540, 411, 41));
        aliasInput3->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        remove_bt3 = new QPushButton(launchTTRPage);
        remove_bt3->setObjectName("remove_bt3");
        remove_bt3->setGeometry(QRect(630, 420, 61, 61));
        remove_bt3->setFont(font);
        remove_bt3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d84445,\n"
"    		stop:1 #a42223\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ea9899,\n"
"    		stop:1 #db5152\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #971f20,\n"
"    		stop:1 #501011\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        uname_label_3 = new QLabel(launchTTRPage);
        uname_label_3->setObjectName("uname_label_3");
        uname_label_3->setGeometry(QRect(60, 440, 141, 31));
        uname_label_3->setFont(font1);
        save_btn3_noInc = new QPushButton(launchTTRPage);
        save_btn3_noInc->setObjectName("save_btn3_noInc");
        save_btn3_noInc->setGeometry(QRect(690, 480, 61, 61));
        save_btn3_noInc->setFont(font);
        save_btn3_noInc->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #32a852,\n"
"    		stop:1 #1e7035\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #56cd76,\n"
"    		stop:1 #31b957\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #257e3d\n"
"    		stop:1 #175428\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        edit_btn3 = new QPushButton(launchTTRPage);
        edit_btn3->setObjectName("edit_btn3");
        edit_btn3->setGeometry(QRect(550, 420, 61, 61));
        edit_btn3->setFont(font);
        edit_btn3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ffd900,\n"
"    		stop:1 #c4a704\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ffe866,\n"
"    		stop:1 #fbdd33\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #998200,\n"
"    		stop:1 #605202\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        pword_label_3 = new QLabel(launchTTRPage);
        pword_label_3->setObjectName("pword_label_3");
        pword_label_3->setGeometry(QRect(60, 490, 141, 31));
        pword_label_3->setFont(font1);
        status_label_1 = new QLabel(launchTTRPage);
        status_label_1->setObjectName("status_label_1");
        status_label_1->setGeometry(QRect(40, 200, 711, 31));
        status_label_1->setFont(font1);
        status_label_1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: red;\n"
"    qproperty-alignment: 'AlignCenter';\n"
"}"));
        status_label_2 = new QLabel(launchTTRPage);
        status_label_2->setObjectName("status_label_2");
        status_label_2->setGeometry(QRect(50, 380, 701, 31));
        status_label_2->setFont(font1);
        status_label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: red;\n"
"    qproperty-alignment: 'AlignCenter';\n"
"}"));
        status_label_3 = new QLabel(launchTTRPage);
        status_label_3->setObjectName("status_label_3");
        status_label_3->setGeometry(QRect(50, 560, 701, 31));
        status_label_3->setFont(font1);
        status_label_3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: red;\n"
"    qproperty-alignment: 'AlignCenter';\n"
"}"));
        manual_loc_btnEDIT1 = new QPushButton(launchTTRPage);
        manual_loc_btnEDIT1->setObjectName("manual_loc_btnEDIT1");
        manual_loc_btnEDIT1->setGeometry(QRect(630, 130, 61, 61));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        manual_loc_btnEDIT1->setFont(font2);
        manual_loc_btnEDIT1->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #edc868,\n"
"    		stop:1 #cfad57\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #f8e9c3,\n"
"    		stop:1 #e6d4a6\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d6a119,\n"
"    		stop:1 #95772b\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        fileLocation_input1 = new QLineEdit(launchTTRPage);
        fileLocation_input1->setObjectName("fileLocation_input1");
        fileLocation_input1->setGeometry(QRect(250, 140, 371, 41));
        fileLocation_input1->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        installLoc_label1 = new QLabel(launchTTRPage);
        installLoc_label1->setObjectName("installLoc_label1");
        installLoc_label1->setGeometry(QRect(40, 140, 221, 41));
        installLoc_label1->setFont(font1);
        installLoc_label2 = new QLabel(launchTTRPage);
        installLoc_label2->setObjectName("installLoc_label2");
        installLoc_label2->setGeometry(QRect(50, 320, 221, 41));
        installLoc_label2->setFont(font1);
        fileLocation_input2 = new QLineEdit(launchTTRPage);
        fileLocation_input2->setObjectName("fileLocation_input2");
        fileLocation_input2->setGeometry(QRect(250, 320, 371, 41));
        fileLocation_input2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        manual_loc_btnEDIT2 = new QPushButton(launchTTRPage);
        manual_loc_btnEDIT2->setObjectName("manual_loc_btnEDIT2");
        manual_loc_btnEDIT2->setGeometry(QRect(630, 310, 61, 61));
        manual_loc_btnEDIT2->setFont(font2);
        manual_loc_btnEDIT2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #edc868,\n"
"    		stop:1 #cfad57\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #f8e9c3,\n"
"    		stop:1 #e6d4a6\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d6a119,\n"
"    		stop:1 #95772b\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        fileLocation_input3 = new QLineEdit(launchTTRPage);
        fileLocation_input3->setObjectName("fileLocation_input3");
        fileLocation_input3->setGeometry(QRect(250, 500, 371, 41));
        fileLocation_input3->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #8e918f;\n"
"	border-radius: 10px;\n"
"	padding: 6px;\n"
"	background-color: #fdfdfd;\n"
"	color: black;\n"
"}"));
        manual_loc_btnEDIT3 = new QPushButton(launchTTRPage);
        manual_loc_btnEDIT3->setObjectName("manual_loc_btnEDIT3");
        manual_loc_btnEDIT3->setGeometry(QRect(630, 490, 61, 61));
        manual_loc_btnEDIT3->setFont(font2);
        manual_loc_btnEDIT3->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #edc868,\n"
"    		stop:1 #cfad57\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"	font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #f8e9c3,\n"
"    		stop:1 #e6d4a6\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d6a119,\n"
"    		stop:1 #95772b\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        installLoc_label3 = new QLabel(launchTTRPage);
        installLoc_label3->setObjectName("installLoc_label3");
        installLoc_label3->setGeometry(QRect(50, 500, 221, 41));
        installLoc_label3->setFont(font1);
        stackedWidget->addWidget(launchTTRPage);
        dualToonPage = new QWidget();
        dualToonPage->setObjectName("dualToonPage");
        start_arrowKeysBtn = new QPushButton(dualToonPage);
        start_arrowKeysBtn->setObjectName("start_arrowKeysBtn");
        start_arrowKeysBtn->setGeometry(QRect(100, 190, 251, 91));
        start_arrowKeysBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 20px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	color: white\n"
"}"));
        stop_dualBtn = new QPushButton(dualToonPage);
        stop_dualBtn->setObjectName("stop_dualBtn");
        stop_dualBtn->setGeometry(QRect(500, 200, 201, 181));
        stop_dualBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d84445,\n"
"    		stop:1 #a42223\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 25px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ea9899,\n"
"    		stop:1 #db5152\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #971f20,\n"
"    		stop:1 #501011\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	color: white\n"
"}"));
        start_WASDBtn = new QPushButton(dualToonPage);
        start_WASDBtn->setObjectName("start_WASDBtn");
        start_WASDBtn->setGeometry(QRect(100, 290, 251, 91));
        start_WASDBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 20px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	color: white\n"
"}"));
        whichRunningLabel = new QLabel(dualToonPage);
        whichRunningLabel->setObjectName("whichRunningLabel");
        whichRunningLabel->setGeometry(QRect(120, 400, 571, 41));
        whichRunningLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    qproperty-alignment: 'AlignCenter';\n"
"	color: gray;\n"
"}"));
        dual_headerLabel = new QLabel(dualToonPage);
        dual_headerLabel->setObjectName("dual_headerLabel");
        dual_headerLabel->setGeometry(QRect(70, 60, 681, 41));
        dual_headerLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    qproperty-alignment: 'AlignCenter';\n"
"	color: #2153bf;\n"
"}"));
        typingLabel = new QLabel(dualToonPage);
        typingLabel->setObjectName("typingLabel");
        typingLabel->setGeometry(QRect(120, 470, 571, 41));
        typingLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    qproperty-alignment: 'AlignCenter';\n"
"	color: red;\n"
"}"));
        stackedWidget->addWidget(dualToonPage);
        invasionPage = new QWidget();
        invasionPage->setObjectName("invasionPage");
        invasionListWidget = new QListWidget(invasionPage);
        invasionListWidget->setObjectName("invasionListWidget");
        invasionListWidget->setGeometry(QRect(20, 60, 781, 531));
        invasionListWidget->setStyleSheet(QString::fromUtf8(""));
        invasionCounterLabel = new QLabel(invasionPage);
        invasionCounterLabel->setObjectName("invasionCounterLabel");
        invasionCounterLabel->setGeometry(QRect(750, 550, 31, 31));
        invasionCounterLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"	color: red;\n"
"	font-weight: bold;\n"
"}"));
        stackedWidget->addWidget(invasionPage);
        doodlePage = new QWidget();
        doodlePage->setObjectName("doodlePage");
        start_trick1Btn = new QPushButton(doodlePage);
        start_trick1Btn->setObjectName("start_trick1Btn");
        start_trick1Btn->setGeometry(QRect(70, 80, 161, 61));
        start_trick1Btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        stop_trainingBtn = new QPushButton(doodlePage);
        stop_trainingBtn->setObjectName("stop_trainingBtn");
        stop_trainingBtn->setGeometry(QRect(540, 270, 181, 81));
        stop_trainingBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #d84445,\n"
"    		stop:1 #a42223\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ea9899,\n"
"    		stop:1 #db5152\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #971f20,\n"
"    		stop:1 #501011\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        start_trick2Btn = new QPushButton(doodlePage);
        start_trick2Btn->setObjectName("start_trick2Btn");
        start_trick2Btn->setGeometry(QRect(70, 150, 161, 61));
        start_trick2Btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        grab_coordsBtn = new QPushButton(doodlePage);
        grab_coordsBtn->setObjectName("grab_coordsBtn");
        grab_coordsBtn->setGeometry(QRect(580, 100, 111, 81));
        grab_coordsBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3deb34,\n"
"    		stop:1 #23ad1c\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #ea9899,\n"
"    		stop:1 #db5152\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #971f20,\n"
"    		stop:1 #501011\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        start_trick3Btn = new QPushButton(doodlePage);
        start_trick3Btn->setObjectName("start_trick3Btn");
        start_trick3Btn->setGeometry(QRect(70, 220, 161, 61));
        start_trick3Btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        start_trick4Btn = new QPushButton(doodlePage);
        start_trick4Btn->setObjectName("start_trick4Btn");
        start_trick4Btn->setGeometry(QRect(70, 290, 161, 61));
        start_trick4Btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        start_trick5Btn = new QPushButton(doodlePage);
        start_trick5Btn->setObjectName("start_trick5Btn");
        start_trick5Btn->setGeometry(QRect(70, 360, 161, 61));
        start_trick5Btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        start_trick6Btn = new QPushButton(doodlePage);
        start_trick6Btn->setObjectName("start_trick6Btn");
        start_trick6Btn->setGeometry(QRect(70, 430, 161, 61));
        start_trick6Btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        start_trick7Btn = new QPushButton(doodlePage);
        start_trick7Btn->setObjectName("start_trick7Btn");
        start_trick7Btn->setGeometry(QRect(70, 500, 161, 61));
        start_trick7Btn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3768d8,\n"
"    		stop:1 #1f469f\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(29, 150, 231, 255),\n"
"    		stop:1 rgba(1, 115, 193, 255)\n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color: qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 rgba(20, 121, 190, 255),\n"
"    		stop:1 rgba(1, 85, 142, 255) \n"
"	);\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: white\n"
"}"));
        current_trickLabel = new QLabel(doodlePage);
        current_trickLabel->setObjectName("current_trickLabel");
        current_trickLabel->setGeometry(QRect(470, 370, 331, 31));
        current_trickLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    qproperty-alignment: 'AlignCenter';\n"
"	color: gray;\n"
"}"));
        labelBox = new QComboBox(doodlePage);
        labelBox->addItem(QString());
        labelBox->addItem(QString());
        labelBox->addItem(QString());
        labelBox->addItem(QString());
        labelBox->addItem(QString());
        labelBox->addItem(QString());
        labelBox->addItem(QString());
        labelBox->addItem(QString());
        labelBox->setObjectName("labelBox");
        labelBox->setGeometry(QRect(260, 90, 141, 41));
        labelBox->setStyleSheet(QString::fromUtf8("/* 1. Main ComboBox Container */\n"
"QComboBox {\n"
"    border: 2px solid #008BF8;\n"
"    border-radius: 6px;\n"
"    padding: 4px 10px;\n"
"    min-width: 6em;\n"
"    background-color:  qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3792d8,\n"
"    		stop:1 #2276b5\n"
"    );\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Main container state variations */\n"
"QComboBox:editable {\n"
"    background: #008BF8;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 2px solid #295ed5;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0.5, y1:0,\n"
"        x2:0.5, y2:1,\n"
"        stop:0 #5f86e0,\n"
"        stop:1 #295ed5\n"
"    );\n"
"}\n"
"\n"
"/* 2. The Drop-Down Arrow Button Wrapper */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
""
                        "    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: white;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 4px;\n"
"    border-bottom-right-radius: 4px;\n"
"}\n"
"\n"
"/* The actual arrow icon inside the wrapper */\n"
"QComboBox::down-arrow {\n"
"    image: url(config/icons/arrow_down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* Shift arrow slightly down when active */\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"/* 3. The Popup Menu List View */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #295ed5;\n"
"    border-top: none;\n"
"    background-color: #008BF8;\n"
"    color: #ffffff;\n"
"    selection-background-color: #295ed5;\n"
"    selection-color: #ffffff;\n"
"    outline: 0px;\n"
"}\n"
"\n"
"/* Individual list items */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 30px;\n"
"    padding-left: 10px;\n"
"}\n"
"\n"
"/* Highlighted/Hovered list item */\n"
"QComboBox"));
        labelBox_2 = new QComboBox(doodlePage);
        labelBox_2->addItem(QString());
        labelBox_2->addItem(QString());
        labelBox_2->addItem(QString());
        labelBox_2->addItem(QString());
        labelBox_2->addItem(QString());
        labelBox_2->addItem(QString());
        labelBox_2->addItem(QString());
        labelBox_2->addItem(QString());
        labelBox_2->setObjectName("labelBox_2");
        labelBox_2->setGeometry(QRect(260, 160, 141, 41));
        labelBox_2->setStyleSheet(QString::fromUtf8("/* 1. Main ComboBox Container */\n"
"QComboBox {\n"
"    border: 2px solid #008BF8;\n"
"    border-radius: 6px;\n"
"    padding: 4px 10px;\n"
"    min-width: 6em;\n"
"    background-color:  qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3792d8,\n"
"    		stop:1 #2276b5\n"
"    );\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Main container state variations */\n"
"QComboBox:editable {\n"
"    background: #008BF8;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 2px solid #295ed5;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0.5, y1:0,\n"
"        x2:0.5, y2:1,\n"
"        stop:0 #5f86e0,\n"
"        stop:1 #295ed5\n"
"    );\n"
"}\n"
"\n"
"/* 2. The Drop-Down Arrow Button Wrapper */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
""
                        "    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: white;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 4px;\n"
"    border-bottom-right-radius: 4px;\n"
"}\n"
"\n"
"/* The actual arrow icon inside the wrapper */\n"
"QComboBox::down-arrow {\n"
"    image: url(config/icons/arrow_down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* Shift arrow slightly down when active */\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"/* 3. The Popup Menu List View */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #295ed5;\n"
"    border-top: none;\n"
"    background-color: #008BF8;\n"
"    color: #ffffff;\n"
"    selection-background-color: #295ed5;\n"
"    selection-color: #ffffff;\n"
"    outline: 0px;\n"
"}\n"
"\n"
"/* Individual list items */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 30px;\n"
"    padding-left: 10px;\n"
"}\n"
"\n"
"/* Highlighted/Hovered list item */\n"
"QComboBox"));
        labelBox_3 = new QComboBox(doodlePage);
        labelBox_3->addItem(QString());
        labelBox_3->addItem(QString());
        labelBox_3->addItem(QString());
        labelBox_3->addItem(QString());
        labelBox_3->addItem(QString());
        labelBox_3->addItem(QString());
        labelBox_3->addItem(QString());
        labelBox_3->addItem(QString());
        labelBox_3->setObjectName("labelBox_3");
        labelBox_3->setGeometry(QRect(260, 230, 141, 41));
        labelBox_3->setStyleSheet(QString::fromUtf8("/* 1. Main ComboBox Container */\n"
"QComboBox {\n"
"    border: 2px solid #008BF8;\n"
"    border-radius: 6px;\n"
"    padding: 4px 10px;\n"
"    min-width: 6em;\n"
"    background-color:  qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3792d8,\n"
"    		stop:1 #2276b5\n"
"    );\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Main container state variations */\n"
"QComboBox:editable {\n"
"    background: #008BF8;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 2px solid #295ed5;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0.5, y1:0,\n"
"        x2:0.5, y2:1,\n"
"        stop:0 #5f86e0,\n"
"        stop:1 #295ed5\n"
"    );\n"
"}\n"
"\n"
"/* 2. The Drop-Down Arrow Button Wrapper */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
""
                        "    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: white;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 4px;\n"
"    border-bottom-right-radius: 4px;\n"
"}\n"
"\n"
"/* The actual arrow icon inside the wrapper */\n"
"QComboBox::down-arrow {\n"
"    image: url(config/icons/arrow_down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* Shift arrow slightly down when active */\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"/* 3. The Popup Menu List View */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #295ed5;\n"
"    border-top: none;\n"
"    background-color: #008BF8;\n"
"    color: #ffffff;\n"
"    selection-background-color: #295ed5;\n"
"    selection-color: #ffffff;\n"
"    outline: 0px;\n"
"}\n"
"\n"
"/* Individual list items */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 30px;\n"
"    padding-left: 10px;\n"
"}\n"
"\n"
"/* Highlighted/Hovered list item */\n"
"QComboBox"));
        labelBox_4 = new QComboBox(doodlePage);
        labelBox_4->addItem(QString());
        labelBox_4->addItem(QString());
        labelBox_4->addItem(QString());
        labelBox_4->addItem(QString());
        labelBox_4->addItem(QString());
        labelBox_4->addItem(QString());
        labelBox_4->addItem(QString());
        labelBox_4->addItem(QString());
        labelBox_4->setObjectName("labelBox_4");
        labelBox_4->setGeometry(QRect(260, 300, 141, 41));
        labelBox_4->setStyleSheet(QString::fromUtf8("/* 1. Main ComboBox Container */\n"
"QComboBox {\n"
"    border: 2px solid #008BF8;\n"
"    border-radius: 6px;\n"
"    padding: 4px 10px;\n"
"    min-width: 6em;\n"
"    background-color:  qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3792d8,\n"
"    		stop:1 #2276b5\n"
"    );\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Main container state variations */\n"
"QComboBox:editable {\n"
"    background: #008BF8;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 2px solid #295ed5;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0.5, y1:0,\n"
"        x2:0.5, y2:1,\n"
"        stop:0 #5f86e0,\n"
"        stop:1 #295ed5\n"
"    );\n"
"}\n"
"\n"
"/* 2. The Drop-Down Arrow Button Wrapper */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
""
                        "    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: white;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 4px;\n"
"    border-bottom-right-radius: 4px;\n"
"}\n"
"\n"
"/* The actual arrow icon inside the wrapper */\n"
"QComboBox::down-arrow {\n"
"    image: url(config/icons/arrow_down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* Shift arrow slightly down when active */\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"/* 3. The Popup Menu List View */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #295ed5;\n"
"    border-top: none;\n"
"    background-color: #008BF8;\n"
"    color: #ffffff;\n"
"    selection-background-color: #295ed5;\n"
"    selection-color: #ffffff;\n"
"    outline: 0px;\n"
"}\n"
"\n"
"/* Individual list items */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 30px;\n"
"    padding-left: 10px;\n"
"}\n"
"\n"
"/* Highlighted/Hovered list item */\n"
"QComboBox"));
        labelBox_5 = new QComboBox(doodlePage);
        labelBox_5->addItem(QString());
        labelBox_5->addItem(QString());
        labelBox_5->addItem(QString());
        labelBox_5->addItem(QString());
        labelBox_5->addItem(QString());
        labelBox_5->addItem(QString());
        labelBox_5->addItem(QString());
        labelBox_5->addItem(QString());
        labelBox_5->setObjectName("labelBox_5");
        labelBox_5->setGeometry(QRect(260, 370, 141, 41));
        labelBox_5->setStyleSheet(QString::fromUtf8("/* 1. Main ComboBox Container */\n"
"QComboBox {\n"
"    border: 2px solid #008BF8;\n"
"    border-radius: 6px;\n"
"    padding: 4px 10px;\n"
"    min-width: 6em;\n"
"    background-color:  qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3792d8,\n"
"    		stop:1 #2276b5\n"
"    );\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Main container state variations */\n"
"QComboBox:editable {\n"
"    background: #008BF8;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 2px solid #295ed5;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0.5, y1:0,\n"
"        x2:0.5, y2:1,\n"
"        stop:0 #5f86e0,\n"
"        stop:1 #295ed5\n"
"    );\n"
"}\n"
"\n"
"/* 2. The Drop-Down Arrow Button Wrapper */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
""
                        "    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: white;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 4px;\n"
"    border-bottom-right-radius: 4px;\n"
"}\n"
"\n"
"/* The actual arrow icon inside the wrapper */\n"
"QComboBox::down-arrow {\n"
"    image: url(config/icons/arrow_down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* Shift arrow slightly down when active */\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"/* 3. The Popup Menu List View */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #295ed5;\n"
"    border-top: none;\n"
"    background-color: #008BF8;\n"
"    color: #ffffff;\n"
"    selection-background-color: #295ed5;\n"
"    selection-color: #ffffff;\n"
"    outline: 0px;\n"
"}\n"
"\n"
"/* Individual list items */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 30px;\n"
"    padding-left: 10px;\n"
"}\n"
"\n"
"/* Highlighted/Hovered list item */\n"
"QComboBox"));
        labelBox_6 = new QComboBox(doodlePage);
        labelBox_6->addItem(QString());
        labelBox_6->addItem(QString());
        labelBox_6->addItem(QString());
        labelBox_6->addItem(QString());
        labelBox_6->addItem(QString());
        labelBox_6->addItem(QString());
        labelBox_6->addItem(QString());
        labelBox_6->addItem(QString());
        labelBox_6->setObjectName("labelBox_6");
        labelBox_6->setGeometry(QRect(260, 440, 141, 41));
        labelBox_6->setStyleSheet(QString::fromUtf8("/* 1. Main ComboBox Container */\n"
"QComboBox {\n"
"    border: 2px solid #008BF8;\n"
"    border-radius: 6px;\n"
"    padding: 4px 10px;\n"
"    min-width: 6em;\n"
"    background-color:  qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3792d8,\n"
"    		stop:1 #2276b5\n"
"    );\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Main container state variations */\n"
"QComboBox:editable {\n"
"    background: #008BF8;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 2px solid #295ed5;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0.5, y1:0,\n"
"        x2:0.5, y2:1,\n"
"        stop:0 #5f86e0,\n"
"        stop:1 #295ed5\n"
"    );\n"
"}\n"
"\n"
"/* 2. The Drop-Down Arrow Button Wrapper */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
""
                        "    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: white;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 4px;\n"
"    border-bottom-right-radius: 4px;\n"
"}\n"
"\n"
"/* The actual arrow icon inside the wrapper */\n"
"QComboBox::down-arrow {\n"
"    image: url(config/icons/arrow_down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* Shift arrow slightly down when active */\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"/* 3. The Popup Menu List View */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #295ed5;\n"
"    border-top: none;\n"
"    background-color: #008BF8;\n"
"    color: #ffffff;\n"
"    selection-background-color: #295ed5;\n"
"    selection-color: #ffffff;\n"
"    outline: 0px;\n"
"}\n"
"\n"
"/* Individual list items */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 30px;\n"
"    padding-left: 10px;\n"
"}\n"
"\n"
"/* Highlighted/Hovered list item */\n"
"QComboBox"));
        labelBox_7 = new QComboBox(doodlePage);
        labelBox_7->addItem(QString());
        labelBox_7->addItem(QString());
        labelBox_7->addItem(QString());
        labelBox_7->addItem(QString());
        labelBox_7->addItem(QString());
        labelBox_7->addItem(QString());
        labelBox_7->addItem(QString());
        labelBox_7->addItem(QString());
        labelBox_7->setObjectName("labelBox_7");
        labelBox_7->setGeometry(QRect(260, 510, 141, 41));
        labelBox_7->setStyleSheet(QString::fromUtf8("/* 1. Main ComboBox Container */\n"
"QComboBox {\n"
"    border: 2px solid #008BF8;\n"
"    border-radius: 6px;\n"
"    padding: 4px 10px;\n"
"    min-width: 6em;\n"
"    background-color:  qlineargradient(\n"
"    		spread:pad,\n"
"    		x1:0.5, y1:0,\n"
"    		x2:0.5, y2:1,\n"
"    		stop:0 #3792d8,\n"
"    		stop:1 #2276b5\n"
"    );\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Main container state variations */\n"
"QComboBox:editable {\n"
"    background: #008BF8;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 2px solid #295ed5;\n"
"}\n"
"\n"
"QComboBox:on {\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"    background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0.5, y1:0,\n"
"        x2:0.5, y2:1,\n"
"        stop:0 #5f86e0,\n"
"        stop:1 #295ed5\n"
"    );\n"
"}\n"
"\n"
"/* 2. The Drop-Down Arrow Button Wrapper */\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
""
                        "    width: 25px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: white;\n"
"    border-left-style: solid;\n"
"    border-top-right-radius: 4px;\n"
"    border-bottom-right-radius: 4px;\n"
"}\n"
"\n"
"/* The actual arrow icon inside the wrapper */\n"
"QComboBox::down-arrow {\n"
"    image: url(config/icons/arrow_down.png);\n"
"    width: 12px;\n"
"    height: 12px;\n"
"}\n"
"\n"
"/* Shift arrow slightly down when active */\n"
"QComboBox::down-arrow:on {\n"
"    top: 1px;\n"
"    left: 1px;\n"
"}\n"
"\n"
"/* 3. The Popup Menu List View */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #295ed5;\n"
"    border-top: none;\n"
"    background-color: #008BF8;\n"
"    color: #ffffff;\n"
"    selection-background-color: #295ed5;\n"
"    selection-color: #ffffff;\n"
"    outline: 0px;\n"
"}\n"
"\n"
"/* Individual list items */\n"
"QComboBox QAbstractItemView::item {\n"
"    min-height: 30px;\n"
"    padding-left: 10px;\n"
"}\n"
"\n"
"/* Highlighted/Hovered list item */\n"
"QComboBox"));
        resolutionLabel = new QLabel(doodlePage);
        resolutionLabel->setObjectName("resolutionLabel");
        resolutionLabel->setGeometry(QRect(420, 550, 381, 41));
        resolutionLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    qproperty-alignment: 'AlignCenter';\n"
"	color: orange\n"
"}"));
        stackedWidget->addWidget(doodlePage);
        ToonHQWebsitePage = new QWidget();
        ToonHQWebsitePage->setObjectName("ToonHQWebsitePage");
        stackedWidget->addWidget(ToonHQWebsitePage);
        minBtn = new QPushButton(centralwidget);
        minBtn->setObjectName("minBtn");
        minBtn->setGeometry(QRect(700, 0, 41, 41));
        minBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: #ce9801;\n"
"	font-weight: bold;\n"
"	text-align: center;\n"
"    border: 1px solid #e5a901;\n"
"    border-radius: 20px;\n"
"    border-style: outset;\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 #f8e931, stop:1 #fec421);\n"
"    }\n"
"\n"
"QPushButton:hover {\n"
"    background: qradialgradient(\n"
"        cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,\n"
"        radius: 1.35, stop: 0 #f9ed5a, stop: 1 #fed04d\n"
"        );\n"
"    }\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"    background: qradialgradient(\n"
"        cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,\n"
"        radius: 1.35, stop: 0 #e6d508, stop: 1 #e5a901\n"
"        );\n"
"    }\n"
""));
        xBtn = new QPushButton(centralwidget);
        xBtn->setObjectName("xBtn");
        xBtn->setGeometry(QRect(750, 0, 41, 41));
        xBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: #d83b18;\n"
"	font-weight: bold;\n"
"    border: 1px solid #CC3F1F;\n"
"    border-radius: 20px;\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 #fdb57c, stop:1 #d83b18);\n"
"    padding: 5px;\n"
"    }\n"
"\n"
"QPushButton:hover {\n"
"    background: qradialgradient(\n"
"        cx: 0.3, cy: -0.4, fx: 0.3, fy: -0.4,\n"
"        radius: 1.35, stop: 0 #fdc090, stop: 1 #e85230\n"
"        );\n"
"    }\n"
"\n"
"QPushButton:pressed {\n"
"    border-style: inset;\n"
"    background: qradialgradient(\n"
"        cx: 0.4, cy: -0.1, fx: 0.4, fy: -0.1,\n"
"        radius: 1.35, stop: 0 #fc8b32, stop: 1 #ad2f13\n"
"        );\n"
"    }\n"
""));
        titleBarFrame = new QFrame(centralwidget);
        titleBarFrame->setObjectName("titleBarFrame");
        titleBarFrame->setGeometry(QRect(0, 10, 801, 31));
        titleBarFrame->setStyleSheet(QString::fromUtf8("QFrame#titleBarFrame {\n"
"    background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0, stop:0 #3674f7, stop:0.878307 #2153bf);\n"
"    border-top-left-radius: 12px;\n"
"    border-top-right-radius: 12px;\n"
"}"));
        titleBarFrame->setFrameShape(QFrame::StyledPanel);
        titleBarFrame->setFrameShadow(QFrame::Raised);
        homeBtn = new QPushButton(titleBarFrame);
        homeBtn->setObjectName("homeBtn");
        homeBtn->setGeometry(QRect(290, 0, 211, 31));
        homeBtn->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: transparent;\n"
"	border: 1px solid transparent;\n"
"	border-radius: 12px;\n"
"	color: #fdfdfd;\n"
"	align: \n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	color: #CADAE8;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	color: #9FB8C2;\n"
"}"));
        MainWindow->setCentralWidget(centralwidget);
        contentFrame->raise();
        titleBarFrame->raise();
        minBtn->raise();
        xBtn->raise();
        QWidget::setTabOrder(username_input, password_input);
        QWidget::setTabOrder(password_input, storeLoginCheckbox);
        QWidget::setTabOrder(storeLoginCheckbox, submitBtn);
        QWidget::setTabOrder(submitBtn, AutoGroupSelectBtn);
        QWidget::setTabOrder(AutoGroupSelectBtn, InvasionBtn);
        QWidget::setTabOrder(InvasionBtn, DoodleBtn);
        QWidget::setTabOrder(DoodleBtn, DualToonContBtn);
        QWidget::setTabOrder(DualToonContBtn, LaunchTTBtn);
        QWidget::setTabOrder(LaunchTTBtn, minBtn);
        QWidget::setTabOrder(minBtn, xBtn);
        QWidget::setTabOrder(xBtn, toonListWidget);
        QWidget::setTabOrder(toonListWidget, disconnectToonBtn);
        QWidget::setTabOrder(disconnectToonBtn, unameInput1);
        QWidget::setTabOrder(unameInput1, pwordInput1);
        QWidget::setTabOrder(pwordInput1, aliasInput1);
        QWidget::setTabOrder(aliasInput1, addClient_btn1);
        QWidget::setTabOrder(addClient_btn1, save_btn1);
        QWidget::setTabOrder(save_btn1, edit_btn1);
        QWidget::setTabOrder(edit_btn1, remove_bt1);
        QWidget::setTabOrder(remove_bt1, save_btn1_noInc);
        QWidget::setTabOrder(save_btn1_noInc, launch_btn1);
        QWidget::setTabOrder(launch_btn1, aliasInput2);
        QWidget::setTabOrder(aliasInput2, addClient_btn2);
        QWidget::setTabOrder(addClient_btn2, pwordInput2);
        QWidget::setTabOrder(pwordInput2, unameInput2);
        QWidget::setTabOrder(unameInput2, launch_btn2);
        QWidget::setTabOrder(launch_btn2, save_btn2);
        QWidget::setTabOrder(save_btn2, edit_btn2);
        QWidget::setTabOrder(edit_btn2, remove_bt2);
        QWidget::setTabOrder(remove_bt2, save_btn2_noInc);
        QWidget::setTabOrder(save_btn2_noInc, save_btn3);
        QWidget::setTabOrder(save_btn3, launch_btn3);
        QWidget::setTabOrder(launch_btn3, addClient_btn3);
        QWidget::setTabOrder(addClient_btn3, unameInput3);
        QWidget::setTabOrder(unameInput3, pwordInput3);
        QWidget::setTabOrder(pwordInput3, aliasInput3);
        QWidget::setTabOrder(aliasInput3, remove_bt3);
        QWidget::setTabOrder(remove_bt3, save_btn3_noInc);
        QWidget::setTabOrder(save_btn3_noInc, edit_btn3);
        QWidget::setTabOrder(edit_btn3, manual_loc_btnEDIT1);
        QWidget::setTabOrder(manual_loc_btnEDIT1, fileLocation_input1);
        QWidget::setTabOrder(fileLocation_input1, fileLocation_input2);
        QWidget::setTabOrder(fileLocation_input2, manual_loc_btnEDIT2);
        QWidget::setTabOrder(manual_loc_btnEDIT2, fileLocation_input3);
        QWidget::setTabOrder(fileLocation_input3, manual_loc_btnEDIT3);
        QWidget::setTabOrder(manual_loc_btnEDIT3, start_arrowKeysBtn);
        QWidget::setTabOrder(start_arrowKeysBtn, stop_dualBtn);
        QWidget::setTabOrder(stop_dualBtn, start_WASDBtn);
        QWidget::setTabOrder(start_WASDBtn, start_trick1Btn);
        QWidget::setTabOrder(start_trick1Btn, stop_trainingBtn);
        QWidget::setTabOrder(stop_trainingBtn, start_trick2Btn);
        QWidget::setTabOrder(start_trick2Btn, grab_coordsBtn);
        QWidget::setTabOrder(grab_coordsBtn, start_trick3Btn);
        QWidget::setTabOrder(start_trick3Btn, start_trick4Btn);
        QWidget::setTabOrder(start_trick4Btn, start_trick5Btn);
        QWidget::setTabOrder(start_trick5Btn, start_trick6Btn);
        QWidget::setTabOrder(start_trick6Btn, start_trick7Btn);
        QWidget::setTabOrder(start_trick7Btn, labelBox);
        QWidget::setTabOrder(labelBox, labelBox_2);
        QWidget::setTabOrder(labelBox_2, labelBox_3);
        QWidget::setTabOrder(labelBox_3, labelBox_4);
        QWidget::setTabOrder(labelBox_4, labelBox_5);
        QWidget::setTabOrder(labelBox_5, labelBox_6);
        QWidget::setTabOrder(labelBox_6, labelBox_7);
        QWidget::setTabOrder(labelBox_7, homeBtn);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "TTR MultiTool", nullptr));
        password_input->setText(QString());
        username_input->setText(QString());
        submitBtn->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        storeLoginCheckbox->setText(QCoreApplication::translate("MainWindow", "Don't store my login information", nullptr));
        password_label->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        username_label->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        statusLabel->setText(QString());
        DualToonContBtn->setText(QCoreApplication::translate("MainWindow", "Dual Toon", nullptr));
        AutoGroupSelectBtn->setText(QCoreApplication::translate("MainWindow", "ToonHQ Auto Group Accept", nullptr));
        DoodleBtn->setText(QCoreApplication::translate("MainWindow", "Doodle Training", nullptr));
        InvasionBtn->setText(QCoreApplication::translate("MainWindow", "Invasion Monitor", nullptr));
        LaunchTTBtn->setText(QCoreApplication::translate("MainWindow", "Launch TTR", nullptr));
        ToonHQWebBtn->setText(QCoreApplication::translate("MainWindow", "ToonHQ Web Page", nullptr));
        connectedToonLabel->setText(QString());
        disconnectToonBtn->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        bg_label_x->setText(QString());
        labelToonHQ->setText(QString());
        connectedInfoLabel->setText(QString());
        unameInput1->setText(QString());
        uname_label_1->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        pwordInput1->setText(QString());
        pword_label_1->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        aliasInput1->setText(QString());
        alias_label_1->setText(QCoreApplication::translate("MainWindow", "Alias (optional):", nullptr));
        addClient_btn1->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        addClient_label1->setText(QCoreApplication::translate("MainWindow", "Add Saved Client:", nullptr));
        save_btn1->setText(QCoreApplication::translate("MainWindow", "\342\234\223", nullptr));
        edit_btn1->setText(QCoreApplication::translate("MainWindow", "\342\234\216", nullptr));
        launch_label1->setText(QString());
        remove_bt1->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        save_btn1_noInc->setText(QCoreApplication::translate("MainWindow", "\342\234\223", nullptr));
        launch_btn1->setText(QCoreApplication::translate("MainWindow", "\342\226\266\357\270\216", nullptr));
        aliasInput2->setText(QString());
        addClient_btn2->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pwordInput2->setText(QString());
        alias_label_2->setText(QCoreApplication::translate("MainWindow", "Alias (optional):", nullptr));
        unameInput2->setText(QString());
        pword_label_2->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        launch_btn2->setText(QCoreApplication::translate("MainWindow", "\342\226\266\357\270\216", nullptr));
        save_btn2->setText(QCoreApplication::translate("MainWindow", "\342\234\223", nullptr));
        edit_btn2->setText(QCoreApplication::translate("MainWindow", "\342\234\216", nullptr));
        remove_bt2->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        addClient_label2->setText(QCoreApplication::translate("MainWindow", "Add Saved Client:", nullptr));
        uname_label_2->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        save_btn2_noInc->setText(QCoreApplication::translate("MainWindow", "\342\234\223", nullptr));
        launch_label2->setText(QString());
        save_btn3->setText(QCoreApplication::translate("MainWindow", "\342\234\223", nullptr));
        launch_btn3->setText(QCoreApplication::translate("MainWindow", "\342\226\266\357\270\216", nullptr));
        addClient_btn3->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        alias_label_3->setText(QCoreApplication::translate("MainWindow", "Alias (optional):", nullptr));
        launch_label3->setText(QString());
        unameInput3->setText(QString());
        pwordInput3->setText(QString());
        addClient_label3->setText(QCoreApplication::translate("MainWindow", "Add Saved Client:", nullptr));
        aliasInput3->setText(QString());
        remove_bt3->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        uname_label_3->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        save_btn3_noInc->setText(QCoreApplication::translate("MainWindow", "\342\234\223", nullptr));
        edit_btn3->setText(QCoreApplication::translate("MainWindow", "\342\234\216", nullptr));
        pword_label_3->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        status_label_1->setText(QCoreApplication::translate("MainWindow", "StatusLabel", nullptr));
        status_label_2->setText(QCoreApplication::translate("MainWindow", "StatusLabel", nullptr));
        status_label_3->setText(QCoreApplication::translate("MainWindow", "StatusLabel", nullptr));
        manual_loc_btnEDIT1->setText(QCoreApplication::translate("MainWindow", "\360\237\227\201", nullptr));
        fileLocation_input1->setText(QString());
        installLoc_label1->setText(QCoreApplication::translate("MainWindow", "Install location: ", nullptr));
        installLoc_label2->setText(QCoreApplication::translate("MainWindow", "Install location: ", nullptr));
        fileLocation_input2->setText(QString());
        manual_loc_btnEDIT2->setText(QCoreApplication::translate("MainWindow", "\360\237\227\201", nullptr));
        fileLocation_input3->setText(QString());
        manual_loc_btnEDIT3->setText(QCoreApplication::translate("MainWindow", "\360\237\227\201", nullptr));
        installLoc_label3->setText(QCoreApplication::translate("MainWindow", "Install location: ", nullptr));
        start_arrowKeysBtn->setText(QCoreApplication::translate("MainWindow", "Select Arrow Keys Toon", nullptr));
        stop_dualBtn->setText(QCoreApplication::translate("MainWindow", "Stop Both", nullptr));
        start_WASDBtn->setText(QCoreApplication::translate("MainWindow", "Select WASD Toon", nullptr));
        whichRunningLabel->setText(QCoreApplication::translate("MainWindow", "No Process Started", nullptr));
        dual_headerLabel->setText(QCoreApplication::translate("MainWindow", "Inputs are routed as soon as a window is selected", nullptr));
        typingLabel->setText(QString());
        invasionCounterLabel->setText(QString());
        start_trick1Btn->setText(QCoreApplication::translate("MainWindow", "Train Trick 1", nullptr));
        stop_trainingBtn->setText(QCoreApplication::translate("MainWindow", "Stop Training", nullptr));
        start_trick2Btn->setText(QCoreApplication::translate("MainWindow", "Train Trick 2", nullptr));
        grab_coordsBtn->setText(QCoreApplication::translate("MainWindow", "Dev Button", nullptr));
        start_trick3Btn->setText(QCoreApplication::translate("MainWindow", "Train Trick 3", nullptr));
        start_trick4Btn->setText(QCoreApplication::translate("MainWindow", "Train Trick 4", nullptr));
        start_trick5Btn->setText(QCoreApplication::translate("MainWindow", "Train Trick 5", nullptr));
        start_trick6Btn->setText(QCoreApplication::translate("MainWindow", "Train Trick 6", nullptr));
        start_trick7Btn->setText(QCoreApplication::translate("MainWindow", "Train Trick 7", nullptr));
        current_trickLabel->setText(QCoreApplication::translate("MainWindow", "Not Currently Training", nullptr));
        labelBox->setItemText(0, QCoreApplication::translate("MainWindow", "Optional Label", nullptr));
        labelBox->setItemText(1, QCoreApplication::translate("MainWindow", "Jump", nullptr));
        labelBox->setItemText(2, QCoreApplication::translate("MainWindow", "Beg", nullptr));
        labelBox->setItemText(3, QCoreApplication::translate("MainWindow", "Play Dead", nullptr));
        labelBox->setItemText(4, QCoreApplication::translate("MainWindow", "Rollover", nullptr));
        labelBox->setItemText(5, QCoreApplication::translate("MainWindow", "Backflip", nullptr));
        labelBox->setItemText(6, QCoreApplication::translate("MainWindow", "Dance", nullptr));
        labelBox->setItemText(7, QCoreApplication::translate("MainWindow", "Speak", nullptr));

        labelBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Optional Label", nullptr));
        labelBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Jump", nullptr));
        labelBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Beg", nullptr));
        labelBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "Play Dead", nullptr));
        labelBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "Rollover", nullptr));
        labelBox_2->setItemText(5, QCoreApplication::translate("MainWindow", "Backflip", nullptr));
        labelBox_2->setItemText(6, QCoreApplication::translate("MainWindow", "Dance", nullptr));
        labelBox_2->setItemText(7, QCoreApplication::translate("MainWindow", "Speak", nullptr));

        labelBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "Optional Label", nullptr));
        labelBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Jump", nullptr));
        labelBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Beg", nullptr));
        labelBox_3->setItemText(3, QCoreApplication::translate("MainWindow", "Play Dead", nullptr));
        labelBox_3->setItemText(4, QCoreApplication::translate("MainWindow", "Rollover", nullptr));
        labelBox_3->setItemText(5, QCoreApplication::translate("MainWindow", "Backflip", nullptr));
        labelBox_3->setItemText(6, QCoreApplication::translate("MainWindow", "Dance", nullptr));
        labelBox_3->setItemText(7, QCoreApplication::translate("MainWindow", "Speak", nullptr));

        labelBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "Optional Label", nullptr));
        labelBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "Jump", nullptr));
        labelBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "Beg", nullptr));
        labelBox_4->setItemText(3, QCoreApplication::translate("MainWindow", "Play Dead", nullptr));
        labelBox_4->setItemText(4, QCoreApplication::translate("MainWindow", "Rollover", nullptr));
        labelBox_4->setItemText(5, QCoreApplication::translate("MainWindow", "Backflip", nullptr));
        labelBox_4->setItemText(6, QCoreApplication::translate("MainWindow", "Dance", nullptr));
        labelBox_4->setItemText(7, QCoreApplication::translate("MainWindow", "Speak", nullptr));

        labelBox_5->setItemText(0, QCoreApplication::translate("MainWindow", "Optional Label", nullptr));
        labelBox_5->setItemText(1, QCoreApplication::translate("MainWindow", "Jump", nullptr));
        labelBox_5->setItemText(2, QCoreApplication::translate("MainWindow", "Beg", nullptr));
        labelBox_5->setItemText(3, QCoreApplication::translate("MainWindow", "Play Dead", nullptr));
        labelBox_5->setItemText(4, QCoreApplication::translate("MainWindow", "Rollover", nullptr));
        labelBox_5->setItemText(5, QCoreApplication::translate("MainWindow", "Backflip", nullptr));
        labelBox_5->setItemText(6, QCoreApplication::translate("MainWindow", "Dance", nullptr));
        labelBox_5->setItemText(7, QCoreApplication::translate("MainWindow", "Speak", nullptr));

        labelBox_6->setItemText(0, QCoreApplication::translate("MainWindow", "Optional Label", nullptr));
        labelBox_6->setItemText(1, QCoreApplication::translate("MainWindow", "Jump", nullptr));
        labelBox_6->setItemText(2, QCoreApplication::translate("MainWindow", "Beg", nullptr));
        labelBox_6->setItemText(3, QCoreApplication::translate("MainWindow", "Play Dead", nullptr));
        labelBox_6->setItemText(4, QCoreApplication::translate("MainWindow", "Rollover", nullptr));
        labelBox_6->setItemText(5, QCoreApplication::translate("MainWindow", "Backflip", nullptr));
        labelBox_6->setItemText(6, QCoreApplication::translate("MainWindow", "Dance", nullptr));
        labelBox_6->setItemText(7, QCoreApplication::translate("MainWindow", "Speak", nullptr));

        labelBox_7->setItemText(0, QCoreApplication::translate("MainWindow", "Optional Label", nullptr));
        labelBox_7->setItemText(1, QCoreApplication::translate("MainWindow", "Jump", nullptr));
        labelBox_7->setItemText(2, QCoreApplication::translate("MainWindow", "Beg", nullptr));
        labelBox_7->setItemText(3, QCoreApplication::translate("MainWindow", "Play Dead", nullptr));
        labelBox_7->setItemText(4, QCoreApplication::translate("MainWindow", "Rollover", nullptr));
        labelBox_7->setItemText(5, QCoreApplication::translate("MainWindow", "Backflip", nullptr));
        labelBox_7->setItemText(6, QCoreApplication::translate("MainWindow", "Dance", nullptr));
        labelBox_7->setItemText(7, QCoreApplication::translate("MainWindow", "Speak", nullptr));

        resolutionLabel->setText(QCoreApplication::translate("MainWindow", "\342\232\240\357\270\217 Resolution must be 800x600 \342\232\240\357\270\217", nullptr));
        minBtn->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        xBtn->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        homeBtn->setText(QCoreApplication::translate("MainWindow", "ToonTown MultiTool", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
