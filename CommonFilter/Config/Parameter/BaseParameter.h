#pragma once

#include <string>
#include <variant>

#include "Serialize/JsonStream.h"

using VariantValue = std::variant<
   bool, signed, unsigned, 
   double, std::string
>;

struct VariantStruct
{
   std::variant<
      bool, signed, unsigned, 
      double, std::string, 
      std::vector<VariantStruct>> value;
};

//int main()
//{
//   Foo a{std::vector<Foo>{Foo{}, Foo{}}};
//}

struct ParameterBase
{
   std::string m_ident;
   std::string m_label;

   VariantValue m_default;
   VariantValue m_current;
   VariantValue m_maximum;
   VariantValue m_minimum;

   std::vector<VariantValue> m_values;
};

using BaseParameter = std::unique_ptr<ParameterBase>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
