#pragma once

#include <QTimer>
#include <QTreeView>

#include "Logger/BufferedQueue.h"

struct LoggerEntry
{

};

struct LoggerAppender // public spdlog::sinks::base_sink <Mutex>
{

};

///////////////////////////////////////////////////////////////////////////////

class LoggerModel : public QAbstractItemModel
{
   Q_OBJECT

   using LoggerEntryPtr = std::unique_ptr<LoggerEntry>;

   enum class Column
   {
      Timestamp,
      Priority,
      Message,
      Thread,
      Line,
      Count
   };

public:
   ~LoggerModel() override = default;
   LoggerModel(std::size_t maxLogLength = MAX_ROW_COUNT, 
      std::chrono::milliseconds interval = UPDATE_INTERVAL);

   void appendLog();
   void showBuffered();
   void setFreezed(bool freeze);

   QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
   QModelIndex parent(const QModelIndex &child) const override;

   int rowCount(const QModelIndex& parent = {}) const override;
   int columnCount(const QModelIndex& parent = {}) const override;
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

   static constexpr std::size_t MAX_ROW_COUNT{ 200 };
   static constexpr std::chrono::milliseconds UPDATE_INTERVAL{ 250 };

private:
   void updateViewModelFromBuffer();

private:
   QTimer m_updateTimer;
   BufferedQueue<LoggerEntryPtr> m_queue;
};

///////////////////////////////////////////////////////////////////////////////

class LoggerWidget : public QTreeView
{
   Q_OBJECT

public:
   LoggerWidget(QWidget *parent);
   ~LoggerWidget() override = default;

   void logEvent();
   void setFreeze(bool freeze);
   void clearModel();

protected:
   void showEvent(QShowEvent* event) override;
   void hideEvent(QHideEvent* event) override;

   void handleRowsAboutToBeInserted();
   void handleRowsInserted();

private:
   std::unique_ptr<LoggerModel> m_model;
   bool m_autoScrolling{ true };
   bool m_isFreezed{ false };
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
