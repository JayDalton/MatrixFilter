#pragma once

#include <opencv2/core.hpp>

struct FilterSettings
{
   bool m_histoEqualize{ false };

   bool m_claheEnabled{ false };
   signed m_claheSize{9};
   signed m_claheBins{128};
   double m_claheClip{1.0};

   bool m_suaceEnabled{ false };
   signed m_suaceDistance{21};
   signed m_suaceSigma{36};
};

struct FilterManager
{
   void setFilterSettings(FilterSettings setting);
   void applyFilter(const cv::Mat& source, cv::Mat& target);

private:
   void applyHisto(const cv::Mat& source, cv::Mat& target);
   void applyCLAHE(const cv::Mat& source, cv::Mat& target);
   void applySUACE(const cv::Mat& source, cv::Mat& target);
   void performSUACE(const cv::Mat& source, cv::Mat& target, int distance, double sigma);

private:
   FilterSettings m_setting;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
