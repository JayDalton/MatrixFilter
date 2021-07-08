#pragma once

#include "utils/JsonStream.h"
#include "config/Parameter.h"

struct JsonReader
{
   explicit JsonReader(std::istream& stream);

   ~JsonReader();
   JsonReader(JsonReader&& other);
   JsonReader& operator=(JsonReader&& other);

   bool writeTo(ParameterMapping& mapping);

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
