#include "stdafx.h"

#include "XProgressBar.h"

XProgressBar::XProgressBar(QWidget* parent)
   : QProgressBar(parent)
{
   setTextVisible(false);
}

void XProgressBar::setBusyIndicator(bool active)
{
   setMaximum(active ? 0 : 100);
   setMinimum(0);
   setValue(0);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
