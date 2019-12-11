#pragma once

#include <limits>
#include <numeric>

#include "Config/Parameter.h"

struct IntegerParameter
{
   IntegerParameter(
      std::string_view ident,
      std::string_view label,
      signed default,
      signed maximun = 100,
      signed minimum = 0
   );

   ~IntegerParameter();

   signed getCurrent() const;
   void setCurrent(signed value);

   signed getDefault() const;
   signed getMinimum() const;
   signed getMaximum() const;

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
