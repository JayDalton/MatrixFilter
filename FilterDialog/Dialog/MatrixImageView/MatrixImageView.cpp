#include <stdafx.h>

#include "MatrixImageView.h"
#include "MatrixFrameView.h"

#include "Logger/Logger.h"

#include "ui_MatrixImageView.h"

#include <QDebug>
#include <QKeyEvent>

#include <unordered_set>

struct MatrixImageView::Impl 
{
   explicit Impl(MatrixImageView* par, DataLayerSPtr data) 
      : parent(par), data(data) {}

   Ui::MatrixImageView ui;
   DataLayerSPtr data{ nullptr };
   std::unordered_set<int> m_validKeys{
      Qt::Key_Left, Qt::Key_Right, 
      Qt::Key_Plus, Qt::Key_Minus,
      Qt::Key_Up, Qt::Key_Down,
   };

   const std::map<MatrixLayer, QString> matrixLayer
   { 
      {MatrixLayer::Viewer, "Viewer"}, 
      {MatrixLayer::Display, "Display"}, 
   };

private:
   MatrixImageView* parent{ nullptr };
};

//////////////////////////////////////////////////////////////////////////////////////

MatrixImageView::MatrixImageView(DataLayerSPtr data, QWidget* parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);

   setupUIElements();

   installEventFilter(this);

   setFocusPolicy(Qt::StrongFocus);

   auto con = connect(data.get(), &DataLayer::currentMatrixChanged, 
      this, [=]()
      {
         const auto index{ m->ui.comboBox->currentIndex() };
         const auto value{ m->ui.comboBox->itemData(index) };
         loadMatrix(static_cast<MatrixLayer>(value.toInt())); 
      }
   );
}

MatrixImageView::~MatrixImageView() = default;

bool MatrixImageView::eventFilter(QObject* object, QEvent* event)
{
   if (event->type() != QEvent::KeyPress) 
   {
      return false;
   }

   const auto keyEvent{static_cast<QKeyEvent*>(event)};
   const auto keyValue{ keyEvent->key() };

   if (!m->m_validKeys.contains(keyValue))
   {
      return false;
   }

   //if (object == m->ui.frameView)
   //{
   //   return true;
   //}

   return false;
}

void MatrixImageView::keyReleaseEvent(QKeyEvent* event)
{
   switch (event->key())
   {
   case Qt::Key_Up:
      return m->ui.frameView->setTranslateY(-0.05);
   case Qt::Key_Down:
      return m->ui.frameView->setTranslateY(0.05);
   case Qt::Key_Left:
      return m->ui.frameView->setTranslateX(-0.05);
   case Qt::Key_Right:
      return m->ui.frameView->setTranslateX(0.05);
   case Qt::Key_Plus:
      return m->ui.frameView->setScaleValue(0.95);
   case Qt::Key_Minus:
      return m->ui.frameView->setScaleValue(1.05);
   default:
      break;
   }
}

void MatrixImageView::setupUIElements()
{
   for (const auto& [value, label] : m->matrixLayer)
   {
      m->ui.comboBox->addItem(label, static_cast<int>(value));
   }

   connect(m->ui.comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
      this, [&](int index) 
      {
         const auto value = m->ui.comboBox->itemData(index);
         loadMatrix(static_cast<MatrixLayer>(value.toInt())); 
      });

   connect(m->ui.checkHistoEqualize, &QCheckBox::toggled, 
      this, [&](bool) { applyFilterSetting(); });

   connect(m->ui.claheGroupBox, &QGroupBox::toggled, 
      this, [&](bool) { applyFilterSetting(); });

   connect(m->ui.suaceGroupBox, &QGroupBox::toggled, 
      this, [&](bool) { applyFilterSetting(); });
}

void MatrixImageView::applyFilterSetting()
{
   const auto filter = readFilterSettings();
   m->data->applyImageViewerFilter(filter);
}

void MatrixImageView::loadFilterSettings()
{
   auto filter = m->data->loadImageViewSettings();

   m->ui.checkHistoEqualize->setChecked(filter.m_histoEqualize);
   m->ui.claheGroupBox->setChecked(filter.m_claheEnabled);
   m->ui.suaceGroupBox->setChecked(filter.m_suaceEnabled);
}

void MatrixImageView::saveFilterSettings() const
{
   FilterSettings filter;

   filter.m_histoEqualize = m->ui.checkHistoEqualize->isChecked();
   filter.m_claheEnabled = m->ui.claheGroupBox->isChecked();
   filter.m_suaceEnabled = m->ui.suaceGroupBox->isChecked();

   m->data->saveImageViewSettings(filter);
}

FilterSettings MatrixImageView::readFilterSettings() const
{
   FilterSettings filter;

   filter.m_histoEqualize = m->ui.checkHistoEqualize->isChecked();
   filter.m_claheEnabled = m->ui.claheGroupBox->isChecked();
   filter.m_suaceEnabled = m->ui.suaceGroupBox->isChecked();

   return filter;
}

void MatrixImageView::loadMatrix(MatrixLayer layer)
{
   auto matrix = m->data->currentMatrix(layer);
   m->ui.frameView->setImageMatrix(matrix);
   m->ui.frameView->update();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
