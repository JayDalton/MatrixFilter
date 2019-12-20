#include "stdafx.h"

#include "IntegerParameter.h"

IntegerParameter::IntegerParameter(
   std::string_view ident,
   std::string_view label,
   signed default,
   signed maximun,
   signed minimum
)
   : m(std::make_unique<ParameterBase>())
{
   m->m_ident = ident.data();
   m->m_ident = label.data();
   m->m_default = default;
   m->m_current = default;
   m->m_maximum = std::numeric_limits<signed>::max();
   m->m_minimum = std::numeric_limits<signed>::min();
}

IntegerParameter::~IntegerParameter() = default;

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