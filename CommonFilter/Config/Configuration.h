#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

#include "Config/Parameter.h"
#include "Config/Parameter/StringParameter.h"
#include "Config/Parameter/IntegerParameter.h"
#include "Config/Parameter/DoubleParameter.h"

/////////////////////////////////////////////////////////////////////////////

using VariantParameter = std::variant<
   StringParameter, IntegerParameter, DoubleParameter
>;

struct Configuration
{
   std::string m_ident;
   std::string m_label;

   bool load(const fs::path& filePath);
   bool save(const fs::path& filePath) const;

   std::string toJson() const;

   //bool load(const std::string& filePath);
   //bool save(const fs::path& filePath) const;

   Configuration(const Configuration& other);
   Configuration& operator=(const Configuration& other);
   //Configuration& operator=(Configuration other)
   //{
   //   std::cout << "copy assignment of A\n";
   //   std::swap(map, other.map);
   //   //std::swap(s1, other.s1);
   //   return *this;
   //}

   explicit Configuration(std::string_view ident, std::string_view label);

   bool registerParameter(StringParameter parameter);
   bool registerParameter(IntegerParameter parameter);
   bool registerParameter(DoubleParameter parameter);

   //void registerBaseParameter(const BaseParameter& parameter);
   //void registerListParameter(const ListParameter& parameter);

   //const ParameterVariant& getParameter(const std::string& ident) const;
   //const BaseParameter& getBaseParameter(const std::string& ident) const;
   //const ListParameter& getListParameter(const std::string& ident) const;

   //bool setParameter(const std::string& ident, BaseParameter::ValueType value);
   //bool setParameter(const std::string& ident, const std::string& value);

   //const std::string& getStringParameter(const std::string& ident) const;
   //const fs::path& getPathParameter(const std::string& ident) const;

private:
   std::unordered_map<std::string, signed> m_tmp;

   std::unordered_map<std::string, VariantParameter> m_map;
};

///////////////////////////////////////////////////////////////////////////

// Codepage: UTF-8 (ÜüÖöÄäẞß)
