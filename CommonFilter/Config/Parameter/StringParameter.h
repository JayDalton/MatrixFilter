#pragma once

#include "Config/Parameter.h"

struct StringParameter
{
   StringParameter(
      std::string_view ident,
      std::string_view label,
      std::string_view default
   );

   ~StringParameter();

   const std::string& getCurrent() const;
   void setCurrent(const std::string& value);

   const std::string& getDefault() const;
   const std::string& getMinimum() const;
   const std::string& getMaximum() const;

private:
   BaseParameter m;
};


// Codepage: UTF-8 (ÜüÖöÄäẞß)
