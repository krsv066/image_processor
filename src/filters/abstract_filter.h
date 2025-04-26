#pragma once

#include "image.h"

namespace image_processor
{

struct FilterParams
{
    int64_t int_param1;
    int64_t int_param2;
    double double_param;
};

class AbstractFilter
{
public:
    virtual void Process(Image & image, FilterParams params) = 0;
    virtual ~AbstractFilter() = default;
};

} // namespace image_processor
