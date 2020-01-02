#include "stdafx.h"

#include "JsonReader.h"

using Buffer = json::IStreamWrapper;
using Writer = json::PrettyWriter<Buffer>;
using Reader = json::Reader;

struct JsonParser 
{
   explicit JsonParser(ParameterMapping& mapping)
      : m_map(mapping) {}

   bool Key(const char* str, json::SizeType length, bool copy) 
   {
      logger::info("Key({0}, {1}, {2})", str, length, copy); 
      m_iter = std::find_if(m_map.begin(), m_map.end(), 
         [](const auto& pair) { return false; }
      );
      return m_iter != m_map.end();
   }


   // Handler API
   bool Null() { logger::info("Null()"); return true; }
   bool Int64(int64_t i) { logger::info("Int64({})", i); return true; }
   bool Uint64(uint64_t u) { logger::info("UInt64({})", u); return true; }
   bool RawNumber(const char* str, json::SizeType length, bool copy) { 
      logger::info("Number({0}, {1}, {2})", str, length, copy); return true;
   }

   bool Bool(bool b) { 

      //auto& param = m_params.back();
      //if (std::holds_alternative<bool>(param))
      //{
      //   return std::get<bool>(param);
      //}


      //m_params.back().emplace<BaseParameter>();
      //m_params.back().m_current = b;
      logger::info("Bool({})", b); 
      return true; 
   }

   bool Int(signed i) { 
      //m_params.back().m_current = i;
      logger::info("Int({})", i); 
      return true; 
   }
   bool Uint(unsigned u) { 
      //m_params.back().m_current = u;
      logger::info("Uint({})", u); 
      return true; 
   }

   bool Double(double d) { 
      //m_params.back().m_current = d;
      logger::info("Double({})", d); 
      return true; 
   }

   bool String(const char* str, json::SizeType length, bool copy) { 
      //m_params.back().m_current = std::string{str, length};
      logger::info("String({0}, {1}, {2})", str, length, copy); 
      return true;
   }

   bool StartObject() { logger::info("StartObject()"); return true; }
   bool EndObject(json::SizeType count) { 
      logger::info("EndObject({})", count); return true; 
   }

   bool StartArray() { logger::info("StartArray()"); return true; }
   bool EndArray(json::SizeType count) { 
      logger::info("EndArray({})", count); 
      return true; 
   }

   //   const ParameterListing& getParameters() const { return m_params; }
   //
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

//JsonReader::JsonReader(std::string_view content)
//   : m(std::make_unique<Impl>())
//{
//
//}
//
//JsonReader::JsonReader(const std::string& content)
//   : m(std::make_unique<Impl>())
//{
//
//}
//
//JsonReader::JsonReader(const fs::path& filePath)
//   : m(std::make_unique<Impl>())
//{
//
//}

JsonReader::~JsonReader() = default;
JsonReader::JsonReader(JsonReader&& other) = default;
JsonReader& JsonReader::operator=(JsonReader&& other) = default;

bool JsonReader::writeTo(ParameterMapping& mapping)
{
   json::Reader reader;
   JsonParser parser{ mapping };
   json::IStreamWrapper wrapper(m->stream);
   if (!reader.Parse(wrapper, parser))
   {
      logger::info("config json file parse error");
      return false;
   }


   return false;
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
