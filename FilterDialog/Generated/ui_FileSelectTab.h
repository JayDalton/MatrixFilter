/********************************************************************************
** Form generated from reading UI file 'FileSelectTab.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILESELECTTAB_H
#define UI_FILESELECTTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileSelectTab
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *directoryLayout;
    QPushButton *openButton;
    QLineEdit *lineEditDirectory;
    QTreeView *treeView;

    void setupUi(QWidget *FileSelectTab)
    {
        if (FileSelectTab->objectName().isEmpty())
            FileSelectTab->setObjectName(QString::fromUtf8("FileSelectTab"));
        FileSelectTab->resize(636, 370);
        verticalLayout = new QVBoxLayout(FileSelectTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        directoryLayout = new QHBoxLayout();
        directoryLayout->setSpacing(6);
        directoryLayout->setObjectName(QString::fromUtf8("directoryLayout"));
        openButton = new QPushButton(FileSelectTab);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setFocusPolicy(Qt::StrongFocus);

        directoryLayout->addWidget(openButton);

        lineEditDirectory = new QLineEdit(FileSelectTab);
        lineEditDirectory->setObjectName(QString::fromUtf8("lineEditDirectory"));
        lineEditDirectory->setFocusPolicy(Qt::NoFocus);
        lineEditDirectory->setReadOnly(true);

        directoryLayout->addWidget(lineEditDirectory);


        verticalLayout->addLayout(directoryLayout);

        treeView = new QTreeView(FileSelectTab);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        QWidget::setTabOrder(treeView, openButton);
        QWidget::setTabOrder(openButton, lineEditDirectory);

        retranslateUi(FileSelectTab);

        QMetaObject::connectSlotsByName(FileSelectTab);
    } // setupUi

    void retranslateUi(QWidget *FileSelectTab)
    {
        FileSelectTab->setWindowTitle(QCoreApplication::translate("FileSelectTab", "FileSelectTab", nullptr));
        openButton->setText(QCoreApplication::translate("FileSelectTab", "Verzeichnis...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileSelectTab: public Ui_FileSelectTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILESELECTTAB_H
