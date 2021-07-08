#pragma once

#include <QProgressBar>
#include <QTimer>

class XProgressBar : public QProgressBar
{
   Q_OBJECT

public:
   XProgressBar(QWidget* parent = nullptr);
   ~XProgressBar() override = default;

   void setBusyIndicator(bool active);

private:
   QTimer m_timer;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
