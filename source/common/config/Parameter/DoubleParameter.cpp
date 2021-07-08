#include "stdafx.h"

#include "DoubleParameter.h"

DoubleParameter::DoubleParameter(
   std::string_view ident,
   std::string_view label,
   double defaultValue,
   double maximum,
   double minimum
)
   : m(std::make_unique<ParameterBase>())
{
   m->m_ident = ident.data();
   m->m_label = label.data();
   m->m_default = defaultValue;
   m->m_current = defaultValue;
   m->m_maximum = maximum;
   m->m_minimum = minimum;
}

DoubleParameter::~DoubleParameter() = default;
DoubleParameter::DoubleParameter(DoubleParameter&& other) = default;
DoubleParameter& DoubleParameter::operator=(DoubleParameter&& other) = default;

DoubleParameter::DoubleParameter(const DoubleParameter& other)
{
   m = std::make_unique<ParameterBase>(*other.m);
}

DoubleParameter& DoubleParameter::operator=(DoubleParameter other)
{
   std::swap(m, other.m);
   return *this;
}

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
