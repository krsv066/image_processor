#include <cstdint>

namespace image_processor
{

enum class FilterType : uint8_t
{
    Crop,
    Grayscale,
    Negative,
    Sharpening,
    EdgeDetection,
    GaussianBlur,
    Crystallize
};

} // namespace image_processor
