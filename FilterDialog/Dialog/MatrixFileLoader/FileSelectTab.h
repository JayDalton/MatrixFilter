#pragma once

#include <QWidget>
#include <QFileSystemModel>

#include "Application/DataLayer.h"
#include "Dialog/MatrixFileLoader/FileSelectModel.h"

class FileSelectTab : public QWidget
{
    Q_OBJECT

public:
   explicit FileSelectTab(DataLayerSPtr data, QWidget* parent);
   ~FileSelectTab() = default;

signals:
   void displayMatrixData();

protected:
   bool eventFilter(QObject* object, QEvent* event) override;
   void contextMenuEvent(QContextMenuEvent* event) override;

private:
   void setupUIElements();
   void setupUIInteractions();
   void setupContextActions();

   void openFile(const QModelIndex& index);
   void setCurrentDir(const QString& path);
   void selectDirectory();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
