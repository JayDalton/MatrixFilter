#include <stdafx.h>

#include "FilterDialog.h"
#include "Generated/ui_FilterDialog.h"

#include "QTabWidget"
#include "QKeyEvent"
#include "QTimer"

#include "MatrixFileLoader/FileSelectTab.h"
#include "MatrixDataView/MatrixDataTab.h"
#include "MatrixDataPlot/MatrixDataPlot.h"
#include "MatrixImageView/MatrixImageView.h"

#include "Application/DataLayer.h"

struct FilterDialog::Impl
{
   explicit Impl(DataLayerSPtr data) : data(data) {}

   FileSelectTab* tabFileSelect{ nullptr };
   MatrixDataTab* tabMatrixData{ nullptr };
   MatrixDataPlot* tabMatrixPlot{ nullptr };
   MatrixImageView* tabMatrixView{ nullptr };

   DataLayerSPtr data{ nullptr };

   QTimer m_progressTimer;

   Ui::FilterDialogClass ui;
};

//////////////////////////////////////////////////////////////////

FilterDialog::FilterDialog(DataLayerSPtr data)
   : QDialog(nullptr, Qt::Window), m{ std::make_unique<Impl>(data) }
{
   m->ui.setupUi(this);

   restoreSettings();
   setupDataLayers();
   setupTabWidgets();
   setupProgress();

   installEventFilter(this);

   setWindowTitle(tr("Matrix Filter Dialog"));
}

FilterDialog::~FilterDialog() = default;

void FilterDialog::setConfig(const Configuration& config)
{
}

bool FilterDialog::eventFilter(QObject* object, QEvent* event)
{
   if (event->type() != QEvent::KeyPress) 
   {
      return false;
   }

   if (auto* keyEvent = static_cast<QKeyEvent*>(event))
   {
      if (keyEvent->key() == Qt::Key_Escape) {
         QCoreApplication::exit();
         return true;
      }
   }

   return false;
}

void FilterDialog::closeEvent(QCloseEvent* event)
{
   auto config = m->data->settings();
   config.setValue("geometry", saveGeometry());
   QWidget::closeEvent(event);
}

void FilterDialog::restoreSettings()
{
   const auto settings = m->data->settings();
   restoreGeometry(settings.value("geometry").toByteArray());
}

void FilterDialog::setupProgress()
{
   m->ui.progressBar->setTextVisible(false);
   m->ui.progressBar->setMaximum(0);
   m->ui.progressBar->setMinimum(0);
   m->ui.progressBar->setValue(0);

   using namespace std::chrono_literals;
   m->m_progressTimer.setInterval(100ms);
   m->m_progressTimer.setSingleShot(false);
   m->m_progressTimer.callOnTimeout(this, &FilterDialog::updateProgress);
   //m->m_progressTimer.start(); // ???
}

void FilterDialog::updateProgress()
{
   const auto value = m->ui.progressBar->value();
   m->ui.progressBar->setValue(100 <= value ? 0 : value + 1);
}

void FilterDialog::saveSettings()
{
}

void FilterDialog::setupDataLayers()
{
   //m->data->loadConfiguration();
}

void FilterDialog::setupTabWidgets()
{
   m->tabFileSelect = new FileSelectTab{ m->data, this };
   m->ui.tabWidget->addTab(m->tabFileSelect, tr("File Select"));

   m->tabMatrixView = new MatrixImageView{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixView, tr("Matrix View"));

   m->tabMatrixData = new MatrixDataTab{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixData, tr("Matrix Data"));

   m->tabMatrixPlot = new MatrixDataPlot{ m->data, this };
   m->ui.tabWidget->addTab(m->tabMatrixPlot, tr("Matrix Plot"));

   auto con = connect(m->tabFileSelect, &FileSelectTab::displayMatrixData, 
      this, [=]() { m->ui.tabWidget->setCurrentWidget(m->tabMatrixView); }
   );
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
