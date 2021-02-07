/********************************************************************************
** Form generated from reading UI file 'LoggerView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGGERVIEW_H
#define UI_LOGGERVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "LoggerWidget.h"

QT_BEGIN_NAMESPACE

class Ui_LoggerView
{
public:
    QGridLayout *gridLayout;
    LoggerWidget *loggerWidget;

    void setupUi(QWidget *LoggerView)
    {
        if (LoggerView->objectName().isEmpty())
            LoggerView->setObjectName(QString::fromUtf8("LoggerView"));
        LoggerView->resize(400, 300);
        gridLayout = new QGridLayout(LoggerView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        loggerWidget = new LoggerWidget(LoggerView);
        loggerWidget->setObjectName(QString::fromUtf8("loggerWidget"));

        gridLayout->addWidget(loggerWidget, 0, 0, 1, 1);


        retranslateUi(LoggerView);

        QMetaObject::connectSlotsByName(LoggerView);
    } // setupUi

    void retranslateUi(QWidget *LoggerView)
    {
        LoggerView->setWindowTitle(QCoreApplication::translate("LoggerView", "LoggerView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoggerView: public Ui_LoggerView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGERVIEW_H
