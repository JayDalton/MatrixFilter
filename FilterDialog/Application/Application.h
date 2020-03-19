#pragma once

#include <optional>

#include <QApplication>

#include "ApplicationConfig.h"
#include "Logger/Logger.h"
#include "DataLayer.h"

//using FileLogger = std::shared_ptr<spdlog::logger>;

class Application : public QApplication
{
   Q_OBJECT

public:
   Application(int argc, char** argv, std::string_view title);
   ~Application();

   void setConfig(const ApplicationConfig& config);

   DataLayerSPtr getDataLayer() const;
   QStringList getArguments() const;

private:
   void setupLogger();
   void setupDialog();

private:
   QStringList m_arguments;
   ApplicationConfig m_config;
   DataLayerSPtr m_data{ nullptr };
   //FilterDialogUPtr m_dialog{ nullptr };
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
