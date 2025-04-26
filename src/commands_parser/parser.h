#pragma once

#include <cstdint>
#include <vector>
#include "filters.h"

namespace image_processor
{

struct FilterParamsWithType
{
    FilterType Filter;
    int64_t int_param1;
    int64_t int_param2;
    double double_param;
};

struct CmdParams
{
    const char * InputFilePath;
    const char * OutputFilePath;
    std::vector<FilterParamsWithType> FiltersParams;
};

class Parser
{
public:
    static CmdParams Parse(int argc, char * argv[]);
};

} // namespace image_processor
