#pragma once

#include "filter_factory.h"

namespace image_processor
{

class ConcreteFilterFactory final : public FilterFactory
{
public:
    std::unique_ptr<AbstractFilter> CreateFilter(FilterType type) override;
};

} // namespace image_processor
