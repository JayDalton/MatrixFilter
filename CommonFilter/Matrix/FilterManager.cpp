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
   if (m_setting.m_histoEqualize)
   {
      applyHisto(source, target);
   }

   if (m_setting.m_claheEnabled)
   {
      applyCLAHE(source, target);
   }

   if (m_setting.m_suaceEnabled)
   {
      applySUACE(source, target);
   }
}

void FilterManager::applyHisto(const cv::Mat& source, cv::Mat& target)
{
   spdlog::debug("applying histogram equalize filter...");
   cv::equalizeHist(source, target);
}

void FilterManager::applyCLAHE(const cv::Mat& source, cv::Mat& target)
{
   spdlog::debug("applying CLAHE filter...");
   auto clahe {cv::createCLAHE()};
   auto clip {m_setting.m_claheClip};
   auto size {m_setting.m_claheSize};
   auto area {cv::Size(size, size)};

   clahe->setClipLimit(clip);
   clahe->setTilesGridSize(area);
   clahe->apply(source, target); // inplace
}

void FilterManager::applySUACE(const cv::Mat& source, cv::Mat& target)
{
   spdlog::debug("applying structure enhancement filter...");
   auto distance {m_setting.m_suaceDistance};
   auto sigma {m_setting.m_suaceSigma};

   cv::Mat output;
   performSUACE(source, output, distance, (sigma + 1) / 8.0);
   target = output;
}

//https://www.codeproject.com/Articles/1203383/A-Fast-Simple-and-Powerful-Contrast-Enhancement-Al
void FilterManager::performSUACE(const cv::Mat& source, cv::Mat& target, int distance, double sigma)
{
   assert(source.type() == CV_8UC1);
   if (!(distance > 0 && sigma > 0))
   {
      spdlog::warn("distance and sigma must be greater 0");
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

// Codepage: UTF-8 (ÜüÖöÄäẞß)