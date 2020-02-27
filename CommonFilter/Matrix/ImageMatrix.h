#pragma once

#include <opencv2/core.hpp>

struct ImageMatrix
{
   explicit ImageMatrix(cv::Mat matrix);
   ~ImageMatrix();

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

using ImageMatrixUPtr = std::unique_ptr<ImageMatrix>;
using ImagematrixSPtr = std::shared_ptr<ImageMatrix>;

// Codepage: UTF-8 (ÜüÖöÄäẞß)
