#pragma once

#include "utils/JsonStream.h"

struct JsonWriter
{
   explicit JsonWriter(std::ostream& stream);
   ~JsonWriter();

   JsonWriter(JsonWriter&& other);
   JsonWriter& operator=(JsonWriter&& other);

   void Key(std::string_view key);
   void Key(const std::string& key);

   void Boolean(bool value);
   void Double(double value);
   void Signed(signed value);
   void String(std::string_view value);
   void String(const std::string& value);

   void StartObject();
   void CloseObject();

   void StartArray();
   void CloseArray();

   std::string getString() const;

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
