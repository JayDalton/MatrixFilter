#include "stdafx.h"

#include "DoubleParameter.h"

DoubleParameter::DoubleParameter(
   std::string_view ident,
   std::string_view label,
   double default,
   double maximun,
   double minimum
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

DoubleParameter::~DoubleParameter() = default;

const std::string& DoubleParameter::getIdent() const
{
   return m->m_ident;
}

const std::string& DoubleParameter::getLabel() const
{
   return m->m_label;
}

double DoubleParameter::getDefault() const
{
   return std::get<double>(m->m_default);
}

double DoubleParameter::getCurrent() const
{
   return std::get<double>(m->m_current);
}

void DoubleParameter::setCurrent(double value)
{
   std::get<double>(m->m_current) = value;
}

double DoubleParameter::getMinimum() const
{
   return std::get<double>(m->m_minimum);
}

double DoubleParameter::getMaximum() const
{
   return std::get<double>(m->m_maximum);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
