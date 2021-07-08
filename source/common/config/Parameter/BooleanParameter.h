#pragma once

#include "Config/Parameter/BaseParameter.h"

struct BooleanParameter
{
   BooleanParameter(
      std::string_view ident,
      std::string_view label,
      bool defaultValue
   );

   ~BooleanParameter();
   BooleanParameter(BooleanParameter&& other);
   BooleanParameter& operator=(BooleanParameter&& other);
   BooleanParameter(const BooleanParameter& other);
   BooleanParameter& operator=(BooleanParameter other);

   const std::string& getIdent() const;
   const std::string& getLabel() const;

   bool getDefault() const;
   bool getCurrent() const;
   void setCurrent(bool value);

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
