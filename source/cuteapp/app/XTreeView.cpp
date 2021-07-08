#include "stdafx.h"

#include <QHeaderView>

#include "Application/DataLayer.h"
#include "Application/XTreeView.h"

XTreeView::XTreeView(QWidget* parent, std::string_view name)
   : QTreeView(parent), m_widgetName(name)
{
   setRootIsDecorated(false);
   setUniformRowHeights(true);

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
