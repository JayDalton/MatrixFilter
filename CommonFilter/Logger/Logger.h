#pragma once

#include <mutex>
#include <iostream>
#include <string_view>

// Logger
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include "spdlog/sinks/basic_file_sink.h"
#include <spdlog/sinks/rotating_file_sink.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/reader.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <rapidjson/encodings.h>
#include <rapidjson/encodedstream.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
namespace json = rapidjson;

#include "BufferedQueue.h"

enum class LoggerLevel
{
   Trace,
   Debug,
   Info,
   Warning,
   Error,
   Critical,
   None,
};

struct LoggerEntry
{
   LoggerEntry(const spdlog::details::log_msg& msg);

   LoggerLevel m_level;
   std::string m_logger;
   std::string m_payload;
   std::size_t m_threadId;
   std::string m_srcFileName;
   std::string m_srcFuncName;
   std::size_t m_srcLocation;
   using TimePoint = std::chrono::system_clock::time_point;
     TimePoint m_timePoint;

private:
   LoggerLevel getLevel(spdlog::level::level_enum level) const;
};

using LoggerEntryPtr = std::unique_ptr<LoggerEntry>;

///////////////////////////////////////////////////////////////////

//template<typename Mutex>
struct LoggerAdapter : public spdlog::sinks::base_sink <std::mutex>
{
   //LoggerAdapter();

protected:
   void sink_it_(const spdlog::details::log_msg& msg) override
   {
      //msg.level;
      //msg.logger_name;
      //msg.payload;
      //msg.source;
      //msg.thread_id;
      //msg.time;

      //spdlog::memory_buf_t formatted;
      //base_sink<Mutex>::formatter_->format(msg, formatted);
      //std::cout << fmt::to_string(formatted);

      appendEntry(LoggerEntry{ msg });
      //appendEntry(std::make_unique<LoggerEntry>(msg));
   }

   void flush_() override 
   {
      //std::cout << std::flush;
   }

   virtual void appendEntry(const LoggerEntry& entry) = 0;
   //virtual void appendEntry(LoggerEntryPtr&& entry) = 0;
};

using LoggerAdapterPtr = std::shared_ptr<LoggerAdapter>;

/////////////////////////////////////////////////////////////////////////////////

struct Logger
{
   Logger();

   static void appendLoggerSink(spdlog::sink_ptr loggerSink);
   static void removeLoggerSink(spdlog::sink_ptr loggerSink);

   static spdlog::sink_ptr createMsvcLoggerSink();
   static spdlog::sink_ptr createFileLoggerSink(const std::string& fileName);

//private:
//   std::unordered_set<BaseMutexLoggerPtr> m_loggerSinks;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
