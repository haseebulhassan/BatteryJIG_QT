/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "ledindicator.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QPushButton *charge_all;
    QPushButton *discharge_all;
    QGroupBox *groupBox_3;
    QComboBox *cb_comport;
    QPushButton *pb_Refresh;
    QPushButton *pushButton;
    LedIndicator *led;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1045, 880);
        MainWindow->setAnimated(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 160, 1001, 641));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 20, 291, 121));
        groupBox_2->setStyleSheet(QString::fromUtf8("font: 75 14pt \"MS Shell Dlg 2\";\n"
"\n"
"background-color:rgb(85, 170, 255)"));
        groupBox_2->setFlat(true);
        charge_all = new QPushButton(groupBox_2);
        charge_all->setObjectName(QString::fromUtf8("charge_all"));
        charge_all->setGeometry(QRect(60, 30, 151, 31));
        charge_all->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 0);color: rgb(255, 255, 255);"));
        discharge_all = new QPushButton(groupBox_2);
        discharge_all->setObjectName(QString::fromUtf8("discharge_all"));
        discharge_all->setGeometry(QRect(60, 70, 151, 31));
        discharge_all->setStyleSheet(QString::fromUtf8("background-color: rgb(85,0, 0);color: rgb(255, 255, 255);"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(660, 20, 361, 121));
        groupBox_3->setStyleSheet(QString::fromUtf8("font: 75 14pt \"MS Shell Dlg 2\";\n"
"\n"
"background-color:rgb(85, 170, 255)"));
        groupBox_3->setFlat(true);
        cb_comport = new QComboBox(groupBox_3);
        cb_comport->setObjectName(QString::fromUtf8("cb_comport"));
        cb_comport->setGeometry(QRect(210, 30, 81, 22));
        pb_Refresh = new QPushButton(groupBox_3);
        pb_Refresh->setObjectName(QString::fromUtf8("pb_Refresh"));
        pb_Refresh->setGeometry(QRect(210, 60, 81, 31));
        pb_Refresh->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 0);color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 40, 181, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 0);color: rgb(255, 255, 255);"));
        led = new LedIndicator(groupBox_3);
        led->setObjectName(QString::fromUtf8("led"));
        led->setGeometry(QRect(300, 30, 50, 50));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(320, 50, 331, 71));
        label->setStyleSheet(QString::fromUtf8("font: 100 20pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(0, 200, 0);\n"
"color: rgb(255, 255, 255);"));
        label->setFrameShape(QFrame::Box);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(740, 810, 281, 21));
        label_2->setFrameShape(QFrame::Box);
        label_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1045, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Smart Battery Jig", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Functions", nullptr));
        charge_all->setText(QApplication::translate("MainWindow", "CHARGE ALL", nullptr));
        discharge_all->setText(QApplication::translate("MainWindow", "DISCHARGE ALL", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "COM Port", nullptr));
        pb_Refresh->setText(QApplication::translate("MainWindow", "Refresh", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "OPEN COM PORT", nullptr));
        label->setText(QApplication::translate("MainWindow", "SMART Battery JIG", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Designed and Developed by Impact Solutions Pvt Ltd", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
