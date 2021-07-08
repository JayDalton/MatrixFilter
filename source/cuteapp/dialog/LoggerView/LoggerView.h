#pragma once

#include <QWidget>

#include "Application/DataLayer.h"

class LoggerView : public QWidget
{
   Q_OBJECT

public:
   LoggerView(DataLayerSPtr data, QWidget* parent);
   ~LoggerView();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
