#pragma once

#include "abstract_filter.h"

namespace image_processor
{

class Crop final : public AbstractFilter
{
public:
    void Process(Image & image, FilterParams params) override;
};

} // namespace image_processor
