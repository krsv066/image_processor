#include <iostream>
#include "crop_filter.h"
#include "crystallize_filter.h"
#include "edge_detection_filter.h"
#include "gaussian_blur_filter.h"
#include "grayscale_filter.h"
#include "image.h"
#include "negative_filter.h"
#include "parser.h"
#include "sharpening_filter.h"

int main(int argc, char * argv[])
{
    image_processor::CmdParams cmd_params = image_processor::Parser::Parse(argc, argv);
    std::vector<image_processor::FilterParams> params = cmd_params.FiltersParams;

    try
    {
        image_processor::Image image(cmd_params.InputFilePath);

        for (const auto & param : params)
        {
            switch (param.Filter)
            {
                case image_processor::FilterType::Crop: {
                    image_processor::Crop filter;
                    filter.Process(image, param.IntParam1, param.IntParam2, 0);
                    break;
                }
                case image_processor::FilterType::Grayscale: {
                    image_processor::Grayscale filter;
                    filter.Process(image, 0, 0, 0);
                    break;
                }
                case image_processor::FilterType::Negative: {
                    image_processor::Negative filter;
                    filter.Process(image, 0, 0, 0);
                    break;
                }
                case image_processor::FilterType::Sharpening: {
                    image_processor::Sharpening filter;
                    filter.Process(image, 0, 0, 0);
                    break;
                }
                case image_processor::FilterType::EdgeDetection: {
                    image_processor::EdgeDetection filter;
                    filter.Process(image, 0, 0, param.DoubleParam);
                    break;
                }
                case image_processor::FilterType::GaussianBlur: {
                    image_processor::GaussianBlur filter;
                    filter.Process(image, 0, 0, param.DoubleParam);
                    break;
                }
                case image_processor::FilterType::Crystallize: {
                    image_processor::Crystallize filter;
                    filter.Process(image, param.IntParam1, 0, 0);
                    break;
                }
            }
        }

        image.Write(cmd_params.OutputFilePath);
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
