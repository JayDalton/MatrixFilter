#pragma once

#include <QSpinBox>

class XIntegerSpinBox : public QSpinBox
{
   Q_OBJECT

public:
   XIntegerSpinBox(QWidget *parent);
   ~XIntegerSpinBox();
};

////////////////////////////////////////////////////////////

class XDoubleSpinBox : public QDoubleSpinBox
{
   Q_OBJECT

public:
   XDoubleSpinBox(QWidget *parent);
   ~XDoubleSpinBox();
};


// Codepage: UTF-8 (ÜüÖöÄäẞß)
