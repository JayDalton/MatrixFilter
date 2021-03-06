﻿#pragma once

#include <optional>

#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
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

   const ParameterListing& getParameterListing() const;

   VariantParameter& getConfigParameter(const QModelIndex& index);

signals:
   void sizeChanged(QRect size); // ???

protected:
   QModelIndex index(int row, int column, const QModelIndex& parent) const override;
   QModelIndex parent(const QModelIndex& child) const override;
   int rowCount(const QModelIndex& parent) const override;
   int columnCount(const QModelIndex& parent) const override;
   Qt::ItemFlags flags(const QModelIndex&) const override;
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
   QVariant data(const QModelIndex& index, int role) const override;

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

   uint getSourceRow(const QModelIndex& index);
   VariantParameter& getSourceParameter(const QModelIndex& index);

protected:
   bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
   bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

private:
   QStringList m_searchStringList;
};

using ConfigurationProxyPtr = std::unique_ptr<ConfigurationProxy>;

//////////////////////////////////////////////////////////////////////////////////////////

class BooleanParameterEditor : public QCheckBox /*QComboBox*/
{
   Q_OBJECT
public:
   BooleanParameterEditor(QWidget* parent, const BooleanParameter& param);
};

class IntegerParameterEditor : public QSpinBox
{
   Q_OBJECT
public:
   IntegerParameterEditor(QWidget* parent, const IntegerParameter& param);
};

class DoubleParameterEditor : public QDoubleSpinBox
{
   Q_OBJECT
public:
   DoubleParameterEditor(QWidget* parent, const DoubleParameter& param);
};

class StringParameterEditor : public QLineEdit
{
   Q_OBJECT
public:
   StringParameterEditor(QWidget* parent, const StringParameter& param);
};

class ListParameterEditor : public QComboBox
{
   Q_OBJECT
public:
   ListParameterEditor(QWidget* parent, const ListParameter& param);
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
