#include "stdafx.h"

#include "StringParameter.h"


//struct StringParameter::Impl
//{
//
//};

StringParameter::StringParameter(
   std::string_view ident, 
   std::string_view label, 
   std::string_view default)
   : m(std::make_unique<ParameterBase>())
{
}

StringParameter::~StringParameter() = default;


// Codepage: UTF-8 (ÜüÖöÄäẞß)