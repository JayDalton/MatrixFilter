#pragma once

#include <unordered_map>

#include "config/parameter/BaseParameter.h"

#include "config/parameter/BinaryParameter.h"
#include "config/parameter/StringParameter.h"
#include "config/parameter/IntegerParameter.h"
#include "config/parameter/BooleanParameter.h"
#include "config/parameter/DoubleParameter.h"
#include "config/parameter/ListParameter.h"

using VariantParameter = std::variant<
   StringParameter, IntegerParameter, 
   DoubleParameter, BooleanParameter, 
   ListParameter
>;

using ParameterListing = std::vector<VariantParameter>;
using ParameterMapping = std::unordered_map<std::string, VariantParameter>;

using StringVector = std::vector<std::string>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)

