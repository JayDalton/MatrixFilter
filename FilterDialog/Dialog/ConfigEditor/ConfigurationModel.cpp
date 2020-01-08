#include "stdafx.h"

#include "ConfigurationModel.h"

ConfigurationModel::ConfigurationModel()
{
}

void ConfigurationModel::setConfiguration(const Configuration& config)
{

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
   return QAbstractItemModel::flags(index);
}

QVariant ConfigurationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   return section;
}

QVariant ConfigurationModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   //if (!m_config.has_value())
   //{
   //   return {};
   //}

   if (index.parent().isValid() 
      || (index.row() > m_config.getParameterCount()) 
      || (index.column() > static_cast<int>(Column::Count)))
   {
      return {};
   }

   return {};
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
