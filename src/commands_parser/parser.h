#pragma once

#include "../filters/filters.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <tuple>

struct FilterParams {
    FilterType Filter;
    int64_t IntParam1;
    int64_t IntParam2;
    double DoubleParam;

    bool operator==(const FilterParams &) const = default;
};

struct CmdParams {
    const char *InputFilePath;
    const char *OutputFilePath;
    std::vector<FilterParams> FiltersParams;

    bool operator==(const CmdParams &) const = default;
};

class Parser {
public:
    CmdParams Parse(int argc, char **argv);
};
