#pragma once

#include <QDialog>

#include "ui_ConfigurationEditor.h"

#include "Config/Configuration.h"
#include "Application/DataLayer.h"
#include "Dialog/ConfigEditor/ConfigurationModel.h"

class ConfigurationEditor : public QDialog
{
   Q_OBJECT

public:
   ConfigurationEditor(QWidget* parent, const Configuration& config);
   ConfigurationEditor(QWidget* parent, DataLayerSPtr data);
   ~ConfigurationEditor();

   const Configuration& getModifiedConfig() const;
   const Configuration& getOriginalConfig() const;

   std::string toString() const;
   const ParameterListing& toVector() const;

protected:
   //bool eventFilter(QObject* object, QEvent* event) override;
   void closeEvent(QCloseEvent* event) override;

private:
   void setupGUIElements();
   void restoreSettings();
   void saveSettings();

private:
   //struct Impl;
   //std::unique_ptr<Impl> m;

   Ui::ConfigurationEditor m_ui;
   const Configuration m_config;
   ConfigurationModelPtr m_model;
   ConfigurationProxyPtr m_proxy;
   ConfigurationDelegatePtr m_delegate;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
