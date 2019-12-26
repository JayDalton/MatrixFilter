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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "MatrixFrameView.h"

QT_BEGIN_NAMESPACE

class Ui_MatrixImageView
{
public:
    QGridLayout *gridLayout;
    QGroupBox *suaceGroupBox;
    QCheckBox *checkHistoEqualize;
    QGroupBox *claheGroupBox;
    QSpacerItem *verticalSpacer;
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
        suaceGroupBox = new QGroupBox(MatrixImageView);
        suaceGroupBox->setObjectName(QString::fromUtf8("suaceGroupBox"));
        suaceGroupBox->setCheckable(true);
        suaceGroupBox->setChecked(false);

        gridLayout->addWidget(suaceGroupBox, 2, 1, 1, 1);

        checkHistoEqualize = new QCheckBox(MatrixImageView);
        checkHistoEqualize->setObjectName(QString::fromUtf8("checkHistoEqualize"));

        gridLayout->addWidget(checkHistoEqualize, 0, 1, 1, 1);

        claheGroupBox = new QGroupBox(MatrixImageView);
        claheGroupBox->setObjectName(QString::fromUtf8("claheGroupBox"));
        claheGroupBox->setCheckable(true);
        claheGroupBox->setChecked(false);

        gridLayout->addWidget(claheGroupBox, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        frameView = new MatrixFrameView(MatrixImageView);
        frameView->setObjectName(QString::fromUtf8("frameView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameView->sizePolicy().hasHeightForWidth());
        frameView->setSizePolicy(sizePolicy);
        frameView->setFrameShape(QFrame::StyledPanel);
        frameView->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameView, 0, 0, 4, 1);


        retranslateUi(MatrixImageView);

        QMetaObject::connectSlotsByName(MatrixImageView);
    } // setupUi

    void retranslateUi(QWidget *MatrixImageView)
    {
        MatrixImageView->setWindowTitle(QCoreApplication::translate("MatrixImageView", "MatrixImageView", nullptr));
        suaceGroupBox->setTitle(QCoreApplication::translate("MatrixImageView", "SUACE", nullptr));
        checkHistoEqualize->setText(QCoreApplication::translate("MatrixImageView", "Histo Equalize", nullptr));
        claheGroupBox->setTitle(QCoreApplication::translate("MatrixImageView", "CLAHE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixImageView: public Ui_MatrixImageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXIMAGEVIEW_H
