#include "stdafx.h"
#include "ConfigurationEditor.h"

ConfigurationEditor::ConfigurationEditor(QWidget* parent, const Configuration& config)
   : QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint), m_config(config)
{
    m_ui.setupUi(this);

    connect(m_ui.pushButtonSave, &QPushButton::clicked, this, [&]() { accept(); });
    connect(m_ui.pushButtonCancle, &QPushButton::clicked, this, [&]() { reject(); });
}

ConfigurationEditor::~ConfigurationEditor() = default;



// Codepage: UTF-8 (ÜüÖöÄäẞß)
