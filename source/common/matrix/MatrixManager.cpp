#include "stdafx.h"

#include "MatrixManager.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include "MatrixImage.h"
#include "../Logger/MethodTimer.h"
#include <iostream>

//#include <dcmtk/dcmdata/dcdatset.h> // dcm infos
//#include <dcmtk/dcmimgle/dcmimage.h>

void MatrixManager::loadMatrixFromFile(MatrixFileInfo fileInfo)
{
   if (!fileInfo.isValid())
   {
      return;
   }

   m_fileInfo = fileInfo;

   m_source = importMatrixFile(fileInfo);
   //m_source = normalizeMatrix(m_source);

   m_viewer = transformToViewer(m_source);
   //m_viewer = normalizeMatrix(m_viewer);

   m_floating = transformToFloating(m_source);

   m_fourier = transformToFourier(m_floating);

   m_magnitude = transformToMagnitude(m_fourier);

   m_display = transformToInteger(m_magnitude);

   m_target = transformToInteger(m_fourier);
}

cv::Mat MatrixManager::getMatrixData(MatrixLayer layer) const
{
   switch (layer)
   {
   case MatrixLayer::Source:
      return m_source;
   case MatrixLayer::Viewer:
      return m_viewer;
   case MatrixLayer::Floating:
      return m_floating;
   case MatrixLayer::Fourier:
      return m_fourier;
   case MatrixLayer::Magnitude:
      return m_magnitude;
   case MatrixLayer::Display:
      return m_display;
   case MatrixLayer::Target:
      return m_target;
   default:
      return {};
   }
}

cv::Mat MatrixManager::getViewerSource()
{
   m_viewer = transformToViewer(m_source);
   return m_viewer;
}

MatrixPropertyList MatrixManager::getMatrixPropertyList(MatrixLayer layer) const
{
   switch (layer)
   {
   case MatrixLayer::Source:
      return showInformation(m_source);
   case MatrixLayer::Floating:
      return showInformation(m_floating);
   case MatrixLayer::Fourier:
      return showInformation(m_fourier);
   case MatrixLayer::Magnitude:
      return showInformation(m_magnitude);
   case MatrixLayer::Target:
      return showInformation(m_target);
   default:
      return {};
   }
}

cv::Mat MatrixManager::importMatrixFile(MatrixFileInfo info) const
{
   info.getFileType(); // pgm, dcm

   const auto filePath{ info.getPath().string() };
   return cv::imread(filePath, cv::IMREAD_GRAYSCALE | cv::IMREAD_ANYDEPTH);
}

cv::Mat MatrixManager::normalizeMatrix(const cv::Mat& source) const
{
   cv::Mat converted;
   using Bounds = std::pair<double, double>;
   const std::unordered_map<int, Bounds> table {
      {CV_8UC1, {0, std::numeric_limits<unsigned char>::max()}},
      {CV_16UC1, {0, std::numeric_limits<unsigned short>::max()}},
   };

   const auto& [lowerBound, upperBound] = table.at(source.type());
   cv::normalize(source, converted, lowerBound, upperBound, cv::NORM_MINMAX);
   return converted;
}

cv::Mat MatrixManager::transformToViewer(const cv::Mat& source) const
{
   cv::Mat converted;
   source.convertTo(converted, CV_8UC1, 1.0 / UCHAR_MAX);  // bytes
   return converted;
}

cv::Mat MatrixManager::transformToFloating(const cv::Mat& source) const
{
   cv::Mat converted;
   source.convertTo(converted, CV_32F, 1.0 / USHRT_MAX); // float
   return converted;
}

cv::Mat MatrixManager::transformToInteger(const cv::Mat& source) const
{
   cv::Mat converted;
   source.convertTo(converted, CV_16UC1, USHRT_MAX);  // short
   return converted;
}

