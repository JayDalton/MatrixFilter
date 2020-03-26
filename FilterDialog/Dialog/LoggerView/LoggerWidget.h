﻿#pragma once

#include <QTimer>
#include <QTreeView>
#include <QDateTime>

#include "Logger/Logger.h"
#include "Application/DataLayer.h"

///////////////////////////////////////////////////////////////////////////////

struct LoggerItem
{
   LoggerItem(const LoggerEntry& entry);

   uint m_thread;
   QString m_place;
   QString m_message;
   QDateTime m_timestamp;
   LoggerLevel m_priority;
};

class LoggerModel : public QAbstractItemModel
{
   Q_OBJECT

   using LoggerItemPtr = std::unique_ptr<LoggerItem>;

   enum class Column
   {
      Timestamp,
      Priority,
      Message,
      Thread,
      Place,
      Count
   };

public:
   ~LoggerModel() override = default;
   LoggerModel(std::size_t maxLogLength = MAX_ROW_COUNT);

   static constexpr std::size_t MAX_ROW_COUNT{ 200 };

   void setFreezed(bool freeze);
   void applyBufferedContent();
   void appendLoggerEntry(const LoggerEntry& entry);

   QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
   QModelIndex parent(const QModelIndex &child) const override;

   int rowCount(const QModelIndex& parent = {}) const override;
   int columnCount(const QModelIndex& parent = {}) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
   QVariant getDisplayData(int column, const LoggerItemPtr& item) const;
   QVariant getPriorityInfo(LoggerLevel level) const;

private:
   BufferedQueue<LoggerItemPtr> m_queue;
};

using LoggerModelPtr = std::unique_ptr<LoggerModel>;

///////////////////////////////////////////////////////////////////////////////

class LoggerWidget : public QTreeView
{
   Q_OBJECT

public:
   LoggerWidget(QWidget *parent);
   ~LoggerWidget() override = default;

   void logEvent(const LoggerEntry& entry);
   void setFreeze(bool freeze);
   void clearModel();

   BaseMutexLoggerPtr createLoggerAdapter();

protected:
   void showEvent(QShowEvent* event) override;
   void hideEvent(QHideEvent* event) override;

   void handleRowsAboutToBeInserted();
   void handleRowsInserted();

private:
   QTimer m_updateTimer;
   LoggerModelPtr m_model;
   bool m_autoScrolling{ true };
   bool m_isFreezed{ false };
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)