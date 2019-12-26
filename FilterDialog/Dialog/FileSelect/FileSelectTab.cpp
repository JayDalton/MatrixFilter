#include <stdafx.h>

#include "FileSelectTab.h"

#include "ui_FileSelectTab.h"

#include <QMenu>
#include <QtGui/qevent.h>
#include <QPushButton>
#include <QAbstractItemView>
#include <QtWidgets\qfiledialog.h>
#include <QtWidgets\qmessagebox.h>
#include <Matrix/FileManager.h>

struct FileSelectTab::Impl
{
   explicit Impl(FileSelectTab* parent, DataLayerSPtr data) 
      : m_parent{ parent }, data{data} {}

   std::unique_ptr<QAction> m_openFile{nullptr};
   std::unique_ptr<QAction> m_saveFile{nullptr};

   QFileSystemModel fileModel;
   DataLayerSPtr data{ nullptr };
   Ui::FileSelectTab ui;

private:
   FileSelectTab* m_parent{ nullptr };
};

//////////////////////////////////////////////////////////////////////

FileSelectTab::FileSelectTab(DataLayerSPtr data, QWidget* parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);
   setupUIElements();
   setupActions();
}

void FileSelectTab::setupUIElements()
{
   auto con1 = connect(m->ui.openButton, &QPushButton::clicked, this, [&]() { selectDirectory(); });
   auto con2 = connect(m->ui.loadButton, &QPushButton::clicked, this, [&]() { loadFile(); });
   auto con3 = connect(m->ui.treeView, &QTreeView::doubleClicked, 
      this, [&](const QModelIndex& index) { openFile(index); });

   m->fileModel.setRootPath(QDir::currentPath());
   m->fileModel.setFilter(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot);
   m->fileModel.setNameFilterDisables(false);
   m->fileModel.setNameFilters({"*.pgm"});
   m->fileModel.setReadOnly(true);
   
   m->ui.treeView->setModel(&m->fileModel);
   m->ui.treeView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
   m->ui.treeView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
   m->ui.treeView->setSortingEnabled(true);
   m->ui.treeView->setAnimated(false);
   m->ui.treeView->setIndentation(20);
   m->ui.treeView->setColumnWidth(0, 200); // geschätzt

   setCurrentDir("c:/develop/dicom/raster/"); // save in config
}

void FileSelectTab::setupActions()
{
   m->m_openFile = std::make_unique<QAction>(tr("&Öffnen"));
   m->m_openFile->setShortcuts(QKeySequence::Open);
   m->m_openFile->setStatusTip(tr("Create a new file"));
   connect(m->m_openFile.get(), &QAction::triggered, this, &FileSelectTab::selectDirectory);

   m->m_saveFile = std::make_unique<QAction>(tr("&Sichern"));
   m->m_saveFile->setShortcuts(QKeySequence::Save);
   m->m_saveFile->setStatusTip(tr("Save existing file"));
   connect(m->m_saveFile.get(), &QAction::triggered, this, &FileSelectTab::saveFile);
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

void FileSelectTab::loadFile()
{
   auto* selectionModel = m->ui.treeView->selectionModel();
   if (!selectionModel->hasSelection())
   {
      return;
   }

   openFile(selectionModel->currentIndex());
   // switch dialog tab with file index
}

void FileSelectTab::saveFile()
{
}

void FileSelectTab::openFile(const QModelIndex& index)
{
   auto fileInfo = m->fileModel.fileInfo(index);
   auto filePath = m->fileModel.filePath(index);
   const auto matrixFile = filePath.toStdString();
   m->data->loadMatrixFile(MatrixFileInfo{ matrixFile });

   emit displayMatrixData();
}

void FileSelectTab::setCurrentDir(const QString& path)
{
   auto index = m->fileModel.index(path);
   m->ui.treeView->setRootIndex(index);
   m->ui.lineEdit->setText(path);
}

void FileSelectTab::contextMenuEvent(QContextMenuEvent* event)
{
   QMenu menu(this);
   menu.addAction(m->m_openFile.get());
   menu.addAction(m->m_saveFile.get());
   menu.exec(event->globalPos());
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
