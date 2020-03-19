#pragma once

#include "spdlog/sinks/base_sink.h"

#include "BufferedQueue.h"

struct LoggerEntry
{

};

template<typename Mutex>
struct LoggerAdapter : public spdlog::sinks::base_sink <Mutex>
{
   LoggerAdapter();

   using EntryType = std::unique_ptr<LoggerEntry>;

protected:
   void sink_it_(const spdlog::details::log_msg& msg) override
   {
      msg.level;
      msg.logger_name;
      msg.payload;
      msg.source;
      msg.thread_id;
      msg.time;

      spdlog::memory_buf_t formatted;
      base_sink<Mutex>::formatter_->format(msg, formatted);
      std::cout << fmt::to_string(formatted);
      m_buffer.append(std::make_unique<EntryType>());
   }

   void flush_() override 
   {
      std::cout << std::flush;
   }

private:
   BufferedQueue<EntryType> m_buffer;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
