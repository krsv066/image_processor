#include "parser.h"

#include <iostream>

namespace image_processor
{

CmdParams Parser::Parse(int argc, char * argv[])
{
    CmdParams cmd_params;
    std::vector<FilterParamsWithType> filters_params;

    try
    {
        if (argc < 3)
        {
            throw std::runtime_error("Not enough arguments");
        }

        cmd_params.input_path = std::filesystem::path(argv[1]);
        cmd_params.output_path = std::filesystem::path(argv[2]);

        int i = 3;
        while (i < argc)
        {
            std::string filter = argv[i];

            if (filter == "-crop")
            {
                if (i + 2 >= argc)
                {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParamsWithType{
                    .type = FilterType::Crop,
                    .int_param1 = std::stoll(argv[i + 1]),
                    .int_param2 = std::stoll(argv[i + 2]),
                });
                i += 3;
            }

            else if (filter == "-gs")
            {
                filters_params.emplace_back(FilterParamsWithType{
                    .type = FilterType::Grayscale,
                });
                ++i;
            }

            else if (filter == "-neg")
            {
                filters_params.emplace_back(FilterParamsWithType{
                    .type = FilterType::Negative,
                });
                ++i;
            }

            else if (filter == "-sharp")
            {
                filters_params.emplace_back(FilterParamsWithType{
                    .type = FilterType::Sharpening,
                });
                ++i;
            }

            else if (filter == "-edge")
            {
                if (i + 1 >= argc)
                {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParamsWithType{
                    .type = FilterType::EdgeDetection,
                    .double_param = std::stof(argv[i + 1]),
                });
                i += 2;
            }

            else if (filter == "-blur")
            {
                if (i + 1 >= argc)
                {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParamsWithType{
                    .type = FilterType::GaussianBlur,
                    .double_param = std::stof(argv[i + 1]),
                });
                i += 2;
            }

            else if (filter == "-crystal")
            {
                if (i + 1 >= argc)
                {
                    throw std::runtime_error("Not enough arguments");
                }
                filters_params.emplace_back(FilterParamsWithType{
                    .type = FilterType::Crystallize,
                    .int_param1 = std::stoll(argv[i + 1]),
                });
                i += 2;
            }

            else
            {
                throw std::runtime_error("Invalid arguments");
            }
        }

        cmd_params.filters_params = filters_params;
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return cmd_params;
}

} // namespace image_processor
