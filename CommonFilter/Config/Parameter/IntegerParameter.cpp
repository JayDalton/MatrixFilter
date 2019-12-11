#include "stdafx.h"

#include "IntegerParameter.h"

IntegerParameter::IntegerParameter(
   std::string_view ident,
   std::string_view label,
   signed default,
   signed maximun,
   signed minimum
)
   : m(std::make_unique<ParameterBase>())
{
}

IntegerParameter::~IntegerParameter() = default;

// Codepage: UTF-8 (ÜüÖöÄäẞß)