#include "parser.h"
#include <tuple>
#include <unordered_map>

namespace image_processor
{

CmdArgs Parser::Parse(int argc, char * argv[])
{
    if (argc < 3)
    {
        throw std::runtime_error("Not enough arguments");
    }

    const std::unordered_map<std::string, std::tuple<FilterType, int32_t, int32_t>> filter_info
        = {{"-crop", {FilterType::Crop, 2, 0}},
           {"-gs", {FilterType::Grayscale, 0, 0}},
           {"-neg", {FilterType::Negative, 0, 0}},
           {"-sharp", {FilterType::Sharpening, 0, 0}},
           {"-edge", {FilterType::EdgeDetection, 1, 1}},
           {"-blur", {FilterType::GaussianBlur, 1, 1}},
           {"-crystal", {FilterType::Crystallize, 1, 0}}};

    CmdArgs cmd_args;
    std::vector<FilterParamsWithType> filters_settings;

    cmd_args.input_path = std::filesystem::path(argv[1]);
    cmd_args.output_path = std::filesystem::path(argv[2]);

    int i = 3;
    while (i < argc)
    {
        std::string filter = argv[i];
        auto it = filter_info.find(filter);
        if (it == filter_info.end())
        {
            throw std::runtime_error("Invalid filter: " + filter);
        }

        auto [type, param_count, param_type] = it->second;
        if (i + param_count >= argc)
        {
            throw std::runtime_error("Not enough arguments for " + filter);
        }

        FilterParamsWithType params{.type = type};

        switch (param_count)
        {
            case 2:
                params.int_param1 = std::stoll(argv[i + 1]);
                params.int_param2 = std::stoll(argv[i + 2]);
                break;
            case 1:
                if (param_type == 0)
                {
                    params.int_param1 = std::stoll(argv[i + 1]);
                }
                else
                {
                    params.double_param = std::stod(argv[i + 1]);
                }
                break;
            case 0:
                break;
            default:
                throw std::runtime_error("Unexpected parameter count for filter: " + filter);
        }

        filters_settings.emplace_back(params);
        i += param_count + 1;
    }

    cmd_args.filters_params = filters_settings;

    return cmd_args;
}

} // namespace image_processor
