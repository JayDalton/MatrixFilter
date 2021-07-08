#include <stdafx.h>

#include "MatrixValueDataModel.h"

#include <opencv2/core/mat.hpp>

MatrixValueDataModel::MatrixValueDataModel()
{
}

void MatrixValueDataModel::setImageMatrix(const cv::Mat& matrix)
{
   beginResetModel();
   m_matrix = matrix;
   m_range.setRect(0, 0, 100, 100);
   endResetModel();

   emit sizeChanged(m_range);
}

void MatrixValueDataModel::setSectionRange(const QRect& range)
{
   if (m_range != range)
   {
      beginResetModel();
      m_range = range;
      endResetModel();
   }
}

const QRect& MatrixValueDataModel::getSectionRange() const
{
   return m_range;
}

QModelIndex MatrixValueDataModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!parent.isValid())
   {
      return createIndex(row, column);
   }
   return {};
}

QModelIndex MatrixValueDataModel::parent(const QModelIndex& child) const
{
   return {};
}

int MatrixValueDataModel::rowCount(const QModelIndex& parent) const
{
   if (m_range.isValid())
   {
      return m_range.height();
   }
   return 0;
}

int MatrixValueDataModel::columnCount(const QModelIndex& parent) const
{
   if (m_range.isValid())
   {
      return m_range.width();
   }
   return 0;
}

Qt::ItemFlags MatrixValueDataModel::flags(const QModelIndex& index) const
{
   return QAbstractItemModel::flags(index);
}

QVariant MatrixValueDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   return section;
}

QVariant MatrixValueDataModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   if (!m_range.isValid()
      || m_matrix.empty()
      || index.parent().isValid() 
      || (index.row() >= m_range.height()) 
      || (index.column() >= m_range.width()))
   {
      return {};
   }

   const auto row = m_range.y() + index.row();
   const auto col = m_range.x() + index.column();
   return getVariant(row, col);
}

QVariant MatrixValueDataModel::getVariant(int row, int col) const
{
   switch (m_matrix.type())
   {
   case CV_8U:
      return m_matrix.at<uchar>(row, col);
   case CV_8S:
      return m_matrix.at<schar>(row, col);
   case CV_16U:
      return m_matrix.at<ushort>(row, col);
   case CV_16S:
      return m_matrix.at<short>(row, col);
   case CV_32S:
      return m_matrix.at<int>(row, col);
   case CV_32F:
      return m_matrix.at<float>(row, col);
   case CV_64F:
      return m_matrix.at<double>(row, col);
   default:
      return {};
   }

   return {};
}

//////////////////////////////////////////////////////////////////////////////////////////

MatrixValueDataProxy::MatrixValueDataProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

void MatrixValueDataProxy::updateSearch(const QString& searchString)
{
   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
   invalidate();
}

uint MatrixValueDataProxy::getSourceIndex(const QModelIndex& index)
{
   auto sourceIndex{ mapToSource(index) };
   auto sourceRow{ sourceIndex.row() };
   return static_cast<uint>(sourceRow);
}

//MatrixFileInfo MatrixDataProxy::getSourceContact(const QModelIndex& index)
//{
//   const auto sourceIndex{ mapFromSource(index) };
//   if (auto model = qobject_cast<MatrixDataModel*>(sourceModel()))
//   {
//      return model->getMatrixFile(sourceIndex);
//   }
//   return MatrixFileInfo{""};
//}

bool MatrixValueDataProxy::filterAcceptsRow(int row, const QModelIndex& parent) const
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

bool MatrixValueDataProxy::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
