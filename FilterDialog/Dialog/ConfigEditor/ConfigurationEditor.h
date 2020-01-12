#pragma once

#include <QDialog>

#include "ui_ConfigurationEditor.h"

#include "Serialize/JsonReader.h"
#include "Serialize/JsonWriter.h"
#include "Config/Configuration.h"

#include "Dialog/ConfigEditor/ConfigurationModel.h"

class ConfigurationEditor : public QDialog
{
   Q_OBJECT

public:
   ConfigurationEditor(QWidget* parent, const Configuration& config);
   ~ConfigurationEditor();

   const Configuration& getModifiedConfig() const;
   const Configuration& getOriginalConfig() const;

   std::string toString() const;

private:
   void setupGUIElements();

private:
   Ui::ConfigurationEditor m_ui;
   ConfigurationModelPtr m_model;
   ConfigurationProxyPtr m_proxy;
   const Configuration m_config;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
