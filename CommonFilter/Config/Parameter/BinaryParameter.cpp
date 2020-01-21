#include "stdafx.h"

#include "BinaryParameter.h"

BinaryParameter::BinaryParameter(
   std::string_view ident,
   std::string_view label,
   bool default
)
   : m(std::make_unique<ParameterBase>())
{
   m->m_ident = ident.data();
   m->m_label = label.data();
   m->m_default = default;
   m->m_current = default;
}

BinaryParameter::~BinaryParameter() = default;
BinaryParameter::BinaryParameter(BinaryParameter&& other) = default;
BinaryParameter& BinaryParameter::operator=(BinaryParameter&& other) = default;

BinaryParameter::BinaryParameter(const BinaryParameter& other)
{
   m = std::make_unique<ParameterBase>(*other.m);
}

BinaryParameter& BinaryParameter::operator=(BinaryParameter other)
{
   std::swap(m, other.m);
   return *this;
}

const std::string& BinaryParameter::getIdent() const
{
   return m->m_ident;
}

const std::string& BinaryParameter::getLabel() const
{
   return m->m_label;
}

bool BinaryParameter::getDefault() const
{
   return std::get<bool>(m->m_default);
}

bool BinaryParameter::getCurrent() const
{
   return std::get<bool>(m->m_current);
}

void BinaryParameter::setCurrent(bool value)
{
   std::get<bool>(m->m_current) = value;
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
