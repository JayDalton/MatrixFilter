#pragma once

#include "Config/Parameter/BaseParameter.h"

struct ListParameter
{
   ListParameter(
      std::string_view ident,
      std::string_view label,
      std::vector<VariantValue>&& default,
      unsigned maximun = 500,
      unsigned minimun = 0
   );

   ~ListParameter();
   ListParameter(ListParameter&& other);
   ListParameter& operator=(ListParameter&& other);
   ListParameter(const ListParameter& other);
   ListParameter& operator=(ListParameter other);

   const std::string& getIdent() const;
   const std::string& getLabel() const;

   const std::vector<VariantValue>& getDefault() const;

   const std::vector<VariantValue>& getCurrent() const;
   void setCurrent(const std::vector<VariantValue>& value);

   std::size_t getMinimum() const;
   std::size_t getMaximum() const;

private:
   BaseParameter m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
