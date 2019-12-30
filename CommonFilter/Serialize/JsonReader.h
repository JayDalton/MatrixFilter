#pragma once

#include "Serialize/JsonStream.h"

struct JsonReader
{
   explicit JsonReader(std::string_view content);
   explicit JsonReader(const fs::path& filePath);

private:
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
