#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FilterDialog.h"

class FilterDialog : public QMainWindow
{
    Q_OBJECT

public:
    FilterDialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::FilterDialogClass ui;
};
