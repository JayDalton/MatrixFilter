#pragma once

#include <iostream>
#include <string_view>
//#include <experimental/>

// Logger
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // support for basic file logging
#include <spdlog/sinks/rotating_file_sink.h> // support for rotating file logging

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

using cstr = const char * const;

static constexpr cstr past_last_slash(cstr str, cstr last_slash)
{
   return
      *str == '\0' ? last_slash :
      *str == '/' ? past_last_slash(str + 1, str + 1) :
      past_last_slash(str + 1, last_slash);
}

static constexpr cstr past_last_slash(cstr str) 
{ 
   return past_last_slash(str, str);
}

#define __SHORT_FILE__ ({constexpr cstr sf__ {past_last_slash(__FILE__)}; sf__;})

struct Logger
{
   explicit Logger();
   ~Logger();
   // const char* functionName, const char* fileName, int lineNo, int maxDurationMSecs = 0
   //explicit Logger(const std::string_view& message, const std::string_view& file, const std::string_view& line);
   //~Logger();

   static void debug(std::string_view message);

private:
   struct Impl;
   static std::unique_ptr<Impl> m;
};

struct CallLogger
{
   CallLogger(std::string_view message, std::string_view file = __FILE__);
};

constexpr auto Square = [] (int n) { return n*n; }; // implicitly constexpr
//constexpr auto LOGGER_CALL() { return Logger(__FUNCTION__, __FILE__, __LINE__); }

