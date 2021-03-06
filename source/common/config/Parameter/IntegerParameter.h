﻿#pragma once

#include <limits>
#include <numeric>

#include "config/parameter/BaseParameter.h"

struct IntegerParameter
{
   IntegerParameter(
      std::string_view ident,
      std::string_view label,
      signed defaultValue,
      signed maximum = std::numeric_limits<signed>::max(),
      signed minimum = std::numeric_limits<signed>::min()
   );

   ~IntegerParameter();
   IntegerParameter(IntegerParameter&& other);
   IntegerParameter& operator=(IntegerParameter&& other);
   IntegerParameter(const IntegerParameter& other);
   IntegerParameter& operator=(IntegerParameter other);

   const std::string& getIdent() const;
   const std::string& getLabel() const;

   signed getDefault() const;
   signed getCurrent() const;
   void setCurrent(signed value);

   signed getMinimum() const;
   signed getMaximum() const;

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
