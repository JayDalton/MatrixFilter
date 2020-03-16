#pragma once

#include <QImage>
#include <QFrame>
#include <QRect>

#include "Application/DataLayer.h"
#include "Matrix/MatrixImage.h"

class MatrixFrameView : public QFrame
{
   Q_OBJECT
public:
   explicit MatrixFrameView(QWidget* parent);

   void setImageMatrix(const cv::Mat& matrix);

   void setScaleValue(double value);
   void setTranslateX(double value);
   void setTranslateY(double value);

protected:
   void paintEvent(QPaintEvent* event) override;

private:
   QTransform createTransform() const;
   QImage coverMatrixByImage(const cv::Mat& _matrix) const;

private:
   cv::Mat m_matrix;
   QImage m_bitmapImage;
   QRectF m_displayRect{};
   QRectF m_visibleRect{};
   QRectF m_contentRect{};
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
