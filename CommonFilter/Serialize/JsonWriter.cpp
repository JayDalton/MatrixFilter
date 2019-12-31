#include "stdafx.h"

#include "JsonWriter.h"

using Writer = json::PrettyWriter<json::StringBuffer>;


struct JsonWriter::JsonWriter::Impl
{
   Impl() {}

   //Writer writer;
};

JsonWriter::JsonWriter()
   : m(std::make_unique<Impl>())
{
}

JsonWriter::JsonWriter(std::string_view content)
   : m(std::make_unique<Impl>())
{

}

JsonWriter::JsonWriter(const fs::path& filePath)
   : m(std::make_unique<Impl>())
{

}

JsonWriter::~JsonWriter() = default;
JsonWriter::JsonWriter(JsonWriter&& other) = default;
JsonWriter& JsonWriter::operator=(JsonWriter&& other) = default;

std::string JsonWriter::getString() const
{
   return {};
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
