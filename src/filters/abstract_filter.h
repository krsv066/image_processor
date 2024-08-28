#pragma once

#include "../image/image.h"

class AbstractFilter {
public:
    virtual void Process(Image &image, int64_t int_param1, int64_t int_param2, double double_param) = 0;

    virtual ~AbstractFilter() = default;
};
