#include "stdafx.h"

#include "Serialize/JsonWriter.h"
#include "ConfigurationEditor.h"

#include <QDebug>
#include <QKeyEvent>
#include <QHeaderView>

ConfigurationEditor::ConfigurationEditor(QWidget* parent, const Configuration& config)
   : QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint), m_config(config)
{
    m_ui.setupUi(this);
    setupGUIElements();

    installEventFilter(this);

    m_model->setConfiguration(config);
    m_ui.treeView->installEventFilter(this);
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

const ParameterListing& ConfigurationEditor::toVector() const
{
   return m_model->getParameterListing();
}

bool ConfigurationEditor::eventFilter(QObject* object, QEvent* event)
{
   if (event->type() != QEvent::KeyPress)
   {
      return false;
   }

   const auto keyEvent{static_cast<QKeyEvent*>(event)};
   const auto keyValue{ keyEvent->key() };

   if (object == this && m_treeViewKeySet.count(keyValue))
   {
      m_ui.treeView->setFocus();
      qDebug() << "SaveBtn Key: " << keyEvent->key();
      //return QCoreApplication::sendEvent(m_ui.treeView, event);
      return true;
   }
   if (object == m_ui.treeView && m_treeViewKeySet.count(keyValue))
   {
      qDebug() << "TreeView Key: " << keyEvent->key();
      return true;
   }

   return QObject::eventFilter(object, event);
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

   m_ui.treeView->setHeaderHidden(true);
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


// Codepage: UTF-8 (ÜüÖöÄäẞß)
