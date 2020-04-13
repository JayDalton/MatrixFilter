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

   //bool m_sharpEnabled{false};
   //double m_sharpRadius{1.0};
   //double m_sharpSigma{0.0}; // bei 0 automatische Berechnung verwenden - calculateUnsharpMaskSigma
   //double m_sharpAmount{5.0};
   //double m_sharpThreshold{0.01};

   bool m_contrastEnhancement{false};
   signed m_contrastIntensity{3};

   bool m_structureEnhancement{false};
   signed m_structureDistance{21};
   signed m_structureSigma{36};

   static constexpr signed CLAHE_SIZE_MINIMUM{2};
   static constexpr signed CLAHE_SIZE_DEFAULT{2};
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
   void applyHisto(const cv::Mat& source, cv::Mat& target);
   void applyCLAHE(const cv::Mat& source, cv::Mat& target);
   void applySUACE(const cv::Mat& source, cv::Mat& target);
   void performSUACE(const cv::Mat& source, cv::Mat& target, int distance, double sigma);


   void applyUnsharpMask(const cv::Mat& _input, cv::Mat& _output);
   void applyContrastEnhancement(const cv::Mat& _input, cv::Mat& _output);
   void applyStructureEnhancement(const cv::Mat& _input, cv::Mat& _output);

private:
   FilterSettings m_setting;
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
