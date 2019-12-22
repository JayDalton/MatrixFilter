#pragma once

#include <QWidget>

#include "Application/DataLayer.h"
#include <Dialog\FileSelect\FileSelectModel.h>

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
   void setupMenus();

   void openFile();
   void loadFile();
   void saveFile();

private:
   struct Impl;
   std::unique_ptr<Impl> m;

   FileSelectModelPtr m_fileSelectModel{ nullptr };
   FileSelectProxyPtr m_fileSelectProxy{ nullptr };
};
