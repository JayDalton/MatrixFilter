﻿#pragma once

#include <QWidget>

#include "Application/DataLayer.h"
#include "MatrixValueDataModel.h"
#include "MatrixPropertyModel.h"

class MatrixDataTab : public QWidget
{
    Q_OBJECT

public:
    explicit MatrixDataTab(DataLayerSPtr data, QWidget *parent);
    ~MatrixDataTab();

    void loadMatrix(MatrixLayer layer);

private:
   void setupUIElements();
   void setupMatrixRange(const QRect& range);

private:
   struct Impl;
   std::unique_ptr<Impl> m;

   MatrixValueDataModelPtr m_matrixValueDataModel{ nullptr };
   MatrixValueDataProxyPtr m_matrixValueDataProxy{ nullptr };

   MatrixPropertyModelPtr m_matrixPropertyModel{ nullptr };
   MatrixPropertyProxyPtr m_matrixPropertyProxy{ nullptr };
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
