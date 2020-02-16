#include "stdafx.h"

#include "ProgressBar.h"

ProgressBar::ProgressBar(QWidget* parent)
   : QProgressBar(parent)
{
   setTextVisible(false);
}

void ProgressBar::setBusyIndicator(bool active)
{
   setMaximum(active ? 0 : 100);
   setMinimum(0);
   setValue(0);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
