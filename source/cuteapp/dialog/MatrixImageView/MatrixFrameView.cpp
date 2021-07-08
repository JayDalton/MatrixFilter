#include <stdafx.h>

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

#include "MatrixFrameView.h"

#include "Logger/Logger.h"

MatrixFrameView::MatrixFrameView(QWidget* parent)
   : QFrame(parent)
{
}

void MatrixFrameView::setImageMatrix(const cv::Mat& matrix)
{
   m_matrix = matrix;
   m_bitmapImage = coverMatrixByImage(matrix);
   m_contentRect = m_bitmapImage.rect();
   m_visibleRect = m_bitmapImage.rect();
   m_displayRect = {};
}

void MatrixFrameView::setScaleValue(double value)
{
   QTransform transform;
   transform.scale(value, value);
   const auto center = m_visibleRect.center();
   m_visibleRect = transform.mapRect(m_visibleRect);
   m_visibleRect.moveCenter(center);
   update();
}

void MatrixFrameView::setTranslateX(double value)
{
   value = std::clamp(value, -1.0, +1.0);
   value = m_visibleRect.width() * value;
   const auto translated = m_visibleRect.translated(value, 0);
   if (m_contentRect.contains(translated.center()))
   {
      m_visibleRect = translated;
      update();
   }
}

void MatrixFrameView::setTranslateY(double value)
{
   value = std::clamp(value, -1.0, +1.0);
   value = m_visibleRect.height() * value;
   const auto translated = m_visibleRect.translated(0, value);
   if (m_contentRect.contains(translated.center()))
   {
      m_visibleRect = translated;
      update();
   }
}

void MatrixFrameView::paintEvent(QPaintEvent* event)
{
   QFrame::paintEvent(event);

   QPainter painter(this);
   if (m_matrix.empty())
   {
      painter.fillRect(rect(), Qt::gray);
      return;
   }

   m_displayRect = rect();
   painter.setTransform(createTransform());
   painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
   painter.drawImage(QPoint(0,0), m_bitmapImage);
}

QTransform MatrixFrameView::createTransform() const
{
   QTransform transform;
   if (m_matrix.empty()) return transform;

   // Berechnungen
   const auto translate{m_displayRect.center() - m_visibleRect.center()};

   const auto scaleW{ m_displayRect.width() / m_visibleRect.width() };
   const auto scaleH{ m_displayRect.height() / m_visibleRect.height() };
   const auto [minimum, maximum] { std::minmax(scaleW, scaleH) };

   // Transformation
   transform.translate(m_displayRect.center().x(), m_displayRect.center().y());
   transform.scale(minimum, minimum);
   transform.translate(translate.x(), translate.y());
   transform.translate(-m_displayRect.center().x(), -m_displayRect.center().y());

   return transform;
}

QImage MatrixFrameView::coverMatrixByImage(const cv::Mat& _matrix) const
{
   const std::unordered_map<int, QImage::Format> formats = {
      {CV_8UC1, QImage::Format_Grayscale8},
   {CV_16UC1, QImage::Format_Grayscale16},
   };

   const auto format{ _matrix.type() };
   if (!formats.contains(format))
   {
      qDebug() << "DPImageHelper::coverMatrixToImage - wrong image format";
      return {};
   }

   return QImage(
      _matrix.data, _matrix.cols, _matrix.rows,
      static_cast<int>(_matrix.step), formats.at(format)
   );
}


// Codepage: UTF-8 (ÜüÖöÄäẞß)
