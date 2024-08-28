cmake_minimum_required(VERSION 3.22.1)

project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        image_processor
        image_processor.cpp
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
)
