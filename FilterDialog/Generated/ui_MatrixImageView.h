/********************************************************************************
** Form generated from reading UI file 'MatrixImageView.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXIMAGEVIEW_H
#define UI_MATRIXIMAGEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>
#include "MatrixFrameView.h"

QT_BEGIN_NAMESPACE

class Ui_MatrixImageView
{
public:
    QGridLayout *gridLayout;
    QGroupBox *GroupBox2;
    QGroupBox *GroupBox1;
    QCheckBox *checkHistoEqualize;
    MatrixFrameView *frameView;

    void setupUi(QWidget *MatrixImageView)
    {
        if (MatrixImageView->objectName().isEmpty())
            MatrixImageView->setObjectName(QString::fromUtf8("MatrixImageView"));
        MatrixImageView->resize(588, 400);
        gridLayout = new QGridLayout(MatrixImageView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        GroupBox2 = new QGroupBox(MatrixImageView);
        GroupBox2->setObjectName(QString::fromUtf8("GroupBox2"));
        GroupBox2->setCheckable(true);

        gridLayout->addWidget(GroupBox2, 2, 1, 1, 1);

        GroupBox1 = new QGroupBox(MatrixImageView);
        GroupBox1->setObjectName(QString::fromUtf8("GroupBox1"));
        GroupBox1->setCheckable(true);

        gridLayout->addWidget(GroupBox1, 1, 1, 1, 1);

        checkHistoEqualize = new QCheckBox(MatrixImageView);
        checkHistoEqualize->setObjectName(QString::fromUtf8("checkHistoEqualize"));

        gridLayout->addWidget(checkHistoEqualize, 0, 1, 1, 1);

        frameView = new MatrixFrameView(MatrixImageView);
        frameView->setObjectName(QString::fromUtf8("frameView"));
        frameView->setFrameShape(QFrame::StyledPanel);
        frameView->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameView, 0, 0, 3, 1);


        retranslateUi(MatrixImageView);

        QMetaObject::connectSlotsByName(MatrixImageView);
    } // setupUi

    void retranslateUi(QWidget *MatrixImageView)
    {
        MatrixImageView->setWindowTitle(QCoreApplication::translate("MatrixImageView", "MatrixImageView", nullptr));
        GroupBox2->setTitle(QCoreApplication::translate("MatrixImageView", "SUACE", nullptr));
        GroupBox1->setTitle(QCoreApplication::translate("MatrixImageView", "CLAHE", nullptr));
        checkHistoEqualize->setText(QCoreApplication::translate("MatrixImageView", "Histo Equalize", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixImageView: public Ui_MatrixImageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXIMAGEVIEW_H
