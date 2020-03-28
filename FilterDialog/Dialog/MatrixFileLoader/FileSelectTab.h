#pragma once

#include <QWidget>
#include <QFileSystemModel>

#include "Application/DataLayer.h"
#include "Dialog/MatrixFileLoader/FileSelectWidget.h"

class FileSelectTab : public QWidget
{
    Q_OBJECT

public:
   explicit FileSelectTab(DataLayerSPtr data, QWidget* parent);
   ~FileSelectTab() override = default;

signals:
   void startLoadingData();
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
   void finishedOpenFile();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
