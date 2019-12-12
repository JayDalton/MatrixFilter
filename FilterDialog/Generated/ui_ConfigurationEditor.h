/********************************************************************************
** Form generated from reading UI file 'ConfigurationEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATIONEDITOR_H
#define UI_CONFIGURATIONEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigurationEditor
{
public:
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancle;

    void setupUi(QWidget *ConfigurationEditor)
    {
        if (ConfigurationEditor->objectName().isEmpty())
            ConfigurationEditor->setObjectName(QString::fromUtf8("ConfigurationEditor"));
        ConfigurationEditor->resize(400, 300);
        pushButtonSave = new QPushButton(ConfigurationEditor);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(50, 240, 93, 28));
        pushButtonCancle = new QPushButton(ConfigurationEditor);
        pushButtonCancle->setObjectName(QString::fromUtf8("pushButtonCancle"));
        pushButtonCancle->setGeometry(QRect(210, 240, 93, 28));

        retranslateUi(ConfigurationEditor);

        QMetaObject::connectSlotsByName(ConfigurationEditor);
    } // setupUi

    void retranslateUi(QWidget *ConfigurationEditor)
    {
        ConfigurationEditor->setWindowTitle(QCoreApplication::translate("ConfigurationEditor", "ConfigurationEditor", nullptr));
        pushButtonSave->setText(QCoreApplication::translate("ConfigurationEditor", "Sichern", nullptr));
        pushButtonCancle->setText(QCoreApplication::translate("ConfigurationEditor", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigurationEditor: public Ui_ConfigurationEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATIONEDITOR_H
