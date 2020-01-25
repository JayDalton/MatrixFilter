#include "stdafx.h"

#include "Serialize/JsonWriter.h"

#include "ConfigurationEditor.h"

#include <QHeaderView>

ConfigurationEditor::ConfigurationEditor(QWidget* parent, const Configuration& config)
   : QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint), m_config(config)
{
    m_ui.setupUi(this);
    setupGUIElements();

    m_model->setConfiguration(config);
    m_ui.treeView->resizeColumnToContents(0);
    m_ui.treeView->header()->setStretchLastSection(true);

    m_ui.treeView->setItemDelegate(m_delegate.get());

    setWindowTitle(
       QString("Config Editor: %1")
       .arg(QString::fromStdString(config.m_label))
    );

    auto con1 = connect(m_ui.pushButtonSave, &QPushButton::clicked, this, [&]() { accept(); });
    auto con2 = connect(m_ui.pushButtonCancle, &QPushButton::clicked, this, [&]() { reject(); });
}

ConfigurationEditor::~ConfigurationEditor() = default;

const Configuration& ConfigurationEditor::getModifiedConfig() const
{
   return m_model->getConfiguration();
}

const Configuration& ConfigurationEditor::getOriginalConfig() const
{
   return m_config;
}

std::string ConfigurationEditor::toString() const
{
   std::ostringstream oss;
   JsonWriter writer{oss};
   m_config.writeTo(writer);
   return oss.str();
}

void ConfigurationEditor::closeEvent(QCloseEvent* event)
{
   saveSettings();
   QWidget::closeEvent(event);
}

void ConfigurationEditor::setupGUIElements()
{
   m_model = std::make_unique<ConfigurationModel>();
   m_proxy = std::make_unique<ConfigurationProxy>();
   m_proxy->setSourceModel(m_model.get());
   m_ui.treeView->setModel(m_proxy.get());

   //m_ui.treeView->setHeaderHidden(true);
   m_ui.treeView->setUniformRowHeights(true);
   m_ui.treeView->setAlternatingRowColors(true);

   m_delegate = std::make_unique<ConfigurationDelegate>(m_proxy.get());
}

void ConfigurationEditor::restoreSettings()
{
   QSettings settings;
   restoreGeometry(settings.value("geometry").toByteArray());
}

void ConfigurationEditor::saveSettings()
{
   QSettings settings;
   settings.setValue("geometry", saveGeometry());
}

/////////////////////////////////////////////////////////////////////////////

IntegerParameterEditor::IntegerParameterEditor(QWidget* parent, const IntegerParameter& param)
   : QSpinBox(parent)
{
   setMaximum(param.getMaximum());
   setMinimum(param.getMinimum());
   setValue(param.getCurrent());
}

DoubleParameterEditor::DoubleParameterEditor(QWidget* parent, const DoubleParameter& param)
   : QDoubleSpinBox(parent)
{
   setMaximum(param.getMaximum());
   setMinimum(param.getMinimum());
   setValue(param.getCurrent());
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
