/********************************************************************************
** Form generated from reading UI file 'ConfigurationEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATIONEDITOR_H
#define UI_CONFIGURATIONEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigurationEditor
{
public:
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QPushButton *pushButtonCancle;
    QPushButton *pushButtonSave;

    void setupUi(QWidget *ConfigurationEditor)
    {
        if (ConfigurationEditor->objectName().isEmpty())
            ConfigurationEditor->setObjectName(QString::fromUtf8("ConfigurationEditor"));
        ConfigurationEditor->resize(442, 307);
        gridLayout = new QGridLayout(ConfigurationEditor);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeView = new QTreeView(ConfigurationEditor);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        gridLayout->addWidget(treeView, 0, 0, 1, 2);

        pushButtonCancle = new QPushButton(ConfigurationEditor);
        pushButtonCancle->setObjectName(QString::fromUtf8("pushButtonCancle"));

        gridLayout->addWidget(pushButtonCancle, 1, 0, 1, 1);

        pushButtonSave = new QPushButton(ConfigurationEditor);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));

        gridLayout->addWidget(pushButtonSave, 1, 1, 1, 1);


        retranslateUi(ConfigurationEditor);

        QMetaObject::connectSlotsByName(ConfigurationEditor);
    } // setupUi

    void retranslateUi(QWidget *ConfigurationEditor)
    {
        ConfigurationEditor->setWindowTitle(QCoreApplication::translate("ConfigurationEditor", "ConfigurationEditor", nullptr));
        pushButtonCancle->setText(QCoreApplication::translate("ConfigurationEditor", "Abbrechen", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ConfigurationEditor", "Sichern", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigurationEditor: public Ui_ConfigurationEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATIONEDITOR_H
