#include "stdafx.h"
#include "LoggerWidget.h"

#include <QScrollBar>

LoggerItem::LoggerItem(const LoggerEntry& entry)
   : m_message(QString::fromStdString(entry.m_payload))
   , m_thread(entry.m_threadId), m_priority(entry.m_level)
{
   auto time = entry.m_timePoint.time_since_epoch();
   auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(time);
   m_timestamp.setMSecsSinceEpoch(msec.count());

   m_place = QString("%1:%2")
      .arg(entry.m_srcFileName.data())
      .arg(entry.m_srcLocation);
}

struct StandardWidgetLoggerSink : public LoggerAdapter
{
   StandardWidgetLoggerSink(LoggerWidget* owner)
      : m_owner(owner)
   {
   }

protected:
   void appendEntry(const LoggerEntry& entry) override
   {
      QMetaObject::invokeMethod(m_owner, [=]() { m_owner->logEvent(entry); });
   }

private:
   LoggerWidget* m_owner{ nullptr };
};

///////////////////////////////////////////////////////////////////

LoggerModel::LoggerModel(std::size_t maxLogLength)
   : m_queue(maxLogLength)
{
}

void LoggerModel::applyBufferedContent()
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

void LoggerModel::appendLoggerEntry(const LoggerEntry& entry)
{
   m_queue.append(std::make_unique<LoggerItem>(entry));
}

void LoggerModel::setFreezed(bool freeze)
{
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
   const LoggerItemPtr& entry = m_queue.getElement(index.row());
   
   switch (role)
   {
   case Qt::DisplayRole:
      return getDisplayData(index.column(), entry);
   default:
      return {};
   }
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
   case Column::Place:
      return "Zeile";
   default:
      return "???";
   }
}

QVariant LoggerModel::getDisplayData(int column, const LoggerItemPtr& item) const
{
   switch (static_cast<Column>(column))
   {
   case Column::Timestamp:
      return item->m_timestamp;
   case Column::Priority:
      return getPriorityInfo(item->m_priority);
   case Column::Message:
      return item->m_message;
   case Column::Thread:
      return item->m_thread;
   case Column::Place:
      return item->m_place;
   default:
      return {};
   }
}

QVariant LoggerModel::getPriorityInfo(LoggerLevel level) const
{
   switch (level)
   {
   case LoggerLevel::Trace:
      return "Trace";
   case LoggerLevel::Debug:
      return "Debug";
   case LoggerLevel::Info:
      return "Info";
   case LoggerLevel::Warning:
      return "Warnung";
   case LoggerLevel::Error:
      return "Fehler";
   case LoggerLevel::Critical:
      return "Kritisch";
   case LoggerLevel::None:
      return "Ohne";
   default:
      return "???";
   }
}

///////////////////////////////////////////////////////////////////////////////

LoggerWidget::LoggerWidget(QWidget *parent)
   : QTreeView(parent), m_model(std::make_unique<LoggerModel>())
{
   setRootIsDecorated(false);
   setUniformRowHeights(true);

   setModel(m_model.get());
   m_updateTimer.setSingleShot(true);
   m_updateTimer.setInterval(std::chrono::milliseconds(200));
   m_updateTimer.callOnTimeout(this, [&]() { m_model->applyBufferedContent(); });

   connect(m_model.get(), &QAbstractItemModel::rowsAboutToBeInserted,
      this, &LoggerWidget::handleRowsAboutToBeInserted);

   connect(m_model.get(), &QAbstractItemModel::rowsInserted,
      this, &LoggerWidget::handleRowsInserted);

   m_loggerSink = std::make_shared<StandardWidgetLoggerSink>(this);
   Logger::appendLoggerSink(m_loggerSink);
}

LoggerWidget::~LoggerWidget()
{
   Logger::removeLoggerSink(m_loggerSink);
   m_loggerSink.reset();
}

void LoggerWidget::logEvent(const LoggerEntry& entry)
{
   m_model->appendLoggerEntry(entry);
}

void LoggerWidget::setFreeze(bool freeze)
{
   m_isFreezed = freeze;
   if (freeze)
   {
      m_updateTimer.stop();
   }
   else
   {
      m_updateTimer.start();
   }
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

