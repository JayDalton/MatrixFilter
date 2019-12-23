﻿#pragma once

#include <optional>

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "Config/Configuration.h"

class ConfigurationModel : public QAbstractItemModel
{
   Q_OBJECT
public:
   enum class Column { Name, Type, Size, Path, Extension, Count };

   explicit ConfigurationModel();
   ~ConfigurationModel() override = default;

   void setConfiguration();

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

private:
   std::optional<Configuration> m_config;
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