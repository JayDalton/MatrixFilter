#include "stdafx.h"

#include "Serialize/JsonWriter.h"

#include "ConfigurationEditor.h"

ConfigurationEditor::ConfigurationEditor(QWidget* parent, const Configuration& config)
   : QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint), m_config(config)
{
    m_ui.setupUi(this);
    setupGUIElements();

    setWindowTitle(tr("Configuration Editor"));

    auto con1 = connect(m_ui.pushButtonSave, &QPushButton::clicked, this, [&]() { accept(); });
    auto con2 = connect(m_ui.pushButtonCancle, &QPushButton::clicked, this, [&]() { reject(); });
}

ConfigurationEditor::~ConfigurationEditor() = default;

const Configuration& ConfigurationEditor::getConfig() const
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

void ConfigurationEditor::setContent(std::string_view content)
{
}

void ConfigurationEditor::setupGUIElements()
{
   m_model = std::make_unique<ConfigurationModel>();
   m_proxy = std::make_unique<ConfigurationProxy>();
   m_proxy->setSourceModel(m_model.get());
   m_ui.treeView->setModel(m_proxy.get());
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
