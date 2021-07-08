#include <stdafx.h>

#include <QSpinBox>

#include "MatrixDataTab.h"

#include "ui_MatrixDataTab.h"

struct MatrixDataTab::Impl
{
   explicit Impl(MatrixDataTab* parent, DataLayerSPtr data) 
      : parent(parent), data(data) {}
   
   DataLayerSPtr data{ nullptr };
   Ui::MatrixDataTab ui;

   const std::map<MatrixLayer, QString> matrixLayer
   { 
      {MatrixLayer::Source, "Source"}, 
      {MatrixLayer::Viewer, "Viewer"}, 
      {MatrixLayer::Floating, "Floating"}, 
      {MatrixLayer::Magnitude, "Magnitude"}, 
      {MatrixLayer::Display, "Display"}, 
   };

private:
   MatrixDataTab* parent{ nullptr };
};

//////////////////////////////////////////////////////////////////////

MatrixDataTab::MatrixDataTab(DataLayerSPtr data, QWidget* parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);
   
   setupUIElements();

   auto con = connect(data.get(), &DataLayer::currentMatrixChanged, 
      this, [&]() 
      { 
         const auto index{ m->ui.comboBox->currentIndex() };
         loadMatrix(static_cast<MatrixLayer>(index)); 
      }
   );
}

MatrixDataTab::~MatrixDataTab() = default;

void MatrixDataTab::loadMatrix(MatrixLayer layer)
{
   auto matrix = m->data->currentMatrix(layer);
   m_matrixValueDataModel->setImageMatrix(matrix);
   
   auto list = m->data->currentPropertyList(layer);
   m_matrixPropertyModel->setPropertyList(list);
}

void MatrixDataTab::setupUIElements()
{
   m->ui.treeView->setRootIsDecorated(false);
   m->ui.treeView->setUniformRowHeights(true);

   m_matrixValueDataModel = std::make_unique<MatrixValueDataModel>();
   m_matrixValueDataProxy = std::make_unique<MatrixValueDataProxy>();
   m_matrixValueDataProxy->setSourceModel(m_matrixValueDataModel.get());
   m->ui.treeView->setModel(m_matrixValueDataProxy.get());

   m_matrixPropertyModel = std::make_unique<MatrixPropertyModel>();
   m_matrixPropertyProxy = std::make_unique<MatrixPropertyProxy>();
   m_matrixPropertyProxy->setSourceModel(m_matrixPropertyModel.get());
   m->ui.treePropertyView->setModel(m_matrixPropertyProxy.get());

   auto a = connect(m_matrixValueDataModel.get(), &MatrixValueDataModel::sizeChanged,
      this, [&]() { setupMatrixRange(m_matrixValueDataModel->getSectionRange()); });

   auto z = connect(m->ui.comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
      this, [&](int index) 
      {
         const auto value = m->ui.comboBox->itemData(index);
         loadMatrix(static_cast<MatrixLayer>(value.toInt())); 
      });

   for (const auto& [value, label] : m->matrixLayer)
   {
      m->ui.comboBox->addItem(label, static_cast<int>(value));
   }

   setupMatrixRange(QRect{});

   auto b = connect(m->ui.spinBoxPointX, QOverload<int>::of(&QSpinBox::valueChanged),
      this, [&](int value) { 
         auto rect = m_matrixValueDataModel->getSectionRange(); rect.setLeft(value);
         m_matrixValueDataModel->setSectionRange(rect); });

   auto c = connect(m->ui.spinBoxPointY, QOverload<int>::of(&QSpinBox::valueChanged),
      this, [&](int value) { 
         auto rect = m_matrixValueDataModel->getSectionRange(); rect.setTop(value);
         m_matrixValueDataModel->setSectionRange(rect); });

   auto x = connect(m->ui.spinBoxSizeW, QOverload<int>::of(&QSpinBox::valueChanged),
      this, [&](int value) { 
         auto rect = m_matrixValueDataModel->getSectionRange(); rect.setWidth(value);
         m_matrixValueDataModel->setSectionRange(rect); });

   auto y = connect(m->ui.spinBoxSizeH, QOverload<int>::of(&QSpinBox::valueChanged),
      this, [&](int value) { 
         auto rect = m_matrixValueDataModel->getSectionRange(); rect.setHeight(value);
         m_matrixValueDataModel->setSectionRange(rect); });

}

void MatrixDataTab::setupMatrixRange(const QRect& range)
{
   //#todo range => matrix.size
   m->ui.spinBoxPointX->setRange(0, range.width());
   m->ui.spinBoxPointY->setRange(0, range.height());


   m->ui.spinBoxPointX->setValue(range.x());
   m->ui.spinBoxPointY->setValue(range.y());

   m->ui.spinBoxSizeW->setRange(0, range.width());
   m->ui.spinBoxSizeW->setValue(range.width());

   m->ui.spinBoxSizeH->setRange(0, range.height());
   m->ui.spinBoxSizeH->setValue(range.height());
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
