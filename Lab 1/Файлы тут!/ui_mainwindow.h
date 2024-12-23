/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRGB_LAB_CMYK;
    QAction *actionCMYK_RGB_HSV;
    QAction *actionRGB_XYZ_CMYK;
    QAction *actionRGB_CMYK_HLS;
    QAction *actionRGB_XYZ_HSV;
    QAction *actionCMYK_LAB_XYZ;
    QAction *actionRGB_XYZ_LAB;
    QAction *actionHSV_XYZ_LAB;
    QAction *actionRGB_CMYK_HSV;
    QAction *action_RGB_HSV_LAB;
    QAction *actionCMYK_LAB_RGB;
    QAction *actionCMYK_HLS_XYZ;
    QAction *actionCMYK_LAB_HSV;
    QAction *actionXYZ_LAB_HLS;
    QAction *actionRGB_HLS_LAB;
    QAction *actionCMYK_RGB_HLS;
    QAction *actionRGB_XYZ_HLS;
    QAction *actionCMYK_XYZ_RGB;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionRGB_LAB_CMYK = new QAction(MainWindow);
        actionRGB_LAB_CMYK->setObjectName("actionRGB_LAB_CMYK");
        actionCMYK_RGB_HSV = new QAction(MainWindow);
        actionCMYK_RGB_HSV->setObjectName("actionCMYK_RGB_HSV");
        actionRGB_XYZ_CMYK = new QAction(MainWindow);
        actionRGB_XYZ_CMYK->setObjectName("actionRGB_XYZ_CMYK");
        actionRGB_CMYK_HLS = new QAction(MainWindow);
        actionRGB_CMYK_HLS->setObjectName("actionRGB_CMYK_HLS");
        actionRGB_XYZ_HSV = new QAction(MainWindow);
        actionRGB_XYZ_HSV->setObjectName("actionRGB_XYZ_HSV");
        actionCMYK_LAB_XYZ = new QAction(MainWindow);
        actionCMYK_LAB_XYZ->setObjectName("actionCMYK_LAB_XYZ");
        actionRGB_XYZ_LAB = new QAction(MainWindow);
        actionRGB_XYZ_LAB->setObjectName("actionRGB_XYZ_LAB");
        actionHSV_XYZ_LAB = new QAction(MainWindow);
        actionHSV_XYZ_LAB->setObjectName("actionHSV_XYZ_LAB");
        actionRGB_CMYK_HSV = new QAction(MainWindow);
        actionRGB_CMYK_HSV->setObjectName("actionRGB_CMYK_HSV");
        action_RGB_HSV_LAB = new QAction(MainWindow);
        action_RGB_HSV_LAB->setObjectName("action_RGB_HSV_LAB");
        actionCMYK_LAB_RGB = new QAction(MainWindow);
        actionCMYK_LAB_RGB->setObjectName("actionCMYK_LAB_RGB");
        actionCMYK_HLS_XYZ = new QAction(MainWindow);
        actionCMYK_HLS_XYZ->setObjectName("actionCMYK_HLS_XYZ");
        actionCMYK_LAB_HSV = new QAction(MainWindow);
        actionCMYK_LAB_HSV->setObjectName("actionCMYK_LAB_HSV");
        actionXYZ_LAB_HLS = new QAction(MainWindow);
        actionXYZ_LAB_HLS->setObjectName("actionXYZ_LAB_HLS");
        actionRGB_HLS_LAB = new QAction(MainWindow);
        actionRGB_HLS_LAB->setObjectName("actionRGB_HLS_LAB");
        actionCMYK_RGB_HLS = new QAction(MainWindow);
        actionCMYK_RGB_HLS->setObjectName("actionCMYK_RGB_HLS");
        actionRGB_XYZ_HLS = new QAction(MainWindow);
        actionRGB_XYZ_HLS->setObjectName("actionRGB_XYZ_HLS");
        actionCMYK_XYZ_RGB = new QAction(MainWindow);
        actionCMYK_XYZ_RGB->setObjectName("actionCMYK_XYZ_RGB");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionRGB_LAB_CMYK->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 LAB \342\206\224\357\270\217 CMYK ", nullptr));
        actionCMYK_RGB_HSV->setText(QCoreApplication::translate("MainWindow", "CMYK \342\206\224\357\270\217 RGB \342\206\224\357\270\217 HSV ", nullptr));
        actionRGB_XYZ_CMYK->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 XYZ \342\206\224\357\270\217 CMYK ", nullptr));
        actionRGB_CMYK_HLS->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 CMYK \342\206\224\357\270\217 HLS ", nullptr));
        actionRGB_XYZ_HSV->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 XYZ \342\206\224\357\270\217 HSV ", nullptr));
        actionCMYK_LAB_XYZ->setText(QCoreApplication::translate("MainWindow", "CMYK \342\206\224\357\270\217 LAB \342\206\224\357\270\217 XYZ ", nullptr));
        actionRGB_XYZ_LAB->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 XYZ \342\206\224\357\270\217 LAB ", nullptr));
        actionHSV_XYZ_LAB->setText(QCoreApplication::translate("MainWindow", "HSV \342\206\224\357\270\217 XYZ \342\206\224\357\270\217 LAB ", nullptr));
        actionRGB_CMYK_HSV->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 CMYK \342\206\224\357\270\217 HSV ", nullptr));
        action_RGB_HSV_LAB->setText(QCoreApplication::translate("MainWindow", "\n"
"RGB \342\206\224\357\270\217 HSV \342\206\224\357\270\217 LAB ", nullptr));
        actionCMYK_LAB_RGB->setText(QCoreApplication::translate("MainWindow", "CMYK \342\206\224\357\270\217 LAB \342\206\224\357\270\217 RGB ", nullptr));
        actionCMYK_HLS_XYZ->setText(QCoreApplication::translate("MainWindow", "CMYK \342\206\224\357\270\217 HLS \342\206\224\357\270\217 XYZ ", nullptr));
        actionCMYK_LAB_HSV->setText(QCoreApplication::translate("MainWindow", "CMYK \342\206\224\357\270\217 LAB \342\206\224\357\270\217 HSV ", nullptr));
        actionXYZ_LAB_HLS->setText(QCoreApplication::translate("MainWindow", "XYZ \342\206\224\357\270\217 LAB \342\206\224\357\270\217 HLS ", nullptr));
        actionRGB_HLS_LAB->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 HLS \342\206\224\357\270\217 LAB ", nullptr));
        actionCMYK_RGB_HLS->setText(QCoreApplication::translate("MainWindow", "CMYK \342\206\224\357\270\217 RGB \342\206\224\357\270\217 HLS ", nullptr));
        actionRGB_XYZ_HLS->setText(QCoreApplication::translate("MainWindow", "RGB \342\206\224\357\270\217 XYZ \342\206\224\357\270\217 HLS ", nullptr));
        actionCMYK_XYZ_RGB->setText(QCoreApplication::translate("MainWindow", "CMYK \342\206\224\357\270\217 XYZ \342\206\224\357\270\217 RGB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
