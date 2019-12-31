#include "stdafx.h"

#include "JsonReader.h"

struct JsonReader::JsonReader::Impl
{

};

JsonReader::JsonReader()
   : m(std::make_unique<Impl>())
{
}

JsonReader::JsonReader(std::string_view content)
   : m(std::make_unique<Impl>())
{

}

JsonReader::JsonReader(const std::string& content)
   : m(std::make_unique<Impl>())
{

}

JsonReader::JsonReader(const fs::path& filePath)
   : m(std::make_unique<Impl>())
{

}

JsonReader::~JsonReader() = default;
JsonReader::JsonReader(JsonReader&& other) = default;
JsonReader& JsonReader::operator=(JsonReader&& other) = default;


// Codepage: UTF-8 (ÜüÖöÄäẞß)
