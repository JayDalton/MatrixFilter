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

   //auto base_sink = std::make_shared<BasicSinkLogger>(m_data);
   auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
   msvc_sink->set_pattern("[%M:%S.%e] [%t] [%l] %v ");
   auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path.string());
   file_sink->set_pattern("[%H:%M:%S.%e] [%t] [%l] %-64v [%!] [%@]");

   std::vector<spdlog::sink_ptr> sinks{ msvc_sink, file_sink };
   spdlog::set_default_logger(std::make_shared<spdlog::logger>(
      "logger", std::begin(sinks), std::end(sinks)));
   m_data->setDefaultLogger(spdlog::default_logger());

   spdlog::flush_on(spdlog::level::debug);
   spdlog::set_level(spdlog::level::trace);

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
