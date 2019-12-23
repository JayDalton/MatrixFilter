#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

#include "Serialize/JsonReader.h"
#include "Serialize/JsonWriter.h"

#include "Config/Parameter/StringParameter.h"
#include "Config/Parameter/IntegerParameter.h"
#include "Config/Parameter/DoubleParameter.h"
#include "Config/Parameter/ListParameter.h"

/////////////////////////////////////////////////////////////////////////////

using VariantParameter = std::variant<
   StringParameter, IntegerParameter, 
   DoubleParameter, ListParameter
>;

struct Configuration
{
   std::string m_ident;
   std::string m_label;

   bool load(const fs::path& filePath);
   bool save(const fs::path& filePath) const;

   std::string toJson() const;
   bool fromJson(const std::string& input);

   bool load(JsonReader reader);
   bool save(JsonWriter writer) const;

   void createCopy() const;

   // copy and swap idiom ?
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

   std::size_t getParameterCount() const;
   std::vector<std::string> getParameterNames() const;

   bool registerParameter(StringParameter&& parameter);
   bool registerParameter(IntegerParameter&& parameter);
   bool registerParameter(DoubleParameter&& parameter);
   bool registerParameter(ListParameter&& parameter);

   const IntegerParameter& getIntegerParameter(const std::string& ident) const;
   const StringParameter& getStringParameter(const std::string& ident) const;
   const DoubleParameter& getDoubleParameter(const std::string& ident) const;

   IntegerParameter& editIntegerParameter(const std::string& ident);
   StringParameter& editStringParameter(const std::string& ident);
   DoubleParameter& editDoubleParameter(const std::string& ident);

private:
   std::unordered_map<std::string, VariantParameter> m_map;
};

///////////////////////////////////////////////////////////////////////////

// Codepage: UTF-8 (ÜüÖöÄäẞß)
