/********************************************************************************
** Form generated from reading UI file 'FilterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERDIALOG_H
#define UI_FILTERDIALOG_H

#include <Basic/ProgressBar.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterDialogClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *statusLabel;
    QSpacerItem *horizontalSpacer;
    ProgressBar *progressBar;
    QTabWidget *tabWidget;

    void setupUi(QWidget *FilterDialogClass)
    {
        if (FilterDialogClass->objectName().isEmpty())
            FilterDialogClass->setObjectName(QString::fromUtf8("FilterDialogClass"));
        FilterDialogClass->resize(614, 370);
        gridLayout = new QGridLayout(FilterDialogClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        statusLabel = new QLabel(FilterDialogClass);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        horizontalLayout->addWidget(statusLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        progressBar = new ProgressBar(FilterDialogClass);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setTextVisible(false);

        horizontalLayout->addWidget(progressBar);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        tabWidget = new QTabWidget(FilterDialogClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(FilterDialogClass);

        QMetaObject::connectSlotsByName(FilterDialogClass);
    } // setupUi

    void retranslateUi(QWidget *FilterDialogClass)
    {
        FilterDialogClass->setWindowTitle(QCoreApplication::translate("FilterDialogClass", "Filter Dialog", nullptr));
        statusLabel->setText(QCoreApplication::translate("FilterDialogClass", "Status:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FilterDialogClass: public Ui_FilterDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERDIALOG_H
