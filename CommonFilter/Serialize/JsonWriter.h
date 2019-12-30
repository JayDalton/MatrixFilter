#pragma once

#include "Serialize/JsonStream.h"

struct JsonWriter
{
   explicit JsonWriter(std::string_view content);
   explicit JsonWriter(const fs::path& filePath);

private:

};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
