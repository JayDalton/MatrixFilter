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
      {MatrixLayer::Fourier, "Fourier"}, 
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
      this, [&]() { load(); }
   );
}

MatrixDataTab::~MatrixDataTab() = default;

void MatrixDataTab::load()
{
   auto matrix = m->data->currentMatrix(MatrixLayer::Source);
   m_matrixValueDataModel->setImageMatrix(matrix);
   
   auto list = m->data->currentPropertyList(MatrixLayer::Source);
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

   auto b = connect(m->ui.comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
      this, [&](int index) { static_cast<MatrixLayer>(index); });

   for (const auto& [value, label] : m->matrixLayer)
   {
      m->ui.comboBox->addItem(label, static_cast<int>(value));
   }


   setupMatrixRange(QRect{});

   //auto b = connect(m->ui.spinBoxPointX, QOverload<int>::of(&QSpinBox::valueChanged),
   //   this, [&](int value) { 
   //      auto rect = retriveMatrixRange(); rect.setLeft(value);
   //      m_matrixValueDataModel->setSectionRange(rect); });

   //auto c = connect(m->ui.spinBoxPointY, QOverload<int>::of(&QSpinBox::valueChanged),
   //   this, [&](int value) { 
   //      auto rect = retriveMatrixRange(); rect.setTop(value);
   //      m_matrixValueDataModel->setSectionRange(rect); });

   //auto x = connect(m->ui.spinBoxSizeW, QOverload<int>::of(&QSpinBox::valueChanged),
   //   this, [&](int value) { 
   //      auto rect = retriveMatrixRange(); rect.setWidth(value);
   //      m_matrixValueDataModel->setSectionRange(rect); });

   //auto y = connect(m->ui.spinBoxSizeH, QOverload<int>::of(&QSpinBox::valueChanged),
   //   this, [&](int value) { 
   //      auto rect = retriveMatrixRange(); rect.setHeight(value);
   //      m_matrixValueDataModel->setSectionRange(rect); });

}

void MatrixDataTab::setupMatrixRange(const QRect& range)
{
   m->ui.spinBoxPointX->setRange(0, range.width());
   m->ui.spinBoxPointX->setSingleStep(10);
   m->ui.spinBoxPointX->setValue(range.x());

   m->ui.spinBoxPointY->setRange(0, range.height());
   m->ui.spinBoxPointY->setSingleStep(10);
   m->ui.spinBoxPointY->setValue(range.y());

   m->ui.spinBoxSizeW->setRange(0, range.width());
   m->ui.spinBoxSizeW->setSingleStep(10);
   m->ui.spinBoxSizeW->setValue(10);

   m->ui.spinBoxSizeH->setRange(0, range.height());
   m->ui.spinBoxSizeH->setSingleStep(10);
   m->ui.spinBoxSizeH->setValue(10);
}

QRect MatrixDataTab::retriveMatrixRange() const
{
   const auto rect = QRect(
      m->ui.spinBoxPointX->value(),
      m->ui.spinBoxPointY->value(),
      m->ui.spinBoxSizeW->value(),
      m->ui.spinBoxSizeH->value()
   );
   return rect;
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
