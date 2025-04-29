#pragma once

#include "abstract_filter.h"

#include <cstdint>
#include <filesystem>
#include <vector>

namespace image_processor
{

struct FilterParamsWithType
{
    FilterType type;
    int64_t int_param1;
    int64_t int_param2;
    double double_param;
};

struct CmdArgs
{
    std::filesystem::path input_path;
    std::filesystem::path output_path;
    std::vector<FilterParamsWithType> filters_params;
};

class Parser
{
public:
    static CmdArgs Parse(int argc, char * argv[]);
};

} // namespace image_processor
