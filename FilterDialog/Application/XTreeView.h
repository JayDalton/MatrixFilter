#pragma once

#include <QTreeView>

#include "Application/XLatin1String.h"

class XTreeView : public QTreeView
{
   Q_OBJECT

public:
    XTreeView(QWidget* parent, std::string_view name);
    ~XTreeView() override;

private:
   const XLatin1String m_widgetName;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
