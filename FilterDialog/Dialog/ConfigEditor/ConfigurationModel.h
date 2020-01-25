#pragma once

#include <optional>

#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QSortFilterProxyModel>
#include <QSpinBox>

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

   VariantParameter& getConfigParameter(const QModelIndex& index);

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
      const QModelIndex& parent = {}) override;
   bool removeColumns(int position, int columns,
      const QModelIndex &parent = {}) override;
   bool insertRows(int position, int rows,
      const QModelIndex &parent = {}) override;
   bool removeRows(int position, int rows,
      const QModelIndex &parent = {}) override;
private:
   Configuration m_config;
   ParameterListing m_repository;
};

using ConfigurationModelPtr = std::unique_ptr<ConfigurationModel>;

//////////////////////////////////////////////////////////////////////////////////////////

class ConfigurationProxy final : public QSortFilterProxyModel
{
public:
   explicit ConfigurationProxy(QObject* parent = nullptr);
   ~ConfigurationProxy() override = default;

   //void updateSearch(const QString& searchString);
   uint getSourceRow(const QModelIndex& index);
   VariantParameter getSourceParameter(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using ConfigurationProxyPtr = std::unique_ptr<ConfigurationProxy>;

//////////////////////////////////////////////////////////////////////////////////////////

class IntegerParameterEditor : public QSpinBox
{
   Q_OBJECT
public:
   IntegerParameterEditor(QWidget* parent, const IntegerParameter& param);

private:
   signed m_minimum{ 0 };
   signed m_maximum{ 0 };
   signed m_current{ 0 };
};

class DoubleParameterEditor : public QDoubleSpinBox
{
   Q_OBJECT
public:
   DoubleParameterEditor(QWidget* parent, const DoubleParameter& param);

private:
   double m_minimum{ 0 };
   double m_maximum{ 0 };
   double m_current{ 0 };
};

/////////////////////////////////////////////////////////////////////////////

class ConfigurationDelegate : public QStyledItemDelegate
{
   Q_OBJECT
public:

   ConfigurationDelegate(ConfigurationProxy* model);

   QWidget* createEditor(QWidget* parent, 
      const QStyleOptionViewItem& option,
      const QModelIndex &index) const override;

   void setEditorData(QWidget* editor, 
      const QModelIndex& index) const override;

   void setModelData(QWidget* editor, 
      QAbstractItemModel* model,
      const QModelIndex& index) const override;

   void updateEditorGeometry(QWidget* editor, 
      const QStyleOptionViewItem& option,
      const QModelIndex& index) const override;

private:
   ConfigurationProxy* m_model{ nullptr };
};

using ConfigurationDelegatePtr = std::unique_ptr<ConfigurationDelegate>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
