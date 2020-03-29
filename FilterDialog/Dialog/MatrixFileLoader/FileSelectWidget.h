#pragma once

#include <unordered_set>

#include <QKeyEvent>
#include <QFileSystemModel>
#include <QFileSystemWatcher>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "Matrix/MatrixFile.h"
#include "Application/XTreeView.h"

class FileSelectModel final : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Name, Type, Size, Path, Extension, Count };

   explicit FileSelectModel();
   ~FileSelectModel() override = default;

   void setImageMatrix(MatrixFileInfo matrixFile);
   void reloadFileModel(const MatrixFileRepository& repository);
   MatrixFileInfo getMatrixFile(const QModelIndex& index) const;

   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

private:
   QString formatFileType(MatrixFileInfo::Type type) const;
   void searchForFiles();

private:
   MatrixFileRepository m_repository;
};

using FileSelectModelPtr = std::unique_ptr<FileSelectModel>;

//////////////////////////////////////////////////////////////////////////////////////////

class FileSelectProxy final : public QSortFilterProxyModel
{
public:
   explicit FileSelectProxy(QObject* parent = nullptr);
   ~FileSelectProxy() override = default;

   void updateSearch(const QString& searchString);
   uint getSourceIndex(const QModelIndex& index);
   MatrixFileInfo getSourceContact(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using FileSelectProxyPtr = std::unique_ptr<FileSelectProxy>;

//////////////////////////////////////////////////////////////////////////////////////////

class FileSelectWidget : public XTreeView
{
   Q_OBJECT

public:
   FileSelectWidget(QWidget *parent);
   ~FileSelectWidget() override = default;

   void setRootDirectory(const QString& directory);

signals:
   void fileSelected(const QFileInfo& fileInfo);
   void fileChoosen(const QFileInfo& fileInfo);

protected:
   bool eventFilter(QObject* object, QEvent* event) override;
   void showEvent(QShowEvent* event) override;
   void hideEvent(QHideEvent* event) override;

private:
   void setupModel(QAbstractItemModel* model);
   void handleRowsAboutToBeInserted();
   void handleRowsInserted();
   void handleUpdate();

private:
   QFileSystemModel m_fileModel;
   //QFileSystemWatcher m_fileWatcher; // ???
   const std::unordered_set<int> m_validKeys{
      Qt::Key_Return, Qt::Key_Space
   };

   bool m_autoScrolling{ true };
   bool m_isFreezed{ false };
};


// Codepage: UTF-8 (ÜüÖöÄäẞß)
