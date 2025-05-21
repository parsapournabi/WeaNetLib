/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *frameHeader;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *gbCOM;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *txtIPLocal;
    QLineEdit *txtPortLocal;
    QPushButton *btnBind;
    QLabel *label_2;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *txtIPPeer;
    QLineEdit *txtPortPeer;
    QPushButton *btnConnect;
    QGroupBox *gbControl;
    QHBoxLayout *horizontalLayout_6;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *rbTcpServer;
    QRadioButton *rbTcpClient;
    QRadioButton *rbUdp;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QSpinBox *sbPacketIndex;
    QPushButton *btnSend;
    QCheckBox *cbPrintRx;
    QFrame *frameMain;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *gbBuffer;
    QVBoxLayout *verticalLayout_7;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lblTxRate;
    QLabel *lblTxBufferSize;
    QLabel *lblRxRate;
    QLabel *lblRxBufferSize;
    QPlainTextEdit *plaintxtReceiveBuffer;
    QFrame *frameFooter;
    QHBoxLayout *horizontalLayout;
    QGroupBox *gbStatus;
    QVBoxLayout *verticalLayout_5;
    QPlainTextEdit *plaintxtStatus;
    QGroupBox *gbError;
    QVBoxLayout *verticalLayout_6;
    QPlainTextEdit *plaintxtError;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(779, 656);
        MainWindow->setMouseTracking(false);
        MainWindow->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border: none;\n"
