#include "Configuration.h"

#include <Config\Visitor.h>

Configuration::Configuration(std::string_view ident, std::string_view label)
   : m_ident(ident), m_label(label)
{

}

Configuration::Configuration(const Configuration& other)
{
   m_ident = other.m_ident;
   m_label = other.m_label;
   m_map.reserve(other.m_map.size());
   for (const auto& [key, value] : other.m_map)
   {
      m_map.insert({key, value});
   }
}

Configuration& Configuration::operator=(Configuration other)
{
   std::swap(m_ident, other.m_ident);
   std::swap(m_label, other.m_label);
   std::swap(m_map, other.m_map);
   return *this;
}

std::size_t Configuration::getParameterCount() const
{
   return m_map.size();
}

StringVector Configuration::getParameterNames() const
{
   //#todo aus m_ordered nehmen
   StringVector result;
   result.reserve(m_map.size());
   std::transform(m_map.cbegin(), m_map.cend(), std::back_inserter(result), 
      [](const auto& pair) { return pair.first; }
   );

   //return result;
   return m_ordered;
}

ParameterListing Configuration::getParameterList() const
{
   ParameterListing result;
   result.reserve(m_map.size());
   std::transform(m_map.cbegin(), m_map.cend(), std::back_inserter(result), 
      [](const auto& pair) { return pair.second; }
   );

   return result;
}

void Configuration::updateParameter(const ParameterListing& list)
{
   Visitor isValid =
   {
      [&](const auto& param) -> bool { return m_map.contains(param.getIdent()); }
   };

   Visitor updateCurrent =
   {
      [&](const BooleanParameter& param) { getBooleanParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const IntegerParameter& param) { getIntegerParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const DoubleParameter& param) { getDoubleParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const StringParameter& param) { getStringParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const ListParameter& param) { getListParameter(param.getIdent()).setCurrent(param.getCurrent()); },
   };

   for (const VariantParameter& param : list)
   {
      if (std::visit(isValid, param))
      {
         std::visit(updateCurrent, param);
      }
   }
}

//todo auslagern
bool Configuration::readFile(const fs::path& filePath)
{
   if (!fs::exists(filePath))
   {
      //SPDLOG_INFO("config json file not existing");
      return false;
   }

   if (auto stream = std::ifstream(filePath, std::ios::binary))
   {
      JsonReader reader(stream);
      return readFrom(reader);
   }

   return false;
}

bool Configuration::saveFile(const fs::path& filePath) const
{
   if (!fs::exists(filePath))
   {
      fs::create_directories(filePath.parent_path());
   }

   if (auto stream = std::ofstream(filePath, std::ios::binary))
   {
      JsonWriter writer(stream);
      return writeTo(writer);
   }

   return false;
}

std::string Configuration::toString() const
{
   std::ostringstream stream;
   JsonWriter writer(stream);
   return stream.str();
}

bool Configuration::readFrom(const std::string& content)
{
   std::istringstream iss(content);
   JsonReader reader(iss);
   return readFrom(reader);
}

bool Configuration::readFrom(JsonReader& reader)
{
   if (!reader.writeTo(m_map))
   {
      //SPDLOG_WARN("config json file parse error");
      return false;
   }

   return true;
}

bool Configuration::writeTo(JsonWriter& writer) const
{
   Visitor writeValue = {
      [&](const bool value) { writer.Boolean(value); },
      [&](const signed value) { writer.Signed(value); },
      [&](const unsigned value) { writer.Signed(value); },
      [&](const double value) { writer.Double(value); },
      [&](const std::string& value) { writer.String(value); },
   };

   Visitor writeParameter = {
      [&](const DoubleParameter& value) { writer.Double(value.getCurrent()); },
      [&](const StringParameter& value) { writer.String(value.getCurrent()); },
      [&](const BooleanParameter& value) { writer.Boolean(value.getCurrent()); },
      [&](const IntegerParameter& value) { writer.Signed(value.getCurrent()); },
      [&](const ListParameter& value) { 
      writer.StartArray();
      for (const auto& value : value.getCurrent())
      {
         std::visit(writeValue, value);
      }
      writer.CloseArray();
   },
   };

   writer.StartObject();
   for (const auto& [key, value] : m_map)
   {
      writer.Key(key);
      std::visit(writeParameter, value);
   }
   writer.CloseObject();

   return true;
}

void Configuration::registerParameter(StringParameter&& parameter)
{
   m_ordered.push_back(parameter.getIdent());
   m_map.emplace( parameter.getIdent(), std::move(parameter) );
}

void Configuration::registerParameter(BooleanParameter&& parameter)
{
   m_ordered.push_back(parameter.getIdent());
   m_map.emplace( parameter.getIdent(), std::move(parameter) );
}

void Configuration::registerParameter(IntegerParameter&& parameter)
{
   m_ordered.push_back(parameter.getIdent());
   m_map.emplace( parameter.getIdent(), std::move(parameter) );
}

void Configuration::registerParameter(DoubleParameter&& parameter)
{
   m_ordered.push_back(parameter.getIdent());
   m_map.emplace( parameter.getIdent(), std::move(parameter) );
}

void Configuration::registerParameter(ListParameter&& parameter)
{
   m_ordered.push_back(parameter.getIdent());
   m_map.emplace( parameter.getIdent(), std::move(parameter) );
}

const VariantParameter& Configuration::getParameter(const std::string& ident) const
{
   return m_map.at(ident);
}

const BooleanParameter& Configuration::getBooleanParameter(const std::string& ident) const
{
   return std::get<BooleanParameter>(getParameter(ident));
}

const IntegerParameter& Configuration::getIntegerParameter(const std::string& ident) const
{
   return std::get<IntegerParameter>(getParameter(ident));
}

const StringParameter& Configuration::getStringParameter(const std::string& ident) const
{
   return std::get<StringParameter>(getParameter(ident));
}

const DoubleParameter& Configuration::getDoubleParameter(const std::string& ident) const
{
   return std::get<DoubleParameter>(getParameter(ident));
}

const ListParameter& Configuration::getListParameter(const std::string& ident) const
{
   return std::get<ListParameter>(getParameter(ident));
}

VariantParameter& Configuration::getParameter(const std::string& ident)
{
   return m_map.at(ident);
}

BooleanParameter& Configuration::getBooleanParameter(const std::string& ident)
{
   return std::get<BooleanParameter>(getParameter(ident));
}

IntegerParameter& Configuration::getIntegerParameter(const std::string& ident)
{
   return std::get<IntegerParameter>(getParameter(ident));
}

StringParameter& Configuration::getStringParameter(const std::string& ident)
{
   return std::get<StringParameter>(getParameter(ident));
}

DoubleParameter& Configuration::getDoubleParameter(const std::string& ident)
{
   return std::get<DoubleParameter>(getParameter(ident));
}

ListParameter& Configuration::getListParameter(const std::string& ident)
{
   return std::get<ListParameter>(getParameter(ident));
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
