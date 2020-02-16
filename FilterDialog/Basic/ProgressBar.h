#pragma once

#include <QProgressBar>
#include <QTimer>

class ProgressBar : public QProgressBar
{
   Q_OBJECT

public:
   ProgressBar(QWidget* parent = nullptr);
   ~ProgressBar() override = default;

   void setBusyIndicator(bool active);

private:
   QTimer m_timer;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
