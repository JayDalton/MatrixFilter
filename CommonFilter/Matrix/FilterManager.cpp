#include "stdafx.h"

#include "FilterManager.h"

#include <opencv2/core/base.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

void FilterManager::setFilterSettings(FilterSettings setting)
{
   m_setting = setting;
}

void FilterManager::applyFilter(const cv::Mat& source, cv::Mat& target)
{
   target = source;
   if (m_setting.m_claheEnabled)
   {
      applyCLAHE(source, target);
   }

   if (m_setting.m_histoEqualize)
   {
      applyHistogramEqualization(source, target);
   }

   if (m_setting.m_structureEnhancement)
   {
      applyStructureEnhancement(source, target);
   }

   if (m_setting.m_contrastEnhancement)
   {
      applyContrastEnhancement(source, target);
   }
}

void FilterManager::applyCLAHE(const cv::Mat& source, cv::Mat& target)
{
   const auto clip {m_setting.m_claheClip};
   const auto size {m_setting.m_claheSize};
   const auto area {cv::Size(size, size)};
   SPDLOG_DEBUG("apply CLAHE clip {} size {}", clip, size);

   auto clahe{ cv::createCLAHE(clip, area) };
   clahe->apply(source, target); // inplace
}

void FilterManager::applyHistogramEqualization(const cv::Mat& source, cv::Mat& target)
{
   SPDLOG_DEBUG("apply histogram...{}", source.type());
   assert(source.type() == CV_8UC1);
   cv::equalizeHist(source, target);
}

void FilterManager::applyContrastEnhancement(const cv::Mat& source, cv::Mat& target)
{
   const auto contrast {m_setting.m_contrastIntensity};
   const auto bright {m_setting.m_brightnessIntensity};
   SPDLOG_DEBUG("apply contrast {} brightness {}", contrast, bright);

   source.convertTo(target, -1, contrast, bright);
}

void FilterManager::applyStructureEnhancement(const cv::Mat& source, cv::Mat& target)
{
   const auto distance {m_setting.m_structureDistance};
   const auto sigma {m_setting.m_structureSigma};
   SPDLOG_DEBUG("apply distance {} sima {}", distance, sigma);

   cv::Mat output;
   performSUACE(source, output, distance, (sigma + 1.0) / 8.0);
   target = output;
}

//https://www.codeproject.com/Articles/1203383/A-Fast-Simple-and-Powerful-Contrast-Enhancement-Al
void FilterManager::performSUACE(const cv::Mat& source, cv::Mat& target, int distance, double sigma)
{
   assert(source.type() == CV_8UC1);
   if (!(distance > 0 && sigma > 0))
   {
      SPDLOG_WARN("distance and sigma must be greater 0");
      //CV_Error(CV_StsBadArg, "distance and sigma must be greater 0");
   }

   target = cv::Mat(source.size(), CV_8UC1);
   cv::Mat smoothed;
   int val;
   int a, b;
   int adjuster;
   int half_distance = distance / 2;
   double distance_d = distance;

   cv::GaussianBlur(source, smoothed, cv::Size(0, 0), sigma); // langsam für hohes sigma

   for (int x = 0; x < source.cols; x++)
   {
      for (int y = 0; y < source.rows; y++)
      {
         val = source.at<uchar>(y, x);
         adjuster = smoothed.at<uchar>(y, x);
         if ((val - adjuster) > distance_d) adjuster += (val - adjuster)*0.5;
         adjuster = adjuster < half_distance ? half_distance : adjuster;
         b = adjuster + half_distance;
         b = b > 255 ? 255 : b;
         a = b - distance;
         a = a < 0 ? 0 : a;

         if (val >= a && val <= b)
         {
            target.at<uchar>(y, x) = (int)(((val - a) / distance_d) * 255);
         }
         else if (val < a) {
            target.at<uchar>(y, x) = 0;
         }
         else if (val > b) {
            target.at<uchar>(y, x) = 255;
         }
      }
   }
}

// Sigmoidal Contrast: angepasst an Verfahren mit ImageMagick (digipaX 1)

#define Sigmoidal(a,b,x) ( 1.0/(1.0+exp((a)*((b)-(x)))) )

#define ScaledSigmoidal(a,b,x) (                    \
  (Sigmoidal((a),(b),(x))-Sigmoidal((a),(b),0.0)) / \
  (Sigmoidal((a),(b),1.0)-Sigmoidal((a),(b),0.0)) )

void FilterManager::performSigmoidalContrast(const cv::Mat& _input, cv::Mat& _output, double _contrast)
{
   assert(_input.type() == CV_8UC1);
   _output = cv::Mat(_input.size(), CV_8UC1);
   auto midpoint = 128;
   uchar sigmoidMap[255];
   for (int i = 0; i < 256; i++)
   {
      sigmoidMap[i] = static_cast<uchar>(std::round(255.0*ScaledSigmoidal(_contrast,midpoint/255.0,i/255.0)));
   }

   for (int x = 0; x < _input.cols; x++)
   {
      for (int y = 0; y < _input.rows; y++)
      {
         int valIn = _input.at<uchar>(y, x);
         auto valOut = sigmoidMap[valIn];
         assert(valOut>=0.0 && valOut<=255.0);
         _output.at<uchar>(y, x) = valOut;
      }
   }
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)