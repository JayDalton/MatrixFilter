#pragma once

#include <string>
#include <variant>
#include <filesystem>
namespace fs = std::filesystem;

#include "Logger/Logger.h"

using Writer = json::PrettyWriter<json::StringBuffer>;

using VariantValue = std::variant<
   bool, signed, unsigned, 
   double, std::string
>;

struct ParameterBase
{
   //ParameterBase();

   //const std::string& getIdent() const;
   //const std::string& getLabel() const;

//protected:

   std::string m_ident;
   std::string m_label;

   VariantValue m_default;
   VariantValue m_current;
   VariantValue m_maximum;
   VariantValue m_minimum;
};

using BaseParameter = std::unique_ptr<ParameterBase>;

//using ParameterVariant = std::variant<BaseParameter, ListParameter>;
//using ParameterListing = std::vector<ParameterVariant>;
//using ParameterMapping = std::unordered_map<std::string, ParameterVariant>;

//class Writer;

//struct BaseParameter /*: public ParameterBase*/
//{
//   using ValueType = std::variant<
//      bool, signed, unsigned, double, 
//      std::string, fs::path>;
//
//   std::string m_ident;
//   std::string m_label;
//   VariantValue m_current;
//   VariantValue m_maximum;
//   VariantValue m_minimum;
//
//   void Serialize(Writer& writer) const;
//};
//
//struct ListParameter /*: public ParameterBase*/
//{
//   using ValueType = std::variant<
//      bool, signed, unsigned, double, 
//      std::string, fs::path>;
//
//   using ValueList = std::vector<ValueType>;
//
//   std::string m_ident;
//   std::string m_label;
//   ValueList m_current;
//
//   void Serialize(Writer& writer) const;
//};
//
//struct ConfigParameter
//{
//   std::string m_ident;
//   std::string m_label;
//
//   void Serialize(Writer& writer) const;
//};



// Codepage: UTF-8 (ÜüÖöÄäẞß)

