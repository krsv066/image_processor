cmake_minimum_required(VERSION 3.22.1)

project(image_processor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -O3)

include_directories(
        src/application
        src/commands_parser
        src/filters
        src/filters_utils
        src/image
)

add_executable(
        image_processor
        src/main.cpp
        src/application/application.cpp
        src/commands_parser/parser.cpp
        src/image/image.cpp
        src/filters/scale_filter.cpp
        src/filters/negative_filter.cpp
        src/filters/grayscale_filter.cpp
        src/filters/sharpening_filter.cpp
        src/filters/edge_detection_filter.cpp
        src/filters/crop_filter.cpp
        src/filters/gaussian_blur_filter.cpp
        src/filters/crystallize_filter.cpp
        src/filters_utils/concrete_filter_factory.cpp
)
