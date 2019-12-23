#include "stdafx.h"

#include "StringParameter.h"

StringParameter::StringParameter(
   std::string_view ident, 
   std::string_view label, 
   std::string_view default,
   unsigned maximum,
   unsigned minimum
)
   : m(std::make_unique<ParameterBase>())
{
   m->m_ident = ident.data();
   m->m_label = label.data();
   m->m_default = default.data();
   m->m_current = default.data();
   m->m_maximum = maximum;
   m->m_minimum = minimum;
}

StringParameter::~StringParameter() = default;
StringParameter::StringParameter(StringParameter&& other) = default;
StringParameter& StringParameter::operator=(StringParameter&& other) = default;

StringParameter::StringParameter(const StringParameter& other)
{
   m = std::make_unique<ParameterBase>(*other.m);
}

StringParameter& StringParameter::operator=(StringParameter other)
{
   std::swap(m, other.m);
   return *this;
}

const std::string& StringParameter::getIdent() const
{
   return m->m_ident;
}

const std::string& StringParameter::getLabel() const
{
   return m->m_label;
}

const std::string& StringParameter::getDefault() const
{
   return std::get<std::string>(m->m_default);
}

const std::string& StringParameter::getCurrent() const
{
   return std::get<std::string>(m->m_current);
}

void StringParameter::setCurrent(const std::string& value)
{
   std::get<std::string>(m->m_current) = value;
}

std::size_t StringParameter::getMinimum() const
{
   return std::get<unsigned>(m->m_minimum);
}

std::size_t StringParameter::getMaximum() const
{
   return std::get<unsigned>(m->m_default);
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)