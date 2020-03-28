#include "stdafx.h"

#include <QHeaderView>

#include "XTreeView.h"

#include "Application/DataLayer.h"

XTreeView::XTreeView(QWidget* parent, std::string_view name)
   : QTreeView(parent), m_widgetName(name)
{
   auto config = DataLayer::settings();
   auto state = config.value(m_widgetName);
   header()->restoreState(state.toByteArray());
}

XTreeView::~XTreeView()
{
   auto config = DataLayer::settings();
   config.setValue(m_widgetName, header()->saveState());
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
