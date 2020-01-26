#include "stdafx.h"

#include "ConfigurationModel.h"
#include <Config\Visitor.h>

#include <QDebug>

ConfigurationModel::ConfigurationModel()
{
}

void ConfigurationModel::setConfiguration(const Configuration& config)
{
   beginResetModel();
   m_config = config;
   m_repository = config.getParameterList();
   //m_repository.insert();
   endResetModel();
}

const Configuration& ConfigurationModel::getConfiguration() const
{
   return m_config;
}

VariantParameter& ConfigurationModel::getConfigParameter(const QModelIndex& index)
{
   return m_repository.at(index.row());
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
      return m_repository.size();
      //return m_config.getParameterCount();
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
   if (!index.isValid())
   {
      return Qt::NoItemFlags;
   }

   return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant ConfigurationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   switch (static_cast<Column>(section))
   {
   case Column::Label:
      return "Bezeichnung";
   case Column::Value:
      return "Wertigkeit";
   default:
      return {};
   }
}

QVariant ConfigurationModel::data(const QModelIndex& index, int role) const
{
   if (role != Qt::DisplayRole)
   {
      return {};
   }

   if (index.parent().isValid() 
      || (index.row() > m_repository.size()) 
      //|| (index.row() > m_config.getParameterCount()) 
      || (index.column() > static_cast<int>(Column::Count)))
   {
      return {};
   }

   Visitor getLabel = {
      [](const auto& param) -> std::string { return param.getLabel(); }
   };

   Visitor getValue = {
      [&](const DoubleParameter& value) -> QVariant { return value.getCurrent(); },
      [&](const StringParameter& value) -> QVariant { return QString::fromStdString(value.getCurrent()); },
      [&](const BooleanParameter& value) -> QVariant { return value.getCurrent(); },
      [&](const IntegerParameter& value) -> QVariant { return value.getCurrent(); },
      [&](const ListParameter& value) -> QVariant { return {}; },
   };

   //const auto names{ m_config.getParameterNames() };
   //const auto ident{ names.at(index.row()) };
   //const auto parameter{ m_config.getParameter(ident) };
   const auto parameter{ m_repository.at(index.row()) };

   switch (static_cast<Column>(index.column()))
   {
   case Column::Label: 
      return QLatin1String(std::visit(getLabel, parameter).c_str());
   case Column::Value:
      return std::visit(getValue, parameter);
   default: 
      return {};
   }
}

bool ConfigurationModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
   return false;
}

//////////////////////////////////////////////////////////////////////////////////////////

ConfigurationProxy::ConfigurationProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

uint ConfigurationProxy::getSourceRow(const QModelIndex& index)
{
   auto sourceIndex{ mapToSource(index) };
   auto sourceRow{ sourceIndex.row() };
   return static_cast<uint>(sourceRow);
}

VariantParameter& ConfigurationProxy::getSourceParameter(const QModelIndex& index)
{
   const auto sourceIndex{ mapToSource(index) };
   auto model = qobject_cast<ConfigurationModel*>(sourceModel());
   return model->getConfigParameter(sourceIndex);
}

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

//////////////////////////////////////////////////////////////////////////////////////////

BooleanParameterEditor::BooleanParameterEditor(QWidget* parent, const BooleanParameter& param)
   : QCheckBox(parent)
{
   setChecked(param.getCurrent());
}

IntegerParameterEditor::IntegerParameterEditor(QWidget* parent, const IntegerParameter& param)
   : QSpinBox(parent)
{
   setMaximum(param.getMaximum());
   setMinimum(param.getMinimum());
   setValue(param.getCurrent());
   setFrame(false);
}

DoubleParameterEditor::DoubleParameterEditor(QWidget* parent, const DoubleParameter& param)
   : QDoubleSpinBox(parent)
{
   setMaximum(param.getMaximum());
   setMinimum(param.getMinimum());
   setValue(param.getCurrent());
   setFrame(false);
}

StringParameterEditor::StringParameterEditor(QWidget* parent, const StringParameter& param)
   : QLineEdit(parent)
{
   setText(QString::fromStdString(param.getCurrent()));
}

//////////////////////////////////////////////////////////////////////////////////////////

ConfigurationDelegate::ConfigurationDelegate(ConfigurationProxy* model)
   : m_model(model)
{
}

QWidget* ConfigurationDelegate::createEditor(QWidget* parent, 
   const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   auto& param = m_model->getSourceParameter(index);

   Visitor setWidget = 
   {
      [parent, &param](const BooleanParameter&) -> QWidget* 
   { 
      const auto& parameter = std::get<BooleanParameter>(param);
      return new BooleanParameterEditor(parent, parameter); 
   },
      [parent, &param](const IntegerParameter&) -> QWidget* 
   { 
      const auto& parameter = std::get<IntegerParameter>(param);
      return new IntegerParameterEditor(parent, parameter); 
   },
      [parent, &param](const StringParameter&) -> QWidget* 
   { 
      const auto& parameter = std::get<StringParameter>(param);
      return new StringParameterEditor(parent, parameter); 
   },
      [parent, &param](const DoubleParameter&) -> QWidget* 
   { 
      const auto& parameter = std::get<DoubleParameter>(param);
      return new DoubleParameterEditor(parent, parameter); 
   },
      [parent, &param](const ListParameter&) -> QWidget* { return nullptr; },
   };

   return std::visit(setWidget, param);
}

void ConfigurationDelegate::setEditorData(QWidget* widget, 
   const QModelIndex& index) const
{
   Q_UNUSED(widget);
   qDebug() << "setEditorData: " << index;
   //int value = index.model()->data(index, Qt::EditRole).toInt();
   //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
   //spinBox->setValue(value);
}

void ConfigurationDelegate::setModelData(QWidget* widget, 
   QAbstractItemModel* model, const QModelIndex& index) const
{
   qDebug() << "setModelData: " << index;

   Visitor setCurrent = 
   {
      [widget](BooleanParameter& param) mutable { 
      if (auto* editor = static_cast<BooleanParameterEditor*>(widget))
      {
         param.setCurrent(editor->isChecked());
      }},
      [widget](IntegerParameter& param) mutable { 
      if (auto* editor = static_cast<IntegerParameterEditor*>(widget))
      {
         param.setCurrent(editor->value());
      }},
      [widget](StringParameter& param) mutable { 
      if (auto* editor = static_cast<StringParameterEditor*>(widget))
      {
         param.setCurrent(editor->text().toStdString());
      }},
      [widget](DoubleParameter& param) mutable {
      if (auto* editor = static_cast<DoubleParameterEditor*>(widget))
      {
         param.setCurrent(editor->value());
      }},
      [widget](ListParameter& param) mutable { ; },
   };

   std::visit(setCurrent, m_model->getSourceParameter(index));
}

void ConfigurationDelegate::updateEditorGeometry(QWidget* editor, 
   const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   editor->setGeometry(option.rect);
}


//signed IntegerParameterEditor::getCurrentValue() const
//{
//   return value();
//}
//
//double DoubleParameterEditor::getCurrentValue() const
//{
//   return value();
//}

// Codepage: UTF-8 (ÜüÖöÄäẞß)