#include "stdafx.h"

#include "ui_LoggerView.h"

#include "LoggerView.h"

struct LoggerView::Impl
{
   explicit Impl(LoggerView* parent, DataLayerSPtr data) 
      : parent(parent), data(data) {}

   DataLayerSPtr data{ nullptr };
   Ui::LoggerView ui;

private:
   LoggerView* parent{ nullptr };
};

LoggerView::LoggerView(DataLayerSPtr data, QWidget* parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);

   m->ui.loggerWidget;
}

LoggerView::~LoggerView() = default;



// Codepage: UTF-8 (ÜüÖöÄäẞß)
