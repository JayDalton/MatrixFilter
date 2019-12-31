#pragma once

#include "Serialize/JsonStream.h"

struct JsonWriter
{
   explicit JsonWriter();
   explicit JsonWriter(std::string_view content);
   explicit JsonWriter(const fs::path& filePath);

   ~JsonWriter();
   JsonWriter(JsonWriter&& other);
   JsonWriter& operator=(JsonWriter&& other);

   void Key(std::string_view key);
   
   void Null();
   void Boolean(bool value);
   void String(std::string_view value);
   void Double(double value);
   void Signed(signed value);
   void Unsigned(unsigned value);
   
   void StartArray();
   void EndArray();

   std::string getString() const;

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
