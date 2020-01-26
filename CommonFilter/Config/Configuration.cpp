#include "stdafx.h"

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
   //#todo aus m_orderedIdents nehmen
   StringVector result;
   result.reserve(m_map.size());
   std::transform(m_map.cbegin(), m_map.cend(), std::back_inserter(result), 
      [](const auto& pair) { return pair.first; }
   );

   return result;
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
      [&](const BooleanParameter& param) { editBooleanParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const IntegerParameter& param) { editIntegerParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const DoubleParameter& param) { editDoubleParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const StringParameter& param) { editStringParameter(param.getIdent()).setCurrent(param.getCurrent()); },
      [&](const ListParameter& param) { editListParameter(param.getIdent()).setCurrent(param.getCurrent()); },
   };

   for (const VariantParameter& param : list)
   {
      if (std::visit(isValid, param))
      {
         std::visit(updateCurrent, param);
      }
   }
}

void Configuration::updateParameter(const VariantParameter& parameter)
{
}

//todo auslagern
bool Configuration::readFile(const fs::path& filePath)
{
   if (!fs::exists(filePath))
   {
      logger::info("config json file not existing");
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
      logger::info("config json file parse error");
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

bool Configuration::registerParameter(StringParameter&& parameter)
{
   return m_map.emplace( parameter.getIdent(), std::move(parameter) ).second;
}

bool Configuration::registerParameter(BooleanParameter&& parameter)
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
}

const VariantParameter& Configuration::getParameter(const std::string& ident) const
{
   return m_map.at(ident);
}

const BooleanParameter& Configuration::getBooleanParameter(const std::string& ident) const
{
   return std::get<BooleanParameter>(m_map.at(ident));
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

const ListParameter& Configuration::getListParameter(const std::string& ident) const
{
   return std::get<ListParameter>(m_map.at(ident));
}

VariantParameter& Configuration::getParameter(const std::string& ident)
{
   return m_map.at(ident);
}

BooleanParameter& Configuration::editBooleanParameter(const std::string& ident)
{
   return std::get<BooleanParameter>(m_map.at(ident));
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

ListParameter& Configuration::editListParameter(const std::string& ident)
{
   return std::get<ListParameter>(m_map.at(ident));
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
