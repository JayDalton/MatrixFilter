cmake_minimum_required(VERSION 3.20)

project(common CXX)
message(STATUS ${PROJECT_NAME})

# find_package(fmt CONFIG REQUIRED)

add_library(${PROJECT_NAME})

# target_compile_options()
target_compile_definitions(${PROJECT_NAME} PUBLIC UNICODE)

# target_precompile_headers(${PROJECT_NAME} PRIVATE precompheader.h)

# target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
# target_link_libraries(main PRIVATE fmt::fmt-header-only)

target_sources(${PROJECT_NAME} PRIVATE
"config/Configuration.cpp"
"config/Configuration.h"
"config/Parameter.cpp"
"config/Parameter.h"
"config/Visitor.cpp"
"config/Visitor.h"
"config/parameter/BaseParameter.cpp"
"config/parameter/BaseParameter.h"
"config/parameter/BinaryParameter.cpp"
"config/parameter/BinaryParameter.h"
"config/parameter/BooleanParameter.cpp"
"config/parameter/BooleanParameter.h"
"config/parameter/DoubleParameter.cpp"
"config/parameter/DoubleParameter.h"
"config/parameter/IntegerParameter.cpp"
"config/parameter/IntegerParameter.h"
"config/parameter/ListParameter.cpp"
"config/parameter/ListParameter.h"
"config/parameter/StringParameter.cpp"
"config/parameter/StringParameter.h"
"utils/JsonReader.cpp"
"utils/JsonReader.h"
"utils/JsonStream.cpp"
"utils/JsonStream.h"
"utils/JsonWriter.cpp"
"utils/JsonWriter.h"
)