#pragma once

#include <QDialog>
#include <QWidget>
#include <QMainWindow>

#include <Config\Configuration.h>
#include "Application/DataLayer.h"

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
   explicit FilterDialog(DataLayerSPtr data);
   ~FilterDialog();

   void setConfig(const Configuration& config);

protected:
   bool eventFilter(QObject* object, QEvent* event) override;
   void closeEvent(QCloseEvent* event) override;

private:
   void setupDataLayers();
   void setupTabWidgets();
   void restoreSettings();
   void saveSettings();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

using FilterDialogUPtr = std::unique_ptr<FilterDialog>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
