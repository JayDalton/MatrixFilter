#pragma once

#include "Application/DataLayer.h"

#include <QWidget>
#include <QMainWindow>

class FilterDialog : public QMainWindow
{
    Q_OBJECT

public:
   explicit FilterDialog(DataLayerSPtr data);

   ~FilterDialog();
   //FilterDialog(FilterDialog&& rhs);
   //FilterDialog& operator=(FilterDialog&&);

protected:
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
