
#include "JsonWriter.h"

using Buffer = json::OStreamWrapper;
using Writer = json::PrettyWriter<Buffer>;

struct JsonWriter::JsonWriter::Impl
{
   Impl(std::ostream& stream) 
      : stream(stream), buffer(stream), writer(buffer)
   {
   }

   std::ostream& stream;
   Buffer buffer;
   Writer writer;
};

JsonWriter::JsonWriter(std::ostream& stream)
   : m(std::make_unique<Impl>(stream))
{
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

void JsonWriter::StartArray()
{
   m->writer.StartArray();
}

void JsonWriter::CloseArray()
{
   m->writer.EndArray();
}

std::string JsonWriter::getString() const
{
   bool close = m->writer.EndObject();
   bool complete = m->writer.IsComplete();//???

   std::ostringstream oss;
   oss << m->stream.rdbuf();
   return oss.str();
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
