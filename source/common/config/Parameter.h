#pragma once

#include "Config/Parameter/BaseParameter.h"

#include "Config/Parameter/BinaryParameter.h"
#include "Config/Parameter/StringParameter.h"
#include "Config/Parameter/IntegerParameter.h"
#include "Config/Parameter/BooleanParameter.h"
#include "Config/Parameter/DoubleParameter.h"
#include "Config/Parameter/ListParameter.h"

using VariantParameter = std::variant<
   StringParameter, IntegerParameter, 
   DoubleParameter, BooleanParameter, 
   ListParameter
>;

using ParameterListing = std::vector<VariantParameter>;
using ParameterMapping = std::unordered_map<std::string, VariantParameter>;

using StringVector = std::vector<std::string>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)

