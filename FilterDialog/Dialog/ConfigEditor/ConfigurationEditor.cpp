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
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
