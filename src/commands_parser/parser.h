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

    bool operator==(const FilterParams &) const = default;
};

struct CmdParams
{
    const char * InputFilePath;
    const char * OutputFilePath;
    std::vector<FilterParams> FiltersParams;

    bool operator==(const CmdParams &) const = default;
};

class Parser
{
public:
    CmdParams Parse(int argc, char ** argv);
};

} // namespace image_processor
