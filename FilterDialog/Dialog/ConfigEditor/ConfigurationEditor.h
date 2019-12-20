#pragma once

#include <QDialog>

#include "ui_ConfigurationEditor.h"

#include "Config/Configuration.h"

class ConfigurationEditor : public QDialog
{
   Q_OBJECT

public:
   ConfigurationEditor(QWidget* parent, const Configuration& config);
   ~ConfigurationEditor();

   std::string getConfig() const;

private:
   Ui::ConfigurationEditor m_ui;
   Configuration m_config;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