cv::Mat MatrixManager::transformToFourier(const cv::Mat& source) const
{
   assert(source.depth() == CV_32F);		// 32 bit - float
   assert(source.channels() == 1);			// 1 chan

   MethodTimer timer{__func__};
   auto now{ cv::getTickCount() };

   cv::Mat padded;
   cv::copyMakeBorder(source, padded, 
      0, cv::getOptimalDFTSize(source.rows) - source.rows,
      0, cv::getOptimalDFTSize(source.cols) - source.cols,
      cv::BORDER_CONSTANT, cv::Scalar::all(0)
   );

   cv::Mat result;
   cv::dft(padded, result, cv::DFT_ROWS | cv::DFT_COMPLEX_OUTPUT);

   dump_duration(now, "complete transform");
   assert(result.depth() == CV_32F);		// 32 bit - float
   assert(result.channels() == 2);			// 2 chan

   return result;
}

cv::Mat MatrixManager::transformToMagnitude(const cv::Mat& source) const
{
   CV_Assert(source.depth() == CV_32F);		// 32 bit
   CV_Assert(source.channels() == 2);			// 2 chan

   auto now{ cv::getTickCount() };

   cv::Mat planes[2];
   cv::split(source, planes);

   cv::magnitude(
      planes[0], 
      planes[1], 
      planes[0]
   );

   cv::Mat result = planes[0];
   result += cv::Scalar::all(1);							// switch to logarithmic scale
   cv::log(result, result);

   // crop the spectrum, if it has an odd number of rows or columns
   result = result(cv::Rect(0, 0, result.cols & -2, result.rows & -2));

   result = recenterDFT(result);

   cv::normalize(result, result, 0.0, 1.0, cv::NORM_MINMAX);

   dump_duration(now, "complete magnitude");
   CV_Assert(result.depth() == CV_32F);		// 32 bit - float
   CV_Assert(result.channels() == 1);			// 1 chan
   CV_Assert(result.cols > 0);
   CV_Assert(result.rows > 0);
   CV_Assert(result.size > 0);

   return result;
}

cv::Mat MatrixManager::recenterDFT(const cv::Mat& source) const
{
   int centerX = source.cols / 2;
   int centerY = source.rows / 2;

   cv::Mat q1(source, cv::Rect(0, 0, centerX, centerY));
   cv::Mat q2(source, cv::Rect(centerX, 0, centerX, centerY));
   cv::Mat q3(source, cv::Rect(0, centerY, centerX, centerY));
   cv::Mat q4(source, cv::Rect(centerX, centerY, centerX, centerY));

   cv::Mat swapMap;

   q1.copyTo(swapMap);
   q4.copyTo(q1);
   swapMap.copyTo(q4);

   q2.copyTo(swapMap);
   q3.copyTo(q2);
   swapMap.copyTo(q3);

   return swapMap;
}

cv::Mat MatrixManager::transformToInvert(const cv::Mat& source) const
{
   assert(source.depth() == CV_32F);		// 32 bit
   assert(source.channels() == 2);			// 2 chan

   auto now{ cv::getTickCount() };

   cv::Mat target;
   cv::dft(source, target, 
      cv::DFT_COMPLEX_INPUT | cv::DFT_REAL_OUTPUT | 
      cv::DFT_INVERSE | cv::DFT_SCALE | cv::DFT_ROWS
   );

   dump_duration(now, "complete dft invert: ");
   return target;
}

int64 MatrixManager::dump_duration(int64 now, std::string label) const
{
   auto duration = cv::getTickCount() - now;
   std::cout << label << ": " << duration / cv::getTickFrequency() << std::endl;
   return cv::getTickCount();
}

MatrixPropertyList MatrixManager::showInformation(const cv::Mat& matrix) const
{
   MethodTimer timer{ __func__ };

   CV_Assert(matrix.channels() == 1);			// 1 chan

   double min_val{ 0 }, max_val{ 0 };
   cv::Point min_loc{ 0,0 }, max_loc{ 0,0 };
   cv::minMaxLoc(matrix, &min_val, &max_val, &min_loc, &max_loc);

   return MatrixPropertyList {
      MatrixProperty{"Type", matrix.type()},
      MatrixProperty{"Rows", matrix.rows},
      MatrixProperty{"Columns", matrix.cols},
      MatrixProperty{"Channels", matrix.channels()},
      MatrixProperty{"Minimum", min_val},
      MatrixProperty{"Maximum", max_val},
      MatrixProperty{"Min Loc", MatrixPoint{min_loc.x, min_loc.y}},
      MatrixProperty{"Max Loc", MatrixPoint{max_loc.x, max_loc.y}},
   };
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
