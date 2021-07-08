#include "JsonReader.h"

#include <config\Visitor.h>

using Buffer = json::IStreamWrapper;
using Writer = json::PrettyWriter<Buffer>;
using Reader = json::Reader;

struct JsonParser 
{
   explicit JsonParser(ParameterMapping& mapping)
      : m_map(mapping) {}

   bool Key(const char* str, json::SizeType length, bool copy) 
   {
      m_iter = std::find_if(m_map.begin(), m_map.end(), 
         [str](const auto& pair) { return pair.first == str; }
      );
      return true;
   }

   bool String(const char* str, json::SizeType length, bool copy) 
   {
      if (m_iter == m_map.end())
      {
         return false;
      }
      if (!std::get_if<StringParameter>(&m_iter->second))
      {
         return false;
      }
      std::get<StringParameter>(m_iter->second).setCurrent(str);
      return true;
   }

   bool Double(double value) 
   { 
      if (m_iter != m_map.end())
      {
         if (std::get_if<DoubleParameter>(&m_iter->second))
         {
            std::get<DoubleParameter>(m_iter->second).setCurrent(value);
         }
      }
      return true; 
   }

   bool Bool(bool value) 
   { 
      if (m_iter != m_map.end())
      {
         if (std::get_if<BooleanParameter>(&m_iter->second))
         {
            std::get<BooleanParameter>(m_iter->second).setCurrent(value);
         }
      }
      return true; 
   }

   bool Int(signed value) { 
      if (m_iter != m_map.end())
      {
         if (std::get_if<IntegerParameter>(&m_iter->second))
         {
            std::get<IntegerParameter>(m_iter->second).setCurrent(value);
         }
      }
      return true; 
   }
   bool Uint(unsigned value) 
   { 
      if (m_iter != m_map.end())
      {
         if (std::get_if<IntegerParameter>(&m_iter->second))
         {
            std::get<IntegerParameter>(m_iter->second).setCurrent(value);
         }
      }
      return true; 
   }

   bool Null() 
   { 
      SPDLOG_WARN("Null()"); return true; 
   }
   bool Int64(int64_t i) 
   { 
      SPDLOG_WARN("Int64({})", i); return true; 
   }
   bool Uint64(uint64_t u) 
   { 
      SPDLOG_WARN("UInt64({})", u); return true; 
   }
   bool RawNumber(const char* str, json::SizeType length, bool copy) { 
      SPDLOG_WARN("Number({0}, {1}, {2})", str, length, copy); return true;
   }

   bool StartObject() { return true; }
   bool EndObject(json::SizeType count) { return true; }

   bool StartArray() { return true; }
   bool EndArray(json::SizeType count) { return true; }

private:
   ParameterMapping& m_map;
   ParameterMapping::iterator m_iter;
};


struct JsonReader::JsonReader::Impl
{
   Impl(std::istream& stream) 
      : stream(stream)
   {
   }

   std::istream& stream;
   Reader reader;
};

JsonReader::JsonReader(std::istream& stream)
   : m(std::make_unique<Impl>(stream))
{
}

JsonReader::~JsonReader() = default;
JsonReader::JsonReader(JsonReader&& other) = default;
JsonReader& JsonReader::operator=(JsonReader&& other) = default;

bool JsonReader::writeTo(ParameterMapping& mapping)
{
   json::Reader reader;
   JsonParser parser{ mapping };
   json::IStreamWrapper wrapper(m->stream);
   if (auto error = reader.Parse(wrapper, parser))
   {
      SPDLOG_WARN("json parse error: {} {}", error.Code(), error.Offset());
      return false;
   }

   return true;
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
