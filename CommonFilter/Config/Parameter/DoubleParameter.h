#pragma once

#include "Config/Parameter.h"

struct DoubleParameter
{
   DoubleParameter(
      std::string_view ident,
      std::string_view label,
      double default,
      double maximun = 100.0,
      double minimum = 0.0
   );

   ~DoubleParameter();

   double getCurrent() const;
   void setCurrent(double value);

   double getDefault() const;
   double getMinimum() const;
   double getMaximum() const;

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
