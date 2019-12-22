﻿#pragma once

#include <string>
#include <variant>
#include <filesystem>
namespace fs = std::filesystem;

#include "Logger/Logger.h"

using Writer = json::PrettyWriter<json::StringBuffer>;

using VariantValue = std::variant<
   bool, signed, unsigned, 
   double, std::string
   //, std::vector<VariantValue>
>;

struct VariantStruct
{
   std::variant<int, float, std::vector<VariantStruct>> value;
};
//
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

//using ParameterVariant = std::variant<BaseParameter, ListParameter>;
//using ParameterListing = std::vector<ParameterVariant>;
//using ParameterMapping = std::unordered_map<std::string, ParameterVariant>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)