"	background: transparent;\n"
"}\n"
"QGroupBox {\n"
"	border: 1px solid white;\n"
"	border-radius: 8px;\n"
"}\n"
"QGroupBox::title {\n"
"	subcontrol-origin: margin;\n"
"	subcontrol-position: top left;\n"
"	padding: 0 10px;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"	background-color: #5e5e5e;\n"
"	min-height: 20px;\n"
"	border-radius: 4px;\n"
"}\n"
"QScrollBar:vertical {\n"
"	background-color: #2e2e2e;\n"
"	width: 10px;\n"
"	margin: 0px;\n"
"}\n"
"QPlainTextEdit {\n"
"	background: transparent;\n"
"	\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frameHeader = new QFrame(centralwidget);
        frameHeader->setObjectName(QString::fromUtf8("frameHeader"));
        frameHeader->setFrameShape(QFrame::StyledPanel);
        frameHeader->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frameHeader);
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gbCOM = new QGroupBox(frameHeader);
        gbCOM->setObjectName(QString::fromUtf8("gbCOM"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gbCOM->sizePolicy().hasHeightForWidth());
        gbCOM->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(gbCOM);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(20, 25, 20, 20);
        label = new QLabel(gbCOM);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        frame = new QFrame(gbCOM);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        txtIPLocal = new QLineEdit(frame);
        txtIPLocal->setObjectName(QString::fromUtf8("txtIPLocal"));
        txtIPLocal->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(txtIPLocal);

        txtPortLocal = new QLineEdit(frame);
        txtPortLocal->setObjectName(QString::fromUtf8("txtPortLocal"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtPortLocal->sizePolicy().hasHeightForWidth());
        txtPortLocal->setSizePolicy(sizePolicy1);
        txtPortLocal->setMinimumSize(QSize(75, 0));
        txtPortLocal->setMaximumSize(QSize(75, 16777215));
        txtPortLocal->setMaxLength(32768);
        txtPortLocal->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(txtPortLocal);

        btnBind = new QPushButton(frame);
        btnBind->setObjectName(QString::fromUtf8("btnBind"));
        btnBind->setMaximumSize(QSize(16777215, 16777215));
        btnBind->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(btnBind);


        verticalLayout_2->addWidget(frame);

        label_2 = new QLabel(gbCOM);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        frame_2 = new QFrame(gbCOM);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMaximumSize(QSize(16777215, 75));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        txtIPPeer = new QLineEdit(frame_2);
        txtIPPeer->setObjectName(QString::fromUtf8("txtIPPeer"));
        txtIPPeer->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(txtIPPeer);

        txtPortPeer = new QLineEdit(frame_2);
        txtPortPeer->setObjectName(QString::fromUtf8("txtPortPeer"));
        sizePolicy1.setHeightForWidth(txtPortPeer->sizePolicy().hasHeightForWidth());
        txtPortPeer->setSizePolicy(sizePolicy1);
        txtPortPeer->setMinimumSize(QSize(75, 0));
        txtPortPeer->setMaximumSize(QSize(75, 16777215));
        txtPortPeer->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(txtPortPeer);

        btnConnect = new QPushButton(frame_2);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_5->addWidget(btnConnect);


        verticalLayout_2->addWidget(frame_2);


        horizontalLayout_2->addWidget(gbCOM);

        gbControl = new QGroupBox(frameHeader);
        gbControl->setObjectName(QString::fromUtf8("gbControl"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gbControl->sizePolicy().hasHeightForWidth());
        gbControl->setSizePolicy(sizePolicy2);
        horizontalLayout_6 = new QHBoxLayout(gbControl);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, -1, 15, -1);
        frame_3 = new QFrame(gbControl);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        rbTcpServer = new QRadioButton(frame_3);
        rbTcpServer->setObjectName(QString::fromUtf8("rbTcpServer"));
        rbTcpServer->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_4->addWidget(rbTcpServer);

        rbTcpClient = new QRadioButton(frame_3);
        rbTcpClient->setObjectName(QString::fromUtf8("rbTcpClient"));
        rbTcpClient->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_4->addWidget(rbTcpClient);

        rbUdp = new QRadioButton(frame_3);
        rbUdp->setObjectName(QString::fromUtf8("rbUdp"));
        rbUdp->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_4->addWidget(rbUdp);


        horizontalLayout_6->addWidget(frame_3);

        frame_4 = new QFrame(gbControl);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy3);
        frame_4->setMinimumSize(QSize(200, 0));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(frame_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        sbPacketIndex = new QSpinBox(frame_4);
        sbPacketIndex->setObjectName(QString::fromUtf8("sbPacketIndex"));

        verticalLayout_3->addWidget(sbPacketIndex);

        btnSend = new QPushButton(frame_4);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));
        btnSend->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_3->addWidget(btnSend);

        cbPrintRx = new QCheckBox(frame_4);
        cbPrintRx->setObjectName(QString::fromUtf8("cbPrintRx"));

        verticalLayout_3->addWidget(cbPrintRx);


        horizontalLayout_6->addWidget(frame_4);


        horizontalLayout_2->addWidget(gbControl);


        verticalLayout->addWidget(frameHeader);

        frameMain = new QFrame(centralwidget);
        frameMain->setObjectName(QString::fromUtf8("frameMain"));
        frameMain->setFrameShape(QFrame::StyledPanel);
        frameMain->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frameMain);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        gbBuffer = new QGroupBox(frameMain);
        gbBuffer->setObjectName(QString::fromUtf8("gbBuffer"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(gbBuffer->sizePolicy().hasHeightForWidth());
        gbBuffer->setSizePolicy(sizePolicy4);
        verticalLayout_7 = new QVBoxLayout(gbBuffer);
        verticalLayout_7->setSpacing(10);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(20, 25, 20, 20);
        frame_5 = new QFrame(gbBuffer);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_5);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        lblTxRate = new QLabel(frame_5);
        lblTxRate->setObjectName(QString::fromUtf8("lblTxRate"));

        horizontalLayout_7->addWidget(lblTxRate);

        lblTxBufferSize = new QLabel(frame_5);
        lblTxBufferSize->setObjectName(QString::fromUtf8("lblTxBufferSize"));

        horizontalLayout_7->addWidget(lblTxBufferSize);

        lblRxRate = new QLabel(frame_5);
        lblRxRate->setObjectName(QString::fromUtf8("lblRxRate"));

        horizontalLayout_7->addWidget(lblRxRate);

        lblRxBufferSize = new QLabel(frame_5);
        lblRxBufferSize->setObjectName(QString::fromUtf8("lblRxBufferSize"));

        horizontalLayout_7->addWidget(lblRxBufferSize);


        verticalLayout_7->addWidget(frame_5);

        plaintxtReceiveBuffer = new QPlainTextEdit(gbBuffer);
        plaintxtReceiveBuffer->setObjectName(QString::fromUtf8("plaintxtReceiveBuffer"));
        plaintxtReceiveBuffer->setStyleSheet(QString::fromUtf8(""));
        plaintxtReceiveBuffer->setReadOnly(true);

        verticalLayout_7->addWidget(plaintxtReceiveBuffer);


        horizontalLayout_3->addWidget(gbBuffer);


        verticalLayout->addWidget(frameMain);

        frameFooter = new QFrame(centralwidget);
        frameFooter->setObjectName(QString::fromUtf8("frameFooter"));
        frameFooter->setFrameShape(QFrame::StyledPanel);
        frameFooter->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frameFooter);
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gbStatus = new QGroupBox(frameFooter);
        gbStatus->setObjectName(QString::fromUtf8("gbStatus"));
        verticalLayout_5 = new QVBoxLayout(gbStatus);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(15, 15, 15, 15);
        plaintxtStatus = new QPlainTextEdit(gbStatus);
        plaintxtStatus->setObjectName(QString::fromUtf8("plaintxtStatus"));
        sizePolicy2.setHeightForWidth(plaintxtStatus->sizePolicy().hasHeightForWidth());
        plaintxtStatus->setSizePolicy(sizePolicy2);
        plaintxtStatus->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout_5->addWidget(plaintxtStatus);


        horizontalLayout->addWidget(gbStatus);

        gbError = new QGroupBox(frameFooter);
        gbError->setObjectName(QString::fromUtf8("gbError"));
        verticalLayout_6 = new QVBoxLayout(gbError);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(15, 15, 15, 15);
        plaintxtError = new QPlainTextEdit(gbError);
        plaintxtError->setObjectName(QString::fromUtf8("plaintxtError"));
        sizePolicy2.setHeightForWidth(plaintxtError->sizePolicy().hasHeightForWidth());
        plaintxtError->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(plaintxtError);


        horizontalLayout->addWidget(gbError);


        verticalLayout->addWidget(frameFooter);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        gbCOM->setTitle(QCoreApplication::translate("MainWindow", "Communication", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Local Address", nullptr));
        txtIPLocal->setPlaceholderText(QCoreApplication::translate("MainWindow", "192.168.1.1", nullptr));
        txtPortLocal->setPlaceholderText(QCoreApplication::translate("MainWindow", "12345", nullptr));
        btnBind->setText(QCoreApplication::translate("MainWindow", "Bind", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Peer Address", nullptr));
        txtIPPeer->setPlaceholderText(QCoreApplication::translate("MainWindow", "192.168.1.2", nullptr));
        txtPortPeer->setPlaceholderText(QCoreApplication::translate("MainWindow", "54321", nullptr));
        btnConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        gbControl->setTitle(QCoreApplication::translate("MainWindow", "Control", nullptr));
        rbTcpServer->setText(QCoreApplication::translate("MainWindow", "TcpServer", nullptr));
        rbTcpClient->setText(QCoreApplication::translate("MainWindow", "TcpClient", nullptr));
        rbUdp->setText(QCoreApplication::translate("MainWindow", "Udp", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Packet Index", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        cbPrintRx->setText(QCoreApplication::translate("MainWindow", "Print receive buffer", nullptr));
        gbBuffer->setTitle(QCoreApplication::translate("MainWindow", "Buffer", nullptr));
        lblTxRate->setText(QCoreApplication::translate("MainWindow", "Tx Rate:", nullptr));
        lblTxBufferSize->setText(QCoreApplication::translate("MainWindow", "Tx Buffer Size:", nullptr));
        lblRxRate->setText(QCoreApplication::translate("MainWindow", "Rx Rate:", nullptr));
        lblRxBufferSize->setText(QCoreApplication::translate("MainWindow", "Rx Buffer Size:", nullptr));
        gbStatus->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        gbError->setTitle(QCoreApplication::translate("MainWindow", "Errors", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
