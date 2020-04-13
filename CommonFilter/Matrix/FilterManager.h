#pragma once

#include <opencv2/core.hpp>

struct FilterSettings
{
   bool m_claheEnabled{ false };
   signed m_claheSize{9};
   signed m_claheBins{128};
   double m_claheClip{1.0};

   bool m_histoEqualize{ false };

   bool m_suaceEnabled{ false };
   signed m_suaceDistance{21};
   signed m_suaceSigma{36};

   bool m_contrastEnhancement{false};
   double m_contrastIntensity{3};
   signed m_brightnessIntensity{3};

   bool m_structureEnhancement{false};
   signed m_structureDistance{21};
   signed m_structureSigma{36};

   static constexpr signed CLAHE_SIZE_MINIMUM{2};
   static constexpr signed CLAHE_SIZE_DEFAULT{4};
   static constexpr signed CLAHE_SIZE_MAXIMUM{16};
   static constexpr double CLAHE_CLIP_MINIMUM{0.1};
   static constexpr double CLAHE_CLIP_DEFAULT{2.5};
   static constexpr double CLAHE_CLIP_MAXIMUM{10.0};
};

struct FilterManager
{
   void setFilterSettings(FilterSettings setting);
   void applyFilter(const cv::Mat& source, cv::Mat& target);

private:
   void applyHistogramEqualization(const cv::Mat& source, cv::Mat& target);
   void applyCLAHE(const cv::Mat& source, cv::Mat& target);
   void applyContrastEnhancement(const cv::Mat& source, cv::Mat& target);
   void performSUACE(const cv::Mat& source, cv::Mat& target, int distance, double sigma);
   void applyStructureEnhancement(const cv::Mat& source, cv::Mat& target);
   void performSigmoidalContrast(const cv::Mat& source, cv::Mat& target, double contrast);

   void applyUnsharpMask(const cv::Mat& _input, cv::Mat& _output);

private:
   FilterSettings m_setting;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
