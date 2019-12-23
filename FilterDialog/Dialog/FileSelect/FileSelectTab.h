#pragma once

#include <QWidget>
#include <QFileSystemModel>

#include "Application/DataLayer.h"
#include "Dialog\FileSelect\FileSelectModel.h"

class FileSelectTab : public QWidget
{
    Q_OBJECT

public:
   explicit FileSelectTab(DataLayerSPtr data, QWidget* parent);
   ~FileSelectTab() = default;

signals:
   void displayMatrixData();

protected:
   void contextMenuEvent(QContextMenuEvent* event) override;

private:
   void setupUIElements();
   void setupActions();

   void setCurrentDir(const QString& path);
   void selectDirectory();
   void loadFile();
   void saveFile();
   void openFile(const QModelIndex& index);

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};
