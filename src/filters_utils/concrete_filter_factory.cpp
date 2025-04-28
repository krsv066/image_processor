#include "concrete_filter_factory.h"
#include "crop_filter.h"
#include "crystallize_filter.h"
#include "edge_detection_filter.h"
#include "gaussian_blur_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"

namespace image_processor
{

std::unique_ptr<AbstractFilter> ConcreteFilterFactory::CreateFilter(FilterType type)
{
    switch (type)
    {
        case FilterType::Crop:
            return std::make_unique<Crop>();
        case FilterType::Grayscale:
            return std::make_unique<Grayscale>();
        case FilterType::Negative:
            return std::make_unique<Negative>();
        case FilterType::Sharpening:
            return std::make_unique<Sharpening>();
        case FilterType::EdgeDetection:
            return std::make_unique<EdgeDetection>();
        case FilterType::GaussianBlur:
            return std::make_unique<GaussianBlur>();
        case FilterType::Crystallize:
            return std::make_unique<Crystallize>();
        default:
            return nullptr;
    }
}

} // namespace image_processor
