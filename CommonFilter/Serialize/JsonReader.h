#pragma once

#include "Serialize/JsonStream.h"

struct JsonReader
{
   explicit JsonReader();
   explicit JsonReader(const std::string& input);
   explicit JsonReader(std::string_view content);
   explicit JsonReader(const fs::path& filePath);

   ~JsonReader();
   JsonReader(JsonReader&& other);
   JsonReader& operator=(JsonReader&& other);

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
