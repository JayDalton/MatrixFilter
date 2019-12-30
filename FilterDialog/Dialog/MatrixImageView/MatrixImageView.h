#pragma once

#include "Application/DataLayer.h"

#include <QWidget>

class MatrixImageView : public QWidget
{
    Q_OBJECT

public:
    explicit MatrixImageView(DataLayerSPtr data, QWidget* parent);
    ~MatrixImageView();

protected:
   bool eventFilter(QObject* object, QEvent* event) override;
   void keyReleaseEvent(QKeyEvent* event) override;

private:
   void setupUIElements();
   void applyFilterSetting();
   void loadFilterSettings();
   void saveFilterSettings() const;
   FilterSettings readFilterSettings() const;

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
