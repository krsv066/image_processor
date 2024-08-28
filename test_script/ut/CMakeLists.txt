cmake_minimum_required(VERSION 3.22.1)

project(image_processor_tests)

set(CMAKE_CXX_STANDARD 20)

add_library(
        contrib_catch_main
        ../../../../contrib/catch/catch_main.cpp
)

target_include_directories(
        contrib_catch_main
        PUBLIC ../../../../contrib/catch
)

add_executable(
        image_processor_tests
        test.cpp
        ../../src/commands_parser/parser.cpp
        ../../src/image/image.cpp
        ../../src/filters/scale_filter.cpp
        ../../src/filters/negative_filter.cpp
        ../../src/filters/grayscale_filter.cpp
        ../../src/filters/sharpening_filter.cpp
        ../../src/filters/edge_detection_filter.cpp
        ../../src/filters/crop_filter.cpp
        ../../src/filters/gaussian_blur_filter.cpp
        ../../src/filters/crystallize_filter.cpp
)

target_link_libraries(
        image_processor_tests
        contrib_catch_main
)
