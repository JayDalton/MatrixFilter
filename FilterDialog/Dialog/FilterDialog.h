﻿#pragma once

#include <QDialog>
#include <QWidget>
#include <QMainWindow>

#include "Config/Configuration.h"
#include "Application/DataLayer.h"
#include "Basic/TLatin1String.h"

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
   explicit FilterDialog(DataLayerSPtr data);
   ~FilterDialog();

protected:
   bool eventFilter(QObject* object, QEvent* event) override;

private:
   void setupTabWidgets();
   void restoreSettings();
   void saveSettings();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
   static constexpr TLatin1String WIDGET_GEOMETRY{ "DialogGeometry" };
};

using FilterDialogUPtr = std::unique_ptr<FilterDialog>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
