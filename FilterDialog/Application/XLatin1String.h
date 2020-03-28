#pragma once

#include <QLatin1String>

struct XLatin1String : public QLatin1String
{
   constexpr XLatin1String(std::string_view string) noexcept
      : QLatin1String(string.data(), string.size())
   {
   }
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
