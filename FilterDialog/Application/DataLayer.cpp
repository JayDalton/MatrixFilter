#include <stdafx.h>

#include <QApplication>

#include "Application/DataLayer.h"
#include "Matrix/MatrixFile.h"

namespace fs = std::filesystem;

DataLayer::DataLayer()
{
}

QSettings DataLayer::settings()
{
   const auto orga{ QCoreApplication::organizationName() };
   const auto app{ QCoreApplication::applicationName() };
   return QSettings(orga, app);
}

bool DataLayer::readMatrixFileInfo(const StringVector& pathList)
{
   return m_fileManger.loadMatrixFileInfo(pathList);
}

bool DataLayer::readMatrixFileInfo(std::string_view importFileName)
{
   return m_fileManger.loadMatrixFileInfo(importFileName);
}

void DataLayer::loadMatrixFile(MatrixFileInfo file)
{
   m_matrixManager.loadMatrixFromFile(file);
   emit currentMatrixChanged();
}

cv::Mat DataLayer::currentMatrix(MatrixLayer layer)
{
   return m_matrixManager.getMatrixData(layer);
}

MatrixPropertyList DataLayer::currentPropertyList(MatrixLayer layer)
{
   return m_matrixManager.getMatrixPropertyList(layer);
}

const MatrixFileRepository& DataLayer::getFileRepository() const
{
   return m_fileManger.getFileList();
}

FilterSettings DataLayer::loadImageViewSettings() const
{
   return FilterSettings();
}

void DataLayer::saveImageViewSettings(FilterSettings setting)
{
}

void DataLayer::applyImageViewerFilter(FilterSettings setting)
{
   auto target = currentMatrix(MatrixLayer::Viewer);
   auto source = m_matrixManager.getViewerSource();
   m_filterManager.setFilterSettings(setting);
   m_filterManager.applyFilter(source, target);
   emit currentMatrixChanged();
}

//////////////////////////////////////////////////////////////////////


// Codepage: UTF-8 (ÜüÖöÄäẞß)