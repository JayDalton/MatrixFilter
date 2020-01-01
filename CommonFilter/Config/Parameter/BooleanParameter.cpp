#include "stdafx.h"

#include "BooleanParameter.h"

BooleanParameter::BooleanParameter(
   std::string_view ident,
   std::string_view label,
   bool default
)
   : m(std::make_unique<ParameterBase>())
{
   m->m_ident = ident.data();
   m->m_ident = label.data();
   m->m_default = default;
   m->m_current = default;
}

BooleanParameter::~BooleanParameter() = default;
BooleanParameter::BooleanParameter(BooleanParameter&& other) = default;
BooleanParameter& BooleanParameter::operator=(BooleanParameter&& other) = default;

BooleanParameter::BooleanParameter(const BooleanParameter& other)
{
   m = std::make_unique<ParameterBase>(*other.m);
}

BooleanParameter& BooleanParameter::operator=(BooleanParameter other)
{
   std::swap(m, other.m);
   return *this;
}

const std::string& BooleanParameter::getIdent() const
{
   return m->m_ident;
}

const std::string& BooleanParameter::getLabel() const
{
   return m->m_label;
}

bool BooleanParameter::getDefault() const
{
   return std::get<bool>(m->m_default);
}

bool BooleanParameter::getCurrent() const
{
   return std::get<bool>(m->m_current);
}

void BooleanParameter::setCurrent(bool value)
{
   std::get<bool>(m->m_current) = value;
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
