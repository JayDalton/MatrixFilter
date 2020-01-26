#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

#include "Serialize/JsonStream.h"
#include "Serialize/JsonReader.h"
#include "Serialize/JsonWriter.h"

#include "Config/Parameter.h"
#include "Config/Visitor.h"

/////////////////////////////////////////////////////////////////////////////

struct Configuration
{
   std::string m_ident;
   std::string m_label;

   Configuration() = default;
   Configuration(const Configuration& other);
   Configuration& operator=(Configuration other);

   bool readFile(const fs::path& filePath);
   bool saveFile(const fs::path& filePath) const;

   std::string toString() const;
   bool readFrom(const std::string& content);

   bool readFrom(JsonReader& reader);
   bool writeTo(JsonWriter& writer) const;

   void createCopy() const;

   explicit Configuration(std::string_view ident, std::string_view label);

   std::size_t getParameterCount() const;
   StringVector getParameterNames() const;

   ParameterListing getParameterList() const;
   void updateParameter(const ParameterListing& list);

   bool registerParameter(BooleanParameter&& parameter);
   bool registerParameter(IntegerParameter&& parameter);
   bool registerParameter(StringParameter&& parameter);
   bool registerParameter(DoubleParameter&& parameter);
   bool registerParameter(ListParameter&& parameter);

   const VariantParameter& getParameter(const std::string& ident) const;
   const BooleanParameter& getBooleanParameter(const std::string& ident) const;
   const IntegerParameter& getIntegerParameter(const std::string& ident) const;
   const StringParameter& getStringParameter(const std::string& ident) const;
   const DoubleParameter& getDoubleParameter(const std::string& ident) const;
   const ListParameter& getListParameter(const std::string& ident) const;

   VariantParameter& getParameter(const std::string& ident);
   BooleanParameter& getBooleanParameter(const std::string& ident);
   IntegerParameter& getIntegerParameter(const std::string& ident);
   StringParameter& getStringParameter(const std::string& ident);
   DoubleParameter& getDoubleParameter(const std::string& ident);
   ListParameter& getListParameter(const std::string& ident);

private:
   ParameterMapping m_map;
   StringVector m_ordered; // ???
};

///////////////////////////////////////////////////////////////////////////

// Codepage: UTF-8 (ÜüÖöÄäẞß)
