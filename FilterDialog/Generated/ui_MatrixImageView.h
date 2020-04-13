/********************************************************************************
** Form generated from reading UI file 'MatrixImageView.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXIMAGEVIEW_H
#define UI_MATRIXIMAGEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MatrixFrameView.h"

QT_BEGIN_NAMESPACE

class Ui_MatrixImageView
{
public:
    QGridLayout *gridLayout;
    QGroupBox *contrastGroupBox;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *contrastSpinBoxIntensity;
    QGroupBox *structureGroupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QSpinBox *structureSpinBoxDistance;
    QLabel *label_4;
    QSpinBox *structureSpinBoxSigma;
    QCheckBox *checkHistoEqualize;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_3;
    QGroupBox *claheGroupBox;
    QVBoxLayout *verticalLayout;
    QLabel *claheLabelClipBox;
    QSpinBox *claheSpinBoxSize;
    QLabel *claheLabelSizeBox;
    QDoubleSpinBox *claheSpinBoxClip;
    MatrixFrameView *frameView;
    QComboBox *comboBox;

    void setupUi(QWidget *MatrixImageView)
    {
        if (MatrixImageView->objectName().isEmpty())
            MatrixImageView->setObjectName(QString::fromUtf8("MatrixImageView"));
        MatrixImageView->resize(746, 703);
        gridLayout = new QGridLayout(MatrixImageView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        contrastGroupBox = new QGroupBox(MatrixImageView);
        contrastGroupBox->setObjectName(QString::fromUtf8("contrastGroupBox"));
        contrastGroupBox->setCheckable(true);
        contrastGroupBox->setChecked(false);
        verticalLayout_3 = new QVBoxLayout(contrastGroupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        contrastSpinBoxIntensity = new QSpinBox(contrastGroupBox);
        contrastSpinBoxIntensity->setObjectName(QString::fromUtf8("contrastSpinBoxIntensity"));

        verticalLayout_3->addWidget(contrastSpinBoxIntensity);


        gridLayout->addWidget(contrastGroupBox, 9, 1, 1, 1);

        structureGroupBox = new QGroupBox(MatrixImageView);
        structureGroupBox->setObjectName(QString::fromUtf8("structureGroupBox"));
        structureGroupBox->setCheckable(true);
        structureGroupBox->setChecked(false);
        verticalLayout_4 = new QVBoxLayout(structureGroupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_5 = new QLabel(structureGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        structureSpinBoxDistance = new QSpinBox(structureGroupBox);
        structureSpinBoxDistance->setObjectName(QString::fromUtf8("structureSpinBoxDistance"));

        verticalLayout_4->addWidget(structureSpinBoxDistance);

        label_4 = new QLabel(structureGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        structureSpinBoxSigma = new QSpinBox(structureGroupBox);
        structureSpinBoxSigma->setObjectName(QString::fromUtf8("structureSpinBoxSigma"));

        verticalLayout_4->addWidget(structureSpinBoxSigma);


        gridLayout->addWidget(structureGroupBox, 10, 1, 1, 1);

        checkHistoEqualize = new QCheckBox(MatrixImageView);
        checkHistoEqualize->setObjectName(QString::fromUtf8("checkHistoEqualize"));

        gridLayout->addWidget(checkHistoEqualize, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 12, 1, 1, 1);

        groupBox_2 = new QGroupBox(MatrixImageView);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setCheckable(true);
        groupBox_2->setChecked(false);
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

        verticalLayout_2->addWidget(doubleSpinBox);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        doubleSpinBox_2 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

        verticalLayout_2->addWidget(doubleSpinBox_2);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        doubleSpinBox_3 = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));

        verticalLayout_2->addWidget(doubleSpinBox_3);


        gridLayout->addWidget(groupBox_2, 5, 1, 1, 1);

        claheGroupBox = new QGroupBox(MatrixImageView);
        claheGroupBox->setObjectName(QString::fromUtf8("claheGroupBox"));
        claheGroupBox->setCheckable(true);
        claheGroupBox->setChecked(false);
        verticalLayout = new QVBoxLayout(claheGroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        claheLabelClipBox = new QLabel(claheGroupBox);
        claheLabelClipBox->setObjectName(QString::fromUtf8("claheLabelClipBox"));

        verticalLayout->addWidget(claheLabelClipBox);

        claheSpinBoxSize = new QSpinBox(claheGroupBox);
        claheSpinBoxSize->setObjectName(QString::fromUtf8("claheSpinBoxSize"));

        verticalLayout->addWidget(claheSpinBoxSize);

        claheLabelSizeBox = new QLabel(claheGroupBox);
        claheLabelSizeBox->setObjectName(QString::fromUtf8("claheLabelSizeBox"));

        verticalLayout->addWidget(claheLabelSizeBox);

        claheSpinBoxClip = new QDoubleSpinBox(claheGroupBox);
        claheSpinBoxClip->setObjectName(QString::fromUtf8("claheSpinBoxClip"));

        verticalLayout->addWidget(claheSpinBoxClip);


        gridLayout->addWidget(claheGroupBox, 3, 1, 1, 1);

        frameView = new MatrixFrameView(MatrixImageView);
        frameView->setObjectName(QString::fromUtf8("frameView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frameView->sizePolicy().hasHeightForWidth());
        frameView->setSizePolicy(sizePolicy);
        frameView->setFrameShape(QFrame::StyledPanel);
        frameView->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameView, 0, 0, 13, 1);

        comboBox = new QComboBox(MatrixImageView);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 1, 1, 1, 1);


        retranslateUi(MatrixImageView);

        QMetaObject::connectSlotsByName(MatrixImageView);
    } // setupUi

    void retranslateUi(QWidget *MatrixImageView)
    {
        MatrixImageView->setWindowTitle(QCoreApplication::translate("MatrixImageView", "MatrixImageView", nullptr));
        contrastGroupBox->setTitle(QCoreApplication::translate("MatrixImageView", "Kontrast", nullptr));
        structureGroupBox->setTitle(QCoreApplication::translate("MatrixImageView", "Struktur", nullptr));
        label_5->setText(QCoreApplication::translate("MatrixImageView", "Distanz", nullptr));
        label_4->setText(QCoreApplication::translate("MatrixImageView", "Sigma", nullptr));
        checkHistoEqualize->setText(QCoreApplication::translate("MatrixImageView", "Histo Equalize", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MatrixImageView", "Sch\303\244rfen", nullptr));
        label->setText(QCoreApplication::translate("MatrixImageView", "Sigma", nullptr));
        label_3->setText(QCoreApplication::translate("MatrixImageView", "St\303\244rke", nullptr));
        label_2->setText(QCoreApplication::translate("MatrixImageView", "Schwellenwert", nullptr));
        claheGroupBox->setTitle(QCoreApplication::translate("MatrixImageView", "CLAHE", nullptr));
        claheLabelClipBox->setText(QCoreApplication::translate("MatrixImageView", "Gr\303\266\303\237e (Size)", nullptr));
        claheLabelSizeBox->setText(QCoreApplication::translate("MatrixImageView", "St\303\244rke (Clip)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatrixImageView: public Ui_MatrixImageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXIMAGEVIEW_H
