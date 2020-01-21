#pragma once

#include <sstream>

#include "Config/Parameter/BaseParameter.h"

struct BinaryParameter
{
   BinaryParameter(
      std::string_view ident,
      std::string_view label,
      bool default
   );

   ~BinaryParameter();
   BinaryParameter(BinaryParameter&& other);
   BinaryParameter& operator=(BinaryParameter&& other);
   BinaryParameter(const BinaryParameter& other);
   BinaryParameter& operator=(BinaryParameter other);

   const std::string& getIdent() const;
   const std::string& getLabel() const;

   bool getDefault() const;
   bool getCurrent() const;
   void setCurrent(bool value);

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
