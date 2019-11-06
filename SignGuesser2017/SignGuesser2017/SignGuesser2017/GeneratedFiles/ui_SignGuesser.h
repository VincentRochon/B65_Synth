/********************************************************************************
** Form generated from reading UI file 'SignGuesser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNGUESSER_H
#define UI_SIGNGUESSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignGuesserClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SignGuesserClass)
    {
        if (SignGuesserClass->objectName().isEmpty())
            SignGuesserClass->setObjectName(QString::fromUtf8("SignGuesserClass"));
        SignGuesserClass->resize(600, 400);
        menuBar = new QMenuBar(SignGuesserClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SignGuesserClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SignGuesserClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SignGuesserClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SignGuesserClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SignGuesserClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SignGuesserClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SignGuesserClass->setStatusBar(statusBar);

        retranslateUi(SignGuesserClass);

        QMetaObject::connectSlotsByName(SignGuesserClass);
    } // setupUi

    void retranslateUi(QMainWindow *SignGuesserClass)
    {
        SignGuesserClass->setWindowTitle(QApplication::translate("SignGuesserClass", "SignGuesser", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignGuesserClass: public Ui_SignGuesserClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNGUESSER_H
