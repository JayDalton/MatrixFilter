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
      return m_config.getParameterCount();
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
      || (index.row() > m_config.getParameterCount()) 
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

   const auto names{ m_config.getParameterNames() };
   const auto ident{ names.at(index.row()) };
   const auto parameter{ m_config.getParameter(ident) };

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

bool ConfigurationModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
   return false;
}

bool ConfigurationModel::insertColumns(int position, int columns, const QModelIndex& parent)
{
   return false;
}

bool ConfigurationModel::removeColumns(int position, int columns, const QModelIndex& parent)
{
   return false;
}

bool ConfigurationModel::insertRows(int position, int rows, const QModelIndex& parent)
{
   return false;
}

bool ConfigurationModel::removeRows(int position, int rows, const QModelIndex& parent)
{
   return false;
}

//////////////////////////////////////////////////////////////////////////////////////////

ConfigurationProxy::ConfigurationProxy(QObject* parent)
   : QSortFilterProxyModel(parent)
{
}

//void ConfigurationProxy::updateSearch(const QString& searchString)
//{
//   m_searchStringList = searchString.split(' ', QString::SkipEmptyParts);
//   invalidate();
//}

uint ConfigurationProxy::getSourceRow(const QModelIndex& index)
{
   auto sourceIndex{ mapToSource(index) };
   auto sourceRow{ sourceIndex.row() };
   return static_cast<uint>(sourceRow);
}

VariantParameter ConfigurationProxy::getSourceParameter(const QModelIndex& index)
{
   const auto sourceIndex{ mapToSource(index) };
   if (auto model = qobject_cast<ConfigurationModel*>(sourceModel()))
   {
      return model->getConfigParameter(sourceIndex);
   }
   return BooleanParameter("default", "default", false);
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


ConfigurationDelegate::ConfigurationDelegate(ConfigurationProxy* model)
   : m_model(model)
{

}

QWidget* ConfigurationDelegate::createEditor(QWidget* parent, 
   const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   qDebug() << "createEditor: " << index;

   auto param = m_model->getSourceParameter(index);

   Visitor setWidget = {
      [parent, &param](const BooleanParameter&) -> QWidget* { return nullptr; },
      [parent, &param](const IntegerParameter&) -> QWidget* 
   { 
      const auto& parameter = std::get<IntegerParameter>(param);
      return new IntegerParameterEditor(parent, parameter); 
   },
      [parent, &param](const StringParameter&) -> QWidget* { return nullptr; },
      [parent, &param](const DoubleParameter&) -> QWidget* 
   { 
      const auto& parameter = std::get<DoubleParameter>(param);
      return new DoubleParameterEditor(parent, parameter); 
   },
      [parent, &param](const ListParameter&) -> QWidget* { return nullptr; },
   };

   QWidget* editor = std::visit(setWidget, param);

   return editor;
}

void ConfigurationDelegate::setEditorData(QWidget* editor, 
   const QModelIndex& index) const
{
   qDebug() << "setEditorData: " << index;
   //int value = index.model()->data(index, Qt::EditRole).toInt();

   //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
   //spinBox->setValue(value);
}

void ConfigurationDelegate::setModelData(QWidget* editor, 
   QAbstractItemModel* model, const QModelIndex& index) const
{
   qDebug() << "setModelData: " << index;
   //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
   //spinBox->interpretText();
   //int value = spinBox->value();

   //model->setData(index, value, Qt::EditRole);
}

void ConfigurationDelegate::updateEditorGeometry(QWidget* editor, 
   const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   qDebug() << "" << index;
   editor->setGeometry(option.rect);
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)