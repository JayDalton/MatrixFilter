#include "stdafx.h"

#include "JsonWriter.h"

using Buffer = json::StringBuffer;
using Writer = json::PrettyWriter<Buffer>;

struct JsonWriter::JsonWriter::Impl
{
   Impl() : writer(stream) {}

   Buffer stream;
   Writer writer;
};

JsonWriter::JsonWriter()
   : m(std::make_unique<Impl>())
{
   m->writer.StartObject();
}

JsonWriter::~JsonWriter() = default;
JsonWriter::JsonWriter(JsonWriter&& other) = default;
JsonWriter& JsonWriter::operator=(JsonWriter&& other) = default;

void JsonWriter::Key(std::string_view key)
{
   m->writer.Key(key.data());
}

void JsonWriter::Key(const std::string& key)
{
   m->writer.Key(key.data());
}

void JsonWriter::Boolean(bool value)
{
   m->writer.Bool(value);
}

void JsonWriter::Double(double value)
{
   m->writer.Double(value);
}

void JsonWriter::Signed(signed value)
{
   m->writer.Int(value);
}

void JsonWriter::String(std::string_view value)
{
   m->writer.String(value.data());
}

void JsonWriter::String(const std::string& value)
{
   m->writer.String(value);
}

void JsonWriter::StartObject()
{
   m->writer.StartObject();
}

void JsonWriter::CloseObject()
{
   m->writer.EndObject();
}

std::string JsonWriter::getString() const
{
   m->writer.EndObject();
   m->writer.IsComplete();//???
   return m->stream.GetString();
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
