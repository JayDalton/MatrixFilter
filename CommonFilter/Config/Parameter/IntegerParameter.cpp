#include "stdafx.h"

#include "IntegerParameter.h"

IntegerParameter::IntegerParameter(
   std::string_view ident,
   std::string_view label,
   signed default,
   signed maximum,
   signed minimum
)
   : m(std::make_unique<ParameterBase>())
{
   m->m_ident = ident.data();
   m->m_label = label.data();
   m->m_default = default;
   m->m_current = default;
   m->m_maximum = maximum;
   m->m_minimum = minimum;
}

IntegerParameter::~IntegerParameter() = default;
IntegerParameter::IntegerParameter(IntegerParameter&& other) = default;
IntegerParameter& IntegerParameter::operator=(IntegerParameter&& other) = default;

IntegerParameter::IntegerParameter(const IntegerParameter& other)
{
   m = std::make_unique<ParameterBase>(*other.m);
}

IntegerParameter& IntegerParameter::operator=(IntegerParameter other)
{
   std::swap(m, other.m);
   return *this;
}

const std::string& IntegerParameter::getIdent() const
{
   return m->m_ident;
}

const std::string& IntegerParameter::getLabel() const
{
   return m->m_label;
}

signed IntegerParameter::getDefault() const
{
   return std::get<signed>(m->m_default);
}

signed IntegerParameter::getCurrent() const
{
   return std::get<signed>(m->m_current);
}

void IntegerParameter::setCurrent(signed value)
{
   std::get<signed>(m->m_current) = value;
}

signed IntegerParameter::getMinimum() const
{
   return std::get<signed>(m->m_minimum);
}

signed IntegerParameter::getMaximum() const
{
   return std::get<signed>(m->m_maximum);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)