#include "stdafx.h"

#include "ListParameter.h"

ListParameter::ListParameter(
   std::string_view ident, 
   std::string_view label, 
   std::initializer_list<VariantValue> default,
   unsigned maximum,
   unsigned minimum
)
   : m(std::make_unique<ParameterBase>())
{
   m->m_ident = ident.data();
   m->m_label = label.data();
   //m->m_default = default;
   //m->m_current = default;
   m->m_maximum = maximum;
   m->m_minimum = minimum;
}

ListParameter::~ListParameter() = default;
ListParameter::ListParameter(ListParameter&& other) = default;
ListParameter& ListParameter::operator=(ListParameter&& other) = default;

const std::string& ListParameter::getIdent() const
{
   return m->m_ident;
}

const std::string& ListParameter::getLabel() const
{
   return m->m_label;
}

const std::vector<VariantValue>& ListParameter::getDefault() const
{
   return {};
}

const std::vector<VariantValue>& ListParameter::getCurrent() const
{
   return {};
}

void ListParameter::setCurrent(const std::vector<VariantValue>& value)
{
}

std::size_t ListParameter::getMinimum() const
{
   return std::get<unsigned>(m->m_minimum);
}

std::size_t ListParameter::getMaximum() const
{
   return std::get<unsigned>(m->m_maximum);
}

//const std::string& StringParameter::getDefault() const
//{
//   return std::get<std::string>(m->m_default);
//}
//
//const std::string& StringParameter::getCurrent() const
//{
//   return std::get<std::string>(m->m_current);
//}
//
//void StringParameter::setCurrent(const std::string& value)
//{
//   std::get<std::string>(m->m_current) = value;
//}
//
//std::size_t StringParameter::getMinimum() const
//{
//   return std::get<unsigned>(m->m_minimum);
//}
//
//std::size_t StringParameter::getMaximum() const
//{
//   return std::get<unsigned>(m->m_default);
//}


// Codepage: UTF-8 (ÜüÖöÄäẞß)