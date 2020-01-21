﻿#pragma once

#include <optional>

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "Config/Configuration.h"

class ConfigurationModel : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Label, Value, Count };

   explicit ConfigurationModel();
   ~ConfigurationModel() override = default;

   void setConfiguration(const Configuration& config);
   const Configuration& getConfiguration() const;

signals:
   void sizeChanged(QRect size);

protected:
   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

   bool setData(const QModelIndex &index, const QVariant &value,
      int role = Qt::EditRole) override;
   bool setHeaderData(int section, Qt::Orientation orientation,
      const QVariant &value, int role = Qt::EditRole) override;

   bool insertColumns(int position, int columns,
      const QModelIndex &parent = QModelIndex()) override;
   bool removeColumns(int position, int columns,
      const QModelIndex &parent = QModelIndex()) override;
   bool insertRows(int position, int rows,
      const QModelIndex &parent = QModelIndex()) override;
   bool removeRows(int position, int rows,
      const QModelIndex &parent = QModelIndex()) override;
private:
   Configuration m_config;
};

using ConfigurationModelPtr = std::unique_ptr<ConfigurationModel>;

//////////////////////////////////////////////////////////////////////////////////////////

class ConfigurationProxy final : public QSortFilterProxyModel
{
public:
   explicit ConfigurationProxy(QObject* parent = nullptr);
   ~ConfigurationProxy() override = default;

   //void updateSearch(const QString& searchString);
   //uint getSourceIndex(const QModelIndex& index);
   //MatrixFileInfo getSourceContact(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using ConfigurationProxyPtr = std::unique_ptr<ConfigurationProxy>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
