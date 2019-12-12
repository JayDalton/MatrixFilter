#pragma once

#include <QDialog>

#include "ui_ConfigurationEditor.h"

class ConfigurationEditor : public QDialog
{
   Q_OBJECT

public:
   ConfigurationEditor(QWidget *parent = nullptr);
   ~ConfigurationEditor();

private:
    Ui::ConfigurationEditor m_ui;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
