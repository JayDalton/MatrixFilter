#include "stdafx.h"

#include <string_view>
#include "Logger/Logger.h"

#include "Application.h"

namespace fs = std::filesystem;

Application::Application(int argc, char** argv, std::string_view title)
   : QApplication(argc, argv), m_data(std::make_shared<DataLayer>())
{
   QApplication::setOrganizationName("NoneProfit");
   QApplication::setApplicationName(title.data());
   QApplication::setApplicationVersion("0.2");

   m_arguments = QApplication::arguments();

   setupLogger();
   setupDialog();

   auto con = connect(this, &QApplication::lastWindowClosed, this, &QApplication::quit);
}

Application::~Application()
{
   spdlog::info("###############################################");
}

void Application::setConfig(const ApplicationConfig& config)
{
   m_config = config;
}

DataLayerSPtr Application::getDataLayer() const
{
   return m_data;
}

QStringList Application::getArguments() const
{
   return m_arguments;
}

void Application::setupLogger()
{
   fs::path path("logfiles/dialog.log");
   if (!fs::exists(path.parent_path()))
   {
      auto p = path.parent_path();
      fs::create_directories(p);
   }

   spdlog::flush_on(spdlog::level::debug);
   spdlog::set_level(spdlog::level::trace);

   Logger::appendLoggerSink(Logger::createMsvcLoggerSink());
   Logger::appendLoggerSink(Logger::createFileLoggerSink(path.string()));

   const auto app = QCoreApplication::applicationName().toStdString();
   const auto ver = QCoreApplication::applicationVersion().toStdString();
   spdlog::info("===============================================");
   spdlog::info("Logging: {0} - {1}", app, ver);
   spdlog::info("===============================================");
}

void Application::setupDialog()
{
   //m_dialog = std::make_unique<FilterDialog>(m_data);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
