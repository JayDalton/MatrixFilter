#include <stdafx.h>

#include "MatrixImageView.h"
#include "MatrixFrameView.h"

#include "Logger/Logger.h"

#include "ui_MatrixImageView.h"

#include <QKeyEvent>

struct MatrixImageView::Impl 
{
   explicit Impl(MatrixImageView* par, DataLayerSPtr data) 
      : parent(par), data(data) {}

   Ui::MatrixImageView ui;
   DataLayerSPtr data{ nullptr };

private:
   MatrixImageView* parent{ nullptr };
};

MatrixImageView::MatrixImageView(DataLayerSPtr data, QWidget* parent)
   : QWidget(parent), m(std::make_unique<Impl>(this, data))
{
   m->ui.setupUi(this);

   setupUIElements();

   setFocusPolicy(Qt::StrongFocus);

   auto con = connect(data.get(), &DataLayer::currentMatrixChanged, 
      this, [=]()
      {
         auto matrix = m->data->currentMatrix(MatrixLayer::Viewer);
         m->ui.frameView->setImageMatrix(matrix);
      }
   );
}

MatrixImageView::~MatrixImageView() = default;

void MatrixImageView::keyReleaseEvent(QKeyEvent* event)
{
   switch (event->key())
   {
   case Qt::Key_Up:
      return m->ui.frameView->setTranslateY(0.05);
   case Qt::Key_Down:
      return m->ui.frameView->setTranslateY(0.05);
   case Qt::Key_Left:
      return m->ui.frameView->setTranslateX(0.05);
   case Qt::Key_Right:
      return m->ui.frameView->setTranslateX(0.05);
   //case Qt::Key_PageUp:
   //case Qt::Key_PageDown:
   //   break;
   case Qt::Key_Plus:
      return m->ui.frameView->setScaleValue(0.95);
   case Qt::Key_Minus:
      return m->ui.frameView->setScaleValue(1.05);

   default:
      //spdlog::debug("key press not valid: {}", event->key());
      break;
   }
}

void MatrixImageView::setupUIElements()
{
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

// Codepage: UTF-8 (ÜüÖöÄäẞß)
