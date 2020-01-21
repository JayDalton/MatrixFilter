#include "stdafx.h"

#include "ConfigurationModel.h"
#include <Config\Visitor.h>

ConfigurationModel::ConfigurationModel()
{
}

void ConfigurationModel::setConfiguration(const Configuration& config)
{
   beginResetModel();
   m_config = config;
   endResetModel();
}

const Configuration& ConfigurationModel::getConfiguration() const
{
   return m_config;
}

QModelIndex ConfigurationModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return createIndex(row, column);
   }
   return {};
}

QModelIndex ConfigurationModel::parent(const QModelIndex& child) const
{
   return {};
}

int ConfigurationModel::rowCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return m_config.getParameterCount();
   }
   return 0;
}

int ConfigurationModel::columnCount(const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return static_cast<int>(Column::Count);
   }
   return 0;
}

Qt::ItemFlags ConfigurationModel::flags(const QModelIndex& index) const
{
   if (!index.isValid())
   {
      return Qt::NoItemFlags;
   }

   return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant ConfigurationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   switch (static_cast<Column>(section))
   {
   case Column::Label:
      return "Bezeichnung";
   case Column::Value:
      return "Wertigkeit";
   default:
      return {};
   }
}

QVariant ConfigurationModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   if (index.parent().isValid() 
      || (index.row() > m_config.getParameterCount()) 
      || (index.column() > static_cast<int>(Column::Count)))
   {
      return {};
   }

   Visitor getLabel = {
      [](const auto& param) -> std::string { return param.getLabel(); }
   };

   Visitor getValue = {
      [&](const DoubleParameter& value) -> QVariant { return value.getCurrent(); },
      [&](const StringParameter& value) -> QVariant { return QString::fromStdString(value.getCurrent()); },
      [&](const BooleanParameter& value) -> QVariant { return value.getCurrent(); },
      [&](const IntegerParameter& value) -> QVariant { return value.getCurrent(); },
      [&](const ListParameter& value) -> QVariant { return {}; },
   };

   const auto names{ m_config.getParameterNames() };
   const auto ident{ names.at(index.row()) };
   const auto parameter{ m_config.getParameter(ident) };

   switch (static_cast<Column>(index.column()))
   {
   case Column::Label: 
      return QLatin1String(std::visit(getLabel, parameter).c_str());
   case Column::Value:
      return std::visit(getValue, parameter);
   default: 
      return {};
   }
}

//////////////////////////////////////////////////////////////////////////////////////////

ConfigurationProxy::ConfigurationProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

//void ConfigurationProxy::updateSearch(const QString& searchString)
//{
//   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
//   invalidate();
//}
//
//uint ConfigurationProxy::getSourceIndex(const QModelIndex& index)
//{
//   auto sourceIndex{ mapToSource(index) };
//   auto sourceRow{ sourceIndex.row() };
//   return static_cast<uint>(sourceRow);
//}

//MatrixFileInfo MatrixDataProxy::getSourceContact(const QModelIndex& index)
//{
//   const auto sourceIndex{ mapFromSource(index) };
//   if (auto model = qobject_cast<MatrixDataModel*>(sourceModel()))
//   {
//      return model->getMatrixFile(sourceIndex);
//   }
//   return MatrixFileInfo{""};
//}

bool ConfigurationProxy::filterAcceptsRow(int row, const QModelIndex& parent) const
{
   // leeres Suchwort = alles anzeigen
   if (m_searchStringList.isEmpty())
   {
      return true;
   }

   const auto model{ sourceModel() };
   for (const auto& searchString : m_searchStringList)
   {
      bool searchStringFound{ false };
      for (auto column{ 0 }; column < model->columnCount(); ++column)
      {
         QModelIndex levelOneIndex = model->index(row, column, parent);
         QString stringData = levelOneIndex.data().toString();
         if (stringData.contains(searchString, Qt::CaseInsensitive))
         {
            searchStringFound = true;
            break;
         }
      }

      if (searchStringFound)
      {
         continue;
      }

      return false;
   }

   return true;
}

bool ConfigurationProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
