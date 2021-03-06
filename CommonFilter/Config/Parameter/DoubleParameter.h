﻿#pragma once

#include "Config/Parameter/BaseParameter.h"

struct DoubleParameter
{
   DoubleParameter(
      std::string_view ident,
      std::string_view label,
      double value,
      double maximun = 100.0,
      double minimum = 0.0
   );

   ~DoubleParameter();
   DoubleParameter(DoubleParameter&& other);
   DoubleParameter& operator=(DoubleParameter&& other);
   DoubleParameter(const DoubleParameter& other);
   DoubleParameter& operator=(DoubleParameter other);

   const std::string& getIdent() const;
   const std::string& getLabel() const;

   double getDefault() const;
   double getCurrent() const;
   void setCurrent(double value);

   double getMinimum() const;
   double getMaximum() const;

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
