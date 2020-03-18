#include "stdafx.h"
#include "LoggerWidget.h"

#include <QScrollBar>

LoggerModel::LoggerModel(std::size_t maxLogLength, std::chrono::milliseconds interval)
   : m_queue(maxLogLength)
{
   m_updateTimer.setSingleShot(true);
   m_updateTimer.setInterval(interval);
   m_updateTimer.callOnTimeout(this, &LoggerModel::updateViewModelFromBuffer);
}

void LoggerModel::showBuffered()
{
   if (const auto needless = m_queue.getAvailableItemSize())
   {
      beginRemoveRows(QModelIndex(), 0, needless - 1);
      m_queue.removeNeedlessHead();
      endRemoveRows();
   }

   if (const auto tailSize = m_queue.getBufferedItemSize())
   {
      const auto rows = m_queue.getStoredItemSize();
      beginInsertRows(QModelIndex(), rows, rows + tailSize - 1);
      endInsertRows();
   }
}

void LoggerModel::setFreezed(bool freeze)
{
   if (freeze)
   {
      m_updateTimer.stop();
   }
   else
   {
      m_updateTimer.start();
   }
}

QModelIndex LoggerModel::index(int row, int column, const QModelIndex& parent) const
{
   if (parent.isValid())
   {
      return {};
   }
   if (row < 0 || rowCount() <= row)
   {
      return {};
   }
   if (column < 0 || columnCount() <= column)
   {
      return {};
   }
   return createIndex(row, column);
}

QModelIndex LoggerModel::parent(const QModelIndex& child) const
{
   return {};
}

int LoggerModel::rowCount(const QModelIndex& parent) const
{
   if (parent.isValid())
   {
      return 0;
   }
   return m_queue.getStoredItemSize();
}

int LoggerModel::columnCount(const QModelIndex& parent) const
{
   if (parent.isValid())
   {
      return 0;
   }
   return static_cast<int>(Column::Count);
}

QVariant LoggerModel::data(const QModelIndex& index, int role) const
{
   return QVariant();
}

QVariant LoggerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }
   if (orientation != Qt::Horizontal)
   {
      return {};
   }

   switch (static_cast<Column>(section))
   {
   case Column::Timestamp:
      return "Zeit";
   case Column::Priority:
      return "Level";
   case Column::Message:
      return "Meldung";
   case Column::Thread:
      return "Thread";
   case Column::Line:
      return "Zeile";
   default:
      return "???";
   }
}

void LoggerModel::updateViewModelFromBuffer()
{
   showBuffered();
   m_updateTimer.start();
}

///////////////////////////////////////////////////////////////////////////////

LoggerWidget::LoggerWidget(QWidget *parent)
   : QTreeView(parent), m_model(std::make_unique<LoggerModel>())
{
   setRootIsDecorated(false);
   setUniformRowHeights(true);

   setModel(m_model.get());

   connect(m_model.get(), &QAbstractItemModel::rowsAboutToBeInserted,
      this, &LoggerWidget::rowsAboutToBeRemoved);

   connect(m_model.get(), &QAbstractItemModel::rowsInserted,
      this, &LoggerWidget::rowsAboutToBeRemoved);
}

void LoggerWidget::setFreeze(bool freeze)
{
   m_isFreezed = freeze;
   m_model->setFreezed(m_isFreezed && isVisible());
}

void LoggerWidget::showEvent(QShowEvent* event)
{
   m_model->setFreezed(m_isFreezed);
   QTreeView::showEvent(event);
}

void LoggerWidget::hideEvent(QHideEvent* event)
{
   m_model->setFreezed(true);
   QTreeView::hideEvent(event);
}

void LoggerWidget::handleRowsAboutToBeInserted()
{
   const auto* scrollBar = verticalScrollBar();
   m_autoScrolling = !scrollBar->isEnabled() ||
      (scrollBar->value() == scrollBar->maximum());
}

void LoggerWidget::handleRowsInserted()
{
   if (m_autoScrolling)
   {
      QMetaObject::invokeMethod(this, 
         [this]() { scrollToBottom(); }, 
         Qt::QueuedConnection
      );
   }
}



// Codepage: UTF-8 (ÜüÖöÄäẞß)