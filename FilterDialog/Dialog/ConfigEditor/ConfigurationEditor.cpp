#include "stdafx.h"

#include "Serialize/JsonWriter.h"

#include "ConfigurationEditor.h"

ConfigurationEditor::ConfigurationEditor(QWidget* parent, const Configuration& config)
   : QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint), m_config(config)
{
    m_ui.setupUi(this);

    setWindowTitle(tr("Configuration Editor"));

    connect(m_ui.pushButtonSave, &QPushButton::clicked, this, [&]() { accept(); });
    connect(m_ui.pushButtonCancle, &QPushButton::clicked, this, [&]() { reject(); });
}

ConfigurationEditor::~ConfigurationEditor() = default;

const Configuration& ConfigurationEditor::getConfig() const
{
   return m_config;
}

std::string ConfigurationEditor::getString() const
{
   // TODO implementieren ...
   JsonWriter writer{};
   m_config.save(writer);
   return writer.getString();
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
