#include <iostream>
#include <filesystem>

#include <opencv2/core/utility.hpp>

import Context;


int main(int argc, const char* const argv[])
{
   const cv::String keys =
      "{help h usage ? |      | print this message   }"
      "{@image         |<none>| image for conversion }"
      "{result         |.     | path to file         }"
      "{fps            | -1.0 | fps for output video }"
      "{N count        |100   | count of objects     }"
      "{ts timestamp   |      | use time stamp       }"
      ;

   cv::CommandLineParser parser(argc, argv, keys);
   parser.about("Application name v1.0.0");
   if (parser.has("help"))
   {
      parser.printMessage();
      return 0;
   }

   if (!parser.check())
   {
      parser.printErrors();
      return 0;
   }

   auto N = parser.get<int>("N");
   auto fps = parser.get<double>("fps");
   auto image = parser.get<cv::String>("@image");
   auto result = parser.get<cv::String>("result");

   namespace fs = std::filesystem;
   if (!fs::exists(image))
   {
      std::cout << "file not found" << std::endl;
      return 0;
   }


   Context context;
   std::cout << image << std::endl;
   std::cout << result << std::endl;
}

