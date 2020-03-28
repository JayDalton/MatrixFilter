#pragma once

#include <QLatin1String>

struct TLatin1String : public QLatin1String
{
   //constexpr TLatin1String(const char* const string) noexcept
   //   : QLatin1String(string, static_cast<int>(std::char_traits<char>::length(string)))
   //{
   //}

   constexpr TLatin1String(std::string_view string) noexcept
      : QLatin1String(string.data(), string.size())
   {
   }

   //constexpr TLatin1String(const std::string& string) noexcept
   //   : QLatin1String(string.data(), static_cast<int>(string.size()))
   //{
   //}
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
