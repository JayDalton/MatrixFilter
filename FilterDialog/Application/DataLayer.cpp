#include <stdafx.h>

#include <QApplication>

#include "Application/DataLayer.h"
#include "Matrix/MatrixFile.h"

namespace fs = std::filesystem;

DataLayer::DataLayer()
{
   //m_loggerQueue = std::make_shared<BufferedLogger>(400);
}

QSettings DataLayer::settings()
{
   const auto orga{ QCoreApplication::organizationName() };
   const auto app{ QCoreApplication::applicationName() };
   return QSettings(orga, app);
}

//void DataLayer::appendLoggerEntry(LoggerEntryPtr&& entry)
//{
//   m_loggerQueue->append(std::move(entry));
//}
//
//DataLayer::LoggerQueuePtr DataLayer::getLoggerQueue() const
//{
//   return m_loggerQueue;
//}

void DataLayer::appendLoggerSink(BaseMutexLoggerPtr loggerSink)
{
   m_logger->sinks().push_back(loggerSink);
}

void DataLayer::setDefaultLogger(std::shared_ptr<spdlog::logger> logger)
{
   m_logger = logger;
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

//BasicSinkLogger::BasicSinkLogger(DataLayerSPtr data)
//   : m_layer(data)
//{
//}
//
//void BasicSinkLogger::appendEntry(LoggerEntryPtr&& entry)
//{
//   //m_layer->appendLoggerEntry(std::move(entry));
//}

// Codepage: UTF-8 (ÜüÖöÄäẞß)