#include "stdafx.h"

#include "Configuration.h"
#include <Config\Visitor.h>

//#include <rapidjson/writer.h>

struct ReadHandler 
{
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

   bool Key(const char* str, json::SizeType length, bool copy) {
      logger::info("Key({0}, {1}, {2})", str, length, copy); 
      //m_params.emplace_back(BaseParameter{ 
      //   std::string{str, length}, 
      //   std::string{str, length} 
      //   });
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
//private:
//   ParameterListing m_params;
};


Configuration::Configuration(std::string_view ident, std::string_view label)
   : m_ident(ident), m_label(label)
{

}

Configuration::Configuration(const Configuration& other)
{
   spdlog::info("");
}

Configuration& Configuration::operator=(const Configuration& other)
{
   spdlog::info("");
   return *this;
}

bool Configuration::load(const fs::path& filePath)
{
   if (!fs::exists(filePath))
   {
      logger::info("config json file not existing");
      return false;
   }

   std::ifstream stream(filePath, std::ios::binary);
   if (!stream)
   {
      logger::info("config json file can not read");
      return false;
   }

   ReadHandler handler;
   json::Reader reader;
   json::IStreamWrapper wrapper(stream);
   if (!reader.Parse(wrapper, handler))
   {
      logger::info("config json file parse error");
      return false;
   }

   //const auto& params{ handler.getParameters() };
   //m_params.assign(params.cbegin(), params.cend());
   //for (const auto& param : handler.getParameters())
   //{
   //   param.m_ident;
   //   param.m_label;
   //}

   //json::Document document;
   ////json::IStreamWrapper isw(stream);
   //document.ParseStream(wrapper);
   //if (document.HasParseError())
   //{
   //   logger::info("config json file parse error");
   //   return false;
   //}
   //
   //for (const auto& member : document.GetObject())
   //{
   //   member.name;
   //   member.value;
   //   logger::debug("json member: {0} : {1}", 
   //      member.name.GetString(),
   //      member.value.GetString()
   //   );
   //}
   return false;
}

bool Configuration::save(const fs::path& filePath) const
{
   json::StringBuffer buffer;
   json::PrettyWriter<json::StringBuffer> writer(buffer);

   auto write = [&writer](const auto& value) { value.Serialize(writer); };

   writer.StartObject();
   //writer.Key("Ident");
   //writer.String(m_ident);
   //writer.Key("Label");
   //writer.String(m_label);

   //for (const auto& keyValue : m_paramMap)
   //{
   //   std::visit(write, keyValue.second);
   //}
   writer.EndObject();

   if (!fs::exists(filePath))
   {
      fs::create_directories(filePath.parent_path());
   }

   if (auto stream = std::ofstream(filePath, std::ios::binary))
   {
      stream << buffer.GetString() << std::endl;
      return true;
   }

   return false;
}

std::string Configuration::toJson() const
{
   json::StringBuffer stream;
   json::Writer<json::StringBuffer> writer(stream);

   Visitor writeValue = {
      [&writer](const DoubleParameter& value) { writer.Double(value.getCurrent()); },
      [&writer](const StringParameter& value) { writer.String(value.getCurrent()); },
      [&writer](const IntegerParameter& value) { writer.Int(value.getCurrent()); },
      [&writer](const ListParameter& value) { /*writer.Int(value.getCurrent())*/; },
   };

   writer.StartObject();
   for (const auto& [key, value] : m_map)
   {
      writer.Key("hello");
      std::visit(writeValue, value);
   }
   writer.EndObject();

   return std::string(stream.GetString());
}

bool Configuration::registerParameter(StringParameter&& parameter)
{
   return m_map.emplace( parameter.getIdent(), std::move(parameter) ).second;
}

bool Configuration::registerParameter(IntegerParameter&& parameter)
{
   return m_map.emplace( parameter.getIdent(), std::move(parameter) ).second;
}

bool Configuration::registerParameter(DoubleParameter&& parameter)
{
   return m_map.emplace( parameter.getIdent(), std::move(parameter) ).second;
}

bool Configuration::registerParameter(ListParameter&& parameter)
{
   return m_map.emplace( parameter.getIdent(), std::move(parameter) ).second;
   return false;
}

const IntegerParameter& Configuration::getIntegerParameter(const std::string& ident) const
{
   return std::get<IntegerParameter>(m_map.at(ident));
}

const StringParameter& Configuration::getStringParameter(const std::string& ident) const
{
   return std::get<StringParameter>(m_map.at(ident));
}

const DoubleParameter& Configuration::getDoubleParameter(const std::string& ident) const
{
   return std::get<DoubleParameter>(m_map.at(ident));
}

IntegerParameter& Configuration::editIntegerParameter(const std::string& ident)
{
   return std::get<IntegerParameter>(m_map.at(ident));
}

StringParameter& Configuration::editStringParameter(const std::string& ident)
{
   return std::get<StringParameter>(m_map.at(ident));
}

DoubleParameter& Configuration::editDoubleParameter(const std::string& ident)
{
   return std::get<DoubleParameter>(m_map.at(ident));
}

//const ListParameter& Configuration::getListParameter(const std::string& ident) const
//{
//   const ParameterVariant& param = getParameter(ident);
//   if (std::holds_alternative<ListParameter>(param))
//   {
//      return std::get<ListParameter>(param);
//   }
//
//   assert(false);
//   return std::get<ListParameter>(param);
//}

//const std::string& Configuration::getStringParameter(const std::string& ident) const
//{
//   const BaseParameter& param = getBaseParameter(ident);
//   if (std::holds_alternative<std::string>(param.m_current))
//   {
//      return std::get<std::string>(param.m_current);
//   }
//
//   assert(false);
//   return std::get<std::string>(param.m_current);
//}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
