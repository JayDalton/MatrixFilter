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
   case spdlog::level::off:
      return LoggerLevel::None;
   }
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
