/********************************************************************************
** Form generated from reading UI file 'FilterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERDIALOG_H
#define UI_FILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterDialogClass
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;

    void setupUi(QWidget *FilterDialogClass)
    {
        if (FilterDialogClass->objectName().isEmpty())
            FilterDialogClass->setObjectName(QString::fromUtf8("FilterDialogClass"));
        FilterDialogClass->resize(655, 506);
        horizontalLayout = new QHBoxLayout(FilterDialogClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(FilterDialogClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setMovable(false);

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(FilterDialogClass);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(FilterDialogClass);
    } // setupUi

    void retranslateUi(QWidget *FilterDialogClass)
    {
        FilterDialogClass->setWindowTitle(QCoreApplication::translate("FilterDialogClass", "FilterDialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterDialogClass: public Ui_FilterDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERDIALOG_H
