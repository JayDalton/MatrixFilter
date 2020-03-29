#include <stdafx.h>

#include "FileSelectTab.h"

#include "ui_FileSelectTab.h"

#include <QMenu>
#include <QEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QAbstractItemView>
#include <QtConcurrent/QtConcurrent>

#include <Matrix/FileManager.h>

#include <unordered_set>
#include <future>

struct FileSelectTab::Impl
{
   explicit Impl(FileSelectTab* parent, DataLayerSPtr data) 
      : m_parent{ parent }, data{data} {}

   std::unique_ptr<QAction> m_openFile{nullptr};
   std::unique_ptr<QAction> m_saveFile{nullptr};

   const std::unordered_set<int> m_validKeys{
      Qt::Key_Return, Qt::Key_Space
   };

   DataLayerSPtr data{ nullptr };
   QFutureWatcher<void> openWatcher;

   Ui::FileSelectTab ui;

private:
   FileSelectTab* m_parent{ nullptr };
};

//////////////////////////////////////////////////////////////////////

FileSelectTab::FileSelectTab(DataLayerSPtr data, QWidget* parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);

   setupUIInteractions();
   setupContextActions();

   setCurrentDir("c:/develop/dicom/raster/"); // save in config
}

void FileSelectTab::setupUIInteractions()
{
   m->ui.treeView->installEventFilter(this);

   auto con1 = connect(m->ui.openButton, &QPushButton::clicked, 
      this, [&]() { selectDirectory(); });
   
   //auto con2 = connect(m->ui.treeView, &QTreeView::doubleClicked, 
   //   this, [&](const QModelIndex& index) { openFile(index); });

   auto con2 = connect(m->ui.treeView, &FileSelectWidget::fileSelected, 
      this, [&](const QFileInfo& fileInfo) { openFile(fileInfo); });

   auto con3 = connect(&m->openWatcher, &QFutureWatcher<void>::finished, 
      this, &FileSelectTab::finishedOpenFile);
}

void FileSelectTab::setupContextActions()
{
   m->m_openFile = std::make_unique<QAction>(tr("&Verzeichnis"));
   m->m_openFile->setShortcuts(QKeySequence::Open);
   m->m_openFile->setStatusTip(tr("Create a new file"));
   connect(m->m_openFile.get(), &QAction::triggered, this, &FileSelectTab::selectDirectory);
}

void FileSelectTab::selectDirectory()
{
   QFileDialog dialog{ this };
   dialog.setViewMode(QFileDialog::Detail);
   dialog.setFileMode(QFileDialog::Directory);
   dialog.setOption(QFileDialog::ShowDirsOnly);

   if (dialog.exec() == QDialog::Accepted)
   {
      setCurrentDir(dialog.selectedFiles().first());
   }
}

void FileSelectTab::finishedOpenFile()
{
   emit displayMatrixData();
}

void FileSelectTab::openFile(const QFileInfo& fileInfo)
{
   if (m->openWatcher.isRunning())
   {
      return;
   }

   auto openTask = [=]() 
   {
      auto filePath = fileInfo.absoluteFilePath();
      const auto matrixFile = filePath.toStdString();
      m->data->loadMatrixFile(MatrixFileInfo{ matrixFile });
   };

   emit startLoadingData();
   m->openWatcher.setFuture(QtConcurrent::run(openTask));
}

void FileSelectTab::setCurrentDir(const QString& path)
{
   m->ui.treeView->setRootDirectory(path);
   m->ui.lineEditDirectory->setText(path);
}

bool FileSelectTab::eventFilter(QObject* object, QEvent* event)
{
   if (event->type() != QEvent::KeyPress) 
   {
      return false;
   }

   const auto keyEvent{static_cast<QKeyEvent*>(event)};
   const auto keyValue{ keyEvent->key() };

   if (!m->m_validKeys.contains(keyValue))
   {
      return false;
   }

   //if (object == m->ui.treeView)
   //{
   //   auto selection = m->ui.treeView->selectionModel();
   //   openFile(selection->currentIndex());
   //   return true;
   //}

   return false;
}

void FileSelectTab::contextMenuEvent(QContextMenuEvent* event)
{
   QMenu menu(this);
   menu.addAction(m->m_openFile.get());
   menu.addAction(m->m_saveFile.get());
   menu.exec(event->globalPos());
}

void FileSelectTab::showEvent(QShowEvent* event)
{
   // set focus to treeView
   m->ui.treeView->setFocus();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
