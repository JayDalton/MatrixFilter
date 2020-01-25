#pragma once

#include <QDialog>
#include <QSpinBox>

#include "ui_ConfigurationEditor.h"

//#include "Serialize/JsonReader.h"
//#include "Serialize/JsonWriter.h"
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

class IntegerParameterEditor : public QSpinBox
{
   Q_OBJECT
public:
   IntegerParameterEditor(QWidget* parent, const IntegerParameter& param);

private:
   signed m_minimum{ 0 };
   signed m_maximum{ 0 };
   signed m_current{ 0 };
};

class DoubleParameterEditor : public QDoubleSpinBox
{
   Q_OBJECT
public:
   DoubleParameterEditor(QWidget* parent, const DoubleParameter& param);

private:
   double m_minimum{ 0 };
   double m_maximum{ 0 };
   double m_current{ 0 };
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
