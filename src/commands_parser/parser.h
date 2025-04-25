#pragma once

#include <cstdint>
#include <vector>
#include "filters.h"

namespace image_processor
{

struct FilterParams
{
    FilterType Filter;
    int64_t IntParam1;
    int64_t IntParam2;
    double DoubleParam;
};

struct CmdParams
{
    const char * InputFilePath;
    const char * OutputFilePath;
    std::vector<FilterParams> FiltersParams;
};

class Parser
{
public:
    static CmdParams Parse(int argc, char * argv[]);
};

} // namespace image_processor
