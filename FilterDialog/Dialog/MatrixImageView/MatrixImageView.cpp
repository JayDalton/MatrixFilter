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
   setupUISettings();

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

   m->ui.claheSpinBoxSize->setRange(
      FilterSettings::CLAHE_SIZE_MINIMUM, FilterSettings::CLAHE_SIZE_MAXIMUM);
   m->ui.claheSpinBoxSize->setValue(FilterSettings::CLAHE_SIZE_DEFAULT);
   m->ui.claheSpinBoxSize->setSingleStep(1);
   connect(m->ui.claheSpinBoxSize, QOverload<int>::of(&QSpinBox::valueChanged), 
      this, [&](auto) { applyFilterSetting(); });

   m->ui.claheSpinBoxClip->setRange(
      FilterSettings::CLAHE_CLIP_MINIMUM, FilterSettings::CLAHE_CLIP_MAXIMUM);
   m->ui.claheSpinBoxClip->setValue(FilterSettings::CLAHE_CLIP_DEFAULT);
   m->ui.claheSpinBoxClip->setSingleStep(0.1);
   connect(m->ui.claheSpinBoxClip, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
      this, [&](auto) { applyFilterSetting(); });

   connect(m->ui.claheGroupBox, &QGroupBox::toggled, 
      this, [&](bool) { applyFilterSetting(); });

   //connect(m->ui.suaceGroupBox, &QGroupBox::toggled, 
   //   this, [&](bool) { applyFilterSetting(); });
}

void MatrixImageView::setupUISettings()
{
   connect(m->ui.contrastGroupBox, &QGroupBox::toggled, 
      this, [&](auto) { applyFilterSetting(); });

   m->ui.contrastSpinBoxIntensity->setRange(1, 25);
   m->ui.contrastSpinBoxIntensity->setValue(3);
   m->ui.contrastSpinBoxIntensity->setSingleStep(1);

   connect(m->ui.contrastSpinBoxIntensity, QOverload<int>::of(&QSpinBox::valueChanged), 
      this, [&](auto) { applyFilterSetting(); });

   connect(m->ui.structureGroupBox, &QGroupBox::toggled, 
      this, [&](auto) { applyFilterSetting(); });

   m->ui.structureSpinBoxDistance->setRange(1, 255);
   m->ui.structureSpinBoxDistance->setValue(128);
   m->ui.structureSpinBoxDistance->setSingleStep(1);

   connect(m->ui.structureSpinBoxDistance, QOverload<int>::of(&QSpinBox::valueChanged), 
      this, [&](auto) { applyFilterSetting(); });

   m->ui.structureSpinBoxSigma->setRange(1, 255);
   m->ui.structureSpinBoxSigma->setValue(128);
   m->ui.structureSpinBoxSigma->setSingleStep(1);

   connect(m->ui.structureSpinBoxSigma, QOverload<int>::of(&QSpinBox::valueChanged), 
      this, [&](auto) { applyFilterSetting(); });
}

void MatrixImageView::applyFilterSetting()
{
   SPDLOG_INFO("apply filter settings");
   const auto filter = readFilterSettings();
   m->data->applyImageViewerFilter(filter);
}

void MatrixImageView::loadFilterSettings()
{
   auto filter = m->data->loadImageViewSettings();

   m->ui.checkHistoEqualize->setChecked(filter.m_histoEqualize);
   m->ui.claheGroupBox->setChecked(filter.m_claheEnabled);
   //m->ui.suaceGroupBox->setChecked(filter.m_suaceEnabled);
}

void MatrixImageView::saveFilterSettings() const
{
   FilterSettings filter;

   filter.m_histoEqualize = m->ui.checkHistoEqualize->isChecked();
   filter.m_claheEnabled = m->ui.claheGroupBox->isChecked();
   //filter.m_suaceEnabled = m->ui.suaceGroupBox->isChecked();

   m->data->saveImageViewSettings(filter);
}

FilterSettings MatrixImageView::readFilterSettings() const
{
   FilterSettings filter;

   filter.m_histoEqualize = m->ui.checkHistoEqualize->isChecked();

   filter.m_claheEnabled = m->ui.claheGroupBox->isChecked();
   filter.m_claheSize = m->ui.claheSpinBoxSize->value();
   filter.m_claheClip = m->ui.claheSpinBoxClip->value();

   filter.m_contrastEnhancement = m->ui.contrastGroupBox->isChecked();
   filter.m_contrastIntensity = m->ui.contrastSpinBoxIntensity->value();

   filter.m_structureEnhancement = m->ui.structureGroupBox->isChecked();
   filter.m_structureDistance = m->ui.structureSpinBoxDistance->value();
   filter.m_structureSigma = m->ui.structureSpinBoxSigma->value();

   //filter.m_suaceEnabled = m->ui.suaceGroupBox->isChecked();

   return filter;
}

void MatrixImageView::loadMatrix(MatrixLayer layer)
{
   auto matrix = m->data->currentMatrix(layer);
   m->ui.frameView->setImageMatrix(matrix);
   m->ui.frameView->update();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
