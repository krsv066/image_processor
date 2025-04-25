#pragma once

#include "abstract_filter.h"
#include "filters.h"

namespace image_processor
{

class FilterFactory
{
public:
    virtual std::unique_ptr<AbstractFilter> CreateFilter(FilterType type) = 0;
    virtual ~FilterFactory() = default;
};

} // namespace image_processor
