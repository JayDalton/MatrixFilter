#pragma once

#include <memory>
#include <string>
#include <vector>

#include <QObject>
#include <QSettings>

#include <Matrix\MatrixManager.h>
#include <Matrix\FileManager.h>
#include <Matrix\FilterManager.h>

#include "Logger/Logger.h"

class DataLayer : public QObject
{
   Q_OBJECT

public:
   explicit DataLayer();

   QSettings settings();

   using BufferedLogger = BufferedQueue<LoggerEntryPtr>;
   using LoggerQueuePtr = std::shared_ptr<BufferedLogger>;

   //void appendLoggerEntry(LoggerEntryPtr&& entry);
   //LoggerQueuePtr getLoggerQueue() const;

   void appendLoggerSink(BaseMutexLoggerPtr loggerSink);
   void setDefaultLogger(std::shared_ptr<spdlog::logger> logger);

   bool readMatrixFileInfo(const StringVector& pathList);
   bool readMatrixFileInfo(std::string_view path);

   void loadMatrixFile(MatrixFileInfo file);

   cv::Mat currentMatrix(MatrixLayer layer);
   MatrixPropertyList currentPropertyList(MatrixLayer layer);

   const MatrixFileRepository& getFileRepository() const;

   FilterSettings loadImageViewSettings() const;
   void saveImageViewSettings(FilterSettings setting);
   void applyImageViewerFilter(FilterSettings setting);

   void getSourceMatrixView();
   void getMagnitudeMatrixView();
   void getResultMatrixView();

   const std::size_t MAX_LOGGER_ROW_COUNT{ 200 };

signals:
   void currentMatrixChanged();

private:
   FileManager m_fileManger;
   MatrixManager m_matrixManager;
   FilterManager m_filterManager;
   //LoggerQueuePtr m_loggerQueue;
   std::shared_ptr<spdlog::logger> m_logger;
};

using DataLayerUPtr = std::unique_ptr<DataLayer>;
using DataLayerSPtr = std::shared_ptr<DataLayer>;

///////////////////////////////////////////////////////////////

//struct BasicSinkLogger : public BaseMutexLogger
//{
//   BasicSinkLogger(DataLayerSPtr data);
//
//protected:
//   void appendEntry(LoggerEntryPtr&& entry) override;
//
//private:
//   DataLayerSPtr m_layer{ nullptr };
//};


// Codepage: UTF-8 (ÜüÖöÄäẞß)
