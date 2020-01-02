#pragma once

#include "Config/Parameter/BaseParameter.h"

struct StringParameter
{
   StringParameter(
      std::string_view ident,
      std::string_view label,
      std::string_view default,
      unsigned maximun = 4096,
      unsigned minimun = 0
   );

   ~StringParameter();
   StringParameter(StringParameter&& other);
   StringParameter& operator=(StringParameter&& other);
   StringParameter(const StringParameter& other);
   StringParameter& operator=(StringParameter other);

   //[[nodiscard]] StringParameter createCopy() const;

   const std::string& getIdent() const;
   const std::string& getLabel() const;

   const std::string& getDefault() const;

   const std::string& getCurrent() const;
   void setCurrent(const std::string& value);

   std::size_t getMinimum() const;
   std::size_t getMaximum() const;

   //bool fromJson(Reader reader);
   //void toJson(Writer writer) const;

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
