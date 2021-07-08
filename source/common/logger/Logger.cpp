#include "stdafx.h"

#include "Logger.h"

LoggerEntry::LoggerEntry(const spdlog::details::log_msg& msg)
   : m_level(getLevel(msg.level))
{
   m_logger = msg.logger_name.data();
   m_payload = msg.payload.data();
   m_threadId = msg.thread_id;
   m_timePoint = msg.time;

   if (!msg.source.empty())
   {
      m_srcFileName = msg.source.filename;
      m_srcFuncName = msg.source.funcname;
      m_srcLocation = msg.source.line;
   }
}

LoggerLevel LoggerEntry::getLevel(spdlog::level::level_enum level) const
{
   switch (level)
   {
   case spdlog::level::trace:
      return LoggerLevel::Trace;
   case spdlog::level::debug:
      return LoggerLevel::Debug;
   case spdlog::level::info:
      return LoggerLevel::Info;
   case spdlog::level::warn:
      return LoggerLevel::Warning;
   case spdlog::level::err:
      return LoggerLevel::Error;
   case spdlog::level::critical:
      return LoggerLevel::Critical;
   default:
      return LoggerLevel::None;
   }
}


void Logger::appendLoggerSink(spdlog::sink_ptr loggerSink)
{
   // it's not thread-safe !!!
   spdlog::default_logger()->sinks().push_back(loggerSink);
}

void Logger::removeLoggerSink(spdlog::sink_ptr loggerSink)
{
   // it's not thread-safe !!!
   auto& sinks{ spdlog::default_logger()->sinks() };
   auto found = std::find(sinks.cbegin(), sinks.cend(), loggerSink);
   if (found != sinks.cend())
   {
      sinks.erase(found);
   }
}

spdlog::sink_ptr Logger::createMsvcLoggerSink()
{
   auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
   msvc_sink->set_pattern("[%M:%S.%e] [%t] [%l] %v ");
   return msvc_sink;
}

spdlog::sink_ptr Logger::createFileLoggerSink(const std::string& fileName)
{
   auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fileName);
   file_sink->set_pattern("[%H:%M:%S.%e] [%t] [%l] %-64v [%!] [%@]");
   return file_sink;
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
