#include "stdafx.h"

#include "DoubleParameter.h"

DoubleParameter::DoubleParameter(
   std::string_view ident,
   std::string_view label,
   double default,
   double maximun,
   double minimum
)
   : m(std::make_unique<ParameterBase>())
{
}

DoubleParameter::~DoubleParameter() = default;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
