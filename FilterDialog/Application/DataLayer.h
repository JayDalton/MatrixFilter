﻿#pragma once

#include <memory>
#include <string>
#include <vector>

#include <QObject>
#include <QSettings>

#include <Matrix\MatrixManager.h>
#include <Matrix\FileManager.h>

// wohin damit?
struct FilterSettings
{
   bool m_histoEqualize{ false };
   bool m_claheEnabled{ false };
   bool m_suaceEnabled{ false };
};

class DataLayer : public QObject
{
   Q_OBJECT

public:
   explicit DataLayer();

   QSettings settings();

   bool readMatrixFileInfo(const StringVector& pathList);
   bool readMatrixFileInfo(std::string_view path);

   void loadMatrixFile(MatrixFileInfo file);

   cv::Mat currentMatrix(MatrixLayer layer);
   MatrixPropertyList currentPropertyList(MatrixLayer layer);

   const MatrixFileRepository& getFileRepository() const;

   void applyImageFilterParameter();
   FilterSettings getImageViewSettings() const;
   void setImageViewSettings(FilterSettings setting);

   void getSourceMatrixView();
   void getMagnitudeMatrixView();
   void getResultMatrixView();

signals:
   void currentMatrixChanged();

private:
   FileManager m_fileManger;
   MatrixManager m_matrixManger;
};

using DataLayerUPtr = std::unique_ptr<DataLayer>;
using DataLayerSPtr = std::shared_ptr<DataLayer>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
